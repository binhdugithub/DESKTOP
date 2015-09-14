using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interactivity;

namespace eVMS.Utils
{
    public class DoubleClickBehavior : Behavior<TextBox>
    {
        protected override void OnAttached()
        {
            AssociatedObject.MouseDoubleClick += AssociatedObjectMouseDoubleClick;
            base.OnAttached();
        }

        protected override void OnDetaching()
        {
            AssociatedObject.MouseDoubleClick -= AssociatedObjectMouseDoubleClick;
            base.OnDetaching();
        }

        private void AssociatedObjectMouseDoubleClick(object sender, RoutedEventArgs routedEventArgs)
        {
            AssociatedObject.SelectAll();
        }
    }
}
