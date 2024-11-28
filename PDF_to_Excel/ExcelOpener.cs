using OfficeOpenXml;
using OfficeOpenXml.Style;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Net;
using System.Runtime.Intrinsics.Arm;
using System.Security.AccessControl;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace pdfToText
{
    class ExcelOpener
    {
        public ExcelOpener()
        {

        }
        public void GrantFileAccess(string filePath)
        {
#if WINDOWS
            FileInfo fileInfo = new FileInfo(filePath);

            FileSecurity fileSecurity = fileInfo.GetAccessControl();

            string userName = Environment.UserName;

            fileSecurity.AddAccessRule(new FileSystemAccessRule(
                userName,
                FileSystemRights.FullControl,
                AccessControlType.Allow));

            fileInfo.SetAccessControl(fileSecurity);
#endif
        }
        private void PutMarket(ExcelWorkbook workbook, string type, string year, Dictionary<string, List<string>> DATA)
        {
            CultureInfo polishCulture = new CultureInfo("pl-PL");
            var worksheet = workbook.Worksheets[$"{type}(20{year}-)Ceny, Wol"];
            int monthNumber = DateTime.ParseExact(DATA["Date"][0], "MMMM", polishCulture).Month;
            string str = (worksheet.Dimension.End.Row - 12 + monthNumber).ToString();

            DATA[type][1] = DATA[type][1].Replace(" ", "");
            worksheet.Cells["C" + str].Style.Numberformat.Format = "0";
            worksheet.Cells["C" + str].Value = double.Parse(DATA[type][1]) / 1000;
            worksheet.Cells["B" + str].Style.Numberformat.Format = "#,##0.00";
            worksheet.Cells["B" + str].Value = float.Parse(DATA[type][0], polishCulture);
            if (year == "09")
            {
                year = "12";
            }
            worksheet = workbook.Worksheets[$"{type}(20{year}-) Bilans ŚP"];
            str = (worksheet.Dimension.End.Row - 12 + monthNumber).ToString();
            string charset = "WUBZ";
            for (char c = 'B'; c < 'F'; c++)
            {
                DATA[type + "_" + charset[c - 'B']][0] = DATA[type + "_" + charset[c - 'B']][0].Replace(" ", "");
                worksheet.Cells[c + str].Value = double.Parse(DATA[type + "_" + charset[c - 'B']][0]) / 1000000;
            }
            var nbr1 = worksheet.Cells["B" + str].Value;
            var nbr2 = worksheet.Cells["F" + (int.Parse(str) - 1).ToString()].Value;
            var nbr3 = worksheet.Cells["C" + str].Value;
            int count = 2;
            while (nbr2 == null && int.Parse(str) > count && int.Parse(str) - count >= 6)
            {
                nbr2 = worksheet.Cells["F" + (int.Parse(str) - count).ToString()].Value;
                count++;
            }
            if (nbr2 == null)
            {
                nbr2 = 0;
            }
            if (nbr1 == null || nbr3 == null)
            {
                return;
            }
            string? s1 = nbr1.ToString();
            string? s2 = nbr2.ToString();
            string? s3 = nbr3.ToString();
            if (s1 == null || s2 == null || s3 == null)
            {
                return;
            }
            worksheet.Cells["F" + str].Value = double.Parse(s1) + double.Parse(s2) - double.Parse(s3);
            worksheet.Cells["G" + str].Style.Numberformat.Format = "#,##0.00";
            worksheet.Cells["G" + str].Value = float.Parse(DATA[type][0], polishCulture);
        }

        public string PutData(string filePath, Dictionary<string, List<string>> DATA)
        {
            if (string.IsNullOrEmpty(filePath))
            {
                return "Nie wczytano pliku.";
            }
            GrantFileAccess(filePath);
            try
            {
                using (var package = new ExcelPackage(new FileInfo(filePath)))
                {
                    string year = DATA["Date"][1].Substring(DATA["Date"][1].Length - 2);
                    string month = DATA["Date"][0];

                    var worksheet = package.Workbook.Worksheets[$"SPOT(RDN{year})"];
                    CultureInfo polishCulture = new CultureInfo("pl-PL");

                    for (char c = 'C'; c < 'O'; c++)
                    {
                        if (worksheet.Cells[c + "3"].Text != month)
                        {
                            continue;
                        }
                        worksheet.Cells[c + "4"].Value = float.Parse(DATA["BASE"][0], polishCulture);
                        worksheet.Cells[c + "5"].Value = float.Parse(DATA["BASE"][1], polishCulture);
                        DATA["Volume"][0] = DATA["Volume"][0].Replace(" ", "");
                        DATA["Volume"][0] = DATA["Volume"][0].Insert(DATA["Volume"][0].Length - 3, ",");
                        worksheet.Cells[c + "6"].Value = float.Parse(DATA["Volume"][0], polishCulture);
                        worksheet.Cells[c + "7"].Value = float.Parse(DATA["PEAK"][0], polishCulture);
                        worksheet.Cells[c + "8"].Value = float.Parse(DATA["PEAK"][1], polishCulture);
                        DATA["Volume"][1] = DATA["Volume"][1].Replace(" ", "");
                        DATA["Volume"][1] = DATA["Volume"][1].Insert(DATA["Volume"][1].Length - 3, ",");
                        worksheet.Cells[c + "9"].Value = float.Parse(DATA["Volume"][1], polishCulture);
                        worksheet.Cells[c + "10"].Value = float.Parse(DATA["OFFPEAK"][0], polishCulture);
                        worksheet.Cells[c + "11"].Value = float.Parse(DATA["OFFPEAK"][1], polishCulture);
                        DATA["Volume"][2] = DATA["Volume"][2].Replace(" ", "");
                        DATA["Volume"][2] = DATA["Volume"][2].Insert(DATA["Volume"][2].Length - 3, ",");
                        worksheet.Cells[c + "12"].Value = float.Parse(DATA["Volume"][2], polishCulture);
                        break;
                    }
                    worksheet = package.Workbook.Worksheets[$"SPOT(RDB{year})"];

                    for (char c = 'D'; c < 'P'; c++)
                    {
                        if (worksheet.Cells[c + "3"].Text != month)
                        {
                            continue;
                        }
                        for (int i = 0; i / 24 != 3; i++)
                        {
                            worksheet.Cells[c + (i + 4).ToString()].Value = float.Parse(DATA["Hour" + ((i + 1) % 24 == 0 ? 24 : (i + 1) % 24).ToString()][i / 24]);
                        }
                        break;
                    }

                    foreach (var key in DATA.Keys.Where(k => k.StartsWith("BASE_Y")).ToList())
                    {
                        worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];
                        for (char c = 'C'; c < 'O'; c++)
                        {
                            if (worksheet.Cells[c + "3"].Text != month)
                            {
                                continue;
                            }
                            worksheet.Cells[c + "4"].Value = float.Parse(DATA[key][0], polishCulture);
                            worksheet.Cells[c + "5"].Value = float.Parse(DATA[key][1], polishCulture);
                            worksheet.Cells[c + "6"].Value = float.Parse(DATA[key][2], polishCulture);
                            worksheet.Cells[c + "7"].Value = float.Parse(DATA[key][3], polishCulture);
                            DATA[key][4] = DATA[key][4].Replace(" ", "");
                            DATA[key][4] = DATA[key][4].Insert((DATA[key][4].Length < 3)? 0 : DATA[key][4].Length - 3, ",");
                            worksheet.Cells[c + "8"].Value = float.Parse(DATA[key][4], polishCulture);
                            break;
                        }
                    }
                    
                    foreach (var key in DATA.Keys.Where(k => k.StartsWith("PEAK5_Y")).ToList())
                    {
                        worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];
                        for (char c = 'B'; c < 'N'; c++)
                        {
                            if (worksheet.Cells[c + "3"].Text != month)
                            {
                                continue;
                            }
                            worksheet.Cells[c + "4"].Value = float.Parse(DATA[key][0], polishCulture);
                            worksheet.Cells[c + "5"].Value = float.Parse(DATA[key][1], polishCulture);
                            worksheet.Cells[c + "6"].Value = float.Parse(DATA[key][2], polishCulture);
                            worksheet.Cells[c + "7"].Value = float.Parse(DATA[key][3], polishCulture);
                            DATA[key][4] = DATA[key][4].Replace(" ", "");
                            DATA[key][4] = DATA[key][4].Insert((DATA[key][4].Length < 3) ? 0 : DATA[key][4].Length - 3, ",");
                            worksheet.Cells[c + "8"].Value = float.Parse(DATA[key][4], polishCulture);
                            break;
                        }
                    }

                    PutMarket(package.Workbook, "PMOZE_A", "09", DATA);
                    if (string.Compare(year, "24", StringComparison.Ordinal) >= 0)
                    {
                        PutMarket(package.Workbook, "PMOZE_BIO", "24", DATA);
                        PutMarket(package.Workbook, "PMEF_F", "24", DATA);
                    }
                    package.Save();
                    return "Pomyślnie wpisano dane";
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("An error occurred while processing the Excel file: " + ex.Message);
                return "ERROR";
            }
        }
        private int GetColumnNumber(string columnLetter)
        {
            int columnNumber = 0;
            for (int i = 0; i < columnLetter.Length; i++)
            {
                columnNumber *= 26;
                columnNumber += (columnLetter[i] - 'A' + 1);
            }
            return columnNumber;
        }
        public void InsertSingleCellInColumn(ExcelWorksheet worksheet, char startColumn, char endColumn, int startRow)
        {
            int lastRow = worksheet.Dimension.End.Row;

            for (int row = lastRow; row >= startRow; row--)
            {
                for (char col = startColumn; col <= endColumn; col++)
                {
                    var cellAddress = $"{col}{row}";
                    var destinationCellAddress = $"{col}{row + 1}";

                    var sourceCell = worksheet.Cells[cellAddress];
                    var destinationCell = worksheet.Cells[destinationCellAddress];

                    destinationCell.Value = sourceCell.Value;

                    if (!string.IsNullOrEmpty(sourceCell.Formula))
                    {
                        destinationCell.Formula = sourceCell.Formula;
                    }
                    if (sourceCell.Hyperlink != null)
                    {
                        destinationCell.Hyperlink = sourceCell.Hyperlink;
                    }
                    destinationCell.StyleID = sourceCell.StyleID;

                    sourceCell.Clear();
                }
            }
        }
        private void SetHyperLinkStyle(ExcelRange cell)
        {
            cell.Style.Font.UnderLine = true;
            cell.Style.Font.Bold = true;
            cell.Style.Fill.PatternType = ExcelFillStyle.Solid;
            cell.Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml("#D9D9D9"));
            cell.Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
            cell.Style.VerticalAlignment = ExcelVerticalAlignment.Center;
            cell.Style.Border.Left.Style = ExcelBorderStyle.Thin;
            cell.Style.Border.Right.Style = ExcelBorderStyle.Thin;
            cell.Style.Border.Left.Color.SetColor(System.Drawing.Color.Black);
            cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);
        }
        private void DuplicateMarket(ExcelPackage package, Dictionary<string, List<string>> DATA, string type, string key, string charset)
        {
            string year = DATA["Date"][1].Substring(DATA["Date"][1].Length - 2);
            if (!int.TryParse(year, out int parsedYear))
            {
                throw new SystemException($"Error parsing {type} year to number");
            }
            var worksheet = package.Workbook.Worksheets[$"Spis Treści"];
            int i = worksheet.Dimension.End.Row;
            int mergedRowCount;
            int lastRow = 0;
            string mergedText = "";
            string firstText = "";
            bool copied = false;
            ExcelRange ExistingCell = worksheet.Cells["Q10"];
            while (i >= 10)
            {
                var cell = worksheet.Cells[$"{charset[1]}{i}"];
                if (cell.Merge)
                {
                    var mergedRangeAddress = worksheet.MergedCells[cell.Start.Row, cell.Start.Column];
                    var mergedRange = worksheet.Cells[mergedRangeAddress];
                    
                    mergedText = worksheet.Cells[$"{charset[1]}{mergedRange.Start.Row}"].Text;
                    mergedRowCount = mergedRange.End.Row - mergedRange.Start.Row + 1;
                    if (lastRow == 0)
                        lastRow = mergedRange.End.Row;
                }
                else if (cell.Text == "")
                {
                    i--;
                    continue;
                }
                else
                {
                    mergedRowCount = 1;
                    mergedText = cell.Text;
                }
                if (firstText == "")
                {
                    firstText = mergedText;
                    lastRow = cell.End.Row;
                    for (int j = lastRow; j >= 11; j--)
                    {
                        var tmp = worksheet.Cells[$"{charset[1]}{j}"];
                        if (key == tmp.Text)
                        {
                            var mergedRangeAddress = worksheet.MergedCells[tmp.Start.Row, tmp.Start.Column];
                            var mergedRange = worksheet.Cells[mergedRangeAddress];

                            ExistingCell = worksheet.Cells[$"{charset[1]}{mergedRange.End.Row}"];
                            break;
                        }
                    }
                }
                for (int j = parsedYear; j >= parsedYear - mergedRowCount; j--)
                {
                    if (package.Workbook.Worksheets[$"{mergedText}(20{j})"] == null)
                        continue;
                    package.Workbook.Worksheets.Copy($"{mergedText}(20{j})", $"{type}{key.Substring(key.Length - 2)}(20{year})");
                    copied = true;
                    break;
                }
                if (copied)
                {
                    if (string.Compare(firstText.Substring(firstText.Length - 2), key.Substring(key.Length - 2), StringComparison.Ordinal) < 0)
                    {
                        int diff = Math.Abs(int.Parse(year) - int.Parse(key.Substring(key.Length - 2)));
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}:{charset[1]}{lastRow + diff}"].Style.Border.BorderAround(ExcelBorderStyle.Thin, System.Drawing.Color.Black);
                        worksheet.Cells[$"{charset[2]}{lastRow + 1}:{charset[2]}{lastRow + diff}"].Style.Border.BorderAround(ExcelBorderStyle.Thin, System.Drawing.Color.Black);
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}:{charset[2]}{lastRow + diff}"].Style.Fill.PatternType = ExcelFillStyle.Solid;
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}:{charset[2]}{lastRow + diff}"].Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml("#D9D9D9"));
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}"].Value = $"{type}{key.Substring(key.Length - 2)}";
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}:{charset[1]}{lastRow + diff}"].Merge = true;
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}"].Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}"].Style.VerticalAlignment = ExcelVerticalAlignment.Center;
                        worksheet.Cells[$"{charset[1]}{lastRow + 1}"].Style.Font.Bold = true;

                        SetHyperLinkStyle(worksheet.Cells[$"{charset[2]}{lastRow + 1}"]);

                        worksheet.Cells[$"{charset[2]}{lastRow + 1}"].Hyperlink = new ExcelHyperLink($"'{type}{key.Substring(key.Length - 2)}(20{year})'!A1", $"20{year}");
                        worksheet.Cells[$"{charset[2]}{lastRow + 1}"].Value = int.Parse($"20{year}");

                        worksheet.Cells[$"{charset[0]}{lastRow + 1}:{charset[0]}{lastRow + diff}"].StyleID = worksheet.Cells[$"{charset[0]}{lastRow}"].StyleID;
                        for (int j = 1; j <= diff; j++)
                        {
                            worksheet.Cells[$"{charset[0]}{lastRow + j}"].Value = int.Parse(worksheet.Cells[$"{charset[0]}{lastRow}"].Text) + j + 2;
                        }
                    }
                    else
                    {
                        var match = Regex.Match(ExistingCell.Address, @"\d+");
                        int row = 11;
                        if (match.Success)
                        {
                            row = int.Parse(match.Value);
                        }
                        string correctcell = charset[2] + (row - Math.Abs(int.Parse(key.Substring(key.Length - 2)) - int.Parse(year)) + 1).ToString();

                        SetHyperLinkStyle(worksheet.Cells[correctcell]);
                        worksheet.Cells[correctcell].Hyperlink = new ExcelHyperLink($"'{type}{key.Substring(key.Length - 2)}(20{year})'!A1", $"20{year}");
                        worksheet.Cells[correctcell].Value = int.Parse($"20{year}");
                    }
                    break;
                }
                i -= mergedRowCount;
            }
            worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];
            if (type == "BASE_Y-")
            {
                worksheet.Cells["C4:N8"].Value = null;
                worksheet.Cells["B2"].Value = key;
                worksheet.Cells["C2"].Value = DATA["Date"][1];
            }
            else
            {
                worksheet.Cells["B4:M8"].Value = null;
                worksheet.Cells["A2"].Value = key;
                worksheet.Cells["B2"].Value = DATA["Date"][1];
            }
            
        }
        public string UpdateExcelFile(string filePath, Dictionary<string, List<string>> DATA)
        {
            string? id = "";
            if (string.IsNullOrEmpty(filePath))
            {
                return "Nie wczytano pliku.";
            }
            GrantFileAccess(filePath);
            try
            {
                using (var package = new ExcelPackage(new FileInfo(filePath)))
                {
                    string year = DATA["Date"][1].Substring(DATA["Date"][1].Length - 2);
                    string month = DATA["Date"][0];
                    CultureInfo polishCulture = new CultureInfo("pl-PL");
                    var worksheet = package.Workbook.Worksheets[$"SPOT(RDN{year})"];
                    if(worksheet == null)
                    {
                        worksheet = package.Workbook.Worksheets[$"Spis Treści"];
                        int y = 0;
                        while (worksheet.Cells["C" + (28 + y).ToString()].Text != "RDB")
                        {
                            y++;
                        }
                        worksheet.Cells["C" + (28 + y).ToString() + ":E" + (28 + y).ToString()].Merge = false;
                        
                        int j = 0;
                        while (worksheet.Cells["D" + (29 + j).ToString()].Text != "Rynek Dnia Bieżącego")
                        {
                            j++;
                        }
                        int offset = 0;
                        while (worksheet.Cells["E" + (29 + j + offset).ToString()].Text != "")
                        {
                            offset++;
                        }
                        worksheet.Cells["D" + (29 + j).ToString() + ":D" + (29 + j + offset - 1).ToString()].Merge = false;

                        int e = 0;
                        while(worksheet.Cells["E" + (20 + e).ToString()].Text != "")
                        {
                            e++;
                        }
          
                        InsertSingleCellInColumn(worksheet, 'C', 'E', 21 + e);

                        var s1 = worksheet.Cells["C" + (20 + e - 1).ToString()].Value;

                        if (s1 == null) return "ERROR";
                        id = s1.ToString();
                        if (id == null) return "ERROR";

                        var cell = worksheet.Cells[$"C" + (20 + e).ToString()];
                        cell.Value = int.Parse(id)+1;
                        cell.Style.Fill.PatternType = ExcelFillStyle.Solid;
                        cell.Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml("#D9D9D9"));
                        cell.Style.Font.Color.SetColor(System.Drawing.ColorTranslator.FromHtml("#7F7F7F"));
                        cell.Style.Font.Italic = true;
                        cell.Style.Border.Left.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Right.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Left.Color.SetColor(System.Drawing.Color.Black);
                        cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);

                        worksheet.Cells["C" + (28 + y + 1).ToString() + ":E" + (28 + y + 1).ToString()].Merge = true;
                        worksheet.Cells["D" + (29 + j + 1).ToString() + ":D" + (29 + j + 1 + offset).ToString()].Merge = true;

                        for (int k = 13; k <= int.Parse(year) - 1; k++)
                        {
                            worksheet.Cells["E" + (29 + k - 13 + j + 1)].Value = int.Parse("20" + k);

                        }

                        SetHyperLinkStyle(worksheet.Cells[$"E" + (20 + e).ToString()]);

                        cell = worksheet.Cells[$"D" + (20 + e).ToString()];

                        worksheet.Cells["D6:D" + (20 + e).ToString()].Merge = false;
                        worksheet.Cells["D6:D" + (20 + e).ToString()].Merge = true;
                        cell.Style.Fill.PatternType = ExcelFillStyle.Solid;
                        cell.Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml("#D9D9D9"));
                        cell.Style.Border.Left.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Right.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Left.Color.SetColor(System.Drawing.Color.Black);
                        cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);

                        worksheet = package.Workbook.Worksheets.Copy($"SPOT(RDN{int.Parse(year) - 1})", $"SPOT(RDN{year})");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells[$"E" + (20 + e).ToString()].Hyperlink = new ExcelHyperLink($"'SPOT(RDN{year})'!" + "E" + (20 + e).ToString(), $"20{year}");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells[$"E" + (20 + e).ToString()].Value = int.Parse($"20{year}");
                        if (worksheet.Cells["B5"].Text != "Średnia cena Euro")
                        {
                            worksheet.Cells["C4:N9"].Value = "";
                        }
                        else
                        {
                            worksheet.Cells["C4:N12"].Value = "";
                        }
                        worksheet.Cells["A3"].Value = $"RDN 20{year}";

                    }


                    CreateExchangeRate(worksheet, month, DATA);

                    if (worksheet.Cells["B5"].Text != "Średnia cena Euro")
                    {
                        InsertAndStyleRow(worksheet, 9, "Średnia cena Euro", false);
                        worksheet.Cells["C9:N9"].Style.Numberformat.Format = "#,##0.00";
                        InsertAndStyleRow(worksheet, 7, "Średnia cena Euro", false);
                        worksheet.Cells["C7:N7"].Style.Numberformat.Format = "#,##0.00";
                        InsertAndStyleRow(worksheet, 5, "Średnia cena Euro", false);
                        worksheet.Cells["C5:N5"].Style.Numberformat.Format = "#,##0.00";
                    }

                    worksheet = package.Workbook.Worksheets[$"SPOT(RDB{year})"];
                    if (worksheet == null)
                    {
                        worksheet = package.Workbook.Worksheets[$"Spis Treści"];
                        int y = 0;
                        while (worksheet.Cells["C" + (28 + y).ToString()].Text != "RDB")
                        {
                            y++;
                        }
                        int e = 1;
                        while (worksheet.Cells["E" + (28 + y + e).ToString()].Text != "")
                        {
                            e++;
                        }

                        for (int i = 0; i < e; i++)
                        {
                            worksheet.Cells[$"C" + (28 + y + 1 + i)].Value = int.Parse(id) + 2 + i;
                        }

                        var cell = worksheet.Cells[$"C" + (28 + y + e).ToString()];
                        
                        cell.Style.Fill.PatternType = ExcelFillStyle.Solid;
                        cell.Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml("#D9D9D9"));
                        cell.Style.Font.Color.SetColor(System.Drawing.ColorTranslator.FromHtml("#7F7F7F"));
                        cell.Style.Font.Italic = true;
                        cell.Style.Border.Left.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Right.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Left.Color.SetColor(System.Drawing.Color.Black);
                        cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);

                        SetHyperLinkStyle(worksheet.Cells[$"E" + (28 + y + e).ToString()]);

                        cell = worksheet.Cells[$"D" + (28 + y + e).ToString()];

                        cell.Style.Fill.PatternType = ExcelFillStyle.Solid;
                        cell.Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml("#D9D9D9"));
                        cell.Style.Border.Left.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Right.Style = ExcelBorderStyle.Thin;
                        cell.Style.Border.Left.Color.SetColor(System.Drawing.Color.Black);
                        cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);

                        worksheet = package.Workbook.Worksheets.Copy($"SPOT(RDB{int.Parse(year) - 1})", $"SPOT(RDB{year})");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells[$"E" + (28 + y + e).ToString()].Hyperlink = new ExcelHyperLink($"'SPOT(RDB{year})'!" + "E" + (28 + y + e).ToString(), $"20{year}");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells[$"E" + (28 + y + e).ToString()].Value = int.Parse($"20{year}");
                        if (worksheet.Cells["B28"].Text != "miesięczna uśredniona cena godzinowa [EUR/MWh]")
                        {
                            worksheet.Cells["D4:O51"].Value = "";
                        }
                        else
                        {
                            worksheet.Cells["D4:O75"].Value = "";
                        }
                        worksheet.Cells["B3"].Value = $"RDB 20{year}";

                    }


                    CreateExchangeRate(worksheet, month, DATA);

                    if (worksheet.Cells["B28"].Text != "miesięczna uśredniona cena godzinowa [EUR/MWh]")
                    {
                        worksheet.InsertRow(28, 24);
                        worksheet.Cells["B28:B51"].Merge = true;
                        ApplyCellStyle(worksheet.Cells["B28:B51"], "", "#054136", null, true);
                        worksheet.Cells["B28"].Value = "miesięczna uśredniona cena godzinowa [EUR/MWh]";
                        worksheet.Cells["B28"].Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
                        worksheet.Cells["B28"].Style.VerticalAlignment = ExcelVerticalAlignment.Center;
                        worksheet.Cells["B28"].Style.WrapText = true;
                        worksheet.Cells["C28:O28"].Style.Border.Top.Style = ExcelBorderStyle.Medium;
                        worksheet.Cells["C28:O28"].Style.Border.Top.Color.SetColor(System.Drawing.Color.Black);
                        worksheet.Cells["C51:O51"].Style.Border.Bottom.Style = ExcelBorderStyle.Medium;
                        worksheet.Cells["C51:O51"].Style.Border.Bottom.Color.SetColor(System.Drawing.Color.Black);
                        worksheet.Cells["D28:O51"].Style.Numberformat.Format = "#,##0.00";
                        for (int i = 1; i <= 24; i++)
                        {
                            string curCell = "C" + (i + 27).ToString();
                            worksheet.Cells[curCell].Value = (i % 24).ToString() + ":00";
                            worksheet.Cells[curCell].Style.Font.Bold = true;
                            worksheet.Cells[curCell + ":O" + (i + 27).ToString()].Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
                            worksheet.Cells[curCell + ":O" + (i + 27).ToString()].Style.VerticalAlignment = ExcelVerticalAlignment.Center;
                            worksheet.Cells[curCell].Style.Border.Right.Style = ExcelBorderStyle.Medium;
                            worksheet.Cells["O" + (i + 27).ToString()].Style.Border.Right.Style = ExcelBorderStyle.Medium;
                            worksheet.Cells["D" + (i + 27).ToString() + ":N" + (i + 27).ToString()].Style.Border.Right.Style = ExcelBorderStyle.Thin;
                            worksheet.Cells[curCell + ":O" + (i + 27).ToString()].Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);
                        }
                    }

                    foreach (var key in DATA.Keys.Where(k => k.StartsWith("BASE_Y")).ToList())
                    {
                        worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];

                        if (worksheet == null)
                        {
                            DuplicateMarket(package, DATA, "BASE_Y-", key, "GHI");
                        }
                        worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];

                        if (worksheet.Cells["B5"].Text != "cena średnia [EUR/MWh]")
                        {
                            CreateExchangeRate(worksheet, month, DATA);
                            InsertAndStyleRow(worksheet, 5, "cena średnia [EUR/MWh]", false);
                            worksheet.Cells["B5"].Style.WrapText = true;
                            worksheet.Cells["B5"].Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
                            worksheet.Cells["B5"].Style.VerticalAlignment = ExcelVerticalAlignment.Center;
                            worksheet.Cells["C5:M5"].Style.Border.Right.Style = ExcelBorderStyle.Thin;
                            worksheet.Cells["C5:N5"].Style.Numberformat.Format = "#,##0.00";
                        }
                    }

                    foreach (var key in DATA.Keys.Where(k => k.StartsWith("PEAK5_Y")).ToList())
                    {
                        worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];
                        if (worksheet == null)
                        {
                            DuplicateMarket(package, DATA, "PEAK5_Y-", key, "KLM");
                        }
                        worksheet = package.Workbook.Worksheets[key + '(' + DATA["Date"][1] + ')'];
                        if (worksheet.Cells["A5"].Text != "cena średnia [EUR/MWh]")
                        {
                            CreateExchangeRate(worksheet, month, DATA);
                            InsertAndStyleRow(worksheet, 5, "cena średnia [EUR/MWh]", true);
                            worksheet.Cells["A5"].Style.WrapText = true;
                            worksheet.Cells["A5"].Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
                            worksheet.Cells["A5"].Style.VerticalAlignment = ExcelVerticalAlignment.Center;
                            worksheet.Cells["B5:L5"].Style.Border.Right.Style = ExcelBorderStyle.Medium;
                            worksheet.Cells["B5:M5"].Style.Numberformat.Format = "#,##0.00";
                        }
                    }

                    worksheet = package.Workbook.Worksheets["PMOZE_A(2012-) Bilans ŚP"];

                    int monthNumber = DateTime.ParseExact(month, "MMMM", polishCulture).Month;
                    int rowNumber = (5 + (int.Parse(year) - 12) * 12 + monthNumber);

                    if (worksheet.Cells['A' + rowNumber.ToString()].Text == "")
                    {
                        worksheet.Cells['A' + (rowNumber - monthNumber + 1).ToString() + ":G" + (rowNumber - monthNumber + 12).ToString()].Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);
                        for (int i = 1; i < 13; i++)
                        {
                            worksheet.Cells['A' + (rowNumber - monthNumber + i).ToString()].Value = polishCulture.DateTimeFormat.GetMonthName(i).Substring(0, 3) + "." + year;
                        }
                    }

                    worksheet = package.Workbook.Worksheets["PMOZE_A(2009-)Ceny, Wol"];

                    rowNumber = (5 + (int.Parse(year) - 9) * 12 + monthNumber);

                    if (worksheet.Cells['A' + rowNumber.ToString()].Text == "")
                    {
                        worksheet.Cells['A' + (rowNumber - monthNumber + 1).ToString() + ":D" + (rowNumber - monthNumber + 12).ToString()].Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);
                        for (int i = 1; i < 13; i++)
                        {
                            worksheet.Cells['A' + (rowNumber - monthNumber + i).ToString()].Value = polishCulture.DateTimeFormat.GetMonthName(i).Substring(0, 3) + "." + year;
                        }
                    }

                    worksheet = package.Workbook.Worksheets["PMOZE_Bio(2024-)Ceny, Wol"];

                    if(worksheet == null)
                    {
                        worksheet = package.Workbook.Worksheets[$"Spis Treści"];
                        worksheet.Cells["O12:Q13"].Merge = false;
                        for (int i = 0; i < 8; i++)
                        {
                            InsertSingleCellInColumn(worksheet, 'O', 'Q', 12);
                        }
                        worksheet.Cells["O20:Q21"].Merge = true;
                        worksheet.Cells["O8:Q10"].Copy(worksheet.Cells["O12:Q14"]);
                        worksheet.Cells["O8:Q10"].Copy(worksheet.Cells["O16:Q18"]);

                        worksheet = package.Workbook.Worksheets.Copy("PMOZE_A(2009-)Ceny, Wol", $"PMOZE_BIO(2024-)Ceny, Wol");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["P13"].Value = "PMOZE_BIO Ceny i wolumeny";
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["Q13"].Hyperlink = new ExcelHyperLink($"'PMOZE_BIO(2024-)Ceny, Wol'!A1", $"2024-20{year}");

                        worksheet.DeleteRow(6, worksheet.Dimension.End.Row - 17);
                        worksheet.Cells["B6:D17"].Value = null;
                        worksheet.Cells["A3"].Value = "PMOZE_BIO";

                        worksheet = package.Workbook.Worksheets.Copy("PMOZE_A(2012-) Bilans ŚP", $"PMOZE_BIO(2024-) Bilans ŚP");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["P14"].Value = "PMOZE_BIO Bilans certyfikatów";
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["Q14"].Hyperlink = new ExcelHyperLink($"'PMOZE_BIO(2024-) Bilans ŚP'!A1", $"2024-20{year}");

                        worksheet.DeleteRow(6, worksheet.Dimension.End.Row - 17);
                        worksheet.Cells["B6:G17"].Value = null;
                        worksheet.Cells["A3"].Value = "PMOZE_BIO";
                        worksheet.Cells["G4"].Value = "kontrakt PMOZE_BIO";

                        worksheet = package.Workbook.Worksheets.Copy("PMOZE_A(2009-)Ceny, Wol", $"PMEF_F(2024-)Ceny, Wol");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["P17"].Value = "PMEF_F Ceny i wolumeny";
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["Q17"].Hyperlink = new ExcelHyperLink($"'PMEF_F(2024-)Ceny, Wol'!A1", $"2024-20{year}");

                        worksheet.DeleteRow(6, worksheet.Dimension.End.Row - 17);
                        worksheet.Cells["B6:D17"].Value = null;
                        worksheet.Cells["A3"].Value = "PMEF_F";
                        worksheet.Cells["B5"].Value = "PLN/toe";
                        worksheet.Cells["C5"].Value = "Mtoe";
                        worksheet.Cells["D5"].Value = "PLN/toe";

                        worksheet = package.Workbook.Worksheets.Copy("PMOZE_A(2012-) Bilans ŚP", $"PMEF_F(2024-) Bilans ŚP");
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["P18"].Value = "PMEF_F Bilans certyfikatów";
                        package.Workbook.Worksheets[$"Spis Treści"].Cells["Q18"].Hyperlink = new ExcelHyperLink($"'PMEF_F(2024-) Bilans ŚP'!A1", $"2024-20{year}");

                        worksheet.DeleteRow(6, worksheet.Dimension.End.Row - 17);
                        worksheet.Cells["B6:G17"].Value = null;
                        worksheet.Cells["A3"].Value = "PMEF_F";
                        worksheet.Cells["B5"].Value = "Gtoe";
                        worksheet.Cells["G4"].Value = "kontrakt PMEF_F";
                        worksheet.Cells["G5"].Value = "[PLN/toe]";
                    }
                    rowNumber = (5 + (int.Parse(year) - 24) * 12 + monthNumber);

                    if (worksheet.Cells['A' + rowNumber.ToString()].Text == "")
                    {
                        worksheet.Cells['A' + (rowNumber - monthNumber + 1).ToString() + ":D" + (rowNumber - monthNumber + 12).ToString()].Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);
                        for (int i = 1; i < 13; i++)
                        {
                            worksheet.Cells['A' + (rowNumber - monthNumber + i).ToString()].Value = polishCulture.DateTimeFormat.GetMonthName(i).Substring(0, 3) + "." + year;
                        }
                    }

                    worksheet = package.Workbook.Worksheets["PMOZE_BIO(2024-) Bilans ŚP"];

                    rowNumber = (5 + (int.Parse(year) - 24) * 12 + monthNumber);

                    if (worksheet.Cells['A' + rowNumber.ToString()].Text == "")
                    {
                        worksheet.Cells['A' + (rowNumber - monthNumber + 1).ToString() + ":G" + (rowNumber - monthNumber + 12).ToString()].Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);
                        for (int i = 1; i < 13; i++)
                        {
                            worksheet.Cells['A' + (rowNumber - monthNumber + i).ToString()].Value = polishCulture.DateTimeFormat.GetMonthName(i).Substring(0, 3) + "." + year;
                        }
                    }

                    worksheet = package.Workbook.Worksheets["PMEF_F(2024-)Ceny, Wol"];

                    rowNumber = (5 + (int.Parse(year) - 24) * 12 + monthNumber);

                    if (worksheet.Cells['A' + rowNumber.ToString()].Text == "")
                    {
                        worksheet.Cells['A' + (rowNumber - monthNumber + 1).ToString() + ":D" + (rowNumber - monthNumber + 12).ToString()].Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);
                        for (int i = 1; i < 13; i++)
                        {
                            worksheet.Cells['A' + (rowNumber - monthNumber + i).ToString()].Value = polishCulture.DateTimeFormat.GetMonthName(i).Substring(0, 3) + "." + year;
                        }
                    }

                    worksheet = package.Workbook.Worksheets["PMOZE_BIO(2024-)Ceny, Wol"];

                    rowNumber = (5 + (int.Parse(year) - 24) * 12 + monthNumber);

                    if (worksheet.Cells['A' + rowNumber.ToString()].Text == "")
                    {
                        worksheet.Cells['A' + (rowNumber - monthNumber + 1).ToString() + ":D" + (rowNumber - monthNumber + 12).ToString()].Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);
                        for (int i = 1; i < 13; i++)
                        {
                            worksheet.Cells['A' + (rowNumber - monthNumber + i).ToString()].Value = polishCulture.DateTimeFormat.GetMonthName(i).Substring(0, 3) + "." + year;
                        }
                    }

                    package.Save();
                    return "Wczytano .xcls pomyślnie!";
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("An error occurred while processing the Excel file: " + ex.Message);
                return "ERROR";
            }
        }
        private void CreateExchangeRate(ExcelWorksheet worksheet, string month, Dictionary<string, List<string>> DATA)
        {
            worksheet.Cells["Q3"].AutoFitColumns();
            double result;
            if (!Double.TryParse(DATA["Exchange"][0].Trim(), out result))
            {
                result = 0d;
            }

            ApplyCellStyle(worksheet.Cells["Q3"], "Średni kurs euro | " + month, "#054136", null, true);
            worksheet.Cells["Q3"].AutoFitColumns();
            ApplyCellStyle(worksheet.Cells["R3"], DATA["Exchange"][0], "#FFFFFF", result, true);
            worksheet.Cells["R3"].Style.Font.Color.SetColor(System.Drawing.Color.Black);
        }

        private void ApplyCellStyle(ExcelRangeBase cell, string text, string backgroundColorHex, double? value = null, bool bold = false)
        {
            cell.Value = text;
            cell.Style.Fill.PatternType = ExcelFillStyle.Solid;
            cell.Style.Fill.BackgroundColor.SetColor(System.Drawing.ColorTranslator.FromHtml(backgroundColorHex));
            cell.Style.Font.Color.SetColor(System.Drawing.Color.White);
            cell.Style.Font.Bold = bold;

            cell.Style.Border.BorderAround(ExcelBorderStyle.Medium, System.Drawing.Color.Black);

            if (value.HasValue)
            {
                cell.Value = value.Value;
            }
        }

        private void InsertAndStyleRow(ExcelWorksheet worksheet, int row, string cellText, bool firstRow)
        {
            worksheet.InsertRow(row, 1);
            
            var range = worksheet.Cells[firstRow ? $"A{row}:N{row}" : $"B{row}:O{row}"];
            range.Style.Border.BorderAround(ExcelBorderStyle.Thin, System.Drawing.Color.Black);

            foreach (var cell in range)
            {
                if (cell.Address == (firstRow ? "A" : "B") + row)
                {
                    ApplyCellStyle(cell, cellText, "#054136", null, true);
                }
                else if (cell.Address == (firstRow ? "B" : "C") + row)
                {
                    cell.Style.Border.Left.Style = ExcelBorderStyle.Thin;
                    cell.Style.Border.Left.Color.SetColor(System.Drawing.Color.Black);
                }
                else if (cell.Address == (firstRow ? "M" : "N") + row)
                {
                    cell.Style.Border.Right.Style = ExcelBorderStyle.Medium;
                    cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);
                }
                else if (cell.Address == (firstRow ? "N" : "O") + row)
                {
                    cell.Style.Border.Right.Style = ExcelBorderStyle.Medium;
                    cell.Style.Border.DiagonalUp = true;
                    cell.Style.Border.DiagonalDown = true;
                    cell.Style.Border.Diagonal.Style = ExcelBorderStyle.Thin;
                    cell.Style.Border.Diagonal.Color.SetColor(System.Drawing.Color.Black);
                    cell.Style.Border.Right.Color.SetColor(System.Drawing.Color.Black);
                }
                else
                {
                    cell.Style.HorizontalAlignment = ExcelHorizontalAlignment.Center;
                    cell.Style.VerticalAlignment = ExcelVerticalAlignment.Center;
                    cell.Style.Border.Top.Style = ExcelBorderStyle.None;
                    cell.Style.Border.Bottom.Style = ExcelBorderStyle.None;
                    cell.Style.Border.Left.Style = ExcelBorderStyle.None;
                    cell.Style.Border.Right.Style = ExcelBorderStyle.None;
                }
            }
        }
    }
}
