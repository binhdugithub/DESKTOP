using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using eVMS.Commands;
using eVMS.Jsoncontract;
using eVMS.Utils;
using Microsoft.Windows.Controls;
using Newtonsoft.Json;
using RestSharp;

namespace eVMS.ViewModel
{
    public class HistoryViewModel : ViewModelBase
    {

        #region Private Fields

        private int start = 0;

         int itemCount = 14;

        public int ItemCount
        {
            get { return itemCount; }
            set { itemCount = value; }
        }

        private string sortColumn = "Id";

        private bool ascending = true;

        private int totalItems = 0;

        private ICommand firstCommand;

        private ICommand previousCommand;

        private ICommand nextCommand;

        private string startDate = string.Empty;
        private string endDate = string.Empty;
        #endregion

        #region Proper
        private bool _count;
        public bool Count
        {
            get { return _count; }
            //set
            //{
            //    _count = value;
            //    RaisePropertyChanged("Count");
            //}
        }

        //private string _totalMoney;
        //public string TotalMoney
        //{
        //    get { return _totalMoney; }
        //    set
        //    {
        //        _totalMoney = value;
        //        RaisePropertyChanged("TotalMoney");
        //    }
        //}
        
        //-----------------------------------------------//
        //This area for command properties
        /// <summary>
        /// Gets the index of the first item in the products list.
        /// </summary>
        public int Start { get { return start + 1; } }

        /// <summary>
        /// Gets the index of the last item in the products list.
        /// </summary>
        public int End { get { return start + itemCount < totalItems ? start + itemCount : totalItems; } }

        /// <summary>
        /// The number of total items in the data store.
        /// </summary>
        public int TotalItems
        {
            get { return totalItems; }
            set { totalItems = value; }
        }
        //End Area
        //---------------------------------------------------//
        #endregion

        private ICommand lastCommand;

        private ObservableCollection<Historylist> _histories;
        public ObservableCollection<Historylist> Histories
        {
            get { return _histories; }
            set
            {
                if (_histories != value)
                {
                    _histories = value;
                    RaisePropertyChanged(() => Histories);
                }
            }
        }

        public HistoryViewModel()
        {
            Histories = new ObservableCollection<Historylist>();
        }

        #region Method

        public async void GetItemsMan(int start)
        {
            var res = await GetHistoryDataFromServer(startDate, endDate, start+1, start+itemCount);
            if (res != null)
            {
                Histories = new ObservableCollection<Historylist>(res.historylist);
                TotalItems = res.rows;
                SetNumberOfData(res.rows);
            }
            else
            {
                MessageBox.Show("Dữ liệu lỗi hoặc không có dữ liệu");
            }
        }

    public void SetNumberOfData(int count)
        {
            if (count > 10)
                _count = true;
            else
                _count = false;
        }

        public void Resetpaging()
        {
            start = 0;
        }

        public void SetProperties()
        {
            RaisePropertyChanged(() => Start);
            RaisePropertyChanged(() => End);
            RaisePropertyChanged(() => TotalItems);
            RaisePropertyChanged(() => Count);
        }


        #endregion

        #region task
        /// <summary>
        /// http://192.168.7.32:8089/api/evms/history?username=hoanglm&action=20&timestart=2015-08-11&timeend=2015-08-12&from=0&to=10
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        /// <returns></returns>
        public async Task<VmsHistoryMessage> GetHistoryDataFromServer(string start, string end, int from = 0, int to = 10)
        {
            try
            {
                startDate = start;
                endDate = end;

                var client = new RestSharp.RestClient(ServerSettingDefine.Service);
                string reUrl = ConfigurationManager.AppSettings["getlisthistory"];
        
                //request.AddParameter("timestart", DpStartSearch.SelectedDate);
                reUrl += string.Format("?timestart={0}", start);
                
                reUrl += string.Format("&timeend={0}", end);
                //request.AddParameter("timeend", DpEndDateSearch.SelectedDate);

                var request = new RestRequest(reUrl, Method.GET);
                request.AddParameter("username", string.Empty);
                request.AddParameter("from", from);
                request.AddParameter("to", to);

                var ok = await Task<string>.Factory.StartNew(() =>
                {
                    var res = client.Execute(request);
                    return res.Content;
                }
                );

                var resHis = JsonConvert.DeserializeObject<VmsHistoryMessage>(ok);
                return resHis;
            }
            catch (Exception ex)
            {
                Log4Net.Log.Error(ex.ToString());
                return null;
            }
        }
        #endregion

