using System.Text.RegularExpressions;
using System.Text;
using System.Diagnostics;
using iText.Kernel.Pdf;
using iText.Kernel.Pdf.Canvas.Parser;
using iText.Kernel.Pdf.Canvas.Parser.Listener;
using System.Globalization;
using System.Collections.Generic;
using OfficeOpenXml;
using System.Windows.Input;
using iText.StyledXmlParser.Jsoup.Safety;

namespace pdfToText
{
    public partial class MainPage : ContentPage
    {
        private PdfOpener pdfOpener = new PdfOpener();
        private ExcelOpener excelOpener = new ExcelOpener();
        string? pdfSource;
        string? excelSource;
        bool backup = true;
        public MainPage()
        {
            InitializeComponent();
            ExcelPackage.LicenseContext = LicenseContext.NonCommercial;
        }
        private async void LoadPdfFile(object sender, EventArgs e)
        {
            var pdf = await FilePicker.Default.PickAsync(new PickOptions
            {
                PickerTitle = "Wybierz plik .PDF",
                FileTypes = FilePickerFileType.Pdf
            });
            if (pdf == null)
            {
                filePathLabel.Text = "Nie wczytano pliku!";
                return;
            }

            // Loop through and process each file
            var watch = System.Diagnostics.Stopwatch.StartNew();
            pdfSource = pdf.FullPath.ToString();
            filePathLabel.Text = pdfOpener.LoadFile(pdfSource);
            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;
            Debug.WriteLine(elapsedMs);
            btnWczytajPDF.IsEnabled = false;
            btnWczytajExcel.IsEnabled = true;
        }
        private async void LoadExcelFile(object sender, EventArgs e)
        {
            var excel = await FilePicker.Default.PickAsync(new PickOptions
            {
                PickerTitle = "Wybierz plik .xlsx (excel)",
                FileTypes = new FilePickerFileType(new Dictionary<DevicePlatform, IEnumerable<string>>(){
                    { 
                        DevicePlatform.WinUI, new[] { ".xlsx" } 
                    },
                })
            });
            if (excel == null)
            {
                filePathLabel.Text = "Nie wczytano pliku!";
                return;
            }
            excelSource = excel.FullPath.ToString();
            filePathLabel.Text = excelOpener.UpdateExcelFile(excelSource, pdfOpener.GetDATA());
            btnWczytajExcel.IsEnabled = false;
            btnStart.IsEnabled = true;
            
        }
        private void PutExcelData(object sender, EventArgs e)
        {
            if(excelSource == null)
                return;
            if (backup)
            {
                string? pathDest = Path.GetDirectoryName(excelSource);
                if (pathDest == null)
                {
                    filePathLabel.Text = "Problem ze stworzeniem pliku zapasowego, wczytywanie danych przerwane!";
                    return;
                }

                if (File.Exists(pathDest + "/KopiaZapasowa.xlsx"))
                {
                    File.Delete(pathDest + "/KopiaZapasowa.xlsx");
                }
                File.Copy(excelSource, pathDest + "/KopiaZapasowa.xlsx");
            }

            filePathLabel.Text = excelOpener.PutData(excelSource, pdfOpener.GetDATA());
            pdfOpener.CleanUp();
            btnWczytajPDF.IsEnabled = true;
            btnStart.IsEnabled = false;
        }
        private void ChangeBackup(object sender, TappedEventArgs e)
        {
            iconKopiaZapasowa.Text = (backup) ? "❌" : "✅";
            backup = !backup;
        }
    }
}