using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using DevExpress.Xpf.Core.Native;
using DrawToolLibWPF;
using eVMS.Jsoncontract;
using eVMS.MessageView;
using eVMS.Utils;
using eVMS.View;
using eVMS.ViewModel;
using eVMS.VMS;
using MahApps.Metro.Controls;
using Newtonsoft.Json;
using RestSharp;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Image = eVMS.Jsoncontract.Image;

namespace eVMS
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        #region Variable for Main tab

        public int _paintingAreaWidth, _paintingAreaHeight;
        private float rate = 1;
        #endregion

        #region Mems
        private TreeViewVmsModel _treeViewVmsModel;
        //string service = Properties.Settings.Default["ServerIp"].ToString() + ":" +
        //                     Properties.Settings.Default["Port"].ToString();
        #endregion
        #region Constructor
        public MainWindow()
        {
            InitializeComponent();

            log4net.Config.XmlConfigurator.Configure();
            Loaded += MainWindow_Loaded;
            CvDrawing.MousedownEvent+=CvDrawing_MousedownEvent;
            Closing += MainWindow_Closing;
        }

        void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {

            if (PageVmsMornitorTransitionControl.Content != null)
            {
                if (PageVmsMornitorTransitionControl.Content is MonitoringScreen)
                {
                    (PageVmsMornitorTransitionControl.Content as MonitoringScreen).StopTimer();
                }
            }
            GC.Collect();

            GC.WaitForPendingFinalizers();

            GC.Collect();
        }

        
        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            AccountHeader.Content = Account.AccountName;
            this.PreviewKeyDown += MainWindow_PreviewKeyDown;
            this.WindowState = WindowState.Maximized;
            if (Account.AccountRole == Utils.Role.User)
            {
                AdminTabItem.Visibility = Visibility.Collapsed;
                VmsAdminTabItem.Visibility = Visibility.Collapsed;
            }

            //if (trvFamilies.SelectedItem != null)
            //{
            //    if (_treeViewVmsModel.SelectedChildItem != null)
            //    {
            //        Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
            //    }
            //}
        }
        #endregion

        #region Control Event
        void MainWindow_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.F11)
            {
                if (WindowState == WindowState.Normal)
                    WindowState = WindowState.Maximized;
                else
                    WindowState = WindowState.Normal;
            }
        }

        private async void Maintab_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.Source is TabControl)
            {
                TblInfo.Text = string.Empty;
                var selected = (e.Source as TabControl).SelectedItem as TabItem;
                if(selected == null)
                    return;

                var name = selected.Name;
                TblInfo.Text = string.Empty;
                if (name == "AdminTabItem")
                {
                    //if (PageAdminTransitionControl.Content == null)
                    {
                        GridMain.IsEnabled = false;
                        FluidProgressBar.Visibility = Visibility.Visible;
                        var resUserlist = await LoadDataForUserAccountTab();
                        var resGetRole = await GetListRoleFromServer();
                        GridMain.IsEnabled = true;
                        FluidProgressBar.Visibility = Visibility.Hidden;
                        if (resUserlist == null || resGetRole == null)
                        {
                            TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                            return;
                        }
                        var userlist = new ObservableCollection<PersonViewModel>();
                        if (resUserlist.userlist != null)
                        {
                            foreach (var user in resUserlist.userlist)
                            {
                                string rolename = string.Empty;
                                foreach (var role in resGetRole.rolelist)
                                {
                                    if (role.roleid == user.RoleId)
                                    {
                                        rolename = role.name;
                                        break;
                                    }
                                }
                                var perViewmodel = new PersonViewModel
                                {
                                    Birthday = user.Birthday,
                                    Address = user.Address,
                                    Email = user.Email,
                                    FullName = user.FullName,
                                    Password = user.Password,
                                    Phone = user.Phone,
                                    RoleName = rolename,
                                    RoleId = user.RoleId,
                                    Sex = (user.Sex == "1") ? "Nam" : "Nữ",
                                    Username = user.Username
                                };
                                userlist.Add(perViewmodel);
                            }
                        }
                        FluidProgressBar.Visibility = Visibility.Hidden;
                        GridMain.IsEnabled = true;
                        PageAdminTransitionControl.Content = new AdminUser(new UserAdministratorViewModel(userlist));
                    }
                }
                else if (name == "VmsAdminTabItem")
                {
                    //if (PageVmsAdminTransitionControl.Content == null)
                    {
                        GridMain.IsEnabled = false;
                        FluidProgressBar.Visibility = Visibility.Visible;
                        var res = await GetVmsFromtoServer(Account.AccountName);

                        FluidProgressBar.Visibility = Visibility.Hidden;
                        GridMain.IsEnabled = true;
                        

                        var adminModel = new VmsAdministratorViewModel();
                        if (res != null)
                            adminModel.SetDataModel(res.objectlist);

                        var vmsAdmin = new VMSAdminstratorScreen(adminModel);
                        PageVmsAdminTransitionControl.Content = vmsAdmin; 
                        //else
                        //{
                        //    var adminModel = new VmsAdministratorViewModel();
                        //    if (res != null)
                        //        adminModel.SetDataModel(res.objectlist);
                        //    var vmsAdmin = new VMSAdminstratorScreen(adminModel, new List<string>());
                        //    vmsAdmin.SyncVmsEvent += vmsAdmin_SyncVmsEvent;
                        //    PageVmsAdminTransitionControl.Content = vmsAdmin;  
                        //}
                        
                    }
                }
                else if (name == "VMSController") // Vms controler tab
                {
                    
                    //if (_treeViewVmsModel != null)
                    //{
                    //    _treeViewVmsModel.VmsMems.Clear();
                    //    CvDrawing.Children.Clear();
                    //    SettingArea.Content = null;
                    //}
                    
                    //GridMain.IsEnabled = false;
                    //FluidProgressBar.Visibility = Visibility.Visible;
                    //var res = await GetVmsFromtoServer(Account.AccountName);

                    //FluidProgressBar.Visibility = Visibility.Hidden;
                    //GridMain.IsEnabled = true;
                    //if (res == null)
                    //{
                    //    TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                    //    return;
                    //}
                    //_treeViewVmsModel = new TreeViewVmsModel();
                    //_treeViewVmsModel.SetViewModel(res.objectlist);
                    //trvFamilies.ItemsSource = _treeViewVmsModel.VmsMems;
                    if (_treeViewVmsModel == null)
                    {
                        if (_treeViewVmsModel != null)
                        {
                            _treeViewVmsModel.VmsMems.Clear();
                            CvDrawing.Children.Clear();
                            SettingArea.Content = null;
                        }

                        GridMain.IsEnabled = false;
                        FluidProgressBar.Visibility = Visibility.Visible;
                        var res = await GetVmsFromtoServer(Account.AccountName);

                        FluidProgressBar.Visibility = Visibility.Hidden;
                        GridMain.IsEnabled = true;
                        if (res == null)
                        {
                            TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                            return;
                        }
                        _treeViewVmsModel = new TreeViewVmsModel();
                        _treeViewVmsModel.SetViewModel(res.objectlist);
                        trvFamilies.ItemsSource = _treeViewVmsModel.VmsMems;
                    }
                    else
                    {
                        //Check sync data
                        List<String> vmsmemName = new List<string>();
                        List<String> vmsmemNameOnServer = new List<string>();
                        if (_treeViewVmsModel != null)
                        {

                            foreach (var vmsMemberse in _treeViewVmsModel.VmsMems)
                            {
                                vmsmemName.Add(vmsMemberse.Name);
                            }
                        }

                        GridMain.IsEnabled = false;
                        FluidProgressBar.Visibility = Visibility.Visible;
                        var res = await GetVmsFromtoServer(Account.AccountName);

                        FluidProgressBar.Visibility = Visibility.Hidden;
                        GridMain.IsEnabled = true;

                        if (res != null)
                        {
                            if (res.objectlist != null)
                            {
                                foreach (var vmse in res.objectlist)
                                {
                                    vmsmemNameOnServer.Add(vmse.name);
                                }
                            }
                        }

                        if (!vmsmemName.SequenceEqual(vmsmemNameOnServer))
                        {
                            //Show mess    
                            MessageBoxResult result1 = MessageBox.Show(ErrorInfoVi.VmsDataNotSync, "Thông báo", MessageBoxButton.YesNo);
                            if (result1 == MessageBoxResult.Yes)
                            {
                                vmsAdmin_SyncVmsEvent(true);
                            }
                        }
                        //End


                        if (trvFamilies.SelectedItem != null)
                        {
                            if (_treeViewVmsModel.SelectedChildItem != null)
                            {
                                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                            }
                        }
                    }
                }
                else if (name == "VmsMornitorTabItem") // Vms mornitoring tab
                {
                    if (PageVmsMornitorTransitionControl.Content == null)
                    {
                        
                        GridMain.IsEnabled = false;
                        FluidProgressBar.Visibility = Visibility.Visible;
                        var res = await GetVmsListMonitoringFromtoServer(Account.AccountName);

                        FluidProgressBar.Visibility = Visibility.Hidden;
                        GridMain.IsEnabled = true;
                        
                        if (res == null)
                        {
                            TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                            return;
                        }

                        var monitoring = new MonitoringScreen();
                        monitoring.SetDataContext(res);
                        monitoring.DoubleClickVmsEvent += monitoring_DoubleClickVmsEvent;
                        PageVmsMornitorTransitionControl.Content = monitoring;
                    }
                    else
                    {
                        if (PageVmsMornitorTransitionControl.Content is MonitoringScreen)
                        {
                            var mor = PageVmsMornitorTransitionControl.Content as MonitoringScreen;
                            GridMain.IsEnabled = false;
                            FluidProgressBar.Visibility = Visibility.Visible;
                            var res = await GetVmsListMonitoringFromtoServer(Account.AccountName);

                            FluidProgressBar.Visibility = Visibility.Hidden;
                            GridMain.IsEnabled = true;

                            if (res == null)
                            {
                                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                                return;
                            }
                            mor.SetDataContext(res);

                        }
                    }
                }
                else if(name=="HistoryTabItem")
                {
                    PageHistoryTransitionControl.Content = new HistoryScreen();
                }

            }
        }

        async void vmsAdmin_SyncVmsEvent(bool obj)
        {
            VMSController.IsSelected = true;
            TblInfo.Text = string.Empty;
            if (_treeViewVmsModel != null)
            {
                _treeViewVmsModel.VmsMems.Clear();
                CvDrawing.Children.Clear();
                SettingArea.Content = null;
            }
            Utils.Section.TemplateSection.Clear(); //Clear all template

            GridMain.IsEnabled = false;
            FluidProgressBar.Visibility = Visibility.Visible;
            var res = await GetVmsFromtoServer(Account.AccountName);

            FluidProgressBar.Visibility = Visibility.Hidden;
            GridMain.IsEnabled = true;
            if (res == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }
            _treeViewVmsModel = new TreeViewVmsModel();
            _treeViewVmsModel.SetViewModel(res.objectlist);
            trvFamilies.ItemsSource = _treeViewVmsModel.VmsMems;
        }

        void monitoring_DoubleClickVmsEvent(Vmsmonitoring obj)
        {
            VMSController.IsSelected = true;
             var items = _treeViewVmsModel.VmsMems.Where(i => i.VmsId == obj.id).ToList();
            if (items.Count > 0)
            {
                SetSelected(trvFamilies, items[0]);
            }
        }

        private void BtnMenu_OnClick(object sender, RoutedEventArgs e)
        {
            if(!(sender is Button))
                return;
            (sender as Button).ContextMenu.IsEnabled = true;
            (sender as Button).ContextMenu.PlacementTarget = (sender as Button);
            (sender as Button).ContextMenu.Placement = System.Windows.Controls.Primitives.PlacementMode.Bottom;
            (sender as Button).ContextMenu.IsOpen = true;
        }

        private void ItemLogout_OnClick(object sender, RoutedEventArgs e)
        {
            Utils.Section.TemplateSection.Clear();
            Login login = new Login();
            this.Close();
            login.ShowDialog();
        }

        #endregion

        #region Task

        /// <summary>
        /// Load data for User account tab
        /// </summary>
        /// <returns></returns>
        public async Task<GetListUser> LoadDataForUserAccountTab()
        {
            try
            {

                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getalluser"];
                //reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.GET);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<GetListUser>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("load all user : " + ex.ToString());
                return null;
            }
            

            return null;
        }

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

        public async Task<VmsmonitoringMessage> GetVmsListMonitoringFromtoServer(string accountname)
        {
            try
            {
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getlistvmsmonitoring"];

                var request = new RestRequest(reUrl, Method.GET);
                request.AddParameter("username", accountname);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var json = JsonConvert.DeserializeObject<VmsmonitoringMessage>(ok);
                return json;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("load all user : " + ex.ToString());
                return null;
            }
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

        public async Task<InfoReturn> SendTreeVmstoServer(string jsonVmstree)
        {
            try
            {
                if (ServerSettingDefine.Service == string.Empty)
                    return null;
                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["updatetreevms"];
                reUrl += string.Format("?username={0}", Account.AccountName);
                var request = new RestRequest(reUrl, Method.PUT);
                request.RequestFormat = RestSharp.DataFormat.Json;
                //request.AddHeader("Accept", "application/json");
                //request.AddParameter("username", Account.AccountName);
                request.AddParameter("application/json", jsonVmstree, ParameterType.RequestBody);
                //request.AddBody("application/json", jsonVmstree);
                // var response = await client.ExecutePostTaskAsync(request);
                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var respose = JsonConvert.DeserializeObject<InfoReturn>(ok);
                return respose;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error("json converter error:" + ex);
                return null;
            }
        }

        #endregion


        #region Event
        void ImageSetting_ErrorInfoEvent(string obj)
        {
            TblInfo.Text = obj;
        }

        void textSetting_EditVmsTextEvent(VmsText obj)
        {
            Drawing(_treeViewVmsModel.SelectedItem,rate);
        }
        #endregion Event
        public void Drawing(VmsMembers listobj,float rate)
        {
            CvDrawing.Children.Clear();
            foreach (var vmsObject in listobj.Members)
            {
                var newItem = ConvertVmsObjectToDrawObject(vmsObject,rate);
                Canvas.SetTop(newItem, vmsObject.Y*rate);
                Canvas.SetLeft(newItem, vmsObject.X*rate);

                CvDrawing.Children.Add(newItem);
                //CvDrawing.TopDescriptor.AddValueChanged(newItem, DesignedItem_PositionChanged);
            }
        }

        public void Drawing(VmsMembers listobj, float rate,string selectedName)
        {
            CvDrawing.Children.Clear();
            foreach (var vmsObject in listobj.Members)
            {
                var newItem = ConvertVmsObjectToDrawObject(vmsObject, rate);
                if (newItem.ItemName == selectedName)
                    newItem.IsSelected = true;
                Canvas.SetTop(newItem, vmsObject.Y * rate);
                Canvas.SetLeft(newItem, vmsObject.X * rate);

                CvDrawing.Children.Add(newItem);
                //CvDrawing.TopDescriptor.AddValueChanged(newItem, DesignedItem_PositionChanged);
            }
        }

        public async void Drawing(VmsMembers listobj)
        {
            CvDrawing.Children.Clear();
            foreach (var vmsObject in listobj.Members)
            {
                var newItem = ConvertVmsObjectToDrawObject(vmsObject, rate);
                Canvas.SetTop(newItem, vmsObject.Y * rate);
                Canvas.SetLeft(newItem, vmsObject.X * rate);

                CvDrawing.Children.Add(newItem);
                //CvDrawing.TopDescriptor.AddValueChanged(newItem, DesignedItem_PositionChanged);
            }
        }

        public DesignerItem ConvertVmsObjectToDrawObject(VmsObject vmsObject, float rate)
        {
            var newItem = new DesignerItem();
            newItem.Width = vmsObject.Width * rate;
            newItem.Height = vmsObject.Height * rate;
            newItem.SelectedItemEvent += NewItem_SelectedItemEvent;
            newItem.SizeChangeItemEvent += NewItem_SizeChangeItemEvent;
            newItem.MoveThumeItemEvent +=NewItem_MoveThumeItemEvent;
            //if (vmsObject.IsSelected)
            //    newItem.IsSelected = true;
            if (vmsObject is VmsText)
            {
                //newItem.Width = vmsObject.Width * rate;
                //newItem.Height = vmsObject.Height * rate;
                if ((vmsObject as VmsText).FontFamily == null)
                    (vmsObject as VmsText).FontFamily = "Arial";
                TextBlock text = new TextBlock();
                //text.Width = vmsObject.Width * rate;
                //text.Height = vmsObject.Height * rate;
                text.Text = (vmsObject as VmsText).Content;
                
                //Hoanglm change
                text.FontFamily = new FontFamily((vmsObject as VmsText).FontFamily);
                
                
                //var fontselected = string.Format("Fonts/#{0}", (vmsObject as VmsText).FontFamily);
                //text.FontFamily = new FontFamily(new Uri("pack://application:,,,/"), fontselected);
                //Hoanglm end change

                int size = 0;
                int.TryParse((vmsObject as VmsText).FontSize, out size);
                if (size == 0)
                    text.FontSize = 12/0.75;
                else
                    text.FontSize = size*rate/0.75;

                text.FontWeight = ((vmsObject as VmsText).FontWight == true) ? FontWeights.Bold : FontWeights.Normal;
                text.FontStyle = ((vmsObject as VmsText).FontStyle == true) ? FontStyles.Italic : FontStyles.Normal;
                //text.Width = vmsObject.Width;
                //text.Height = vmsObject.Height;
                text.Foreground = new SolidColorBrush((vmsObject as VmsText).ColorText);
                text.IsHitTestVisible = false;
                newItem.Content = text;

            }
            else if (vmsObject is VmsImage)
            {
                var image = new System.Windows.Controls.Image();
                image.Stretch = Stretch.Fill;
               

                //if (!string.IsNullOrEmpty((vmsObject as VmsImage).ImageLink)
                //    && File.Exists((vmsObject as VmsImage).ImageLink))
                //if ((vmsObject as VmsImage).ImageLink != string.Empty)
                if (!string.IsNullOrEmpty((vmsObject as VmsImage).ImageLink))
                    if (CheckImageLinkExist((vmsObject as VmsImage).ImageLink))
                {
                    // BitmapImage bitmap = new BitmapImage();
                    //bitmap.BeginInit();
                    //try
                    //{
                    //    bitmap.UriSource = new Uri((vmsObject as VmsImage).ImageLink);
                    //    if (!bitmap.IsDownloading)
                    //     {
                          
                    //     }
                    //     else
                    //     {
                    //      bitmap.DownloadCompleted +=
                    //                       new EventHandler(
                    //        delegate(object sender1, EventArgs e1)
                    //        {
                    //          textBox1.Text = 
                    //                bmi.PixelHeight.ToString();
                    //        });
                    //      }
                    //}
                    //catch (Exception ex)
                    //{
                    //    Log4Net.Log.Error(ex);
                    //}
                    //bitmap.EndInit();
                    try
                    {
                        //var buffer = new WebClient().DownloadData((vmsObject as VmsImage).ImageLink);
                        byte[] buf = null;
                        try
                        {
                            using (var webclient = new WebClient())
                            {
                                webclient.Proxy = null;
                                webclient.UseDefaultCredentials = true;
                                buf = webclient.DownloadData((vmsObject as VmsImage).ImageLink);
                            }
                        }
                        catch (Exception ex)
                        {
                            Log4Net.Log.Error(ex);
                            
                        }

                        if (buf != null)
                        {
                            var bitmap = new BitmapImage();

                            using (var stream = new MemoryStream(buf))
                            {
                                bitmap.BeginInit();
                                bitmap.CacheOption = BitmapCacheOption.OnLoad;
                                bitmap.StreamSource = stream;
                                bitmap.EndInit();
                            }
                            image.Source = bitmap;
                        }
                        
                    }
                    catch (Exception ex)
                    {
                        Log4Net.Log.Error(ex);
                    }
                    
                }
                
                newItem.Content = image;
                image.IsHitTestVisible = false;
                
            }

            newItem.ItemName = vmsObject.Name;
            return newItem;
        }

        public bool CheckImageLinkExist(string url)
        {
            return true;
            HttpWebRequest request = (HttpWebRequest)HttpWebRequest.Create(url);
            request.Method = "HEAD";

            bool exists;
            try
            {
                request.Timeout = 10000;
                request.GetResponse();
                exists = true;
            }
            catch(Exception ex)
            {
                exists = false;
                Log4Net.Log.Error(ex);
            }
            return exists;
        }

        /// <summary>
        /// Once child node is Selected, the setting screen will get the new data to diplay
        /// </summary>
        public void SetDataForSettingScreen()
        {
            
            if (_treeViewVmsModel.SelectedChildItem is VmsImage)
            {
                //if (SettingArea.Content is ImageObjectSettingScreen)
                //{
                //    (SettingArea.Content as ImageObjectSettingScreen).SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsImage);
                //}
                //else
                {
                    //Get all Name in this vms
                    var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                                   //where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                                   select vmsObject.Name;

                    var imageSetting = new ImageObjectSettingScreen();
                    imageSetting.EditVmsImageEvent += ImageSetting_EditVmsImageEvent;
                    imageSetting.ErrorInfoEvent += ImageSetting_ErrorInfoEvent;
                    imageSetting.SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsImage, listName.ToList());
                    SettingArea.Content = imageSetting;
                }
            }
            else if (_treeViewVmsModel.SelectedChildItem is VmsText)
            {
                //if (SettingArea.Content is TextObjectSettingScreen)
                //{
                //    (SettingArea.Content as TextObjectSettingScreen).SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsText);
                //}
                //else
                {
                    //Get all Name in this vms
                    var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                                   //where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                                   select vmsObject.Name;

                    var textSetting = new TextObjectSettingScreen();
                    textSetting.EditVmsTextEvent += textSetting_EditVmsTextEvent;
                    textSetting.ErrorInfoEvent += ImageSetting_ErrorInfoEvent;
                    int color = 111;
                    if (_treeViewVmsModel.SelectedItem != null)
                        color = (_treeViewVmsModel.SelectedItem as VmsMembers).nColor;
                    textSetting.SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsText, listName.ToList(), color);
                    SettingArea.Content = textSetting;
                }
            }
        }


        #region Canvas Event

        private void CvDrawing_MousedownEvent(bool obj)
        {
            SetSelected(trvFamilies, _treeViewVmsModel.SelectedItem);
        }
        void NewItem_SelectedItemEvent(DesignerItem obj)
        {
            //trvFamilies.SelectedItem = _treeViewVmsModel.SelectedItem.Members.First();
            //SetSelected(trvFamilies, _treeViewVmsModel.SelectedItem.Members.First());
            //foreach (var vmsObject in _treeViewVmsModel.SelectedItem.Members)
            //{
            //    vmsObject.IsSelected = false;
            //}

            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                if (_treeViewVmsModel.SelectedChildItem.Name != obj.ItemName)
                {
                    var listitem = _treeViewVmsModel.SelectedItem.Members.Where(x => x.Name == obj.ItemName).ToList();
                    if(listitem.Count <= 0)
                        return;
                    var item = listitem.First();
                    //item.IsSelected = true;
                    //item.Height = (float)obj.Height;
                    //item.Width = (float) obj.Width;
                    _treeViewVmsModel.SelectedChildItem = item;
                    //ExpandeNode(trvFamilies, _treeViewVmsModel.SelectedItem.Name);
                    SetSelected(trvFamilies, item);
                    //SetDataForSettingScreen();
                }
                else
                {
                    //_treeViewVmsModel.SelectedChildItem.Height = (float)obj.Height;
                    //_treeViewVmsModel.SelectedChildItem.Width = (float)obj.Width;

                    //////SetSelected(trvFamilies, _treeViewVmsModel.SelectedChildItem);
                    //SetDataForSettingScreen();
                }
            }
            else
            {
                var listitem = _treeViewVmsModel.SelectedItem.Members.Where(x => x.Name == obj.ItemName).ToList();
                if (listitem.Count <= 0)
                    return;
                var item = listitem.First();
                //item.IsSelected = true;
                _treeViewVmsModel.SelectedChildItem = item;

                //ExpandeNode(trvFamilies, _treeViewVmsModel.SelectedItem.Name);
                trvFamilies.BringIntoView();
                //SetSelected(trvFamilies, item);

                try
                {
                    var res = trvFamilies.ItemContainerGenerator.ContainerFromItem(trvFamilies.SelectedItem);
                    if (res != null && res is TreeViewItem)
                    {
                        var node = GetItemFromObje(res as TreeViewItem, item);
                        if (node != null)
                            node.IsSelected = true;
                    }
                }
                catch (Exception ex)
                {
                    Log4Net.Log.Error(ex);

                }

                
                
            }
        }

        /// <summary>
        /// Expand a TreeView to a specific node
        /// </summary>
        /// <param name="tv">The treeview</param>
        /// <param name="node">The string of the node in the Item.Tag property to expand to</param>
        void ExpandeNode(TreeView tv, string node)
        {
            TreeViewItem item = (TreeViewItem)trvFamilies
            .ItemContainerGenerator
            .ContainerFromItem(trvFamilies.SelectedItem);
            if(item != null)
                item.IsExpanded = true;
        }

        void NewItem_SizeChangeItemEvent(DesignerItem obj)
        {
            var x = Canvas.GetLeft(obj)/rate;
            var y = Canvas.GetTop(obj)/rate;
            if (_treeViewVmsModel.SelectedChildItem == null)
                return;

            if (_treeViewVmsModel.SelectedChildItem.Height != (float)(obj.Height / rate) ||
                _treeViewVmsModel.SelectedChildItem.Width != (float) (obj.Width/rate))
            {
                _treeViewVmsModel.SelectedChildItem.Height = (float) (obj.Height/rate);
                _treeViewVmsModel.SelectedChildItem.Width = (float) (obj.Width/rate);
                _treeViewVmsModel.SelectedChildItem.X = (float)x;
                _treeViewVmsModel.SelectedChildItem.Y = (float)y;

                if (_treeViewVmsModel.SelectedChildItem is VmsImage)
                {
                        //Get all Name in this vms
                        var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                                       where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                                       select vmsObject.Name;

                        var imageSetting = new ImageObjectSettingScreen();
                        imageSetting.EditVmsImageEvent += ImageSetting_EditVmsImageEvent;
                        imageSetting.ErrorInfoEvent += ImageSetting_ErrorInfoEvent;
                        imageSetting.SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsImage, listName.ToList());
                        SettingArea.Content = imageSetting;
                   
                }
                else if (_treeViewVmsModel.SelectedChildItem is VmsText)
                {
                    
                    //Get all Name in this vms
                    var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                                    where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                                    select vmsObject.Name;

                    var textSetting = new TextObjectSettingScreen();
                    textSetting.EditVmsTextEvent += textSetting_EditVmsTextEvent;
                    textSetting.ErrorInfoEvent += ImageSetting_ErrorInfoEvent;
                    int color = 111;
                    if (_treeViewVmsModel.SelectedItem != null)
                        color = (_treeViewVmsModel.SelectedItem as VmsMembers).nColor;
                    textSetting.SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsText, listName.ToList(), color);
                    SettingArea.Content = textSetting;
                    
                }
            }

            
        }

        private void NewItem_MoveThumeItemEvent(DesignerItem obj)
        {
            var x = Canvas.GetLeft((obj as DesignerItem))/rate;
            var y = Canvas.GetTop((obj as DesignerItem))/rate;

            if (_treeViewVmsModel.SelectedChildItem.X != (float)x ||
                _treeViewVmsModel.SelectedChildItem.Y != (float)y)
            {
                _treeViewVmsModel.SelectedChildItem.X = (float)x;
                _treeViewVmsModel.SelectedChildItem.Y = (float)y;

                if (_treeViewVmsModel.SelectedChildItem is VmsImage)
                {
                    //Get all Name in this vms
                    var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                                   where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                                   select vmsObject.Name;

                    var imageSetting = new ImageObjectSettingScreen();
                    imageSetting.EditVmsImageEvent += ImageSetting_EditVmsImageEvent;
                    imageSetting.ErrorInfoEvent += ImageSetting_ErrorInfoEvent;
                    imageSetting.SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsImage, listName.ToList());
                    SettingArea.Content = imageSetting;

                }
                else if (_treeViewVmsModel.SelectedChildItem is VmsText)
                {

                    //Get all Name in this vms
                    var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                                   where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                                   select vmsObject.Name;

                    var textSetting = new TextObjectSettingScreen();
                    textSetting.EditVmsTextEvent += textSetting_EditVmsTextEvent;
                    textSetting.ErrorInfoEvent += ImageSetting_ErrorInfoEvent;
                    int color = 111;
                    if (_treeViewVmsModel.SelectedItem != null)
                        color = (_treeViewVmsModel.SelectedItem as VmsMembers).nColor;
                    textSetting.SetDataContext(_treeViewVmsModel.SelectedChildItem as VmsText, listName.ToList(), color);
                    SettingArea.Content = textSetting;

                }
            }
        }

        
        #endregion Canvas Event

        private bool SetSelected(ItemsControl parent, object child) 
        {
 
            if (parent == null || child == null) {
                return false;
            }
            
            TreeViewItem childNode = parent.ItemContainerGenerator
                .ContainerFromItem(child) as TreeViewItem;
 
            if (childNode != null) 
            {
                childNode.Focus();
                return childNode.IsSelected = true;
            }
 
            if (parent.Items.Count > 0) 
            {
                foreach (object childItem in parent.Items) 
                {
                    ItemsControl childControl = parent.ItemContainerGenerator.ContainerFromItem(childItem) 
                        as ItemsControl;
 
                    if (SetSelected(childControl, child)) 
                    {
                        return true;
                    }
                }
            }
 
            return false;
        }

        private TreeViewItem GetItemFromObje(TreeViewItem parent, object child)
        {
            if (parent == null || child == null)
            {
                return null;
            }
            
            
            var node = (parent as TreeViewItem);
            if (node.Items.Contains(child))
            {
                var res = node.ItemContainerGenerator.ContainerFromIndex(node.Items.IndexOf(child));
                if (res != null && res is TreeViewItem)
                    return (res as TreeViewItem);
            }

            return null;
        }

        /// <summary>
        /// Convert the VmsObj to Draw Tool lib obj
        /// </summary>
        /// <param name="vmsObject"></param>
        /// <returns></returns>
        
        #region Event Click

        private void TrvFamilies_OnSelected(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (!(trvFamilies.SelectedItem is VmsMembers))
            {
                _treeViewVmsModel.SelectedChildItem = trvFamilies.SelectedItem as VmsObject;
                TreeViewItem item = e.OriginalSource as TreeViewItem;
                if (item != null)
                {
                    ItemsControl parent = GetSelectedTreeViewItemParent(item);
                    //if (treeitem != null)
                    {
                        TreeViewItem treeitem = parent as TreeViewItem;
                        if (treeitem != null)
                        {
                            if (_treeViewVmsModel.SelectedItem == null)
                            {
                                _treeViewVmsModel.SelectedItem = treeitem.Header as VmsMembers;
                            }
                            else
                            {
                                if (_treeViewVmsModel.SelectedItem != (treeitem.Header as VmsMembers))
                                {
                                    _treeViewVmsModel.SelectedItem = treeitem.Header as VmsMembers;
                                }
                            }
                            //and
                            //Set data to setting area
                            SetDataForSettingScreen();
                            //End

                        }
                    }
                }
            }
            else
            {
                if (_treeViewVmsModel.SelectedItem != trvFamilies.SelectedItem)
                {
                    _treeViewVmsModel.SelectedItem = trvFamilies.SelectedItem as VmsMembers;

                }
                _treeViewVmsModel.SelectedChildItem = null;
                //Expande the selected item
                try
                {
                    var res = trvFamilies.ItemContainerGenerator.ContainerFromItem(trvFamilies.SelectedItem) as TreeViewItem;
                    if (res != null)
                        res.IsExpanded = true;
                }
                catch (Exception ex)
                {
                    Log4Net.Log.Error(ex);
                    
                }
                SettingArea.Content = null;
            }
            //Calculate width and height area
            float wiRate, hiRate;
            wiRate = hiRate = 1;
            if (_treeViewVmsModel.SelectedItem.Width > BoderDrawArea.ActualWidth)
                wiRate = (float) (BoderDrawArea.ActualWidth/_treeViewVmsModel.SelectedItem.Width);

            if (_treeViewVmsModel.SelectedItem.Height > BoderDrawArea.ActualHeight)
                hiRate = (float)(BoderDrawArea.ActualHeight/_treeViewVmsModel.SelectedItem.Height);

            if (wiRate > hiRate)
                rate = hiRate;
            else
                rate = wiRate;
            //End 
            if (BoderDrawArea.ActualWidth/_treeViewVmsModel.SelectedItem.Width > 3 &&
                BoderDrawArea.ActualHeight/_treeViewVmsModel.SelectedItem.Height > 3)
                rate = 3;

            CvDrawing.Width = _treeViewVmsModel.SelectedItem.Width*rate;
            CvDrawing.Height = _treeViewVmsModel.SelectedItem.Height*rate -3;
            VmsMembers mems = new VmsMembers();
            foreach (var vmsObject in _treeViewVmsModel.SelectedItem.Members)
            {
                mems.Members.Add(vmsObject);
            }
            Drawing(mems, rate);
            if (_treeViewVmsModel.SelectedChildItem != null)
                CvDrawing.SelectItem(_treeViewVmsModel.SelectedChildItem.Name);
            //End
        }

        void ImageSetting_EditVmsImageEvent(VmsImage obj)
        {
            TblInfo.Text = string.Empty;
            Drawing(_treeViewVmsModel.SelectedItem,rate);
        }

        private void AddImage_OnClick(object sender, RoutedEventArgs e)
        {
            if (_treeViewVmsModel.SelectedItem == null)
            {
                MessageBox.Show("Chọn vms để thêm ảnh");
                return;
            }
            //string name = string.Format("Ảnh mới {0}", _treeViewVmsModel.SelectedItem.Members.Count.ToString());
            string name = CreateNewName("Ảnh mới");
            _treeViewVmsModel.SelectedItem.Members.Add(new VmsImage() { Name = name, Avatar = "addpicture",Width = 60,Height = 60});
        }

        private void Addtext_OnClick(object sender, RoutedEventArgs e)
        {
            if (_treeViewVmsModel.SelectedItem == null)
            {
                MessageBox.Show("Chọn vms để thêm text");
                return;
            }
            //string name = string.Format("Từ mới {0}", _treeViewVmsModel.SelectedItem.Members.Count.ToString());
            string name = CreateNewName("Từ mới");
            _treeViewVmsModel.SelectedItem.Members.Add(new VmsText() { Name = name, Avatar = "addtext",Width = 60,Height = 60});
        }

        private string CreateNewName(string objname)
        {
            string name = string.Format("{0} {1}",objname, _treeViewVmsModel.SelectedItem.Members.Count.ToString());
            if (_treeViewVmsModel.SelectedItem == null)
                return string.Empty;

            var listName = from vmsObject in _treeViewVmsModel.SelectedItem.Members
                           //where vmsObject.Name != _treeViewVmsModel.SelectedChildItem.Name
                           select vmsObject.Name;
            {
                if (listName.Contains(name))
                {
                    int a = 0;
                    while (true)
                    {
                        name = objname + " " + (listName.ToList().Count + a).ToString();
                        if (listName.Contains(name))
                            a++;
                        else
                            break;
                    }
                }
                
            }
            return name;
        }

        private void DeleteObject_OnClick(object sender, RoutedEventArgs e)
        {
            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                if (trvFamilies.SelectedItem is VmsObject)
                    if (_treeViewVmsModel.SelectedItem.Members.Contains(trvFamilies.SelectedItem as VmsObject))
                    {
                        _treeViewVmsModel.SelectedItem.Members.Remove(trvFamilies.SelectedItem as VmsObject);
                    }
            }
        }

        public ItemsControl GetSelectedTreeViewItemParent(TreeViewItem item)
        {
            DependencyObject parent = VisualTreeHelper.GetParent(item);
            while (!(parent is TreeViewItem || parent is TreeView))
            {
                parent = VisualTreeHelper.GetParent(parent);
            }

            return parent as ItemsControl;
        }

        private async void BtnSendVms_OnClick(object sender, RoutedEventArgs e)
        {
            //try
            //{
            //    VmsListMessage listVms = new VmsListMessage();
            //    listVms.programs = new List<program>();
            //    foreach (var vmsMemberse in _treeViewVmsModel.VmsMems)
            //    {
            //        if(vmsMemberse.Members == null)
            //            continue;
            //        program pr = new program();
            //        pr.image = new List<Image>();
            //        pr.text = new List<Text>();
            //        foreach (var mem in vmsMemberse.Members)
            //        {
            //            if (mem is VmsText)
            //            {
            //                String contenttemp = ((mem as VmsText).Content != null)
            //                    ? (mem as VmsText).Content
            //                    : string.Empty;
            //                string fonttemp = ((mem as VmsText).FontFamily != null)
            //                    ? (mem as VmsText).FontFamily
            //                    : string.Empty;
            //               pr.text.Add(new Text()
            //               {
            //                   content = contenttemp,
            //                   name = (mem as VmsText).Name,
            //                   fontsize = (mem as VmsText).FontSize,
            //                   font = fonttemp,
            //                   fontstyle = (mem as VmsText).FontStyle?"Italic":"Normal",
            //                   fontweight = (mem as VmsText).FontWight?"Bold":"Normal",
            //                   height = (int)(mem as VmsText).Height,
            //                   with = (int)(mem as VmsText).Width,
            //                   x = (int)(mem as VmsText).X,
            //                   y = (int)(mem as VmsText).Y,
            //                   colortext = (mem as VmsText).ColorText

            //               }); 
            //            }
            //            else if(mem is VmsImage)
            //            {
            //                string imglink = string.Empty;
            //                if ((mem as VmsImage).ImageLink != null)
            //                    imglink = (mem as VmsImage).ImageLink.Replace("\\", "-");
            //                pr.image.Add(new Image()
            //                {
            //                    link = imglink,
            //                    name = (mem as VmsImage).Name,
            //                    height = (int)(mem as VmsImage).Height,
            //                    width = (int)(mem as VmsImage).Width,
            //                    x = (int)(mem as VmsImage).X,
            //                    y = (int)(mem as VmsImage).Y
            //                });
            //            }
            //        }
            //        pr.vmsId = vmsMemberse.VmsId.ToString();
            //        listVms.programs.Add(pr);
            //    }

            //    var json = JsonConvert.SerializeObject(listVms);
            //    GridMain.IsEnabled = false;
            //    var res = await SendTreeVmstoServer(json);
            //    GridMain.IsEnabled = true;
            //    if (res == null)
            //    {
            //        TblInfo.Text = "Không kết nối được đến server";
            //        return;
            //    }
            //    if (res.error)
            //    {
            //        if (MessageInfo.MessInfoCode.ContainsKey(res.status))
            //        {
            //            TblInfo.Text = MessageInfo.MessInfoCode[res.status];
            //            return;
            //        }
            //    }
            //}
            //catch (Exception ex)
            //{
                
            //    Log4Net.Log.Error(ex);
            //}
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void BtnRefreshItemVms_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (_treeViewVmsModel != null)
            {
                _treeViewVmsModel.VmsMems.Clear();
                CvDrawing.Children.Clear();
                SettingArea.Content = null;
            }
            Utils.Section.TemplateSection.Clear(); //Clear all template

            GridMain.IsEnabled = false;
            FluidProgressBar.Visibility = Visibility.Visible;
            var res = await GetVmsFromtoServer(Account.AccountName);

            FluidProgressBar.Visibility = Visibility.Hidden;
            GridMain.IsEnabled = true;
            if (res == null)
            {
                TblInfo.Text = ErrorInfoVi.ServerCannotConnect;
                return;
            }
            _treeViewVmsModel = new TreeViewVmsModel();
            _treeViewVmsModel.SetViewModel(res.objectlist);
            trvFamilies.ItemsSource = _treeViewVmsModel.VmsMems;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void BtnSendItemVms_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = String.Empty;
            if (_treeViewVmsModel.SelectedItem == null)
            {
                TblInfo.Text = "Chọn Vms";
                return;
            }
            if (Utils.Section.TemplateSection.ContainsKey(_treeViewVmsModel.SelectedItem.VmsId))
            {
                Utils.Section.TemplateSection.Remove(_treeViewVmsModel.SelectedItem.VmsId);
            }

            SendingVmsListEditedMessage listVms = new SendingVmsListEditedMessage();
            listVms.programs = new List<VmsProgram>();

            VmsProgram pr = new VmsProgram();
            pr.image = new List<Image>();
            pr.text = new List<Text>();

            foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
            {
                if (mem is VmsText)
                {
                    String contenttemp = ((mem as VmsText).Content != null)
                        ? (mem as VmsText).Content
                        : string.Empty;
                    string fonttemp = ((mem as VmsText).FontFamily != null)
                        ? (mem as VmsText).FontFamily
                        : string.Empty;
                    pr.text.Add(new Text()
                    {
                        content = contenttemp,
                        name = (mem as VmsText).Name,
                        fontsize = (mem as VmsText).FontSize,
                        font = fonttemp,
                        fontstyle = (mem as VmsText).FontStyle ? "Italic" : "Normal",
                        fontweight = (mem as VmsText).FontWight ? "Bold" : "Normal",
                        height = (int)(mem as VmsText).Height,
                        width = (int)(mem as VmsText).Width,
                        x = (int)(mem as VmsText).X,
                        y = (int)(mem as VmsText).Y,
                        colortext = (mem as VmsText).ColorText

                    });
                }
                else if (mem is VmsImage)
                {
                    string imglink = string.Empty;
                    if ((mem as VmsImage).ImageLink != null)
                        imglink = (mem as VmsImage).ImageLink.Replace("\\", "-");
                    pr.image.Add(new Image()
                    {
                        link = imglink,
                        name = (mem as VmsImage).Name,
                        height = (int)(mem as VmsImage).Height,
                        width = (int)(mem as VmsImage).Width,
                        x = (int)(mem as VmsImage).X,
                        y = (int)(mem as VmsImage).Y
                    });
                }
            }
            pr.vmsId = _treeViewVmsModel.SelectedItem.VmsId.ToString();
            listVms.programs.Add(pr);
            //Encode image data
            string imagedata = ExportToPngBase64String(CvDrawing );
            pr.imagedata = imagedata;
            //


            var json = JsonConvert.SerializeObject(listVms);
            FluidProgressBar.Visibility = Visibility.Visible;
            GridMain.IsEnabled = false;
            var res = await SendTreeVmstoServer(json);
            GridMain.IsEnabled = true;
            FluidProgressBar.Visibility = Visibility.Hidden;
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
            TblInfo.Text = "Gửi dữ liệu thành công";
        }

        private async void BtnSaveTemplate_OnClick(object sender, RoutedEventArgs e)
        {

            TblInfo.Text = string.Empty;
            
            if (_treeViewVmsModel.SelectedItem == null)
            {
                TblInfo.Text = "Chọn Vms";
                return;
            }
            if (Section.TemplateSection.ContainsKey(_treeViewVmsModel.SelectedItem.VmsId))
            {
                if (Account.AccountRole == Role.User &&
                    Section.TemplateSection[_treeViewVmsModel.SelectedItem.VmsId].type == 1)
                {
                    TblInfo.Text = "Không có quyền ghi đè chương trình này";
                    return;
                }
                UpdateProgram(Section.TemplateSection[_treeViewVmsModel.SelectedItem.VmsId].id);
                return;
            }
            //Create new program

            ProgramMessage program = new ProgramMessage();
            program.height = _treeViewVmsModel.SelectedItem.Height;
            program.width = _treeViewVmsModel.SelectedItem.Width;
            Jsoncontract.Content conte = new Content();
            foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
            {

                if (mem is VmsText)
                {
                    String contenttemp = ((mem as VmsText).Content != null)
                        ? (mem as VmsText).Content
                        : string.Empty;
                    string fonttemp = ((mem as VmsText).FontFamily != null)
                        ? (mem as VmsText).FontFamily
                        : string.Empty;
                    conte.text.Add(new Text()
                    {
                        content = contenttemp,
                        name = (mem as VmsText).Name,
                        fontsize = (mem as VmsText).FontSize,
                        font = fonttemp,
                        fontstyle = (mem as VmsText).FontStyle ? "Italic" : "Normal",
                        fontweight = (mem as VmsText).FontWight ? "Bold" : "Normal",
                        height = (int)(mem as VmsText).Height,
                        width = (int)(mem as VmsText).Width,
                        x = (int)(mem as VmsText).X,
                        y = (int)(mem as VmsText).Y,
                        colortext = (mem as VmsText).ColorText

                    });
                }
                else if (mem is VmsImage)
                {
                    string imglink = string.Empty;
                    if ((mem as VmsImage).ImageLink != null)
                        imglink = (mem as VmsImage).ImageLink.Replace("\\", "-");
                    conte.image.Add(new Image()
                    {
                        link = imglink,
                        name = (mem as VmsImage).Name,
                        height = (int)(mem as VmsImage).Height,
                        width = (int)(mem as VmsImage).Width,
                        x = (int)(mem as VmsImage).X,
                        y = (int)(mem as VmsImage).Y
                    });
                }

                
            }
            string cont = JsonConvert.SerializeObject(conte);
            program.content = cont;
            SaveAsTemplate dialog = new SaveAsTemplate(program);
            dialog.Owner = System.Windows.Window.GetWindow(this);
            dialog.ShowDialog();
        }

        private void BtnLoadTemplate_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (_treeViewVmsModel.SelectedItem == null)
            {
                TblInfo.Text = "Chọn VMS";
                return;
            }

            ProgramScreen proScreen = new ProgramScreen(_treeViewVmsModel.SelectedItem.Width, _treeViewVmsModel.SelectedItem.Height);
            proScreen.LoadprogramEvent += proScreen_LoadprogramEvent;
            proScreen.Owner = System.Windows.Window.GetWindow(this);
            proScreen.ShowDialog();

        }

        void proScreen_LoadprogramEvent(ProgramUpdateMessage obj)
        {
            //_treeViewVmsModel.SelectedItem.Members.Clear();
            _treeViewVmsModel.SelectedItem.Members.Clear();
            CvDrawing.Children.Clear();

            try
            {
                VmsMembers newMems = new VmsMembers();
                Jsoncontract.Content content = JsonConvert.DeserializeObject<Content>(obj.content);
                foreach (var image in content.image)
                {
                    string link = string.Empty;
                    if (image.link == string.Empty)
                        continue;
                    link = image.link.Replace("-", "\\");
                    var iamgeobj = new VmsImage()
                    {
                        Avatar = "addpicture",
                        Height = image.height,
                        Width = image.width,
                        ImageLink = link,
                        Name = image.name,
                        X = image.x,
                        Y = image.y
                    };
                    newMems.Members.Add(iamgeobj);
                }

                foreach (var text in content.text)
                {
                    var textobj = new VmsText()
                    {
                        Avatar = "addtext",
                        FontFamily = text.font,
                        FontSize = (text.fontsize == null) ? "1" : text.fontsize,
                        Height = text.height,
                        Width = text.width,

                        X = text.x,
                        Y = text.y,
                        Content = text.content,
                        FontStyle = (text.fontstyle == "Italic") ? true : false,
                        FontWight = (text.fontweight == "Bold") ? true : false,
                        Name = text.name,
                        ColorText = text.colortext

                    };
                    newMems.Members.Add(textobj);
                }

                //_treeViewVmsModel.VmsMems.Remove(_treeViewVmsModel.SelectedItem);
                //_treeViewVmsModel.VmsMems.Add(newMems);
                (trvFamilies.SelectedItem as VmsMembers).Members.Clear();
                (trvFamilies.SelectedItem as VmsMembers).Members = newMems.Members;
                SetSelected(trvFamilies, newMems);
                Drawing(_treeViewVmsModel.SelectedItem, rate);
                if (Utils.Section.TemplateSection.ContainsKey(_treeViewVmsModel.SelectedItem.VmsId))
                {
                    Utils.Section.TemplateSection.Remove(_treeViewVmsModel.SelectedItem.VmsId);
                }
                Utils.Section.TemplateSection.Add(_treeViewVmsModel.SelectedItem.VmsId, obj);
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error(ex);
            }
            

        }

        private void BtnSaveAsTemplate_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;

            if (_treeViewVmsModel.SelectedItem == null)
            {
                TblInfo.Text = "Chọn Vms";
                return;
            }
            if (Section.TemplateSection.ContainsKey(_treeViewVmsModel.SelectedItem.VmsId))
            {
                if (Account.AccountRole == Role.User &&
                    Section.TemplateSection[_treeViewVmsModel.SelectedItem.VmsId].type == 1)
                {
                    TblInfo.Text = "Không có quyền ghi đè chương trình này";
                    return;
                }
            }

            ProgramMessage program = new ProgramMessage();
            program.height = _treeViewVmsModel.SelectedItem.Height;
            program.width = _treeViewVmsModel.SelectedItem.Width;
            Jsoncontract.Content conte = new Content();
            foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
            {

                if (mem is VmsText)
                {
                    String contenttemp = ((mem as VmsText).Content != null)
                        ? (mem as VmsText).Content
                        : string.Empty;
                    string fonttemp = ((mem as VmsText).FontFamily != null)
                        ? (mem as VmsText).FontFamily
                        : string.Empty;
                    conte.text.Add(new Text()
                    {
                        content = contenttemp,
                        name = (mem as VmsText).Name,
                        fontsize = (mem as VmsText).FontSize,
                        font = fonttemp,
                        fontstyle = (mem as VmsText).FontStyle ? "Italic" : "Normal",
                        fontweight = (mem as VmsText).FontWight ? "Bold" : "Normal",
                        height = (int)(mem as VmsText).Height,
                        width = (int)(mem as VmsText).Width,
                        x = (int)(mem as VmsText).X,
                        y = (int)(mem as VmsText).Y,
                        colortext = (mem as VmsText).ColorText

                    });
                }
                else if (mem is VmsImage)
                {
                    string imglink = string.Empty;
                    if ((mem as VmsImage).ImageLink != null)
                        imglink = (mem as VmsImage).ImageLink.Replace("\\", "-");
                    conte.image.Add(new Image()
                    {
                        link = imglink,
                        name = (mem as VmsImage).Name,
                        height = (int)(mem as VmsImage).Height,
                        width = (int)(mem as VmsImage).Width,
                        x = (int)(mem as VmsImage).X,
                        y = (int)(mem as VmsImage).Y
                    });
                }

            }
            string cont = JsonConvert.SerializeObject(conte);
            program.content = cont;
            SaveAsTemplate dialog = new SaveAsTemplate(program);
            dialog.Owner = System.Windows.Window.GetWindow(this);
            dialog.ShowDialog();
        }

        public async void UpdateProgram(int vmsId)
        {
            TblInfo.Text = string.Empty;

            if (_treeViewVmsModel.SelectedItem == null)
            {
                TblInfo.Text = "Chọn Vms";
                return;
            }
            if (Section.TemplateSection.ContainsKey(_treeViewVmsModel.SelectedItem.VmsId))
            {
                if (Account.AccountRole == Role.User &&
                    Section.TemplateSection[_treeViewVmsModel.SelectedItem.VmsId].type == 1)
                {
                    TblInfo.Text = "Không có quyền ghi đè chương trình này";
                    return;
                }
            }

            ProgramMessage programVms = new ProgramMessage();
            programVms.height = _treeViewVmsModel.SelectedItem.Height;
            programVms.width = _treeViewVmsModel.SelectedItem.Width;
            
            Jsoncontract.Content conte = new Content();
            foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
            {

                if (mem is VmsText)
                {
                    String contenttemp = ((mem as VmsText).Content != null)
                        ? (mem as VmsText).Content
                        : string.Empty;
                    string fonttemp = ((mem as VmsText).FontFamily != null)
                        ? (mem as VmsText).FontFamily
                        : string.Empty;
                    conte.text.Add(new Text()
                    {
                        content = contenttemp,
                        name = (mem as VmsText).Name,
                        fontsize = (mem as VmsText).FontSize,
                        font = fonttemp,
                        fontstyle = (mem as VmsText).FontStyle ? "Italic" : "Normal",
                        fontweight = (mem as VmsText).FontWight ? "Bold" : "Normal",
                        height = (int)(mem as VmsText).Height,
                        width = (int)(mem as VmsText).Width,
                        x = (int)(mem as VmsText).X,
                        y = (int)(mem as VmsText).Y,
                        colortext = (mem as VmsText).ColorText

                    });
                }
                else if (mem is VmsImage)
                {
                    string imglink = string.Empty;
                    if ((mem as VmsImage).ImageLink != null)
                        imglink = (mem as VmsImage).ImageLink.Replace("\\", "-");
                    conte.image.Add(new Image()
                    {
                        link = imglink,
                        name = (mem as VmsImage).Name,
                        height = (int)(mem as VmsImage).Height,
                        width = (int)(mem as VmsImage).Width,
                        x = (int)(mem as VmsImage).X,
                        y = (int)(mem as VmsImage).Y
                    });
                }

            }
            string cont = JsonConvert.SerializeObject(conte);
            programVms.content = cont;
            SaveTemplateDialog dialog = new SaveTemplateDialog(programVms, true,vmsId);
            dialog.Owner = System.Windows.Window.GetWindow(this);
            dialog.ShowDialog();
        }

        #endregion Event Click

        /// <summary>
        /// Convert the Canvas to png and base 64 string
        /// </summary>
        /// <param name="surface"></param>
        /// <returns></returns>
        public string ExportToPngBase64String(Canvas surface)
        {
            ////if (path == null) return;

            // Save current canvas transform
            Transform transform = surface.LayoutTransform;
            // reset current transform (in case it is scaled or rotated)
            surface.LayoutTransform = null;

            // Get the size of canvas
            Size size = new Size(surface.Width, surface.Height);
            // Measure and arrange the surface
            // VERY IMPORTANT
            surface.Measure(size);
            surface.Arrange(new Rect(size));

            // Create a render bitmap and push the surface to it
            RenderTargetBitmap renderBitmap =
              new RenderTargetBitmap(
                (int)surface.Width,
                (int)surface.Height,
                96d,
                96d,
                PixelFormats.Pbgra32);
            renderBitmap.Render(surface);

            // Create a file stream for saving image
            using (MemoryStream ms = new MemoryStream())
            {
            // Use png encoder for our data
            JpegBitmapEncoder encoder = new JpegBitmapEncoder();
            // push the rendered bitmap to it
            encoder.Frames.Add(BitmapFrame.Create(renderBitmap));
            // save the data to the stream
            
            encoder.Save(ms);
            //using (FileStream file = File.Create("D:\\Temp.jpg"))
            //{
            //    encoder.Save(file);
            //    return null;
            //}

            byte[] bitmapdata = ms.ToArray();
            surface.LayoutTransform = transform;
            return Convert.ToBase64String(bitmapdata);
            }
            
            // Restore previously saved layout
            
        }

        private void BtnAlignLeft_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if(trvFamilies.SelectedItem == null)
                return;
            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                _treeViewVmsModel.SelectedChildItem.X = 0;
                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                SetDataForSettingScreen();
            }
            else
            {
                
                if (trvFamilies.SelectedItem is VmsMembers)
                {
                    foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
                    {
                        mem.X = 0;
                    }

                }
                Drawing(_treeViewVmsModel.SelectedItem, rate);
            }
        }

        private void BtnAlignRight_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (trvFamilies.SelectedItem == null)
                return;

            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                int moveVal = 0;
                moveVal =
                    (int)(_treeViewVmsModel.SelectedItem.Width -
                         (_treeViewVmsModel.SelectedChildItem.X + _treeViewVmsModel.SelectedChildItem.Width));
                _treeViewVmsModel.SelectedChildItem.X += moveVal;
                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                SetDataForSettingScreen();
            }
            else
            {
                if (trvFamilies.SelectedItem is VmsMembers)
                {
                    foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
                    {
                        int moveVal = 0;
                        moveVal =
                            (int)(_treeViewVmsModel.SelectedItem.Width -
                                 (mem.X + mem.Width));
                        mem.X += moveVal;
                    }

                }
                Drawing(_treeViewVmsModel.SelectedItem, rate);
            }
        }

        private void BtnAlignCentre_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (trvFamilies.SelectedItem == null)
                return;
            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                int moveVal = 0;
                moveVal =
                    (int)((_treeViewVmsModel.SelectedItem.Width -
                         _treeViewVmsModel.SelectedChildItem.Width)/2);
                _treeViewVmsModel.SelectedChildItem.X = moveVal;
                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                SetDataForSettingScreen();
            }
            else
            {
                if (trvFamilies.SelectedItem is VmsMembers)
                {
                    foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
                    {
                        int moveVal = 0;
                        moveVal =
                            (int)((_treeViewVmsModel.SelectedItem.Width -
                                 mem.Width)/2);
                        mem.X = moveVal;
                    }
                }
                Drawing(_treeViewVmsModel.SelectedItem, rate);
            }
        }

        private void BtnAlignTop_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (trvFamilies.SelectedItem == null)
                return;
            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                _treeViewVmsModel.SelectedChildItem.Y = 0;
                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                SetDataForSettingScreen();
            }
            else
            {

                if (trvFamilies.SelectedItem is VmsMembers)
                {
                    foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
                    {
                        mem.Y = 0;
                    }

                }
                Drawing(_treeViewVmsModel.SelectedItem, rate);
            }
        }

        private void BtnAlignBottom_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (trvFamilies.SelectedItem == null)
                return;

            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                int moveVal = 0;
                moveVal =
                    (int)(_treeViewVmsModel.SelectedItem.Height -
                         (_treeViewVmsModel.SelectedChildItem.Y + _treeViewVmsModel.SelectedChildItem.Height));
                _treeViewVmsModel.SelectedChildItem.Y += moveVal;
                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                SetDataForSettingScreen();
            }
            else
            {
                if (trvFamilies.SelectedItem is VmsMembers)
                {
                    foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
                    {
                        int moveVal = 0;
                        moveVal =
                            (int)(_treeViewVmsModel.SelectedItem.Height -
                                 (mem.Y + mem.Height));
                        mem.Y += moveVal;
                    }

                }
                Drawing(_treeViewVmsModel.SelectedItem, rate);
            }
        }

        private void BtnAlignVerCentre_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            if (trvFamilies.SelectedItem == null)
                return;
            if (_treeViewVmsModel.SelectedChildItem != null)
            {
                int moveVal = 0;
                moveVal =
                    (int)((_treeViewVmsModel.SelectedItem.Height -
                         _treeViewVmsModel.SelectedChildItem.Height) / 2);
                _treeViewVmsModel.SelectedChildItem.Y = moveVal;
                Drawing(_treeViewVmsModel.SelectedItem, rate, _treeViewVmsModel.SelectedChildItem.Name);
                SetDataForSettingScreen();
            }
            else
            {
                if (trvFamilies.SelectedItem is VmsMembers)
                {
                    foreach (var mem in _treeViewVmsModel.SelectedItem.Members)
                    {
                        int moveVal = 0;
                        moveVal =
                            (int)((_treeViewVmsModel.SelectedItem.Height -
                                 mem.Height) / 2);
                        mem.Y = moveVal;
                    }
                }
                Drawing(_treeViewVmsModel.SelectedItem, rate);
            }
        }

        private void ItemHelp_OnClick(object sender, RoutedEventArgs e)
        {
            TblInfo.Text = string.Empty;
            string helpfilePath = ConfigurationManager.AppSettings["helpfile"];

            if (!string.IsNullOrEmpty(helpfilePath))
            {
                var path = Directory.GetCurrentDirectory();
                string pathfile = path + helpfilePath;
                if (File.Exists(pathfile))
                {
                    Process.Start(pathfile);
                }
            }
        }
    }
}
