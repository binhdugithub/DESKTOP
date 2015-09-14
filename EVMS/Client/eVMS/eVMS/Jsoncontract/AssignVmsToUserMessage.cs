using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    class AssignVmsToUserMessage
    {
        public string username { get; set; }
        public List<VM> VMS { get; set; }
    }

    public class VM
    {
        public string VmsId { get; set; }
    }
    
}
