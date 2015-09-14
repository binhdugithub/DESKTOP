using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    public class AddnewUserMessaget
    {
        public string username { get; set; }
        public string password { get; set; }
        public string fullname { get; set; }

        public string address { get; set; }
        public int sex { get; set; }
        public DateTime birthday { get; set; }
        public string email { get; set; }
        public string phone { get; set; }
        public DateTime currenttime { get; set; }
        public int roleid { get; set; }
    }
}
