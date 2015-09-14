using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;

namespace eVMS.ViewModel
{
    public class MonitoringScreenViewmodel:ViewModelBase
    {
        private ObservableCollection<Vmsmonitoring> _vmsCollection;

        public ObservableCollection<Vmsmonitoring> VmsCollection
        {
            get { return _vmsCollection; }
            set
            {
                if (_vmsCollection != value)
                {
                    _vmsCollection = value;
                    RaisePropertyChanged(()=>VmsCollection);
                }
            }
        }

        public MonitoringScreenViewmodel()
        {
            VmsCollection = new ObservableCollection<Vmsmonitoring>();
        }

    }

    //public class MonitoringModel : ViewModelBase
    //{
    //    public int vmsid { get; set; }
    //    public string vmsname { get; set; }

    //    public string screenshot { get; set; }

    //    public string location { get; set; }

    //    public bool status { get; set; }
    //}
}
