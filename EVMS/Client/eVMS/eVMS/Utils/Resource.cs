using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;

namespace eVMS.Utils
{
    
    public static class Account
    {
        public static string AccountName = string.Empty;
        public static Role AccountRole = Role.Admin;

        //public static Dictionary<> 
        public static string CalculateMD5Hash(string input)
        {
            // step 1, calculate MD5 hash from input
            MD5 md5 = System.Security.Cryptography.MD5.Create();
            byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);
            byte[] hash = md5.ComputeHash(inputBytes);

            // step 2, convert byte array to hex string
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < hash.Length; i++)
            {
                sb.Append(hash[i].ToString("X2"));
            }
            return sb.ToString();
        }
    }

    public static class ServerSettingDefine
    {
        public static string Service ="http://"+ Properties.Settings.Default["ServerIp"].ToString() + ":" +
                             Properties.Settings.Default["Port"].ToString();
    }

    public static class MessageInfo
    {
        public static Dictionary<int, string> MessInfoCode = new Dictionary<int, string>
        {
            {0, "Thành công"},
            {400,	"Không tồn tại user"},
            {401,	"Không có template"},
            {402,	"Không save được tempalte"},
            {403,	"Không có history"},
            {404,	"User đã tồn tại"},
            {405,	"Sai mật khẩu"},
            {406,	"Không tồn tại thiết bị VMS"},
            {407,	"Tên template đã tồn tại"},
            {408,	"Template không tồn tại"},
            {409,	"Không có Url này"},
            {410,	"Content type phải là app/json"},
            {411,	"Dữ liệu nhận không phải json"},
            {420,	"Không chèn được dữ liệu vms"},
            {421,	"Tên VMS đã tồn tại"},
            {422,	"Địa chỉ Ip đã tồn tại"},
            {423,	"Cập nhật VMS không thành công"},
            {424,	"Xóa VMS không thành công"},
            {425,	"Nhận dữ liệu VMS không thành công"},
            {426,	"Phân bổ VMS không thành công"},
            {431,	"Không chèn được quyền hạn"},
            {432,	"Không cập nhật được quyền hạn"},
            {433,	"Không xóa được quyền hạn"},
            {434,	"Không nhận được dữ liệu quyền hạn"},
            {440,	"Không chèn được dữ liệu chương trình"},
            {441,	"Không cập nhật được dữ liệu chương trình"},
            {442,	"Không xóa được chương trình"},
            {443,	"Không nhận được dữ liệu chương trình"},
            {450,	"Không cập nhật được dữ liệu người dùng"},
            {451,	"Không chèn được dữ liệu người dùng"},
            {452,	"Không xóa được dữ liệu người dùng"},
            {453,	"Không nhận được dữ liệu người dùng"},
            //
            {460,	"Gửi dữ liệu thành công"},
            {461,	"Gửi dữ liệu không thành công"},

        };

    
    }

    public static class ColorInfo
    {
        public static Dictionary<int, string> ColorInfoCode = new Dictionary<int, string>
        {
            
            {101,	"#FFFF0000,#FF0000FF"},
            {110,	"#FFFF0000,#FF00FF00"},
            {011,	"#FF00FF00,#FF0000FF"}
        };


    }

    public static class ErrorInfoVi
    {
        public static string EnterSameNameInfo = "Trùng tên";
        public static string EnterEmptyNameInfo = "Nhập tên cho đối tượng";
        public static string ServerCannotConnect = "Lỗi kết nối hoặc không có dữ liệu";
        public static string CheckingServerConnect = "Kiểm tra lại máy chủ và cổng";
        public static string NoComponent = "Không có nội dung nào";

        public static string VmsDataNotSync =
            "Dữ liệu VMS hiện tại không đồng bộ với khu vực điều khiển, bạn có muốn đồng bộ không";
    }

    public enum Role
    {
        Admin,
        User
    }

    public static class Section
    {
        public static Dictionary<int, ProgramUpdateMessage> TemplateSection = new Dictionary<int, ProgramUpdateMessage>(); 
    }

    public static class StringUtil
    {
        public static bool IsFullName(string name)
        {
            string specialCharacters = @"%!@#$%^&*()?/>.<,:;'\|}]{[_~`+=-" + "\"";
            char[] specialCharactersArray = specialCharacters.ToCharArray();

            int index = name.IndexOfAny(specialCharactersArray);
            //index == -1 no special characters
            if (index == -1)
                return true;
            else
                return false;
        }
    }
}
