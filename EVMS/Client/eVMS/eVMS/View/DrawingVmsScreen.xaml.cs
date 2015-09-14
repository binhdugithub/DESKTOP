using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using eVMS.Model;
using eVMS.ViewModel;
using eVMS.VMS;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for DrawingVmsScreen.xaml
    /// </summary>
    public partial class DrawingVmsScreen : UserControl,INotifyPropertyChanged
    {
        #region Properties
        private VmsMembers _selectedVmsItem;
        public VmsMembers SelectedVmsItem  //Vms object
        {
            get { return _selectedVmsItem; }
            set
            {
                if (_selectedVmsItem != value)
                {
                    _selectedVmsItem = value;
                    RaisePropertyChanged(() => SelectedVmsItem);
                }
            }
        }
        

        private VmsObject _selectedVmschildItem;
        public VmsObject SelectedVmsChildItem
        {
            get { return _selectedVmschildItem; }
            set
            {
                //if (_selectedVmschildItem != value)
                {
                    _selectedVmschildItem = value;
                    //RaisePropertyChanged(() => SelectedVmsChildItem);
                }
            }
        }
        #endregion
        public DrawingVmsScreen()
        {
            InitializeComponent();
        }

        public void SetDataContext(VmsMembers vmsmems, VmsObject vmsobject)
        {
            SelectedVmsItem = vmsmems;
            SelectedVmsChildItem = vmsobject;
            if (vmsobject is VmsImage)
            {
                if (SettingArea.Content is ImageObjectSettingScreen)
                {
                    (SettingArea.Content as ImageObjectSettingScreen).SetDataContext(SelectedVmsChildItem as VmsImage);
                }
                else
                {
                    var imageSetting = new ImageObjectSettingScreen();
                    imageSetting.SetDataContext(SelectedVmsChildItem as VmsImage);
                    SettingArea.Content = imageSetting;
                }
            }
        }


        #region Events

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        #region Event Handlers

        /// <summary>
        /// Get name of property
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="e"></param>
        /// <returns></returns>
        public static string GetPropertyName<T>(Expression<Func<T>> e)
        {
            var member = (MemberExpression)e.Body;
            return member.Member.Name;
        }
        /// <summary>
        /// Raise when property value propertychanged or override propertychage
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="propertyExpression"></param>
        protected virtual void RaisePropertyChanged<T>(Expression<Func<T>> propertyExpression)
        {
            RaisePropertyChanged(GetPropertyName(propertyExpression));
        }
        /// <summary>
        /// Raise when property value propertychanged
        /// </summary>
        /// <param name="propertyName"></param>
        protected void RaisePropertyChanged(String propertyName)
        {
            PropertyChangedEventHandler temp = PropertyChanged;
            if (temp != null)
            {
                temp(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
