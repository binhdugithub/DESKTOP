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
using System.Windows.Navigation;
using System.Windows.Shapes;
using eVMS.Jsoncontract;
using eVMS.Utils;
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.MessageView
{
    /// <summary>
    /// Interaction logic for SaveTemplateDialog.xaml
    /// </summary>
    public partial class SaveTemplateDialog : Window
    {
        private ProgramMessage _program = null;
        private bool _update = false;
        private int _proId = -1;
        #region Constructor
        public SaveTemplateDialog()
        {
            InitializeComponent();
        }

        public SaveTemplateDialog(ProgramMessage program, bool update,int proId):this()
        {
            _program = program;
            _update = update;
            _proId = proId;
        }
        #endregion

       

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (TbName.Text == string.Empty)
            {
                TblInfo.Text = "Nhập tên";
                return;
            }
            if(_program == null)
                return;
            _program.name = TbName.Text;
            _program.type = 0;
            string json = JsonConvert.SerializeObject(_program);
            BtnOk.IsEnabled = false;
            FluidProgressBar.Visibility = Visibility.Visible;
            InfoReturn ret = null;
            if (!_update)
            {
                ret = await SaveProgramToDatabase(json);    
            }
            else
            {
                ProgramUpdateMessage updamMessage = new ProgramUpdateMessage();
                updamMessage.content = _program.content;
                updamMessage.height = _program.height;
                updamMessage.width = _program.width;
                updamMessage.type = _program.type;
                updamMessage.name = _program.name;
                updamMessage.id = _proId;
                json = JsonConvert.SerializeObject(updamMessage);
                ret = await UpdateProgramToDatabase(json);  
            }
            

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

        #region Task
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

        public async Task<InfoReturn> UpdateProgramToDatabase(string json)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["updateprogam"];
                reUrl += string.Format("?username={0}", Account.AccountName);
               // var request = new RestRequest(reUrl+"?id={id}", Method.PUT);
                var request = new RestRequest(reUrl, Method.PUT);
                //request.RequestFormat = RestSharp.DataFormat.Json;
                request.AddHeader("Accept", "application/json");
               // request.AddHeader("Content-type", "application/json");
                
                //request.AddUrlSegment("id", _vmsid.ToString());
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
        #endregion
    }
}
