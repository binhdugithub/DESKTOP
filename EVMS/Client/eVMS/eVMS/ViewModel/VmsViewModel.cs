using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;
using eVMS.Model;

namespace eVMS.ViewModel
{
    public class VmsViewModel:ViewModelBase
    {
        #region Mems
        Vms _vms;
        #endregion

        #region Construction
        /// Constructs the default instance of a SongViewModel
        public VmsViewModel()
        {
            VMS = new Vms();
            Vmstypes = new List<Vmstype>();
        }
        #endregion

        #region Properties
        public Vms VMS
        {
            get
            {
                return _vms;
            }
            set
            {
                _vms = value;
            }
        }

        public int VmsId
        {
            get { return VMS.id; }
            set
            {
                VMS.id = value;
                if (VMS.id != value)
                {
                    VMS.id = value;
                    RaisePropertyChanged(() => VmsId);
                }
            }
        }

        public string Vmsname
        {
            get { return VMS.name; }
            set
            {
                VMS.name = value;
                if (VMS.name != value)
                {
                    VMS.name = value;
                    RaisePropertyChanged(() => Vmsname);
                }
            }
        }

        public string Location
        {
            get { return VMS.location; }
            set
            {
                VMS.location = value;
                if (VMS.location != value)
                {
                    VMS.location = value;
                    RaisePropertyChanged(() => Location);
                }
            }
        }

        public string Description
        {
            get { return VMS.description; }
            set
            {
                VMS.description = value;
                if (VMS.description != value)
                {
                    VMS.description = value;
                    RaisePropertyChanged(() => Description);
                }
            }
        }

        public string Width
        {
            get { return VMS.width; }
            set
            {
                VMS.width = value;
                if (VMS.width != value)
                {
                    VMS.width = value;
                    RaisePropertyChanged(() => Width);
                }
            }
        }

        public string Height
        {
            get { return VMS.height; }
            set
            {
                VMS.height = value;
                if (VMS.height != value)
                {
                    VMS.height = value;
                    RaisePropertyChanged(() => Height);
                }
            }
        }

        public bool Status
        {
            get { return VMS.status; }
            set
            {
                VMS.status = value;
                if (VMS.status != value)
                {
                    VMS.status = value;
                    RaisePropertyChanged(() => Status);
                }
            }
        }

        public string Ip
        {
            get { return VMS.ip; }
            set
            {
                VMS.ip = value;
                if (VMS.ip != value)
                {
                    VMS.ip = value;
                    RaisePropertyChanged(() => Ip);
                }
            }
        }

        public string Model
        {
            get { return VMS.model; }
            set
            {
                VMS.model = value;
                if (VMS.model != value)
                {
                    VMS.model = value;
                    RaisePropertyChanged(() => Model);
                }
            }
        }

        public int DeviceId
        {
            get { return VMS.deviceid; }
            set
            {
                VMS.deviceid = value;
                if (VMS.deviceid != value)
                {
                    VMS.deviceid = value;
                    RaisePropertyChanged(() => DeviceId);
                }
            }
        }

        public int Port
        {
            get { return VMS.port; }
            set
            {
                //VMS.port = value;
                if (VMS.port != value)
                {
                    VMS.port = value;
                    RaisePropertyChanged(() => Port);
                }
            }
           
        }

        public List<Vmstype> Vmstypes { get; set; }


        #endregion
    }
}
