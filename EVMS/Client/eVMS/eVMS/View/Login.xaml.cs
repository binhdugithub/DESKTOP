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
using MahApps.Metro.Controls;
using Newtonsoft.Json;
using RestSharp;
using DataFormat = RestSharp.DataFormat;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        public Login()
        {
            InitializeComponent();
            log4net.Config.XmlConfigurator.Configure();
        }

        #region Event Object
        private void OnPasswordChanged(object sender, RoutedEventArgs e)
        {
            PasswordBox pb = sender as PasswordBox;
            if(!string.IsNullOrEmpty(pb.Password))
            {
                pb.Tag = string.Empty;
            }
            else
            {
                pb.Tag = "Password";

            }
        }

        private void Expander_OnExpanded(object sender, RoutedEventArgs e)
        {
            this.Height += 150;
        }

        private void Expander_OnCollapsed(object sender, RoutedEventArgs e)
        {
            this.Height -= 150;
        }


        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
        private async void BtnLogin_OnClick(object sender, RoutedEventArgs e)
        {
            if(!CheckValidation())
                return;

            
            if (Properties.Settings.Default["ServerIp"].ToString() == string.Empty  ||
                Properties.Settings.Default["Port"].ToString() == string.Empty)
            {
                TblInfo.Text = ErrorInfoVi.CheckingServerConnect;
                return;
            }
            //string service = Properties.Settings.Default["ServerIp"].ToString() + ":" +
            //                 Properties.Settings.Default["Port"].ToString();
            BtnLogin.IsEnabled = false;
            FluidProgressBar.Visibility = Visibility.Visible;
            ServerSettingDefine.Service = "http://" + Properties.Settings.Default["ServerIp"].ToString() + ":" +
                             Properties.Settings.Default["Port"].ToString();
            var res = await CheckAccounInDb(TbName.Text, PbPass.Password, ServerSettingDefine.Service);
            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnLogin.IsEnabled = true;
            if (res == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }
            if (res.error)
            {
                if (MessageInfo.MessInfoCode.ContainsKey(res.status))
                {
                    TblInfo.Text = MessageInfo.MessInfoCode[res.status];
                    return;
                }
            }
            Account.AccountName = TbName.Text;
            //if (Account.AccountName == "admin")
            //    Account.AccountRole = Role.Admin;
            //else
            //    Account.AccountRole = Role.User;

            int role = -1;
            int.TryParse(res.description, out role);
            if (res.description == "0")
                Account.AccountRole = Role.Admin;
            else
                Account.AccountRole = Role.User;

            //Account.AccountRole = Role.Admin;
            Log4Net.Log.Info("Login Success");
            //
            MainWindow main = new MainWindow();
            this.Close();
            main.Activate();
            main.Show();
        }
        #endregion

        #region Method

        public bool CheckValidation()
        {
            if (TbName.Text == string.Empty || PbPass.Password == string.Empty)
            {
                TblInfo.Text = "Nhập tài khoản và mật khẩu";
                    return false;
            }
            return true;
        }

        public bool IsValidIP(string addr)
        {
            if (String.IsNullOrEmpty(addr))
                return false;
            string[] parts = addr.Split('.');
            if (parts.Length < 4)
            {
                // not a IPv4 string in X.X.X.X format
                return false;
            }
            else
            {
                foreach (string part in parts)
                {
                    byte checkPart = 0;
                    if (!byte.TryParse(part, out checkPart))
                    {
                        return false;
                    }
                }
                return true;
            }
            return true;
        }

        #endregion

        #region Task
        public async Task<InfoReturn> CheckAccounInDb(string name, string pas, string service)
        {
            //var en = new ReceiptExpanseDBEntities1();
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["login"] + "?" + "pass=" + Utils.RijndaelSimple.Encrypt(pas);
                var request = new RestRequest(reUrl, Method.GET);
                request.AddParameter("username", name); // adds to POST or URL querystring based on Method
                //request.AddParameter("pass", Utils.RijndaelSimple.Encrypt(pas));
                //request.RequestFormat =DataFormat.Json;
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
                Log4Net.Log.Error("login : " + ex.ToString());
                return null;
            }

            return null;
        }
        #endregion

        private void BtnCheckServerIp_OnClick(object sender, RoutedEventArgs e)
        {
            
        }

        private void BtnSaveServerIp_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (!IsValidIP(TbIp.Text))
            {
                TblInfo.Text = "Kiểm tra lại địa chỉ máy chủ";
                return;
            }
            int port = 0;
            if (!int.TryParse(TbPort.Text, out port))
            {
                TblInfo.Text = "Kiểm tra lại cổng";
                return;
            }
            Properties.Settings.Default.Save();
        }
    }
}
