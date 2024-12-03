using OfficeOpenXml;
using OfficeOpenXml.Export.ToCollection;
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


namespace ModelUpdater
{
	internal class ModelUpdater
	{
		Dictionary<string, string> names = new Dictionary<string, string>();

		private Dictionary<string, List<string>> data = new Dictionary<string, List<string>>();
		private string modelPath;
		private string entsoePath;
		public ModelUpdater(string modelPath, string entsoePath) {
			this.modelPath = modelPath;
			this.entsoePath = entsoePath;
			names.Add("Ostrołęka", "OSB");
			names.Add("Jaworzno", "JW");
			names.Add("Połaniec", "POL");
			names.Add("Opole", "OPL");
			names.Add("Bełchatów", "BEL");
			names.Add("Kozienice", "KOZ");
			names.Add("Turów", "TUR");
			names.Add("Dolna", "DOD");
			names.Add("Łagisza", "LGA");
			names.Add("Siersza", "SIA");
			names.Add("Łaziska", "LZA");
			names.Add("Pątnuch", "PAT");
			names.Add("Rybnik", "RYB");
		}
		public string ModelPath { get { return modelPath; } }
		public string EntsoePath { get {return entsoePath; } }

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
		private string GetBlockNumber(string input)
		{
			if (string.IsNullOrWhiteSpace(input))
				return string.Empty;

			Match match = Regex.Match(input, @"[\d]+$");
			return match.Success ? match.Value : string.Empty;
		}
		private string GetFirstWord(string input)
		{
			if (string.IsNullOrWhiteSpace(input))
				return string.Empty;

			Match match = Regex.Match(input, @"^([\p{L}\-]+)");
			return match.Success ? match.Value : string.Empty;
		}
		public string UpdateModel()
		{
			string key;
			string block;
			if (entsoePath == null || modelPath == null)
				return "Problem ze ścieżką do któregoś pliku";
			GrantFileAccess(modelPath);
			GrantFileAccess(entsoePath);
			try
			{
				using (var package = new ExcelPackage(new FileInfo(entsoePath)))
				{
					var worksheet = package.Workbook.Worksheets[$"Sheet1"];
					for (int i = 8; i <= worksheet.Dimension.End.Row; i++)
					{
						if (worksheet.Cells[$"F{i}"].Text.Contains("EC"))
							continue;
						key = GetFirstWord(worksheet.Cells[$"F{i}"].Text);
						block = GetBlockNumber(worksheet.Cells[$"F{i}"].Text).TrimStart('0');
						if (key == string.Empty || block == string.Empty || !names.ContainsKey(key))
							continue;
						if (data.ContainsKey(names[key] + " " + block))
						{
							data.Add("2" + names[key] + " " + block, worksheet.Cells[$"D{i}"].Text.Split(' ').ToList());
							data["2" + names[key] + " " + block].RemoveAt(data["2" + names[key] + " " + block].Count - 1);
							data["2" + names[key] + " " + block].RemoveAt(2);
							if (data["2" + names[key] + " " + block][1].StartsWith("0"))
								data["2" + names[key] + " " + block][1] = data["2" + names[key] + " " + block][1].Substring(1);
							if (data["2" + names[key] + " " + block][3].StartsWith("0"))
								data["2" + names[key] + " " + block][3] = data["2" + names[key] + " " + block][3].Substring(1);
						}
						else
						{
							data.Add(names[key] + " " + block, worksheet.Cells[$"D{i}"].Text.Split(' ').ToList());
							data[names[key] + " " + block].RemoveAt(data[names[key] + " " + block].Count - 1);
							data[names[key] + " " + block].RemoveAt(2);
							if (data[names[key] + " " + block][1].StartsWith("0"))
								data[names[key] + " " + block][1] = data[names[key] + " " + block][1].Substring(1);
							if (data[names[key] + " " + block][3].StartsWith("0"))
								data[names[key] + " " + block][3] = data[names[key] + " " + block][3].Substring(1);
						}
					}
				}
				using (var package = new ExcelPackage(new FileInfo(modelPath)))
				{
					string value;
					string numbers;
					bool dontadd = false;
					int startCell;
					int endCell;
					var worksheet = package.Workbook.Worksheets[$"Planowane_ubytki_JWCD"];
					for (int i = worksheet.Dimension.Start.Column + 2; i <= worksheet.Dimension.End.Column; i = (dontadd) ? i : i + 1)
					{
						if (worksheet.Cells[1, i].Text == "0" || worksheet.Cells[1, i].Text == "")
							break;
						value = GetFirstWord(worksheet.Cells[1, i].Text);
						numbers = GetBlockNumber(worksheet.Cells[1, i].Text).TrimStart('0');
						if (dontadd == false)
						{
							for (int clean = 4; clean <= 366 * 24; clean += 24)
							{
								if (worksheet.Cells[clean, i].Text == "")
								{
									int x = clean;
									int y = clean;
									while (x <= worksheet.Dimension.End.Row && worksheet.Cells[x, i].Text == "")
										x += 24;
									while (x > 1 && worksheet.Cells[x, i].Text != "")
										x--;
									while (y >= 1 && worksheet.Cells[y, i].Text == "" && y >= 28)
										y -= 24;
									while (y < worksheet.Dimension.End.Row && worksheet.Cells[y, i].Text != "")
										y++;
									if (y <= x && y >= 1 && x <= worksheet.Dimension.End.Row)
									{
										Debug.WriteLine("Cleaning from: " + y.ToString() + " to " + x.ToString());
										worksheet.Cells[y, i, x, i].Value = 1;
									}
								}
							}
						}
						if (data.ContainsKey("2" + value + " " + numbers))
						{
							dontadd = true;
							if (data[value + " " + numbers].Count == 0)
							{
								value = "2" + value;
								dontadd = false;
							}
						}
						if (data.ContainsKey(value + " " + numbers))
						{
							Match yearMain = Regex.Match(worksheet.Cells["A4"].Text, @"(?<=[\d]{2}.[\d]{2}.)[\d]{4}");
							Match year = Regex.Match(data[value + " " + numbers][0], @"(?<=[\d]{2}.[\d]{2}.)[\d]{4}");	
							Match monthStart = Regex.Match(data[value + " " + numbers][0], @"(?<=[\d]{2}.)[\d]{2}(?=.[\d]{4})");
							Match month = Regex.Match(data[value + " " + numbers][2], @"(?<=[\d]{2}.)[\d]{2}(?=.[\d]{4})");
							Match dayStart = Regex.Match(data[value + " " + numbers][0], @"[\d]{2}(?=.[\d]{2}.[\d]{4})");
							Match day = Regex.Match(data[value + " " + numbers][2], @"[\d]{2}(?=.[\d]{2}.[\d]{4})");
							Match hourStart = Regex.Match(data[value + " " + numbers][1], @"[\d]{1,2}(?=:[\d]{2})");
							Match hour = Regex.Match(data[value + " " + numbers][3], @"[\d]{1,2}(?=:[\d]{2})");
							if (year.Success && monthStart.Success && dayStart.Success && yearMain.Success && day.Success && month.Success && hour.Success && hourStart.Success)
							{
								DateTime date = new DateTime(int.Parse(yearMain.Value), int.Parse(monthStart.Value.TrimStart('0')), int.Parse(dayStart.Value));
								DateTime dateEnd = new DateTime(int.Parse(yearMain.Value), int.Parse(month.Value.TrimStart('0')), int.Parse(day.Value));
								if (year.Value == yearMain.Value)
									startCell = 4 + (date.DayOfYear - 1) * 24 + int.Parse(hourStart.Value);
								else
									startCell = 4;
								endCell = 4 + (dateEnd.DayOfYear - 1) * 24 - 1 + int.Parse(hour.Value);
								//for (int clean = startCell; clean <= endCell; clean += 24)
								//{
								//	if (worksheet.Cells[clean, i].Text == "")
								//	{
								//		int x = clean;
								//		int y = clean;
								//		while (worksheet.Cells[x, i].Text == "")
								//			x += 24;
								//		while (worksheet.Cells[x, i].Text != "")
								//			x--;
								//		while (worksheet.Cells[y, i].Text == "" && y >= 28)
								//			y -= 24;
								//		while (worksheet.Cells[y, i].Text != "")
								//			y++;
								//		worksheet.Cells[y, i, x, i].Value = 1;
								//	}
								//}
								worksheet.Cells[startCell, i, endCell, i].Clear();
							}
							data[value + " " + numbers].Clear();
						}
					}
					package.Save();
				}
			}
			catch (Exception ex)
			{
				return "Problem z wczytywaniem danych z entso_e:" + ex.Message;
			}
			return "Sukces!";
		}

	}
}
