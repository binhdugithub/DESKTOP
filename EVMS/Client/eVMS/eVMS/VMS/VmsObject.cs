using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;
using eVMS.ViewModel;

namespace eVMS.VMS
{
    public class VmsObject
    {
        public string Name { get; set; }
        public string Avatar { get; set; }

        private float _width;

        public float Width
        {
            get { return _width; }
            set
            {
                if (_width != value)
                {
                    _width = value;
                    RaisePropertyChanged("Width");
                }
            }
        }

        public bool IsSelected { get; set; }
        public float Height { get; set; }

        public float X { get; set; }
        public float Y { get; set; }


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

    public class VmsText:VmsObject
    {
        public string Content { get; set; }
        public bool FontWight { get; set; }
        public string FontFamily { get; set; }
        public bool FontStyle { get; set; }
        public string FontSize { get; set; }

        public Color ColorText { get; set; }
    }

    public class VmsImage : VmsObject
    {
        private string _image;

        public string ImageLink
        {
            get { return _image; }
            set
            {
                if (_image != value)
                {
                    _image = value;
                    RaisePropertyChanged(()=>ImageLink);
                }
            }
        }

        //public string FontWight { get; set; }
        //public int FontSize { get; set; }
    }

    public class VmsMembers:ViewModelBase
    {
        public VmsMembers()
        {
            this.Members = new ObservableCollection<VmsObject>();
        }

        public int Width { get; set; }
        public int Height { get; set; }

        public int nColor { get; set; }

        private string _name;
        private int _id;

        public string Name
        {
            get { return _name; }
            set {
                if (_name != value)
                {
                    _name = value;
                    RaisePropertyChanged(()=>Name);
                }
            }
        }

        public int VmsId
        {
            get { return _id; }
            set
            {
                if (_id != value)
                {
                    _id = value;
                    RaisePropertyChanged(() => VmsId);
                }
            }
        }


        private ObservableCollection<VmsObject> _members;


        public ObservableCollection<VmsObject> Members
        {
            get { return _members; }
            set
            {
                if (_members != value)
                {
                    _members = value;
                    RaisePropertyChanged(()=>Members);
                }
            }
        }
    }
}
