﻿using System;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using DevComponents.WpfDock;
using System.ComponentModel;
using System.Windows.Shapes;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Navigation;
using System.Collections.Generic;
using System.Windows.Media.Imaging;
using System.Windows.Controls.Primitives;

namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for MainLayout.xaml
    /// </summary>
    public partial class MainLayout : WindowLayout
    {
        public MainLayout(MainWindow mainWindow)
        {
            InitializeComponent();
            
            this.Header = "Main Page";
            this.Initialize(mainWindow, this.dockSite);
            { 
                startFileBrowser();
                startTextEditor();
            }
        }

        private void ToolBar_Loaded(object sender, RoutedEventArgs e)
        {
            ToolBar toolBar = sender as ToolBar;
            var overflowGrid = toolBar.Template.FindName("OverflowButton", toolBar) as ButtonBase;
            if (overflowGrid != null)
            {
                overflowGrid.Background = toolBar.Background;
            }
        }

        public void OpenFileBrowser(object sender, RoutedEventArgs e)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.FileBrowser.View(this));

            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Left);
            DockSite.SetDockSize(splitPanel, 150);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        public void OpenTextEditor(object sender, RoutedEventArgs e)
        {
            SplitPanel splitPanel = new SplitPanel();
            DockWindowGroup dg = new DockWindowGroup();
            dg.Items.Add(new ToolWindows.TextEditor.TextEditor(this));
            splitPanel.Children.Add(dg);
            DockSite.SetDock(splitPanel, Dock.Right);
            DockSite.SetDockSize(splitPanel,600);
            this.dockSite.SplitPanels.Add(splitPanel);
            dg.UpdateVisibility();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            PipeSystem.StartVS("FM3D_PIPE_EPIC_GAME_5754656", Project.CurrentProject._Directory + "/C++/GameProject.sln");
        }
    }
}
