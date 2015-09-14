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
using eVMS.Model;
using eVMS.Utils;
using eVMS.ViewModel;
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for ProgramScreen.xaml
    /// </summary>
    public partial class ProgramScreen : Window
    {
        private ProgramScreenViewModel _viewmode;
        private int width, height = 0;

        public event Action<ProgramUpdateMessage> LoadprogramEvent;
        public ProgramScreen()
        {
            InitializeComponent();
            _viewmode = new ProgramScreenViewModel();
            DataContext = _viewmode;
            GetDataProgram();
        }

        public ProgramScreen(int wi, int he):this()
        {
            width = wi;
            height = he;
        }

        public async void GetDataProgram()
        {
            FluidProgressBar.Visibility = Visibility.Visible;
            BtnOk.IsEnabled = false;
            BtnDel.IsEnabled = false;
            var res = await GetListProgramFromtoServer();
            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnOk.IsEnabled = true;
            BtnDel.IsEnabled = true;
            if (res == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }

            try
            {
                _viewmode.Programs = new ObservableCollection<ShortProgram>(res.programs);
            }
            catch (Exception ex)
            {
                TblInfo.Text = "Lỗi:" + ex.ToString();
                Log4Net.Log.Error(ex);
                return;
            }

            

        }

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (dgPrograms.SelectedItem == null)
            {
                TblInfo.Text = "Chon chương trình";
                return;
            }
            if (dgPrograms.SelectedItem is ShortProgram)
            {
                var item = dgPrograms.SelectedItem as ShortProgram;
                if (item.height != height || item.width != width)
                {
                    TblInfo.Text = "Kích thước chương trình không phù hợp";
                    return;
                }

                TblInfo.Text = string.Empty;
                BtnOk.IsEnabled = BtnCan.IsEnabled = false;
                BtnDel.IsEnabled = false;
                FluidProgressBar.Visibility = Visibility.Visible;

                var res = await GetDetailProgramFromtoServer(item.id);
                BtnOk.IsEnabled = BtnCan.IsEnabled = true;
                BtnDel.IsEnabled = true;
                FluidProgressBar.Visibility = Visibility.Hidden;
                if (res == null)
                {
                    BtnOk.IsEnabled = true;
                    TblInfo.Text = "Lỗi tải về";
                    //Log4Net.Log.Error(ex);
                    return;
                }
                if (LoadprogramEvent != null)
                    LoadprogramEvent(res);

                this.Close();

            }
        }

        private async void BtnDel_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (dgPrograms.SelectedItem == null)
            {
                TblInfo.Text = "Chon chương trình";
                return;
            }

            if (dgPrograms.SelectedItem is ShortProgram)
            {
                var item = dgPrograms.SelectedItem as ShortProgram;

                TblInfo.Text = string.Empty;
                BtnOk.IsEnabled = BtnCan.IsEnabled = false;
                BtnDel.IsEnabled = false;
                FluidProgressBar.Visibility = Visibility.Visible;

                var res = await DelProgramFromtoServer(item.id);
                BtnOk.IsEnabled = BtnCan.IsEnabled = true;
                BtnDel.IsEnabled = true;
                FluidProgressBar.Visibility = Visibility.Hidden;
                if (res == null)
                {
                    BtnOk.IsEnabled = true;
                    TblInfo.Text = "Không xóa được chương trình trên máy chủ";
                    return;
                }
                if (res.error)
                {
                    if (MessageInfo.MessInfoCode.ContainsKey(res.status))
                    {
                        BtnOk.IsEnabled = true;
                        TblInfo.Text = MessageInfo.MessInfoCode[res.status];
                        return;
                    }
                }

                if (_viewmode.Programs.Contains(item))
                {
                    _viewmode.Programs.Remove(item);
                }

                //DialogResult = true;
                //this.Close();
            }
        }

        #region Task
        public async Task<ShortProgrammMessage> GetListProgramFromtoServer()
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getlistprogram"];

                var request = new RestRequest(reUrl, Method.GET);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<ShortProgrammMessage>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("load all user : " + ex.ToString());
                return null;
            }
        }

        public async Task<ProgramUpdateMessage> GetDetailProgramFromtoServer(int id)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getdetailprogram"];

                var request = new RestRequest(reUrl, Method.GET);
                request.AddHeader("Accept", "application/json");
                request.AddParameter("id", id);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<ProgramUpdateMessage>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("load all user : " + ex.ToString());
                return null;
            }
        }


        public async Task<InfoReturn> DelProgramFromtoServer(int id)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["delprogram"];

                var request = new RestRequest(reUrl, Method.DELETE);
                request.AddHeader("Accept", "application/json");
                request.AddParameter("id", id);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<InfoReturn>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("load all user : " + ex.ToString());
                return null;
            }
        }
        #endregion Task 

        
    }
}
