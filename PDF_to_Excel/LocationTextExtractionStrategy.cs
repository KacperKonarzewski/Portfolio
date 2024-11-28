
using System;
using System.Collections.Generic;
using System.Text;
using iText.Commons.Utils;
using iText.Kernel.Geom;
using iText.Kernel.Pdf.Canvas;
using iText.Kernel.Pdf.Canvas.Parser;
using iText.Kernel.Pdf.Canvas.Parser.Data;
using iText.Kernel.Pdf.Canvas.Parser.Listener;

namespace pdfToText {
    public class SeparatorStrategy : LocationTextExtractionStrategy
    {

        private readonly IList<TextChunk> locationalResult = new List<TextChunk>();

        private readonly ITextChunkLocationStrategy tclStrat;

        private bool useActualText = false;

        private bool rightToLeftRunDirection = false;

        private TextRenderInfo? lastTextRenderInfo;

        public SeparatorStrategy()
            : this(new ITextChunkLocationStrategyImpl()) {
        }
        public SeparatorStrategy(ITextChunkLocationStrategy strat) {
            tclStrat = strat;
        }

        public override void EventOccurred(IEventData data, EventType type) {
            if (type.Equals(EventType.RENDER_TEXT)) {
                TextRenderInfo renderInfo = (TextRenderInfo)data;
                LineSegment segment = renderInfo.GetBaseline();
                if (renderInfo.GetRise() != 0) {
                    Matrix riseOffsetTransform = new Matrix(0, -renderInfo.GetRise());
                    segment = segment.TransformBy(riseOffsetTransform);
                }
                if (useActualText) {
                    CanvasTag? lastTagWithActualText = lastTextRenderInfo != null ? FindLastTagWithActualText(lastTextRenderInfo.GetCanvasTagHierarchy()) : null;
                    if (lastTagWithActualText != null && lastTagWithActualText == FindLastTagWithActualText(renderInfo.GetCanvasTagHierarchy
                        ())) {
                        TextChunk lastTextChunk = locationalResult[locationalResult.Count - 1];
                        Vector mergedStart = new Vector(Math.Min(lastTextChunk.GetLocation().GetStartLocation().Get(0), segment.GetStartPoint
                            ().Get(0)), Math.Min(lastTextChunk.GetLocation().GetStartLocation().Get(1), segment.GetStartPoint().Get
                            (1)), Math.Min(lastTextChunk.GetLocation().GetStartLocation().Get(2), segment.GetStartPoint().Get(2)));
                        Vector mergedEnd = new Vector(Math.Max(lastTextChunk.GetLocation().GetEndLocation().Get(0), segment.GetEndPoint
                            ().Get(0)), Math.Max(lastTextChunk.GetLocation().GetEndLocation().Get(1), segment.GetEndPoint().Get(1)
                            ), Math.Max(lastTextChunk.GetLocation().GetEndLocation().Get(2), segment.GetEndPoint().Get(2)));
                        TextChunk merged = new TextChunk(lastTextChunk.GetText(), tclStrat.CreateLocation(renderInfo, new LineSegment
                            (mergedStart, mergedEnd)));
                        locationalResult[locationalResult.Count - 1] = merged;
                    }
                    else {
                        String actualText = renderInfo.GetActualText();
                        TextChunk tc = new TextChunk(actualText != null ? actualText : renderInfo.GetText(), tclStrat.CreateLocation
                            (renderInfo, segment));
                        locationalResult.Add(tc);
                    }
                }
                else {
                    TextChunk tc = new TextChunk(renderInfo.GetText(), tclStrat.CreateLocation(renderInfo, segment));
                    locationalResult.Add(tc);
                }
                lastTextRenderInfo = renderInfo;
            }
        }
        public override String GetResultantText() {
            IList<TextChunk> textChunks = new List<TextChunk>(locationalResult);
            SortWithMarks(textChunks);
            StringBuilder sb = new StringBuilder();
            TextChunk? lastChunk = null;
            foreach (TextChunk chunk in textChunks) {
                if (lastChunk == null) {
                    sb.Append(chunk.GetText());
                }
                else {
                    if (SameLine(chunk, lastChunk)) {
                        if (IsChunkAtWordBoundary(chunk, lastChunk) && !StartsWithSpace(chunk.GetText()) && !EndsWithSpace(lastChunk.GetText())) {
                            sb.Append(" || ");
                        }
                        sb.Append(chunk.GetText());
                    }
                    else {
                        sb.Append('\n');
                        sb.Append(chunk.GetText());
                    }
                }
                lastChunk = chunk;
            }
            return sb.ToString();
        }

