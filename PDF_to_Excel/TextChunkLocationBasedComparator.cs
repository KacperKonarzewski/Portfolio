using System.Collections.Generic;
using iText.Kernel.Pdf.Canvas.Parser.Listener;

namespace pdfToText {
    internal class TextChunkLocationBasedComparator : IComparer<TextChunk> {
        private IComparer<ITextChunkLocation> locationComparator;

        public TextChunkLocationBasedComparator(IComparer<ITextChunkLocation> locationComparator) {
            this.locationComparator = locationComparator;
        }

        public virtual int Compare(TextChunk? o1, TextChunk? o2) {
            if (o1 == null || o2 == null) return 0;
            return locationComparator.Compare(o1.GetLocation(), o2.GetLocation());
        }
    }

}
