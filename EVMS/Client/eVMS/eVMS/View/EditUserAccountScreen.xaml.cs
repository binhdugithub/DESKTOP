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
using Role = eVMS.Model.Role;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for EditUserAccountScreen.xaml
    /// </summary>
    public partial class EditUserAccountScreen : Window
    {

        #region Variable
        public event Action<Person> EditAccountEvent;
        public PersonViewModel Model;
        #endregion
        #region Constructors
        public EditUserAccountScreen()
        {
            InitializeComponent();
        }

        public EditUserAccountScreen(PersonViewModel model):this()
        {
            Model = new PersonViewModel();
            Model.Address = model.Address;
            Model.Birthday = model.Birthday;
            Model.Email = model.Email;
            Model.FullName = model.FullName;
            if (String.IsNullOrEmpty(model.Password))
                Model.Password = "1";
            else
                Model.Password = Utils.RijndaelSimple.Decrypt(model.Password);

            //Model.Person = model.Person;
            Model.Phone = model.Phone;
            Model.RoleId = model.RoleId;
            Model.RoleName = model.RoleName;
            Model.Sex = model.Sex;
            Model.Username = model.Username;
            Model.Vms = model.Vms;
            this.DataContext = Model;
            CbxSex.ItemsSource = new List<string> {"Nam", "Nữ"};
            Loaded += EditUserAccountScreen_Loaded;
        }

        void EditUserAccountScreen_Loaded(object sender, RoutedEventArgs e)
        {
            GetListRole();
        }
        #endregion

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

            DateTime birth = DateTime.Today;
            if (DpBirth.SelectedDate != null)
                birth = (DateTime) DpBirth.SelectedDate;

            int sexrole = 0;
            if (CbxSex.SelectedItem.ToString() == "Nam")
                sexrole = 1;
            var addnewMess = new AddnewUserMessaget()
            {
                birthday = birth,
                fullname = TbFullname.Text,
                password = Utils.RijndaelSimple.Encrypt(TbPass.Text),
                phone = TbPhone.Text,
                sex = sexrole,
                roleid = (CbxRole.SelectedItem as Role).roleid,
                email = TbEmail.Text,
                currenttime = DateTime.Now,
                username = TbAccountName.Text,
                address = TbAddress.Text

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
                Log4Net.Log.Error("Parse error: " + ex);
            }
            FluidProgressBar.Visibility = Visibility.Visible;
            BtnOk.IsEnabled = false;
            var res = await SendEditedAccounttoServer(json);
            FluidProgressBar.Visibility = Visibility.Hidden;
            BtnOk.IsEnabled = true;

            if (res == null)
            {
                BtnOk.IsEnabled = true;
                TblInfo.Text = "Không tạo kết nối được máy chủ";
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

            if (EditAccountEvent != null &&! res.error)
            {
                EditAccountEvent(per);
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
            //
            try
            {
                var items = res.rolelist.Where(x => x.name == Model.RoleName).ToList();
                if (items.Count > 0)
                    CbxRole.SelectedItem = items[0];
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error(ex);
            }
            
        }
        #region Task
        public async Task<InfoReturn> SendEditedAccounttoServer(string jsonPersonAccount)
        {
            try
            {
                if (ServerSettingDefine.Service == string.Empty)
                    return null;
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["addnewuser"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.PUT);
                request.RequestFormat = RestSharp.DataFormat.Json;
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
    }
}
