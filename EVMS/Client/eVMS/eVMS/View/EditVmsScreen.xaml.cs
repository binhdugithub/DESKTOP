using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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
    /// Interaction logic for EditVmsScreen.xaml
    /// </summary>
    public partial class EditVmsScreen : Window
    {

        #region Variable

        private VmsViewModel _viewModel;
        public event Action<Vms> EditVmsEvent;
        #endregion
        #region Constructor
        public EditVmsScreen()
        {
            InitializeComponent();
        }
        public EditVmsScreen(VmsViewModel vmsModel):this()
        {
            //_viewModel = vmsModel;
            _viewModel = new VmsViewModel();
            _viewModel.Description = vmsModel.Description;
            _viewModel.DeviceId = vmsModel.DeviceId;
            _viewModel.Height = vmsModel.Height;
            _viewModel.Ip = vmsModel.Ip;
            _viewModel.Location = vmsModel.Location;
            _viewModel.Model = vmsModel.Model;
            _viewModel.Port = vmsModel.Port;
            _viewModel.Status = vmsModel.Status;
            _viewModel.VmsId = vmsModel.VmsId;
            _viewModel.Vmsname = vmsModel.Vmsname;
            _viewModel.Vmstypes = vmsModel.Vmstypes;
            _viewModel.Width = vmsModel.Width;
            TbPort.Text = _viewModel.Port.ToString();
            DataContext = _viewModel;
            Loaded += EditVmsScreen_Loaded;
        }

        void EditVmsScreen_Loaded(object sender, RoutedEventArgs e)
        {
            GetVmsModelList();
        }

        public async void GetVmsModelList()
        {
            FluidProgressBar.Visibility = Visibility.Visible;

            BtnOk.IsEnabled = false;
            var res = await GetVmsModelListFromtoServer();

            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnOk.IsEnabled = true;
            if (res == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }
            BtnOk.IsEnabled = true;
            CbxModel.ItemsSource = res.vmsmodels;
            //Set model current
            var items = res.vmsmodels.Where(x => x.modelname == _viewModel.Model).ToList();
            if (items.Count > 0)
            {
                CbxModel.SelectedItem = items[0];
            }
            //End


        }

        #endregion

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {

            if (TbName.Text == string.Empty)
            {
                TblInfo.Text = "Nhập tên vms";
                return;
            }
            else
            {
                if (!StringUtil.IsFullName(TbName.Text))
                {
                    TblInfo.Text = "Kiểm tra tên vms";
                    return;
                }
            }

            if (TbLocation.Text == string.Empty)
            {
                TblInfo.Text = "Nhập vị trí vms";
                return;
            }
            if (TbDescription.Text == string.Empty)
            {
                TblInfo.Text = "Mô tả vms";
                return;
            }
            if (TbIp.Text == string.Empty)
            {
                TblInfo.Text = "Nhập lại địa chỉ Ip";
                return;
            }
            else
            {
                if (!IsValidIP(TbIp.Text))
                {
                    TblInfo.Text = "Nhập lại địa chỉ Ip";
                    return;
                }
            
            }

            int porttemp = 0;
            if (!int.TryParse(TbPort.Text, out porttemp))
            {
                TblInfo.Text = "Nhập cổng";
                return;
            }
            else
            {
                
            }

            //float wi, he = 0;// wi,he validate
            //if (!float.TryParse(Tbwidth.Text, out wi))
            //{
            //    TblInfo.Text = "Nhập lại chiều rộng";
            //    return;
            //}
            //if (!float.TryParse(Tbheight.Text, out he))
            //{
            //    TblInfo.Text = "Nhập lại chiều cao";
            //    return;
            //}

            if (CbxModel.SelectedItem == null)
            {
                TblInfo.Text = "Chọn Model";
                return;
            }

            if (String.IsNullOrEmpty(Tbheight.Text))
            {
                TblInfo.Text = "Chiều cao không đúng";
                return;
            }

            if (String.IsNullOrEmpty(Tbwidth.Text))
            {
                TblInfo.Text = "Chiều rộng không đúng";
                return;
            }

            var vms = new Vms()
            {
                name = TbName.Text,
                location = TbLocation.Text,
                description = TbDescription.Text,
                id = _viewModel.VmsId,
                height = Tbheight.Text,
                width = Tbwidth.Text,
                deviceid = (CbxModel.SelectedItem as Vmsmodel).deviceid,
                model = (CbxModel.SelectedItem as Vmsmodel).modelname,
                multitype = (CbxModel.SelectedItem as Vmsmodel).vmstype,
                ip = TbIp.Text,
                port = porttemp
                //model = TbModel.Text
            };

            FluidProgressBar.Visibility = Visibility.Visible;
            var res = await SendEditedVmstoServer(vms);
            FluidProgressBar.Visibility = Visibility.Hidden;

            FluidProgressBar.Visibility = Visibility.Hidden;
            if (res == null)
            {
                BtnOk.IsEnabled = true;
                TblInfo.Text = "Không cập nhật được vms trên máy chủ";
                return;
            }
            if (res.error)
            {
                if (MessageInfo.MessInfoCode.ContainsKey(res.status))
                {
                    BtnOk.IsEnabled = true;
                    TblInfo.Text = MessageInfo.MessInfoCode[res.status];
                    
                }
                return;
            }
            if (EditVmsEvent != null)
            {
                EditVmsEvent(vms);
            }
            this.Close();
        }

        public bool IsName(string name)
        {
            Regex myRegularExpression = new
                           Regex(@"^(?=[a-zA-Z])[-\w.]{0,23}([a-zA-Z\d]|(?<![-.])_)$");

            if (myRegularExpression.IsMatch(name))
            {
                return true;
            }
            return false;
        }

        public bool IsValidIP(string addr)
        {
            //create our match pattern
//            string pattern = @"^([1-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(\.
//([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3}$";
//            //create our Regular Expression object
//            Regex check = new Regex(pattern);
//            //boolean variable to hold the status
//            bool valid = false;
//            //check to make sure an ip address was provided
//            if (addr == "")
//            {
//                //no address provided so return false
//                valid = false;
//            }
//            else
//            {
//                //address provided so use the IsMatch Method
//                //of the Regular Expression object
//                valid = check.IsMatch(addr, 0);
//            }
//            //return the results
//            return valid;
            if(String.IsNullOrEmpty(addr))
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

        #region Task

        public async Task<VmsDeviceMessage> GetVmsModelListFromtoServer()
        {
            //var en = new ReceiptExpanseDBEntities1();
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getvmsmodellist"];
                var request = new RestRequest(reUrl, Method.GET);

                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<VmsDeviceMessage>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("login : " + ex.ToString());
                return null;
            }

            return null;
        }
        public async Task<InfoReturn> SendEditedVmstoServer(Vms vms)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string jsonstring = JsonConvert.SerializeObject(vms);
                string reUrl = ConfigurationManager.AppSettings["updatevms"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.PUT);
                request.RequestFormat = RestSharp.DataFormat.Json;
                request.AddHeader("Accept", "application/json");
                request.AddParameter("application/json", jsonstring, ParameterType.RequestBody);
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

        private void CbxModel_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            var item = (CbxModel.SelectedItem as Vmsmodel);
            Tbheight.Text = item.height;
            Tbwidth.Text = item.width;
            dgVms.ItemsSource = item.vmstype;
        }
        
    }
}
