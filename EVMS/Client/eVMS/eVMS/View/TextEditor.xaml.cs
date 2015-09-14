using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Shapes;
using DevExpress.Xpf.Core;
using eVMS.Utils;
using eVMS.ViewModel;
using eVMS.VMS;
using Microsoft.Windows.Controls;

namespace eVMS.View
{
    /// <summary>
    /// Interaction logic for SettingTextScreen.xaml
    /// </summary>
    public partial class TextEditor : Window
    {
        #region Mems

        private ScreenTextEditorViewModel _viewModel = new ScreenTextEditorViewModel();
        private VmsText vmsText;
        public event Action<VmsText> EditorVmsTextEvent;
        private Color pColor = Colors.Black;
        private int nColor;
        private System.Collections.Generic.ICollection<FontFamily> fontFamilies;
        #endregion

        #region Contrucstor
        public TextEditor()
        {
            InitializeComponent();
            Loaded += SettingTextScreen_Loaded;
            //cmbFontFamily.ItemsSource = Fonts.SystemFontFamilies.Where(x=>x.Source.StartsWith("Dot")).OrderBy(f => f.Source).ToList();
            fontFamilies = Fonts.SystemFontFamilies.OrderBy(f => f.Source).ToList();
            cmbFontFamily.ItemsSource = Fonts.SystemFontFamilies.OrderBy(f => f.Source).ToList();
            vmsText = new VmsText();
            //Hoanglm test
            //Hoanglm commnen
            //fontFamilies = Fonts.GetFontFamilies(new Uri("pack://application:,,,/"), "Fonts/");

            //// Enumerate through the font family collection. 
            //foreach (FontFamily fontFamily in fontFamilies)
            //{
            //    // Separate the URI directory source info from the font family name. 
            //    string[] familyName = fontFamily.Source.Split('#');

            //    // Add the font family name to the fonts combo box.
            //    //fonts
            //    cmbFontFamily.Items.Add(familyName[familyName.Length - 1]);
            //}
            cmbFontFamily.SelectedIndex = 0;
            // 
            //Hoanglm end
            cmbFontSize.ItemsSource = new List<string>() {"8", "9", "10", "11", "12", "14", "16", "18", "20", "22"};
                //, 24, 26, 28, 36, 48, 72 };
        }

        void SettingTextScreen_Loaded(object sender, RoutedEventArgs e)
        {
            if (_viewModel.SelectedBoldButton)
                tbEditor.FontWeight = FontWeights.Bold;

            if (_viewModel.SelectedItalicButton)
                tbEditor.FontStyle = FontStyles.Italic;

            
        }

        public TextEditor(VmsText selectedVmsChildItem, int ncolor)
            : this()
        {
            //_viewModel.SelectedBoldButton = selectedVmsChildItem.FontWight;
            //_viewModel.SelectedItalicButton = selectedVmsChildItem.FontStyle;
            //_viewModel.Content = selectedVmsChildItem.Content;
            //_viewModel.Fontfamily = selectedVmsChildItem.FontFamily;
            //_viewModel.Fontsize = selectedVmsChildItem.FontSize;

            //cmbFontFamily.DisplayMemberPath = "Arial";
            //cmbFontSize.Text = "12";
            vmsText.FontFamily = selectedVmsChildItem.FontFamily;
            vmsText.ColorText = selectedVmsChildItem.ColorText;
            vmsText.Content = selectedVmsChildItem.Content;
            vmsText.FontSize = selectedVmsChildItem.FontSize;
            vmsText.FontWight = selectedVmsChildItem.FontWight;
            vmsText.FontStyle = selectedVmsChildItem.FontStyle;
            //vmsText.FontStyle = selectedVmsChildItem.;

            DataContext = vmsText;
            if (selectedVmsChildItem.FontWight)
                btnBold.IsChecked = true;
            if (selectedVmsChildItem.FontStyle)
                btnItalic.IsChecked = true;
            cmbFontSize.Text = selectedVmsChildItem.FontSize;
            nColor = ncolor;
            if (nColor == 111) // Nhieu mau
            {

            }
            else
            {
                if (ColorInfo.ColorInfoCode.ContainsKey(nColor))
                {
                    var items = new ObservableCollection<ColorItem>();
                    var names = ColorInfo.ColorInfoCode[nColor].Split(',');
                    foreach (var name in names)
                    {
                        if (ColorConverter.ConvertFromString(name) != null)
                        {
                            ColorItem item = new ColorItem((Color)ColorConverter.ConvertFromString(name), name);
                            items.Add(item);
                        }
                    }

                    ColorPicker1.AvailableColors = items;
                    ColorPicker1.ShowStandardColors = false;
                    ColorPicker1.ShowAdvancedButton = false;
                    if (names.Contains(selectedVmsChildItem.ColorText.ToString()))
                    {
                        //pColor = selectedVmsChildItem.ColorText;
                        ColorPicker1.SelectedColor = selectedVmsChildItem.ColorText;
                    }
                    else
                    {
                        if (names.Count() > 0)
                        {
                            //pColor = (Color)ColorConverter.ConvertFromString(names[0]);
                            ColorPicker1.SelectedColor = (Color)ColorConverter.ConvertFromString(names[0]);
                        }    
                    }
                    tbEditor.Foreground = new SolidColorBrush(ColorPicker1.SelectedColor);
                }
            }
            //if (cmbFontFamily.ItemsSource)
            //var res = Fonts.SystemFontFamilies.Where(x => x.Source.StartsWith("Dot")).OrderBy(f => f.Source).ToList();
            if (selectedVmsChildItem.FontFamily != string.Empty)
            {
                try
                {
                    //Hoanglm change
                    //var fontselected = string.Format("Fonts/#{0}", selectedVmsChildItem.FontFamily);
                    //if (fontFamilies.Contains(new FontFamily(new Uri("pack://application:,,,/"), fontselected)))
                    //{

                    //    cmbFontFamily.SelectedItem = selectedVmsChildItem.FontFamily;
                    //}
                    if (fontFamilies.Contains(new FontFamily(selectedVmsChildItem.FontFamily)))
                    {
                        cmbFontFamily.SelectedItem = new FontFamily(selectedVmsChildItem.FontFamily);
                    }
                    //Hoang end change
                }
                catch (Exception ex)
                {
                  Log4Net.Log.Error(ex);   
                }
                
            }

            //tbEditor.Foreground = new SolidColorBrush(selectedVmsChildItem.ColorText);
            
        }
        #endregion



