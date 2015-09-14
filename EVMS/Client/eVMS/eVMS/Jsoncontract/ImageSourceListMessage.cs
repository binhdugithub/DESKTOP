using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{
    public class ImageSourceListMessage
    {
        public List<Imagelist> imagelist { get; set; }
    }

    public class Imagelist
    {
        public int id { get; set; }
        public string link { get; set; }
        public string name { get; set; }
    }
}
