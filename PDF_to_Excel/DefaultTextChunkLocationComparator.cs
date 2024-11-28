using System.Collections.Generic;
using iText.Commons.Utils;
using iText.Kernel.Pdf.Canvas.Parser.Listener;

namespace pdfToText {
    internal class DefaultTextChunkLocationComparator : IComparer<ITextChunkLocation> {
        private bool leftToRight = true;
        public DefaultTextChunkLocationComparator()
            : this(true) {
        }
        public DefaultTextChunkLocationComparator(bool leftToRight) {
            this.leftToRight = leftToRight;
        }
        public int Compare(ITextChunkLocation? first, ITextChunkLocation? second) {
            if (first == second || first == null || second == null) {
                return 0;
            }
            int result;
            result = JavaUtil.IntegerCompare(first.OrientationMagnitude(), second.OrientationMagnitude());
            if (result != 0) {
                return result;
            }
            int distPerpendicularDiff = first.DistPerpendicular() - second.DistPerpendicular();
            if (distPerpendicularDiff != 0) {
                return distPerpendicularDiff;
            }
            return leftToRight ? JavaUtil.FloatCompare(first.DistParallelStart(), second.DistParallelStart()) : -JavaUtil.FloatCompare
                (first.DistParallelEnd(), second.DistParallelEnd());
        }
    }
}
