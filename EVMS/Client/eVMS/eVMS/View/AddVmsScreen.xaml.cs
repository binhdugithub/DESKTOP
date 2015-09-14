using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Linq;
using System.Linq.Expressions;
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
using Newtonsoft.Json;
using RestSharp;
using DataFormat = System.Windows.DataFormat;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for AddVmsScreen.xaml
    /// </summary>
    public partial class AddVmsScreen : Window, INotifyPropertyChanged
    {
        public event Action<Vms> AddNewVmsEvent;
        private Vmsmodel _viewModel;

        public Vmsmodel ViewModel
        {
            get { return _viewModel; }
            set {
                if (_viewModel != value)
                {
                    _viewModel = value;
                    RaisePropertyChanged(() => ViewModel);
                }
            }
        }
        public AddVmsScreen()
        {
            InitializeComponent();
            ViewModel = new Vmsmodel();
            DataContext = ViewModel;
            Loaded += AddVmsScreen_Loaded;
        }

        void AddVmsScreen_Loaded(object sender, RoutedEventArgs e)
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
        }

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
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
                TblInfo.Text = "Địa chỉ Ip";
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

            int port = 0;
            if (!int.TryParse(TbPort.Text, out port))
            {
                TblInfo.Text = "Nhập cổng";
                return;
            }

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

            //float wi, he = 0;// wi,he validate
            //if (!float.TryParse(Tbwidth.Text, out wi))
            //{
            //    TblInfo.Text = "Nhập lại chiều rộng";
            //    return;
            //}
            //if(!float.TryParse(Tbheight.Text, out he))
            //{
            //    TblInfo.Text = "Nhập lại chiều cao";
            //    return;
            //}

            

            var vms = new Vms()
            {
                name = TbName.Text,
                location = TbLocation.Text,
                description = TbDescription.Text,
                status = false,
                height = Tbheight.Text,
                width = Tbwidth.Text,
                deviceid = (CbxModel.SelectedItem as Vmsmodel).deviceid,
                model = (CbxModel.SelectedItem as Vmsmodel).modelname,
                multitype = (CbxModel.SelectedItem as Vmsmodel).vmstype,
                ip=TbIp.Text,
                port = port
            };

            FluidProgressBar.Visibility = Visibility.Visible;
            TblInfo.Text = string.Empty;
            BtnOk.IsEnabled = false;
            var res = await SendVmsAccounttoServer(vms);

            FluidProgressBar.Visibility = Visibility.Hidden;
            if (res == null)
            {
                BtnOk.IsEnabled = true;
                TblInfo.Text = "Không tạo được vms trên máy chủ";
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
                    BtnOk.IsEnabled = true;
                    TblInfo.Text = res.description;
                }
                return;
            }
            int vmsid = -1;
            int.TryParse(res.description, out vmsid);
            vms.id = vmsid;

            if (AddNewVmsEvent != null)
            {
                AddNewVmsEvent(vms);
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

        #region Task
        public async Task<InfoReturn> SendVmsAccounttoServer(Vms vms)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string jsonstring = JsonConvert.SerializeObject(vms);
                string reUrl = ConfigurationManager.AppSettings["addnewvms"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.POST);
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
        #endregion

        private void CbxModel_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (CbxModel.SelectedItem as Vmsmodel == null)
                return;
            TblInfo.Text = string.Empty;

            Tbwidth.Text = (CbxModel.SelectedItem as Vmsmodel).width;
            Tbheight.Text = (CbxModel.SelectedItem as Vmsmodel).height;

            dgVms.ItemsSource = (CbxModel.SelectedItem as Vmsmodel).vmstype;
        }


        #region Events

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        #region Event Handlers

        /// <summary>
        /// Get name of property
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="e"></param>
        /// <returns></returns>
        public static string GetPropertyName<T>(Expression<Func<T>> e)
        {
            var member = (MemberExpression)e.Body;
            return member.Member.Name;
        }
        /// <summary>
        /// Raise when property value propertychanged or override propertychage
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="propertyExpression"></param>
        protected virtual void RaisePropertyChanged<T>(Expression<Func<T>> propertyExpression)
        {
            RaisePropertyChanged(GetPropertyName(propertyExpression));
        }
        /// <summary>
        /// Raise when property value propertychanged
        /// </summary>
        /// <param name="propertyName"></param>
        protected void RaisePropertyChanged(String propertyName)
        {
            PropertyChangedEventHandler temp = PropertyChanged;
            if (temp != null)
            {
                temp(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
