using System;
using System.Collections.Generic;
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
using eVMS.MessageView;
using eVMS.Model;
using eVMS.Utils;
using eVMS.ViewModel;
namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for AdminUser.xaml
    /// </summary>
    public partial class AdminUser : UserControl
    {
        #region Variable
        private UserAdministratorViewModel _userAdministratorViewModel;
        #endregion
        #region Constructors
        public AdminUser()
        {
            InitializeComponent();
            Loaded += AdminUser_Loaded;
            _userAdministratorViewModel = new UserAdministratorViewModel();
            DataContext = _userAdministratorViewModel;
        }

        public AdminUser(UserAdministratorViewModel datacontext):this()
        {
            _userAdministratorViewModel = datacontext;
            DataContext = _userAdministratorViewModel;
            _userAdministratorViewModel.InitTemp();
        }

        void AdminUser_Loaded(object sender, RoutedEventArgs e)
        {

        }
        #endregion

        #region Method
        private void DgUsers_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (dgUsers.SelectedItem == null)
            {
                _userAdministratorViewModel.IsSelectItem = false;
                _userAdministratorViewModel.SelectionItem = null;
            }
            else
            {
                _userAdministratorViewModel.IsSelectItem = true;
                _userAdministratorViewModel.SelectionItem = dgUsers.SelectedItem as PersonViewModel;    
            }
            
        }
        #region Add new
        private void AddnewUserButton_OnClick(object sender, RoutedEventArgs e)
        {
            AddUserScreen add = new AddUserScreen();
            add.AddNewEvent += AddNewEvent;
            add.Owner= System.Windows.Window.GetWindow(this);
            add.ShowDialog();

        }

        void AddNewEvent(Model.Person obj)
        {
            _userAdministratorViewModel.AllUserItem.Add(new PersonViewModel()
            {
                FullName = obj.FullName,
                Birthday = obj.Birthday,
                Phone = obj.Phone,
                RoleId = obj.RoleId,
                RoleName = obj.RoleName,
                Sex = obj.Sex,
                Vms = obj.Vms,
                Username = obj.Username,
                Address = obj.Address,
                Email = obj.Email,
                Password = obj.Password
            });
        }
        #endregion

        #region Del
        /// <summary>
        /// Unselect the item after once item was removed in list
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteUserButton_OnClick(object sender, RoutedEventArgs e)
        {
            if(dgUsers.SelectedItem == null)
                return;

            var item = dgUsers.SelectedItem as PersonViewModel;

            if (item.Username == Utils.Account.AccountName)
            {
                MessageBox.Show("Không xóa được tài khoản đang sử dụng",
                    "Thông báo");
                return;
            }

            var deleteDialog = new DeleteAccountScreen(item.Username);
            deleteDialog.Owner = System.Windows.Window.GetWindow(this);
            deleteDialog.ShowDialog();
            if (deleteDialog.DialogResult.HasValue && deleteDialog.DialogResult.Value)
            {
                if (_userAdministratorViewModel.AllUserItem.Contains(item))
                {
                    _userAdministratorViewModel.AllUserItem.Remove(item);
                    //if (dgUsers.SelectedItem == null)
                    //{
                    //    _userAdministratorViewModel.SelectionItem = null;
                    //    _userAdministratorViewModel.IsSelectItem = false;
                    //}
                }
            }
        }

        #endregion
        #region Edit
        private void EditUserButton_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (dgUsers.SelectedItem == null)
            {
                _userAdministratorViewModel.SelectionItem = null;
                _userAdministratorViewModel.IsSelectItem = false;
                return;
            }
            
            var item = dgUsers.SelectedItem as PersonViewModel;
            if (item.Username == Utils.Account.AccountName)
            {
                MessageBox.Show("Không sửa được tài khoản đang sử dụng",
                    "Thông báo");
                return;
            }
            var editItemScreen = new EditUserAccountScreen(item);

            editItemScreen.Owner = System.Windows.Window.GetWindow(this);
            editItemScreen.EditAccountEvent += editItemScreen_EditAccountEvent;
            editItemScreen.ShowDialog();
        }

        void editItemScreen_EditAccountEvent(Model.Person obj)
        {
            if(obj == null)
                return;
            string rolename = string.Empty;
            
            var perModel = new PersonViewModel()
            {
                FullName = obj.FullName,
                Address = obj.Address,
                Birthday = obj.Birthday,
                Email = obj.Email,
                Password = obj.Password,
                Phone = obj.Phone,
                RoleId = obj.RoleId,
                RoleName = obj.RoleName,
                Sex = obj.Sex,
                Username = obj.Username
            };
            try
            {

                var item =
                _userAdministratorViewModel.AllUserItem.Where(
                    x => x.Username == _userAdministratorViewModel.SelectionItem.Username).FirstOrDefault();
                if(item == null)
                    return;
                var index = _userAdministratorViewModel.AllUserItem.IndexOf(item);
                if (index >= 0)
                {
                    _userAdministratorViewModel.AllUserItem[index] = perModel;
                }
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("Edit item button click: "+ ex);
            }
        }
        #endregion Edit

        #region Assign
        private void SettingUserButton_OnClick(object sender, RoutedEventArgs e)
        {
            var per = dgUsers.SelectedItem as PersonViewModel;
            //if(per.Vms.Count==0)
            //    per.Vms.Add(new Vms(){VmsId = 1});
            if (per.RoleId == 0)
            {
                MessageBox.Show("Tài khoản admin,không cần phân bố");
                return;
            }
            var assignVms = new AsignVmsToUserScreen(per);
            assignVms.Owner = System.Windows.Window.GetWindow(this);
            assignVms.ShowDialog();
        }
        #endregion Assign
        #endregion


    }
}
