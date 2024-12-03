using OfficeOpenXml;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace ModelUpdater
{
	public partial class MainPage : ContentPage
	{
		private string? entsoEPath;
		private string? modelPath;
		public MainPage()
		{
			InitializeComponent();
			ExcelPackage.LicenseContext = LicenseContext.NonCommercial;
		}

		private async void LoadEntsoe(object sender, EventArgs e)
		{
			var entsoE = await FilePicker.Default.PickAsync(new PickOptions
			{
				PickerTitle = "Wybierz plik .PDF",
				FileTypes = new FilePickerFileType(new Dictionary<DevicePlatform, IEnumerable<string>>(){
					{
						DevicePlatform.WinUI, new[] { ".xlsx" }
					},
				})
			});
			if (entsoE == null)
			{
				filePathLabel.Text = "Nie wczytano pliku!";
				return;
			}

			entsoEPath = entsoE.FullPath.ToString();
			
			btnWczytajEntsoE.IsEnabled = false;
			btnWczytajModel.IsEnabled = true;
		}
		private async void LoadModel(object sender, EventArgs e)
		{
			var model = await FilePicker.Default.PickAsync(new PickOptions
			{
				PickerTitle = "Wybierz plik .xlsm (excel makro)",
				FileTypes = new FilePickerFileType(new Dictionary<DevicePlatform, IEnumerable<string>>(){
					{
						DevicePlatform.WinUI, new[] { ".xlsm" }
					},
				})
			});
			if (model == null)
			{
				filePathLabel.Text = "Nie wczytano pliku!";
				return;
			}
			modelPath = model.FullPath.ToString();
			btnWczytajModel.IsEnabled = false;
			btnStart.IsEnabled = true;
		}
		private void StartUpdating(object sender, EventArgs e)
		{
			if (modelPath == null || entsoEPath == null)
				return;
			ModelUpdater modUp = new ModelUpdater(modelPath, entsoEPath);
			Stopwatch stopwatch = new Stopwatch();

			filePathLabel.Text = modUp.UpdateModel();

			btnWczytajEntsoE.IsEnabled = true;
			btnStart.IsEnabled = false;
		}
	}

}
