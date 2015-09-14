using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    //public class VmsMessage
    //{
    //    public int vmsid { get; set; }
    //    public string vmsname { get; set; }
    //    public double xpos { get; set; }
    //    public double ypos { get; set; }
    //    public string location { get; set; }
    //    public string images { get; set; }
    //    public string text { get; set; }
    //    public object subtitles { get; set; }
    //}

    public class VmslistMessage
    {
        public List<Model.Vms> objectlist { get; set; }
    }
}
