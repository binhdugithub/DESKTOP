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
using eVMS.Jsoncontract;
using eVMS.Utils;
using eVMS.ViewModel;
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for HistoryScreen.xaml
    /// </summary>
    public partial class HistoryScreen : UserControl
    {
        private HistoryViewModel _viewmode;
        
        public HistoryScreen()
        {
            InitializeComponent();
            DpStartSearch.SelectedDate = DateTime.Now;
            DpEndDateSearch.SelectedDate = DateTime.Now;
            _viewmode = new HistoryViewModel();
            DataContext = _viewmode;
        }

        private void DpStartSearch_OnSelectedDateChanged(object sender, SelectionChangedEventArgs e)
        {
            if (DpEndDateSearch.SelectedDate != null)
            {
                if (DpEndDateSearch.SelectedDate < DpStartSearch.SelectedDate)
                    DpEndDateSearch.SelectedDate = DpStartSearch.SelectedDate;
            }
        }

        private void DpEndDateSearch_OnSelectedDateChanged(object sender, SelectionChangedEventArgs e)
        {
            if (DpStartSearch.SelectedDate != null)
            {
                if (DpEndDateSearch.SelectedDate < DpStartSearch.SelectedDate)
                    DpEndDateSearch.SelectedDate = DpStartSearch.SelectedDate;
            }
        }

        private async void BtnSearch_OnClick(object sender, RoutedEventArgs e)
        {
            FluidProgressBar.Visibility = Visibility.Visible;

            var dateStart = (DateTime)DpStartSearch.SelectedDate;
            string start = dateStart.Year + "-" + dateStart.Month + "-" + dateStart.Day + " 00:00:1";
            var dateEnd = (DateTime)DpEndDateSearch.SelectedDate;
            string end = dateEnd.Year + "-" + dateEnd.Month + "-" + dateEnd.Day + " 23:59:59";
            var res = await _viewmode.GetHistoryDataFromServer(start,end, 0, 14);
            FluidProgressBar.Visibility = Visibility.Hidden;

            if (res == null)
            {
                MessageBox.Show( ErrorInfoVi.ServerCannotConnect);
                return;
            }
            if (res != null)
            {
                if(res.historylist == null)
                {
                    MessageBox.Show("Không có dữ liệu");
                    return;
                }
                else 
                {
                    if (res.historylist.Count == 0)
                    {
                        MessageBox.Show("Không có dữ liệu");
                        return;
                    }
                }
            }

            try
            {
                _viewmode.Resetpaging();
                _viewmode.Histories = new ObservableCollection<Historylist>(res.historylist);
                _viewmode.SetNumberOfData(res.rows);
                _viewmode.TotalItems = res.rows;
                _viewmode.SetProperties();
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error(ex);
                return;
            }
        }

        public String GetTimestamp(DateTime value)
        {
            return value.ToString("yyyyMMddHHmmssffff");
        }

        private async void NextButton_OnClick(object sender, RoutedEventArgs e)
        {
            FluidProgressBar.Visibility = Visibility.Visible;

            var dateStart = (DateTime)DpStartSearch.SelectedDate;
            string start = dateStart.Year + "-" + dateStart.Month + "-" + dateStart.Day + " 00:00:1";
            var dateEnd = (DateTime)DpEndDateSearch.SelectedDate;
            string end = dateEnd.Year + "-" + dateEnd.Month + "-" + dateEnd.Day + " 23:59:59";
            var res = await _viewmode.GetHistoryDataFromServer(start, end, _viewmode.Start, _viewmode.Start + _viewmode.ItemCount);
            FluidProgressBar.Visibility = Visibility.Hidden;

            if (res == null)
            {
                MessageBox.Show(ErrorInfoVi.ServerCannotConnect);
                return;
            }

            try
            {
                _viewmode.Histories = new ObservableCollection<Historylist>(res.historylist);
                _viewmode.SetNumberOfData(res.rows);
                _viewmode.TotalItems = res.rows;
                _viewmode.SetProperties();
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error(ex);
                return;
            }
        }
    }
}
