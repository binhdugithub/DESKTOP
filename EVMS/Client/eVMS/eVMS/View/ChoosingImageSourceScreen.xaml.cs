using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using eVMS.Jsoncontract;
using eVMS.Utils;
using eVMS.ViewModel;
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for ChoosingImageSourceScreen.xaml
    /// </summary>
    public partial class ChoosingImageSourceScreen : Window
    {
        private ChoosingImageSourceScreenViewmodel viewmodel;
        public event Action<Imagelist> ChooseImageEvent;
        public ChoosingImageSourceScreen()
        {
            InitializeComponent();
            viewmodel = new ChoosingImageSourceScreenViewmodel();
            DataContext = viewmodel;
            GetlistImage();
        }

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (lbImages.SelectedItem == null)
            {
                TblInfo.Text = "Chọn ảnh";
                return;
            }
            if (lbImages.SelectedItem is Imagelist)
            {
                var item = (lbImages.SelectedItem as Imagelist);
                if (ChooseImageEvent != null)
                {
                    ChooseImageEvent(item);
                }

                this.Close();
            }
        }

        public async void GetlistImage()
        {
            FluidProgressBar.Visibility = Visibility.Visible;
            BtnOk.IsEnabled = false;
            var res = await GetImageSourceFromDatabase();

            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnOk.IsEnabled = true;

            if (res == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }
            if (res.imagelist == null)
            {
                TblInfo.Text = "Không có dữ liệu ảnh";
                return;
            }
            viewmodel.Images = new ObservableCollection<Imagelist>(res.imagelist);
            //lvImages.ItemsSource = viewmodel.Images;
        }


        #region Task
        public async Task<ImageSourceListMessage> GetImageSourceFromDatabase()
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getlistimagesource"];
                var request = new RestRequest(reUrl, Method.GET);

                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<ImageSourceListMessage>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("json converter error:" + ex);
                return null;
            }

            return null;
        }
        #endregion
    }
}
