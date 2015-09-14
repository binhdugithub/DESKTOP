using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace eVMS.Jsoncontract
{
    public class Text
    {
        public string name { get; set; }
        public string content { get; set; }
        public int x { get; set; }
        public int y { get; set; }
        public int width { get; set; }
        public int height { get; set; }
        public string font { get; set; }
        public string fontweight { get; set; }
        public string fontstyle { get; set; }
        public string fontsize { get; set; }

        public Color colortext { get; set; }
    }

    public class Image
    {
        public string name { get; set; }
        public string link { get; set; }
        public int x { get; set; }
        public int y { get; set; }
        public int width { get; set; }
        public int height { get; set; }
        public int id { get; set; }
    }

    public class program
    {
        public string vmsId { get; set; }
        public List<Text> text { get; set; }
        public List<Image> image { get; set; }
    }

    public class VmsListMessage
    {
        public List<program> programs { get; set; }
    }
    /// <summary>
    /// When user edit a Vms the data convert to image and send to server
    /// </summary>
    public class VmsProgram
    {
        public string vmsId { get; set; }
        public string imagedata { get; set; }
        public List<Text> text { get; set; }
        public List<Image> image { get; set; }
    }

    public class SendingVmsListEditedMessage
    {
        public List<VmsProgram> programs { get; set; }
    }



    public class Desiprogram
    {
        
        public List<Text> text { get; set; }
        public List<Image> image { get; set; }
    }


    public class Vmsmonitoring
    {
        public int id { get; set; }
        public string name { get; set; }
        public string location { get; set; }
        public string width { get; set; }
        public string height { get; set; }
        public int status { get; set; }
        public string screenshoturl { get; set; }
        public string program { get; set; }
        public string ip { get; set; }
    }

    public class VmsmonitoringMessage
    {
        public List<Vmsmonitoring> vmsmonitoring { get; set; }
    }

}
