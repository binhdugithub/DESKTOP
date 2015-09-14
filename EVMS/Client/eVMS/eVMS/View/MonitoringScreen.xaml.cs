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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using eVMS.Jsoncontract;
using eVMS.Utils;
using eVMS.ViewModel;
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for MornitoringScreen.xaml
    /// </summary>
    public partial class MonitoringScreen : UserControl
    {
        #region Variable
        private int numScreen = 5;
        private MonitoringScreenViewmodel _viewmodel;
        private DispatcherTimer dispatcherTimer;
        public event Action<Vmsmonitoring> DoubleClickVmsEvent;
        #endregion
        

         #region Constructor
        public MonitoringScreen()
        {
            InitializeComponent();
            _viewmodel = new MonitoringScreenViewmodel();
            DataContext = _viewmodel;

            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Tick -=DispatcherTimerOnTick;
            dispatcherTimer.Interval = new TimeSpan(0, 0, 10);
            dispatcherTimer.Start();
        }

        private void DispatcherTimerOnTick(object sender, EventArgs eventArgs)
        {
            
        }

        private async void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            var res = await GetVmsListMonitoringFromtoServer(Account.AccountName);
            if(res == null)
                return;
            if(res.vmsmonitoring == null)
                return;

            var emmptr = new ObservableCollection<Vmsmonitoring>(res.vmsmonitoring);

            if (_viewmodel.VmsCollection != emmptr)
                SetDataContext(res);
        }

        public void StopTimer()
        {
            if (dispatcherTimer != null)
            {
                dispatcherTimer.Stop();
            }
        }

        public MonitoringScreen(MonitoringScreenViewmodel viewmodel):this()
        {
            _viewmodel = viewmodel;
        }

        public void SetDataContext(VmsmonitoringMessage mess)
        {
            if (mess.vmsmonitoring == null)
                return;

            _viewmodel.VmsCollection = new ObservableCollection<Vmsmonitoring>(mess.vmsmonitoring);
        }

        #endregion

        #region Method
        //public void DrawLineinGrid()
        //{
        //    //Draw a custom line on centre grid
        //    if (numScreen != -1)
        //    {
        //        var heigh = GrCentreScreen.ActualHeight;
        //        var width = GrCentreScreen.ActualWidth;
        //        if (heigh > 0 && width > 0)
        //        {
        //            for (int i = 1; i < numScreen; i++)
        //            {
        //                //Draw vertical line
        //                var X = (width) / numScreen;
        //                var Y = heigh;

        //                var verLine = new Line();
        //                verLine.X1 = X;
        //                verLine.Y1 = 0;

        //                verLine.X2 = X;
        //                verLine.Y2 = Y;
        //                verLine.StrokeThickness = 1;
        //                verLine.Stroke = new SolidColorBrush(Colors.Black);
        //                Grid.SetColumn(verLine, i - 1);
        //                Grid.SetRowSpan(verLine, numScreen);
        //                GrCentreScreen.Children.Add(verLine);
        //                //End vertical

        //                //Draw horizion line
        //                var Yhorizon = heigh / numScreen;

        //                var hoLine = new Line();
        //                hoLine.X1 = 0;
        //                hoLine.Y1 = Yhorizon;

        //                hoLine.X2 = width;
        //                hoLine.Y2 = Yhorizon;

        //                hoLine.StrokeThickness = 1;
        //                hoLine.Stroke = new SolidColorBrush(Colors.Black);
        //                Grid.SetRow(hoLine, i - 1);
        //                Grid.SetColumnSpan(hoLine, numScreen);
        //                GrCentreScreen.Children.Add(hoLine);
        //                //End Draw
        //            }
        //        }
        //    }

        //    //end
        //}

        //private void DrawControls(int numberScreen)
        //{
        //    numScreen = numberScreen;
        //    GrCentreScreen.Children.Clear();
        //    // Adding Rows and Colums to Grid.
        //    //int count = 2; // 2x2
        //    RowDefinition[] rows = new RowDefinition[numberScreen];
        //    ColumnDefinition[] columns = new ColumnDefinition[numberScreen];
        //    // Draw Rows.
        //    for (int i = 0; i < numberScreen; i++)
        //    {
        //        rows[i] = new RowDefinition();
        //        // Setting Row height.
        //        rows[i].Height = new GridLength(1, GridUnitType.Star);
        //        GrCentreScreen.RowDefinitions.Add(rows[i]);

        //    }

        //    // Draw Columns.
        //    for (int i = 0; i < numberScreen; i++)
        //    {
        //        columns[i] = new ColumnDefinition();
        //        columns[i].Width = new GridLength(1, GridUnitType.Star);
        //        GrCentreScreen.ColumnDefinitions.Add(columns[i]);

        //    }

        //    //Draw Screen in Grid
        //    for (int i = 0; i < numberScreen; i++)
        //        for (int j = 0; j < numberScreen; j++)
        //        {
                    
        //            //VideoScreenUserControl video = ResourceUtil.Listvideo[i * numberScreen + j];
        //            //video.MouseLeftButtonDown += video_MouseLeftButtonDown;
        //            //Grid.SetRow(video, i);
        //            //Grid.SetColumn(video, j);
                    
        //            //GrCentreScreen.Children.Add(video); //hoanlm change
        //             VmsMonitoringScreen mor = new VmsMonitoringScreen();
        //            Border content = new Border();
        //            content.Padding = new Thickness(5);
        //            content.CornerRadius = new CornerRadius(5);
        //            content.ClipToBounds = true;
        //            content.Child = mor;
        //            Grid.SetRow(content, i);
        //            Grid.SetColumn(content, j);
        //            GrCentreScreen.Children.Add(content);
        //        }
        //}
        #endregion Method

        private void UIElement_OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            
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

        public void DoubleClickHandler(object sender, MouseEventArgs e)
        {
            var item = sender as ListBoxItem;
            if(item == null)
                return;

            if (item.Content is Vmsmonitoring)
            {
                if (DoubleClickVmsEvent != null)
                    DoubleClickVmsEvent(item.Content as Vmsmonitoring);
            }
        }
    }
}