        #region Command
        /// <summary>
        /// Gets the command for moving to the first page of products.
        /// </summary>
        public ICommand FirstCommand
        {
            get
            {
                if (firstCommand == null)
                {
                    firstCommand = new RelayCommand
                    (
                        param =>
                        {
                            start = 0;
                            //LoadAllData();
                            GetItemsMan(start);

                            //SetHomeViewModelData(items);
                            SetNumberOfData(totalItems);
                            RaisePropertyChanged(() => Start);
                            RaisePropertyChanged(() => End);
                            RaisePropertyChanged(() => TotalItems);
                            RaisePropertyChanged(() => Count);
                        },
                        param =>
                        {
                            return start - itemCount >= 0 ? true : false;
                        }
                    );
                }

                return firstCommand;
            }
        }

        /// <summary>
        /// Gets the command for moving to the previous page of products.
        /// </summary>
        public ICommand PreviousCommand
        {
            get
            {
                if (previousCommand == null)
                {
                    previousCommand = new RelayCommand
                    (
                        param =>
                        {
                            start -= itemCount;
                            //LoadAllData();
                             GetItemsMan(start);
                            //SetHomeViewModelData(items);
                            SetNumberOfData(totalItems);
                            RaisePropertyChanged(() => Start);
                            RaisePropertyChanged(() => End);
                            RaisePropertyChanged(() => TotalItems);
                            RaisePropertyChanged(() => Count);
                        },
                        param =>
                        {
                            return start - itemCount >= 0 ? true : false;
                        }
                    );
                }

                return previousCommand;
            }
        }

        /// <summary>
        /// Gets the command for moving to the next page of products.
        /// </summary>
        public ICommand NextCommand
        {
            get
            {
                if (nextCommand == null)
                {
                    nextCommand = new RelayCommand
                    (
                        param =>
                        {
                            start += itemCount;
                            //LoadAllData();
                            GetItemsMan(start);

                            //SetHomeViewModelData(items);
                            SetNumberOfData(totalItems);
                            RaisePropertyChanged(() => Start);
                            RaisePropertyChanged(() => End);
                            RaisePropertyChanged(() => TotalItems);
                            RaisePropertyChanged(() => Count);
                        },
                        param =>
                        {
                            return start + itemCount < totalItems ? true : false;
                        }
                    );
                }

                return nextCommand;
            }
        }

        /// <summary>
        /// Gets the command for moving to the last page of products.
        /// </summary>
        public ICommand LastCommand
        {
            get
            {
                if (lastCommand == null)
                {
                    lastCommand = new RelayCommand
                    (
                        param =>
                        {
                            start = (totalItems / itemCount - 1) * itemCount;
                            start += totalItems % itemCount == 0 ? 0 : itemCount;
                            //LoadAllData();
                            GetItemsMan(start);

                            //SetHomeViewModelData(items);
                            SetNumberOfData(totalItems);
                            RaisePropertyChanged(() => Start);
                            RaisePropertyChanged(() => End);
                            RaisePropertyChanged(() => TotalItems);
                            RaisePropertyChanged(() => Count);
                        },
                        param =>
                        {
                            return start + itemCount < totalItems ? true : false;
                        }
                    );
                }

                return lastCommand;
            }
        }

        #endregion
    }
}
