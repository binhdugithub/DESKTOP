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
using DataFormat = System.Windows.DataFormat;

namespace eVMS.MessageView
{
    /// <summary>
    /// Interaction logic for DeleteAccountScreen.xaml
    /// </summary>
    public partial class DeleteAccountScreen : Window
    {
        #region Variable

        private string _username = string.Empty;
        #endregion

        #region Constructor
        public DeleteAccountScreen()
        {
            InitializeComponent();
        }

        public DeleteAccountScreen(string username) : this()
        {
            _username = username;
        }

        #endregion

        #region Click Button
        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            if (_username !=string.Empty)
            {
                TblInfo.Text = string.Empty;
                BtnOk.IsEnabled = BtnCan.IsEnabled = false;
                FluidProgressBar.Visibility = Visibility.Visible;

                var res = await SendAccountToDatabase(_username);
                BtnOk.IsEnabled = BtnCan.IsEnabled = true;
                FluidProgressBar.Visibility = Visibility.Hidden;
                if (res == null)
                {
                    TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                    return;
                }
                if (res.error)
                {
                    if (MessageInfo.MessInfoCode.ContainsKey(res.status))
                    {
                        //BtnOk.IsEnabled = true;
                        TblInfo.Text = MessageInfo.MessInfoCode[res.status];
                    }
                    else
                    {
                        //BtnOk.IsEnabled = true;
                        TblInfo.Text = "Không thành công";// + ret.description;
                        return;
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
        #endregion

        #region Task
        public async Task<InfoReturn> SendAccountToDatabase(string name)
        {
            try
            {
                string service = Properties.Settings.Default["ServerIp"].ToString() + ":" +
                             Properties.Settings.Default["Port"].ToString();

                if (service == string.Empty)
                    return null;
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["deluser"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.DELETE);
                request.AddHeader("Accept", "application/json");
                request.AddParameter("accountname", name);
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
        }
        #endregion
    }
}
