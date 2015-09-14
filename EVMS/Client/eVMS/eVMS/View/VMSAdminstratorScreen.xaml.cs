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
using eVMS.Utils;
using eVMS.ViewModel;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for VMSAdminstratorScreen.xaml
    /// </summary>
    public partial class VMSAdminstratorScreen : UserControl
    {

        #region Variable
        private VmsAdministratorViewModel _vmsAdministratorViewModel;

        //private List<String> _vmsCurrentMembersList = new List<string>();
        public event Action<bool> SyncVmsEvent;
        #endregion
        
        #region Constructors
        public VMSAdminstratorScreen()
        {
            InitializeComponent();
            Loaded += VMSAdminstratorScreen_Loaded;
            //_vmsAdministratorViewModel = new VmsAdministratorViewModel();
            //DataContext = _vmsAdministratorViewModel;
        }



        public VMSAdminstratorScreen(VmsAdministratorViewModel datacontext)
            : this()
        {
            _vmsAdministratorViewModel = datacontext;
            //_vmsCurrentMembersList = vmsListName;
            DataContext = _vmsAdministratorViewModel;

            
        }

        public void CheckVMSSyncData()
        {
            //Check data is sync
            //if (!_vmsCurrentMembersList.SequenceEqual(_vmsAdministratorViewModel.VmsOnServerMembersList))
            //{
            //    //Show mess    
            //    MessageBoxResult result1 = MessageBox.Show(ErrorInfoVi.VmsDataNotSync, "Thông báo", MessageBoxButton.YesNo);
            //    if (result1 == MessageBoxResult.Yes)
            //    {
            //        if (SyncVmsEvent != null)
            //            SyncVmsEvent(true);
            //    }
            //}
        }

        void VMSAdminstratorScreen_Loaded(object sender, RoutedEventArgs e)
        {
            
        }
        #endregion


        private void AddnewVmsButton_OnClick(object sender, RoutedEventArgs e)
        {
            var vmsAddnewScreen = new AddVmsScreen();
            vmsAddnewScreen.AddNewVmsEvent += vmsAddnewScreen_AddNewVmsEvent;
            vmsAddnewScreen.Owner = System.Windows.Window.GetWindow(this);
            vmsAddnewScreen.ShowDialog();
        }

        void vmsAddnewScreen_AddNewVmsEvent(Model.Vms obj)
        {
            _vmsAdministratorViewModel.AllVmsItem.Add(new VmsViewModel()
            {
                Vmsname = obj.name,
                Location = obj.location,
                Description = obj.description,
                Status = obj.status,
                Height = obj.height,
                Width = obj.width,
                VmsId = obj.id,
                Ip = obj.ip,
                Port = obj.port,
                DeviceId = obj.deviceid,
                Model = obj.model,
                Vmstypes = obj.multitype

            });
            //if (!_vmsCurrentMembersList.Contains(obj.name))
            //{
            //    _vmsCurrentMembersList.Add(obj.name);
            //    if (!_vmsCurrentMembersList.SequenceEqual(_vmsAdministratorViewModel.VmsOnServerMembersList))
            //    {
            //        //Show mess    
            //        MessageBoxResult result1 = MessageBox.Show(ErrorInfoVi.VmsDataNotSync, "Thông báo", MessageBoxButton.YesNo);
            //        if (result1 == MessageBoxResult.Yes)
            //        {
            //            if (SyncVmsEvent != null)
            //                SyncVmsEvent(true);
            //        }
            //    }
            //}
        }
        
        private void DeleteUserButton_OnClick(object sender, RoutedEventArgs e)
        {
            if (dgVms.SelectedItem == null)
                return;

            var item = dgVms.SelectedItem as VmsViewModel;
            var deleteDialog = new DeleteVmsScreen(item.VmsId);
            deleteDialog.Owner = System.Windows.Window.GetWindow(this);
            deleteDialog.ShowDialog();
            if (deleteDialog.DialogResult.HasValue && deleteDialog.DialogResult.Value)
            {
                if (_vmsAdministratorViewModel.AllVmsItem.Contains(item))
                {
                    _vmsAdministratorViewModel.AllVmsItem.Remove(item);
                    //if (_vmsCurrentMembersList.Contains(item.Vmsname))
                    //    _vmsCurrentMembersList.Remove(item.Vmsname);
                    //if (!_vmsCurrentMembersList.SequenceEqual(_vmsAdministratorViewModel.VmsOnServerMembersList))
                    //{
                    //    //Show mess    
                    //    MessageBoxResult result1 = MessageBox.Show(ErrorInfoVi.VmsDataNotSync, "Thông báo", MessageBoxButton.YesNo);
                    //    if (result1 == MessageBoxResult.Yes)
                    //    {
                    //        if (SyncVmsEvent != null)
                    //            SyncVmsEvent(true);
                    //    }
                    //}
                }
            }
        }

        private void DgUsers_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (dgVms.SelectedItem == null)
            {
                _vmsAdministratorViewModel.IsSelectItem = false;
                _vmsAdministratorViewModel.SelectionItem = null;
            }
            else
            {
                _vmsAdministratorViewModel.IsSelectItem = true;
                _vmsAdministratorViewModel.SelectionItem = dgVms.SelectedItem as VmsViewModel;
            }
        }

        private void EditUserButton_OnClick(object sender, RoutedEventArgs e)
        {
            if (dgVms.SelectedItem == null)
            {
                _vmsAdministratorViewModel.SelectionItem = null;
                _vmsAdministratorViewModel.IsSelectItem = false;
                return;
            }
            var item = dgVms.SelectedItem as VmsViewModel;
            var editItemScreen = new EditVmsScreen(item);

            editItemScreen.Owner = System.Windows.Window.GetWindow(this);
            editItemScreen.EditVmsEvent += editItemScreen_EditVmsEvent;
            editItemScreen.ShowDialog();
        }

        void editItemScreen_EditVmsEvent(Model.Vms obj)
        {
            if (obj == null)
                return;
            var vmsModel = new VmsViewModel()
            {
                Vmsname = obj.name,
                Ip = obj.ip,
                Port = obj.port,
                Location = obj.location,
                Description = obj.description,
                Status = obj.status,
                Height = obj.height,
                Width = obj.width,
                VmsId = obj.id,
                DeviceId = obj.deviceid,
                Vmstypes = obj.multitype,
                Model = obj.model
            };
            try
            {

                var item =
                _vmsAdministratorViewModel.AllVmsItem.Where(
                    x => x.VmsId == _vmsAdministratorViewModel.SelectionItem.VmsId).FirstOrDefault();
                if (item == null)
                    return;
                var index = _vmsAdministratorViewModel.AllVmsItem.IndexOf(item);
                //var itemchanged = _vmsAdministratorViewModel.AllVmsItem[index].Vmsname;

                //if (_vmsCurrentMembersList.Contains(itemchanged))
                //{
                //    _vmsCurrentMembersList.Remove(itemchanged);
                //    _vmsCurrentMembersList.Add(vmsModel.Vmsname);
                //}
                if (index >= 0)
                {
                    _vmsAdministratorViewModel.AllVmsItem[index] = vmsModel;
                }

                //if (!_vmsCurrentMembersList.SequenceEqual(_vmsAdministratorViewModel.VmsOnServerMembersList))
                //{
                //    //Show mess    
                //    MessageBoxResult result1 = MessageBox.Show(ErrorInfoVi.VmsDataNotSync, "Thông báo", MessageBoxButton.YesNo);
                //    if (result1 == MessageBoxResult.Yes)
                //    {
                //        if (SyncVmsEvent != null)
                //            SyncVmsEvent(true);
                //    }
                //}


            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("Edit item button click: " + ex);
            }
        }
    }
}
