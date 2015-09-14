using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media.Imaging;
using eVMS.Jsoncontract;
using eVMS.Utils;
using Newtonsoft.Json;

namespace eVMS.Converters
{
    class ProgramtoStatusVMSConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if(value== null)
                return ErrorInfoVi.NoComponent;
            else
            {
                if(value.ToString() == string.Empty)
                    return ErrorInfoVi.NoComponent;

                try
                {
                    var json = JsonConvert.DeserializeObject<Jsoncontract.Content>(value.ToString());
                    if (json.image != null && json.text != null)
                    {
                        if(json.image.Count == 0 && json.text.Count ==0)
                            return ErrorInfoVi.NoComponent;
                    }
                    
                }
                catch (Exception ex)
                {
                    Log4Net.Log.Debug(ex);

                }
            }
            return string.Empty;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return null;
        }
    }
}
