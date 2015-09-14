using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Jsoncontract
{

    public class Content
    {
        public Content ()
        {
            text = new List<Text>();
            image = new List<Image>();
        }

        public List<Text> text { get; set; }
        public List<Image> image { get; set; }
    }
    public class ProgramMessage
    {
        //public ProgramMessage()
        //{
        //    content = new Content();
        //}

        public string name { get; set; }
        public int type { get; set; }
        public int width { get; set; }
        public int height { get; set; }

        public string content { get; set; }
    }

    public class ProgramUpdateMessage
    {
        //public ProgramMessage()
        //{
        //    content = new Content();
        //}

        public string name { get; set; }
        public int type { get; set; }
        public int id { get; set; }
        public int width { get; set; }
        public int height { get; set; }

        public string content { get; set; }
    }

    public class ShortProgram
    {
        public string name { get; set; }
        public int type { get; set; }

        public int width { get; set; }
        public int height { get; set; }

        public int id { get; set; }
    }

    public class ShortProgrammMessage
    {
        public ShortProgrammMessage()
        {
            programs = new List<ShortProgram>();
        }

        public List<ShortProgram> programs { get; set; }
    }
}
