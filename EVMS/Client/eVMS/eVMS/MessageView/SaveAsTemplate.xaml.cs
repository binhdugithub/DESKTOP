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
    /// Interaction logic for SaveAsTemplate.xaml
    /// </summary>
    public partial class SaveAsTemplate : Window
    {
        private ProgramMessage _program = null;
        public SaveAsTemplate()
        {
            InitializeComponent();
        }

        public SaveAsTemplate(ProgramMessage program)
            : this()
        {
            _program = program;
            if (Account.AccountRole == Role.User)
                RdProgrram.IsEnabled = false;
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (TbName.Text == string.Empty)
            {
                TblInfo.Text = "Nhập tên";
                return;
            }
            if (_program == null)
                return;
            _program.name = TbName.Text;
            if(RdProgrram.IsChecked == true) 
                _program.type = 0;
            else
                _program.type = 1;

            string json = JsonConvert.SerializeObject(_program);
            BtnOk.IsEnabled = false;
            FluidProgressBar.Visibility = Visibility.Visible;
            InfoReturn ret = null;

            ret = await SaveProgramToDatabase(json);

            BtnOk.IsEnabled = true;
            FluidProgressBar.Visibility = Visibility.Hidden;

            if (ret == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }
            if (ret.error)
            {

                if (MessageInfo.MessInfoCode.ContainsKey(ret.status))
                {
                    //BtnOk.IsEnabled = true;
                    TblInfo.Text = MessageInfo.MessInfoCode[ret.status];
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

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            
        }

        public async Task<InfoReturn> SaveProgramToDatabase(string json)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["saveprogam"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.POST);
                request.AddHeader("Accept", "application/json");

                request.AddParameter("application/json", json, ParameterType.RequestBody);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var val = JsonConvert.DeserializeObject<InfoReturn>(ok);
                return val;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("json converter error:" + ex);
                return null;
            }
        }
    }
}
