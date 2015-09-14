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
    /// Interaction logic for AsignVmsToUserScreen.xaml
    /// </summary>
    public partial class AsignVmsToUserScreen : Window
    {
        #region Mems

        private AssignVmsViewModel _assignVmsViewModel = null;
        private PersonViewModel personViewModel;
        #endregion
        public AsignVmsToUserScreen()
        {
            InitializeComponent();
        }


        public AsignVmsToUserScreen(PersonViewModel per):this()
        {
            personViewModel = per;
            Loaded += AsignVmsToUserScreen_Loaded;
            DataContext = _assignVmsViewModel;
        }

        void AsignVmsToUserScreen_Loaded(object sender, RoutedEventArgs e)
        {
            if (_assignVmsViewModel == null)
            {
                _assignVmsViewModel = new AssignVmsViewModel();
                GetDataVms();
                dgVms.ItemsSource = _assignVmsViewModel.AllVmsItem;
            }
        }

        #region Method Event
        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {
            //Sent the assinged vms to server
            AssignVmsToUserMessage assingMes = new AssignVmsToUserMessage();
            assingMes.VMS = new List<VM>();
            assingMes.username = personViewModel.Username;
            foreach (var assignVmsModel in _assignVmsViewModel.AllVmsItem)
            {
                if(!assignVmsModel.IsSelected)
                    continue;

                var vm = new VM();

                vm.VmsId = assignVmsModel.VmsItem.id.ToString();
                assingMes.VMS.Add(vm);
            }
            string assignMessstring = JsonConvert.SerializeObject(assingMes);
            FluidProgressBar.Visibility = Visibility.Visible;
            BtnOk.IsEnabled = false;
            var res = await SendAssignedVmstoServer(assignMessstring);

            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnOk.IsEnabled = true;

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
                    
                }
                return;
            }
            //end
            personViewModel.Vms.Clear();
            foreach (var assignVmsModel in _assignVmsViewModel.AllVmsItem)
            {
                if (assignVmsModel.IsSelected)
                    personViewModel.Vms.Add(assignVmsModel.VmsItem);
            }
            this.Close();
        }

        #endregion

        #region Async Method

        public async void GetDataVms()
        {
            FluidProgressBar.Visibility = Visibility.Visible;
            BtnOk.IsEnabled = false;

            var res = await GetVmsFromtoServer(Account.AccountName);
            var resUser = await GetVmsFromtoServer(personViewModel.Username);
            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnOk.IsEnabled = true;
            if (res == null || resUser == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }

            if (res.objectlist == null)
            {
                TblInfo.Text = "Không có vms nao cả";
                return;
            }
            else
            {

                foreach (var vmse in res.objectlist)
                {
                    var assign = new AssignVmsModel()
                    {
                        VmsItem = vmse
                        
                    };

                    if (resUser.objectlist != null)
                    {
                        if (resUser.objectlist.Where(x => x.id == vmse.id).FirstOrDefault() != null)
                        {
                            assign.IsSelected = true;
                        }
                        else
                        {
                            assign.IsSelected = false;
                        }
                        
                    }
                    else
                    {
                        assign.IsSelected = false;
                    }
                    _assignVmsViewModel.AllVmsItem.Add(assign);
                }
            }

        }

        #endregion

        #region Task
        public async Task<VmslistMessage> GetVmsFromtoServer(string accountname)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getlistvmsbyuser"];
                //reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.GET);
                request.AddParameter("username", accountname);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<VmslistMessage>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("load all user : " + ex.ToString());
                return null;
            }
        }


        public async Task<InfoReturn> SendAssignedVmstoServer(string assignedVms)
        {
            try
            {
                if (ServerSettingDefine.Service == string.Empty)
                    return null;
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["assignvmstouser"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.PUT);
                request.RequestFormat = RestSharp.DataFormat.Json;
                request.AddHeader("Accept", "application/json");
                request.AddParameter("application/json", assignedVms, ParameterType.RequestBody);
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
        }
        #endregion
    }
}
