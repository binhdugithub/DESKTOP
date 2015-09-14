using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    public class VmsDeviceMessage
    {
        public List<Vmsmodel> vmsmodels { get; set; }

        public VmsDeviceMessage()
        {
            vmsmodels = new List<Vmsmodel>();
        }
    }

    public class Vmstype
    {
        public string typename { get; set; }
    }

    public class Vmsmodel
    {
        public string modelname { get; set; }
        public int deviceid { get; set; }
        public string width { get; set; }
        public string height { get; set; }
        public int nColor { get; set; }
        public List<Vmstype> vmstype { get; set; }

        public Vmsmodel()
        {
            vmstype = new List<Vmstype>();
        }
    }

    
}
