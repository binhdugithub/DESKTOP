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
using Microsoft.Win32;
using Newtonsoft.Json;
using RestSharp;
using DataFormat = RestSharp.DataFormat;
using Role = eVMS.Model.Role;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for AddUserScreen.xaml
    /// </summary>
    public partial class AddUserScreen : Window
    {
        public event Action<Person> AddNewEvent;
        //string service = Properties.Settings.Default["ServerIp"].ToString() + ":" +
        //                     Properties.Settings.Default["Port"].ToString();
        public AddUserScreen()
        {
            InitializeComponent();
            CbxSex.ItemsSource = new List<string> { "Nam", "Nữ" };
            //CbxRole.ItemsSource = new List<Role>
            //{
            //    new Role(){RoleId = 1,RoleName = "Administrator"},
            //    new Role(){RoleId = 2,RoleName = "User"}
            //};
            Loaded += AddUserScreen_Loaded;
        }

        void AddUserScreen_Loaded(object sender, RoutedEventArgs e)
        {
            GetListRole();
        }

        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private async void BtnOk_OnClick(object sender, RoutedEventArgs e)
        {

            TblInfo.Text = string.Empty;
            if (TbAccountName.Text == string.Empty)
            {
                TblInfo.Text = "Nhập tên người dùng";
                return;
            }
            else
            {
                if (!IsName(TbAccountName.Text))
                {
                    TblInfo.Text = "Kiểm tra tên người dùng";
                    return;
                }
            }
            if (TbFullname.Text == string.Empty)
            {
                TblInfo.Text = "Nhập đầy đủ tên người dùng";
                return;
            }
            else
            {
                if (!StringUtil.IsFullName(TbFullname.Text))
                {
                    TblInfo.Text = "Kiểm tra tên đầy đủ người dùng";
                    return;
                }
            }

            if (TbPass.Text == string.Empty)
            {
                TblInfo.Text = "Nhập mật khẩu người dùng";
                return;
            }
            if (TbPhone.Text != string.Empty)
            {
                float phone = 0;
                if (!float.TryParse(TbPhone.Text, out phone))
                {
                    TblInfo.Text = "Nhập lại số điện thoại";
                    return;
                }
            }
            if (CbxSex.SelectedItem == null)
            {
                TblInfo.Text = "Chọn giới tính người dùng";
                return;
            }

            if (CbxRole.SelectedItem == null)
            {
                TblInfo.Text = "Chọn quyền hạn người dùng";
                return;
            }
            if (TbEmail.Text != string.Empty)
            {
                if (!IsEmail(TbEmail.Text))
                {
                    TblInfo.Text = "Nhập lại Email";
                    return;
                }
            }

            FluidProgressBar.Visibility = Visibility.Visible;
            TblInfo.Text = string.Empty;
            BtnOk.IsEnabled = false;
            DateTime birth = DateTime.Today;
            if (DpBirth.SelectedDate != null)
                birth = (DateTime)DpBirth.SelectedDate;
            int sexrole = 0;
            if (CbxSex.SelectedItem.ToString() == "Nam")
                sexrole = 1;
            var addnewMess= new AddnewUserMessaget()
            {
                birthday = birth,
                fullname = TbFullname.Text,
                address = TbAddress.Text,
                //password = Utils.Account.CalculateMD5Hash(TbPass.Text),
                password = Utils.RijndaelSimple.Encrypt(TbPass.Text),
                phone = TbPhone.Text,
                sex = sexrole,
                roleid = (CbxRole.SelectedItem as Role).roleid,
                email = TbEmail.Text,
                currenttime = DateTime.Now,
               username = TbAccountName.Text
                
            };

            var per = new Person()
            {
                Birthday = birth,
                FullName = TbFullname.Text,
                Password = Utils.RijndaelSimple.Encrypt(TbPass.Text),
                Phone = TbPhone.Text,
                Sex = CbxSex.SelectedItem.ToString(),
                RoleId = (CbxRole.SelectedItem as Role).roleid,
                RoleName = (CbxRole.SelectedItem as Role).name,
                Email = TbEmail.Text,
                Username = TbAccountName.Text,
                Address = TbAddress.Text

            };

            string json = string.Empty;
            try
            {
                json = JsonConvert.SerializeObject(addnewMess);
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("Parse error: "+ ex);
            }
            var res = await SendAccounttoServer(json);

            FluidProgressBar.Visibility = Visibility.Hidden;
            if (res == null)
            {
                BtnOk.IsEnabled = true;
                TblInfo.Text = "Không tạo được tài khoản trên máy chủ";
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

            if (AddNewEvent != null)
            {
                AddNewEvent(per);
            }
            this.Close();
        }

        public bool IsEmail(string email)
        {
            Regex myRegularExpression = new
                            Regex(@"^[a-zA-Z][\w\.-]*[a-zA-Z0-9]@[a-zA-Z0-9][\w\.-]*[a-zA-Z0-9]\.[a-zA-Z][a-zA-Z\.]*[a-zA-Z]$");

            if (myRegularExpression.IsMatch(email))
            {
                return true;
            }
            return false;

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

        //public bool IsFullName(string name)
        //{
        //    Regex myRegularExpression = new
        //                   Regex(@"^[a-zA-Z0-9 ]*$");

        //    if (myRegularExpression.IsMatch(name))
        //    {
        //        return true;
        //    }
        //    return false;
        //}

        public async void GetListRole()
        {
            FluidProgressBar.Visibility = Visibility.Visible;
            TblInfo.Text = string.Empty;
            BtnOk.IsEnabled = false;
            var res = await GetListRoleFromServer();

            FluidProgressBar.Visibility = Visibility.Hidden;
            if (res == null)
            {
                BtnOk.IsEnabled = true;
                return;
            }
            BtnOk.IsEnabled = true;
            CbxRole.ItemsSource = res.rolelist;
        }

        #region Task
        public async Task<InfoReturn> SendAccounttoServer(string jsonPersonAccount)
        {
            //var en = new ReceiptExpanseDBEntities1();
            try
            {
                if (ServerSettingDefine.Service == string.Empty)
                    return null;
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["addnewuser"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.POST);
                request.RequestFormat = DataFormat.Json;
                request.AddHeader("Accept", "application/json");
                request.AddParameter("application/json", jsonPersonAccount, ParameterType.RequestBody);
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


        public async Task<RoleList> GetListRoleFromServer()
        {
            //var en = new ReceiptExpanseDBEntities1();
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getrole"];
                var request = new RestRequest(reUrl, Method.GET);

                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<RoleList>(ok);
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

        private void CbxRole_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var item = CbxRole.SelectedItem;

        }
    }
}
