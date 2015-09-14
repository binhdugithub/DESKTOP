﻿#pragma checksum "..\..\..\View\HistoryScreen.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "DE7463A161CFC6B6EFDF990DBFDD7995"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18408
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using WPFSpark;
using eVMS.Converters;


namespace eVMS.View {
    
    
    /// <summary>
    /// HistoryScreen
    /// </summary>
    public partial class HistoryScreen : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 29 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.DatePicker DpStartSearch;
        
        #line default
        #line hidden
        
        
        #line 34 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.DatePicker DpEndDateSearch;
        
        #line default
        #line hidden
        
        
        #line 41 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button BtnSearch;
        
        #line default
        #line hidden
        
        
        #line 86 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.DataGrid dgVms;
        
        #line default
        #line hidden
        
        
        #line 131 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Grid StNavigate;
        
        #line default
        #line hidden
        
        
        #line 139 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button ShowButton;
        
        #line default
        #line hidden
        
        
        #line 164 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button PreButton;
        
        #line default
        #line hidden
        
        
        #line 210 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button NextButton;
        
        #line default
        #line hidden
        
        
        #line 239 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button LastButton;
        
        #line default
        #line hidden
        
        
        #line 268 "..\..\..\View\HistoryScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal WPFSpark.FluidProgressBar FluidProgressBar;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/eVMS;component/view/historyscreen.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\View\HistoryScreen.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.DpStartSearch = ((System.Windows.Controls.DatePicker)(target));
            
            #line 31 "..\..\..\View\HistoryScreen.xaml"
            this.DpStartSearch.SelectedDateChanged += new System.EventHandler<System.Windows.Controls.SelectionChangedEventArgs>(this.DpStartSearch_OnSelectedDateChanged);
            
            #line default
            #line hidden
            return;
            case 2:
            this.DpEndDateSearch = ((System.Windows.Controls.DatePicker)(target));
            
            #line 39 "..\..\..\View\HistoryScreen.xaml"
            this.DpEndDateSearch.SelectedDateChanged += new System.EventHandler<System.Windows.Controls.SelectionChangedEventArgs>(this.DpEndDateSearch_OnSelectedDateChanged);
            
            #line default
            #line hidden
            return;
            case 3:
            this.BtnSearch = ((System.Windows.Controls.Button)(target));
            
            #line 41 "..\..\..\View\HistoryScreen.xaml"
            this.BtnSearch.Click += new System.Windows.RoutedEventHandler(this.BtnSearch_OnClick);
            
            #line default
            #line hidden
            return;
            case 4:
            this.dgVms = ((System.Windows.Controls.DataGrid)(target));
            return;
            case 5:
            this.StNavigate = ((System.Windows.Controls.Grid)(target));
            return;
            case 6:
            this.ShowButton = ((System.Windows.Controls.Button)(target));
            return;
            case 7:
            this.PreButton = ((System.Windows.Controls.Button)(target));
            return;
            case 8:
            this.NextButton = ((System.Windows.Controls.Button)(target));
            return;
            case 9:
            this.LastButton = ((System.Windows.Controls.Button)(target));
            return;
            case 10:
            this.FluidProgressBar = ((WPFSpark.FluidProgressBar)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

