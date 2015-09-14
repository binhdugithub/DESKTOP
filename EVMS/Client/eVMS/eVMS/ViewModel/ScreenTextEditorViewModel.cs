using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media;

namespace eVMS.ViewModel
{
    public class ScreenTextEditorViewModel:ViewModelBase
    {
        #region Properties
        private bool _selectedBoldButton;
        public bool SelectedBoldButton
        {
            get { return _selectedBoldButton; }
            set
            {
                if (_selectedBoldButton != value)
                {
                    _selectedBoldButton = value;
                    RaisePropertyChanged(() => SelectedBoldButton);
                }
            }
        }

        private bool _selectedItalicButton;
        public bool SelectedItalicButton
        {
            get { return _selectedItalicButton; }
            set
            {
                if (_selectedItalicButton != value)
                {
                    _selectedItalicButton = value;
                    RaisePropertyChanged(() => SelectedItalicButton);
                }
            }
        }

        private string _content;
        public string Content
        {
            get { return _content; }
            set
            {
                if (_content != value)
                {
                    _content = value;
                    RaisePropertyChanged(() => Content);
                }
            }
        }

        private string _fontfamily;
        public string Fontfamily
        {
            get { return _fontfamily; }
            set
            {
                if (_fontfamily != value)
                {
                    _fontfamily = value;
                    RaisePropertyChanged(() => Fontfamily);
                }
            }
        }

        private string _fontsize;
        public string Fontsize
        {
            get { return _fontsize; }
            set
            {
                if (_fontsize != value)
                {
                    _fontsize = value;
                    RaisePropertyChanged(() => Fontsize);
                }
            }
        }

        private ObservableCollection<FonFam> _fons;
        public ObservableCollection<FonFam> Fons
        {
            get { return _fons; }
            set
            {
                if (_fons != value)
                {
                    _fons = value;
                    RaisePropertyChanged(() => Fons);
                }
            }
        }

        private ObservableCollection<FontSiz> _size;
        public ObservableCollection<FontSiz> Size
        {
            get { return _size; }
            set
            {
                if (_size != value)
                {
                    _size = value;
                    RaisePropertyChanged(() => Size);
                }
            }
        }
        
        #endregion
        #region Contructors

        public ScreenTextEditorViewModel()
        {
            Fons = new ObservableCollection<FonFam>();
            Size = new ObservableCollection<FontSiz>();
            var fonts = Fonts.SystemFontFamilies.OrderBy(f => f.Source).ToList();
            foreach (var fontFamily in fonts)
            {
                var fonfam = new FonFam();
                fonfam.FontFamily = fontFamily.ToString();
                Fons.Add(fonfam);
            }
            var sizes = new List<string>() { "8", "9", "10", "11", "12", "14", "16", "18", "20", "22" };
            foreach (var size in sizes)
            {
                var fonsiz = new FontSiz();
                fonsiz.FontSize = size;
                Size.Add(fonsiz);
            }
           
        }
        
        #endregion
        
    }

    public class FonFam
    {
        public string FontFamily { get; set; }
    }

    public class FontSiz
    {
        public string FontSize { get; set; }
    }
}
