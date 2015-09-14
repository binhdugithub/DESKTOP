using System;
using System.Collections.Generic;
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
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.MessageView
{
    /// <summary>
    /// Interaction logic for DeleteVmsScreen.xaml
    /// </summary>
    public partial class DeleteVmsScreen : Window
    {
        #region Variable

        private int _vmsId = -1;
        #endregion
        public DeleteVmsScreen()
        {
            InitializeComponent();
        }

        public DeleteVmsScreen(int vmsId)
            : this()
        {
            _vmsId = vmsId;
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            if (_vmsId != -1)
            {
                TblInfo.Text = string.Empty;
                BtnOk.IsEnabled = BtnCan.IsEnabled = false;
                FluidProgressBar.Visibility = Visibility.Visible;

                var res = await SendVmsToDatabase(_vmsId);
                BtnOk.IsEnabled = BtnCan.IsEnabled = true;
                FluidProgressBar.Visibility = Visibility.Hidden;
                if (res == null)
                {
                    BtnOk.IsEnabled = true;
                    TblInfo.Text = "Không xóa được vms trên máy chủ";
                    return;
                }
                if (res.error)
                {
                    if (MessageInfo.MessInfoCode.ContainsKey(res.status))
                    {
                        BtnOk.IsEnabled = true;
                        TblInfo.Text = MessageInfo.MessInfoCode[res.status];
                        
                    }
                    else
                    {
                        //BtnOk.IsEnabled = true;
                        TblInfo.Text = "Không thành công";// + ret.description;
                        //return;
                    }
                    return;
                }

                DialogResult = true;
                this.Close();
            }
        }

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
            this.Close();
        }

        #region Task
        public async Task<InfoReturn> SendVmsToDatabase(int vmsId)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["delvms"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.DELETE);
                request.AddHeader("Accept", "application/json");
                request.AddParameter("vmsid", vmsId);
                // var response = await client.ExecutePostTaskAsync(request);
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
                Log4Net.Log.Error("json converter error:" + ex);
                return null;
            }

            return null;
        }
        #endregion
    }
}
