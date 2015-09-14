using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;

namespace eVMS.Model
{
     public class Vms
    {
        public int id { get; set; }
        public string name { get; set; }
        
        public string description { get; set; }

        public string location { get; set; }

         public bool status { get; set; }

         public string program { get; set; }

         public string ip { get; set; }

         public int port { get; set; }

         public string model { get; set; }
         public int deviceid { get; set; }
         public string width { get; set; }

         public string height { get; set; }

         public int nColor { get; set; }

         public List<Vmstype> multitype { get; set; }
    }
}
