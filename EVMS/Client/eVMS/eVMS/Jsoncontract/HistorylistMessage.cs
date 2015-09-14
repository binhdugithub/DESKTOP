using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    /// <summary>
    /// http://192.168.7.32:8089/api/evms/history?username=hoanglm&action=20&timestart=2015-08-11&timeend=2015-08-12&from=0&to=10
    /// </summary>
    public class Historylist
    {
        public int action { get; set; }
        public string actionname { get; set; }
        public string detail { get; set; }
        public int id { get; set; }
        public string time { get; set; }
        public string username { get; set; }
    }

    public class VmsHistoryMessage
    {
        public VmsHistoryMessage()
        {
            historylist = new List<Historylist>();
        }

        public List<Historylist> historylist { get; set; }
        public int rows { get; set; }
    }
}
