﻿#pragma checksum "..\..\..\View\VMSAdminstratorScreen.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "C1286C432B68EBDBD60CACF401C1AF8B"
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
using eVMS.Converters;


namespace eVMS.View {
    
    
    /// <summary>
    /// VMSAdminstratorScreen
    /// </summary>
    public partial class VMSAdminstratorScreen : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 31 "..\..\..\View\VMSAdminstratorScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button AddnewUserButton;
        
        #line default
        #line hidden
        
        
        #line 60 "..\..\..\View\VMSAdminstratorScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button EditUserButton;
        
        #line default
        #line hidden
        
        
        #line 91 "..\..\..\View\VMSAdminstratorScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button DeleteUserButton;
        
        #line default
        #line hidden
        
        
        #line 149 "..\..\..\View\VMSAdminstratorScreen.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.DataGrid dgVms;
        
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
            System.Uri resourceLocater = new System.Uri("/eVMS;component/view/vmsadminstratorscreen.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\View\VMSAdminstratorScreen.xaml"
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
            this.AddnewUserButton = ((System.Windows.Controls.Button)(target));
            
            #line 32 "..\..\..\View\VMSAdminstratorScreen.xaml"
            this.AddnewUserButton.Click += new System.Windows.RoutedEventHandler(this.AddnewVmsButton_OnClick);
            
            #line default
            #line hidden
            return;
            case 2:
            this.EditUserButton = ((System.Windows.Controls.Button)(target));
            
            #line 61 "..\..\..\View\VMSAdminstratorScreen.xaml"
            this.EditUserButton.Click += new System.Windows.RoutedEventHandler(this.EditUserButton_OnClick);
            
            #line default
            #line hidden
            return;
            case 3:
            this.DeleteUserButton = ((System.Windows.Controls.Button)(target));
            
            #line 92 "..\..\..\View\VMSAdminstratorScreen.xaml"
            this.DeleteUserButton.Click += new System.Windows.RoutedEventHandler(this.DeleteUserButton_OnClick);
            
            #line default
            #line hidden
            return;
            case 4:
            this.dgVms = ((System.Windows.Controls.DataGrid)(target));
            
            #line 151 "..\..\..\View\VMSAdminstratorScreen.xaml"
            this.dgVms.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.DgUsers_OnSelectionChanged);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

