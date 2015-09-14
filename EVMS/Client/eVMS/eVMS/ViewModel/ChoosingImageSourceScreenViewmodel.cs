using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;

namespace eVMS.ViewModel
{
    public class ChoosingImageSourceScreenViewmodel:ViewModelBase
    {
        private ObservableCollection<Imagelist> _imageCollection;

        public ObservableCollection<Imagelist> Images
        {
            get { return _imageCollection; }
            set
            {
                if (_imageCollection != value)
                {
                    _imageCollection = value;
                    RaisePropertyChanged(() => Images);
                }
            }
        }

        public ChoosingImageSourceScreenViewmodel()
        {
            //Images = new ObservableCollection<Imagelist>();
        }
    }
}
