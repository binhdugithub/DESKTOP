using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Model;

namespace eVMS.ViewModel
{
    public class AssignVmsViewModel:ViewModelBase
    {
        #region Mems
        
        #endregion
        #region Properties
        #region Com
        //public AssignVmsModel AssignVms
        //{
        //    get
        //    {
        //        return _assign;
        //    }
        //    set
        //    {
        //        _assign = value;
        //    }
        //}

        //public Vms AllVms
        //{
        //    get { return AssignVms.AllVms; }
        //    set
        //    {
        //        AssignVms.AllVms = value;
        //        if (AssignVms.AllVms != value)
        //        {
        //            AssignVms.AllVms = value;
        //            RaisePropertyChanged(() => AllVms);
        //        }
        //    }
        //}

        //public bool IsSelected
        //{
        //    get { return AssignVms.IsSelected; }
        //    set
        //    {
        //        AssignVms.IsSelected = value;
        //        if (AssignVms.IsSelected != value)
        //        {
        //            AssignVms.IsSelected = value;
        //            RaisePropertyChanged(() => IsSelected);
        //        }
        //    }
        //}
        #endregion

        private ObservableCollection<AssignVmsModel> _assignVms;
        public ObservableCollection<AssignVmsModel> AllVmsItem
        {
            get { return _assignVms; }
            set
            {
                if (_assignVms != value)
                {
                    _assignVms = value;
                    RaisePropertyChanged(() => AllVmsItem);
                }
            }
        }
        #endregion

        #region Construction
        /// Constructs the default instance of a SongViewModel
        public AssignVmsViewModel()
        {
            _assignVms = new ObservableCollection<AssignVmsModel>();

        }
        #endregion
    }

    public class AssignVmsModel
    {
        public Vms VmsItem { get; set; }
        public bool IsSelected { get; set; }
    }


}
