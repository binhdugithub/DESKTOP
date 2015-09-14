using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
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
using eVMS.VMS;
using Microsoft.Win32;
using Net.Sgoliver.NRtfTree.Core;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for TextObjectSettingScreen.xaml
    /// </summary>
    public partial class TextObjectSettingScreen : UserControl, INotifyPropertyChanged
    {
        public event Action<VmsText> EditVmsTextEvent;
        public List<string> ListName;
        private string _selectionText = string.Empty;
        public event Action<String> ErrorInfoEvent;
        public int nColor;
        #region Properties

        private VmsText _selectedVmschildItem;
        public VmsText SelectedVmsChildItem
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
        public TextObjectSettingScreen()
        {
            InitializeComponent();
            ListName = new List<string>();
            //cmbFontFamily.ItemsSource = Fonts.SystemFontFamilies.OrderBy(f => f.Source);
            //cmbFontSize.ItemsSource = new List<double>() { 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
        }

        public void SetDataContext(VmsText textobject)
        {
            SelectedVmsChildItem = textobject;
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
            var fontselected = string.Format("Fonts/#{0}", SelectedVmsChildItem.FontFamily);
            TblContent.FontFamily = new FontFamily(new Uri("pack://application:,,,/"), fontselected);
        }

        public void SetDataContext(VmsText textobject,List<string> listName ,int ncolor)
        {
            SelectedVmsChildItem = textobject;
            ListName = listName;
            _selectionText = textobject.Name;
            nColor = ncolor;
            DataContext = SelectedVmsChildItem;
            var fontselected = string.Format("Fonts/#{0}", SelectedVmsChildItem.FontFamily);
            TblContent.FontFamily = new FontFamily(new Uri("pack://application:,,,/"), fontselected);
        }

        private void cmbFontFamily_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //if (cmbFontFamily.SelectedItem != null)
            //    rtbEditor.Selection.ApplyPropertyValue(Inline.FontFamilyProperty, cmbFontFamily.SelectedItem);
        }

        private void cmbFontSize_TextChanged(object sender, TextChangedEventArgs e)
        {
            //rtbEditor.Selection.ApplyPropertyValue(Inline.FontSizeProperty, cmbFontSize.Text);
        }

        private void rtbEditor_SelectionChanged(object sender, RoutedEventArgs e)
        {
            //object temp = rtbEditor.Selection.GetPropertyValue(Inline.FontWeightProperty);
            //btnBold.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(FontWeights.Bold));
            //temp = rtbEditor.Selection.GetPropertyValue(Inline.FontStyleProperty);
            //btnItalic.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(FontStyles.Italic));
            //temp = rtbEditor.Selection.GetPropertyValue(Inline.TextDecorationsProperty);
            //btnUnderline.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(TextDecorations.Underline));

            //temp = rtbEditor.Selection.GetPropertyValue(Inline.FontFamilyProperty);
            //cmbFontFamily.SelectedItem = temp;
            //temp = rtbEditor.Selection.GetPropertyValue(Inline.FontSizeProperty);
            //cmbFontSize.Text = temp.ToString();

            //object temp = rtbEditor.Selection.GetPropertyValue(Inline.FontWeightProperty);
            
        }

        private void Open_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            //OpenFileDialog dlg = new OpenFileDialog();
            //dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            //if (dlg.ShowDialog() == true)
            //{
            //    FileStream fileStream = new FileStream(dlg.FileName, FileMode.Open);
            //    TextRange range = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
            //    range.Load(fileStream, DataFormats.Rtf);
           // }
        }

        private void Save_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            //SaveFileDialog dlg = new SaveFileDialog();
            //dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            //if (dlg.ShowDialog() == true)
            //{
            //    FileStream fileStream = new FileStream(dlg.FileName, FileMode.Create);
            //    TextRange range = new TextRange(rtbEditor.Document.ContentStart, rtbEditor.Document.ContentEnd);
            //    range.Save(fileStream, DataFormats.Xaml);
            //}
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

        private void RtbEditor_OnSelectionChanged(object sender, RoutedEventArgs e)
        {
            //object temp = rtbEditor.Selection.GetPropertyValue(Inline.FontWeightProperty);
            //btnBold.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(FontWeights.Bold));
            //temp = rtbEditor.Selection.GetPropertyValue(Inline.FontStyleProperty);
            //btnItalic.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(FontStyles.Italic));
            //temp = rtbEditor.Selection.GetPropertyValue(Inline.TextDecorationsProperty);
            //btnUnderline.IsChecked = (temp != DependencyProperty.UnsetValue) && (temp.Equals(TextDecorations.Underline));

            //temp = rtbEditor.Selection.GetPropertyValue(Inline.FontFamilyProperty);
            //cmbFontFamily.SelectedItem = temp;
            //temp = rtbEditor.Selection.GetPropertyValue(Inline.FontSizeProperty);
            //cmbFontSize.Text = temp.ToString();
        }

        private void RtbEditor_OnLostFocus(object sender, RoutedEventArgs e)
        {
            //TextRange t = new TextRange(rtbEditor.Document.ContentStart,rtbEditor.Document.ContentEnd);
            //FileStream file = new FileStream("Temp.xaml", FileMode.Create);
            //t.Save(file, System.Windows.DataFormats.Xaml);
            //file.Close();

            //var doc = (sender as RichTextBox).Document;
            //RtfTree tree = new RtfTree();
            //int tre = tree.LoadRtfFile(@"D:\test.rtf");
            ////RtfTreeNode root = tree.RootNode;
            //TextRange t = new TextRange(rtbEditor.Document.ContentStart,
            //                        rtbEditor.Document.ContentEnd);
            //FileStream file = new FileStream("Sample File.xaml", FileMode.Create);
            //t.Save(file, System.Windows.DataFormats.Xaml);
            //file.Close();
            //RtfTreeNode node = new RtfTreeNode();
            //for (int i = 0; i < root.ChildNodes.Count; i++)
            //{
            //    node = root.ChildNodes[i];

            //    if (node.NodeType == RtfNodeType.Group)
            //    {
            //        foreach (var childNode in node.ChildNodes)
            //        {
                        
            //        }
            //    }
            //    else if (node.NodeType == RtfNodeType.Control)
            //    {
            //        //...
            //    }
            //    else if (node.NodeType == RtfNodeType.Keyword)
            //    {
            //        switch (node.NodeKey)
            //        {
            //            case "f":  //Font type
            //                //...
            //                break;
            //            case "cf":  //Font color
            //                //...
            //                break;
            //            case "fs":  //Font size
            //                //...
            //                break;
            //        }
            //    }
            //    else if (node.NodeType == RtfNodeType.Text)
            //    {
            //        //...
            //    }
            //}
        }

        private void Textbox_OnKeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter && (sender as TextBox).Text != string.Empty)
            {
                if (EditVmsTextEvent != null)
                {
                    //TextBox txt = sender as TextBox;
                    TblContent.Focus();
                    EditVmsTextEvent(SelectedVmsChildItem);
                }
            }

            //if ((sender as TextBox).Text != string.Empty)
            //{
            //    if (ErrorInfoEvent != null)
            //    {
            //        ErrorInfoEvent(Utils.ErrorInfoVi.EnterEmptyNameInfo);
            //    }
            //}
        }

        private void PreviewTextInputHandler(object sender, TextCompositionEventArgs e)
        {
            e.Handled = !DoubleCharChecker(e.Text);
        }

        #region Validate Data
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
        #endregion Validate Data

        //private void TbEditor_OnSelectionChanged(object sender, RoutedEventArgs e)
        //{
        //    if (btnBold.IsChecked == true)
        //    {
        //        tbEditor.FontWeight = FontWeights.Bold;
        //    }
        //    else
        //    {
        //        tbEditor.FontWeight = FontWeights.Normal;
        //    }
        //}

        //private void BtnBold_OnChecked(object sender, RoutedEventArgs e)
        //{
        //    tbEditor.FontWeight = FontWeights.Bold;
        //}

        //private void BtnBold_OnUnchecked(object sender, RoutedEventArgs e)
        //{
        //    tbEditor.FontWeight = FontWeights.Normal;
        //}
        private void BtnTextSetting_OnClick(object sender, RoutedEventArgs e)
        {
            TextEditor textScreen = new TextEditor(SelectedVmsChildItem, nColor);
            textScreen.Owner = System.Windows.Window.GetWindow(this);
            textScreen.EditorVmsTextEvent += textScreen_EditorVmsTextEvent;
            textScreen.ShowDialog();
        }

        void textScreen_EditorVmsTextEvent(VmsText obj)
        {
            SelectedVmsChildItem.FontFamily = obj.FontFamily;
            SelectedVmsChildItem.FontSize = obj.FontSize;
            SelectedVmsChildItem.FontStyle = obj.FontStyle;
            SelectedVmsChildItem.FontWight = obj.FontWight;
            SelectedVmsChildItem.ColorText = obj.ColorText;
            SelectedVmsChildItem.Content = obj.Content;
            //
            if (SelectedVmsChildItem.FontWight)
                TblContent.FontWeight = FontWeights.Bold;
            else
            {
                TblContent.FontWeight = FontWeights.Normal;
            }

            if (SelectedVmsChildItem.FontStyle)
                TblContent.FontStyle = FontStyles.Italic;
            else
            {
                TblContent.FontStyle = FontStyles.Normal;
            }

            int size = 0;
            int.TryParse(SelectedVmsChildItem.FontSize, out size);
            try
            {
                var fontselected = string.Format("Fonts/#{0}", obj.FontFamily);
                TblContent.FontFamily = new FontFamily(new Uri("pack://application:,,,/"), fontselected);
            }
            catch (Exception ex)
            {
                
                
            }
            
            
            TblContent.FontSize = 12;
            TblContent.Foreground = new SolidColorBrush(Colors.Black);
            TblContent.Text = obj.Content;
            if (EditVmsTextEvent != null)
            {
                //TextBox txt = sender as TextBox;
                TblContent.Focus();
                EditVmsTextEvent(SelectedVmsChildItem);
            }
            //EditVmsTextEvent(SelectedVmsChildItem);
        }

        private void TbName_OnPreviewTextInput(object sender, TextCompositionEventArgs e)
        {
        }

        /// <summary>
        /// Check this name if it is the same with existed name in list, it will change the value
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TbName_OnTextChanged(object sender, TextChangedEventArgs e)
        {
           //TblTextsettingInfo.Text = string.Empty;
            string text = (sender as TextBox).Text;
            if(text == _selectionText)
                return;

            if (string.IsNullOrEmpty(text)
                )
            {
                TblTextsettingInfo.Text = "Không được để trống trường tên";
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
                        name = "Từ mới " + (ListName.Count + a).ToString();
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
