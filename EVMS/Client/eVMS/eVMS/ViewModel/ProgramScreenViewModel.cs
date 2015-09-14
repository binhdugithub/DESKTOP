using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;

namespace eVMS.ViewModel
{
    public class ProgramScreenViewModel:ViewModelBase
    {

        private ObservableCollection<ShortProgram> _programs;
        public ObservableCollection<ShortProgram> Programs
        {
            get { return _programs; }
            set
            {
                if (_programs != value)
                {
                    _programs = value;
                    RaisePropertyChanged(() => Programs);
                }
            }
        }

        public ProgramScreenViewModel()
        {
            Programs = new ObservableCollection<ShortProgram>();
        }

        //public void SetDataModel(List<ShortProgram> program)
        //{
        //    Programs.Clear();
        //    = program;
        //}
    }
}
