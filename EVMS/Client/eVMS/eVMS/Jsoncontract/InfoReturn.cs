using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    public class InfoReturn
    {
        public string description { get; set; }
        public bool error { get; set; }
        public string message { get; set; }
        public int status { get; set; }
    }
}