        private bool StartsWithSpace(String str) {
            return str.Length != 0 && str[0] == ' ';
        }

        private bool EndsWithSpace(String str) {
            return str.Length != 0 && str[str.Length - 1] == ' ';
        }

        private CanvasTag? FindLastTagWithActualText(IList<CanvasTag> canvasTagHierarchy) {
            CanvasTag? lastActualText = null;
            foreach (CanvasTag tag in canvasTagHierarchy) {
                if (tag.GetActualText() != null) {
                    lastActualText = tag;
                    break;
                }
            }
            return lastActualText;
        }

        private void SortWithMarks(IList<TextChunk> textChunks)
        {
            IDictionary<TextChunk, TextChunkMarks> marks = new Dictionary<TextChunk, TextChunkMarks>();
            IList<TextChunk> toSort = new List<TextChunk>();

            for (int markInd = 0; markInd < textChunks.Count; markInd++)
            {
                ITextChunkLocation location = textChunks[markInd].GetLocation();
                if (location.GetStartLocation().Equals(location.GetEndLocation()))
                {
                    bool foundBaseToAttachTo = false;
                    for (int baseInd = 0; baseInd < textChunks.Count; baseInd++)
                    {
                        if (markInd != baseInd)
                        {
                            ITextChunkLocation baseLocation = textChunks[baseInd].GetLocation();
                            if (!baseLocation.GetStartLocation().Equals(baseLocation.GetEndLocation()) && TextChunkLocationDefaultImp.ContainsMark(baseLocation, location))
                            {
                                if (!marks.ContainsKey(textChunks[baseInd]))
                                {
                                    marks[textChunks[baseInd]] = new TextChunkMarks();
                                }
                                TextChunkMarks currentMarks = marks[textChunks[baseInd]];

                                if (markInd < baseInd)
                                {
                                    currentMarks.preceding.Add(textChunks[markInd]);
                                }
                                else
                                {
                                    currentMarks.succeeding.Add(textChunks[markInd]);
                                }
                                foundBaseToAttachTo = true;
                                break;
                            }
                        }
                    }
                    if (!foundBaseToAttachTo)
                    {
                        toSort.Add(textChunks[markInd]);
                    }
                }
                else
                {
                    toSort.Add(textChunks[markInd]);
                }
            }

            JavaCollectionsUtil.Sort(toSort, new TextChunkLocationBasedComparator(new DefaultTextChunkLocationComparator(!rightToLeftRunDirection)));

            textChunks.Clear();
            foreach (TextChunk current in toSort)
            {
                TextChunkMarks? currentMarks = marks.ContainsKey(current) ? marks[current] : null;
                if (currentMarks != null)
                {
                    if (!rightToLeftRunDirection)
                    {
                        for (int j = 0; j < currentMarks.preceding.Count; j++)
                        {
                            textChunks.Add(currentMarks.preceding[j]);
                        }
                    }
                    else
                    {
                        for (int j = currentMarks.succeeding.Count - 1; j >= 0; j--)
                        {
                            textChunks.Add(currentMarks.succeeding[j]);
                        }
                    }
                }
                textChunks.Add(current);
                if (currentMarks != null)
                {
                    if (!rightToLeftRunDirection)
                    {
                        for (int j = 0; j < currentMarks.succeeding.Count; j++)
                        {
                            textChunks.Add(currentMarks.succeeding[j]);
                        }
                    }
                    else
                    {
                        for (int j = currentMarks.preceding.Count - 1; j >= 0; j--)
                        {
                            textChunks.Add(currentMarks.preceding[j]);
                        }
                    }
                }
            }
        }
        internal bool SameLine(TextChunk chunk, TextChunk lastChunk)
        {
            return chunk.GetLocation().SameLine(lastChunk.GetLocation());
        }

        private class TextChunkMarks {

            internal IList<TextChunk> preceding = new List<TextChunk>();
            internal IList<TextChunk> succeeding = new List<TextChunk>();
        }

        private sealed class ITextChunkLocationStrategyImpl : ITextChunkLocationStrategy {
            public ITextChunkLocation CreateLocation(TextRenderInfo renderInfo, LineSegment baseline) {
                return new TextChunkLocationDefaultImp(baseline.GetStartPoint(), baseline.GetEndPoint(), renderInfo.GetSingleSpaceWidth());
            }
        }
    }
}
