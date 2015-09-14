using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace eVMS.Converters
{
    public class IntToImageConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int imageIndex;
            if(int.TryParse(value.ToString(), out imageIndex))
            {
               switch(imageIndex)
               {
                 case 1:
                       return new BitmapImage(new Uri(@"/Images/Vmson.png", UriKind.Relative));//"Images/Vmson.png";
                       break;
                   default:
                       return new BitmapImage(new Uri(@"/Images/Vmsoff.png", UriKind.Relative));
                       break;

               }
            }

            return null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return null;
        }
    }
}
