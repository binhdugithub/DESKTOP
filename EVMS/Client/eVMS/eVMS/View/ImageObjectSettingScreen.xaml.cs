using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Text.RegularExpressions;
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
using eVMS.VMS;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for TextObjectSettingScreen.xaml
    /// </summary>
    public partial class ImageObjectSettingScreen : UserControl,INotifyPropertyChanged
    {

        public event Action<VmsImage> EditVmsImageEvent;
        public event Action<String> ErrorInfoEvent;
        #region Properties

        public List<string> ListName;
        private string _selectionText = string.Empty;
        private VmsImage _selectedVmschildItem;
        public VmsImage SelectedVmsChildItem
        {
            get { return _selectedVmschildItem; }
            set
            {
                if (_selectedVmschildItem != value)
                {
                    _selectedVmschildItem = value;
                    RaisePropertyChanged(() => SelectedVmsChildItem);
                }
            }
        }
        #endregion
        public ImageObjectSettingScreen()
        {
            InitializeComponent();
            //DataContext = SelectedVmsChildItem;
            ListName = new List<string>();
        }

        public void SetDataContext(VmsImage imageobject)
        {
            SelectedVmsChildItem = imageobject;
            
            //SelectedVmsChildItem = new VmsImage()
            //{
            //    Avatar = imageobject.Avatar,
            //    Height = imageobject.Height,
            //    Width = imageobject.Width,
            //    ImageLink = imageobject.ImageLink,
            //    Name = imageobject.Name,
            //    X = imageobject.X,
            //    Y = imageobject.Y
            //};
            DataContext = SelectedVmsChildItem;
            RaisePropertyChanged(() => SelectedVmsChildItem);
        }

        public void SetDataContext(VmsImage imageobject,List<string> listName )
        {
            SelectedVmsChildItem = imageobject;
            _selectionText = imageobject.Name;
            ListName = listName;
            DataContext = SelectedVmsChildItem;
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

        private void BtImage_OnClick(object sender, RoutedEventArgs e)
        {
            //Stream checkStream = null;
            //Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();

            //openFileDialog.Multiselect = false;
            //openFileDialog.Filter = "All Image Files | *.*";
            //if ((bool)openFileDialog.ShowDialog())
            //{
            //    try
            //    {
            //        if ((checkStream = openFileDialog.OpenFile()) != null)
            //        {
            //            //listBox1.Items.Add(openFileDialog.FileName);
            //            TblImagelink.Text = openFileDialog.FileName;
            //            SelectedVmsChildItem.ImageLink = openFileDialog.FileName;
                        
            //        }
            //    }
            //    catch (Exception ex)
            //    {
            //        MessageBox.Show("Lỗi: " + ex.Message);
            //    }
            //}
            //else
            //{
            //    //MessageBox.Show("Không thành công");
            //}

            ChoosingImageSourceScreen choosingImage = new ChoosingImageSourceScreen();
            choosingImage.ChooseImageEvent += choosingImage_ChooseImageEvent;
            choosingImage.ShowDialog();
        }

        void choosingImage_ChooseImageEvent(Jsoncontract.Imagelist obj)
        {
            TblImagelink.Text = obj.link;
            SelectedVmsChildItem.ImageLink = obj.link;

            if (EditVmsImageEvent != null)
            {
                EditVmsImageEvent(SelectedVmsChildItem);
            }
        }

        private Boolean IsTextAllowed(String text)
        {
            foreach (Char c in text.ToCharArray())
            {
                if (Char.IsDigit(c) || Char.IsControl(c)) continue;
                else return false;
            }
            return true;
        }

        private bool IntegerCharChecker(string str)
        {
            Regex objNotNumberPattern = new Regex("[^0-9.-]");
            Regex objTwoDotPattern = new Regex("[0-9]*[.][0-9]*[.][0-9]*");
            Regex objTwoMinusPattern = new Regex("[0-9]*[-][0-9]*[-][0-9]*");
            String strValidRealPattern = "^([-]|[.]|[-.]|[0-9])[0-9]*[.]*[0-9]+$";
            String strValidIntegerPattern = "^([-]|[0-9])[0-9]*$";
            Regex objNumberPattern = new Regex("(" + strValidRealPattern + ")|(" + strValidIntegerPattern + ")");
            return !objNotNumberPattern.IsMatch(str) && !objTwoDotPattern.IsMatch(str) && !objTwoMinusPattern.IsMatch(str) && objNumberPattern.IsMatch(str);
        }

        private void PreviewTextInputHandler(object sender, TextCompositionEventArgs e)
        {
            e.Handled = !DoubleCharChecker(e.Text);
        }

        private bool DoubleCharChecker(string str)
        {
            foreach (char c in str)
            {
                if (c.Equals('-'))
                    return true;

                else if (c.Equals('.'))
                    return true;

                else if (Char.IsNumber(c))
                    return true;
            }
            return false;
        }

        private void Textbox_OnKeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                if((sender as TextBox).Text != string.Empty)
                {
                    if (EditVmsImageEvent != null)
                    {
                        TextBox txt = sender as TextBox;
                        TblImagelink.Focus();
                        EditVmsImageEvent(SelectedVmsChildItem);
                    }
                }
                else
                {
                    if (ErrorInfoEvent != null)
                    {
                        ErrorInfoEvent(Utils.ErrorInfoVi.EnterEmptyNameInfo);
                    }
                }
            }
        }

        private void TbName_OnPreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            //e.Handled = !CheckNameinList((sender as TextBox).Text + e.Text);
            
        }

        public bool CheckNameinList(string currentName)
        {
            if (ListName.Contains(currentName))
            {
                if (ErrorInfoEvent != null)
                {
                    ErrorInfoEvent(Utils.ErrorInfoVi.EnterSameNameInfo);
                }
                return false;
            }
            return true;
            
        }

        private void TbName_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            string text = (sender as TextBox).Text;
            if (text == _selectionText)
                return;

            if (string.IsNullOrEmpty(text)
                )
            {
                (sender as TextBox).Text = _selectionText;
                //string name = string.Empty;
                //while (true)
                //{
                //    int a = 0;
                //    name = "Text " + (ListName.Count + a).ToString();
                //    if (ListName.Contains(name))
                //        a++;
                //    else
                //        break;
                //}

                //(sender as TextBox).Text = name;
            }
            else
            {
                if (ListName.Contains(text))
                {
                    string name = string.Empty;
                    int a = 0;
                    while (true)
                    {
                        name = "Ảnh " + (ListName.Count + a).ToString();
                        if (ListName.Contains(name))
                            a++;
                        else
                            break;
                    }

                    (sender as TextBox).Text = name;
                    if (ListName.Contains(_selectionText))
                        ListName.Remove(_selectionText);

                    ListName.Add(name);
                    _selectionText = name;
                }
                else
                {
                    if (ListName.Contains(_selectionText))
                        ListName.Remove(_selectionText);

                    ListName.Add(text);
                    _selectionText = text;
                }
            }
        }
    }
}