        private void cmbFontSize_TextChanged(object sender, TextChangedEventArgs e)
        {
            int fontsize = 0;
            int.TryParse(cmbFontSize.Text, out fontsize);
            if (fontsize != 0)
                tbEditor.FontSize = fontsize;
        }

        private void cmbFontFamily_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //Hoanglm
            //Hoanglm comment 20150807
            //if (cmbFontFamily.SelectedItem != null)
            //{
            //    var fonfam = cmbFontFamily.SelectedItem.ToString();
            //    var local = string.Format("Fonts/#{0}", fonfam);

            //    tbEditor.FontFamily = new FontFamily(new Uri("pack://application:,,,/"), local);
            //   //tbEditor.FontFamily = new FontFamily("Dotline");
            //}
            //Hoanglm end comment
            if (cmbFontFamily.SelectedItem != null)
            {
                tbEditor.FontFamily = cmbFontFamily.SelectedItem as FontFamily;
                //tbEditor.FontFamily = new FontFamily("Dotline");
            }
            //Hoanglm end change
        }

        private void BtnBold_OnChecked(object sender, RoutedEventArgs e)
        {
            tbEditor.FontWeight = FontWeights.Bold;
        }
        private void BtnBold_OnUnchecked(object sender, RoutedEventArgs e)
        {
            tbEditor.FontWeight = FontWeights.Normal;
        }

        private void BtnItalic_OnChecked(object sender, RoutedEventArgs e)
        {
            tbEditor.FontStyle = FontStyles.Italic;
        }

        private void BtnItalic_OnUnchecked(object sender, RoutedEventArgs e)
        {
            tbEditor.FontStyle = FontStyles.Normal;
        }


        private void BtnCan_OnClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void BtnAccept_OnClick(object sender, RoutedEventArgs e)
        {
            if (EditorVmsTextEvent != null)
            {
                //
                string fontfamily = String.Empty;
                string size = tbEditor.FontSize.ToString();

                if(cmbFontFamily.SelectedItem != null)
                    fontfamily = cmbFontFamily.SelectedItem.ToString();

                if (cmbFontSize.SelectedItem != null)
                    size = cmbFontSize.SelectedItem.ToString();
                EditorVmsTextEvent(
                    new VmsText()
                    {
                        Content = tbEditor.Text,
                        FontFamily = fontfamily,
                        FontSize = size,
                        FontWight = (bool)btnBold.IsChecked,
                        FontStyle = (bool)btnItalic.IsChecked,
                        ColorText = pColor
                    }
                    );
            }
            this.Close();
        }

        private void ColorPicker1_SelectedColorChanged(object sender, RoutedPropertyChangedEventArgs<Color> e)
        {
            //pColor = Color.FromArgb(ColorPicker1.SelectedColor.A, ColorPicker1.SelectedColor.R, ColorPicker1.SelectedColor.G, ColorPicker1.SelectedColor.B);
            pColor = ColorPicker1.SelectedColor;
            
            
            tbEditor.Foreground = new SolidColorBrush(pColor);
        }
    }
}
