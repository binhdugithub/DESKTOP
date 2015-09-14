using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    public class UserAccount
    {
        public string userName { get; set; }

        public string fullName { get; set; }
        public string password { get; set; }

        public string sex { get; set; }

        public DateTime birthday { get; set; }

        public string email { get; set; }

        public string phone { get; set; }

        public DateTime currentTime { get; set; }

        public int roleid { get; set; }

    }
}
