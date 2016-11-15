﻿using System;
using System.Collections.Generic;
using System.Linq;
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
using Microsoft.Win32;

using MahApps.Metro.Controls;
using MahApps.Metro.Controls.Dialogs;
namespace FM3D_Designer.src.WindowLayouts
{
    /// <summary>
    /// Interaction logic for StartLayout.xaml
    /// </summary>
    public partial class StartLayout : WindowLayout
    {
        public StartLayout(MainWindow mainWindow)
        {
            InitializeComponent();

            //Initialize DockWindow
            this.Header = "StartPage";

            this.Initialize(mainWindow, null);
        }

        public void New_Click(object sender, RoutedEventArgs e){
        
            //bruh.InitializeComponent();
            //var controller = async ShowProgressAsync("Please wait...", "Progress message");
        }

        private void btn_start_Click(object sender, RoutedEventArgs e)
        {
            mainWindow.ClearAttachedWindows();

            Project.Load(this.tb_path.Text);

            mainWindow.AttachNewWindowLayout(new MainLayout(this.mainWindow), true);
            WindowLayout layout = new TextureLayout();
            mainWindow.AttachNewWindowLayout(layout);

        }
        /// 
        ///Open Windows FileBrowser to load path in txtbox
        ///
        private void btn_load_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
                tb_path.Text = openFileDialog.FileName; //File.ReadAllText(
        }

        private void testButton_Click(object sender, RoutedEventArgs e)
        {
            this.tb_path.Text = "../../TestProjects/Project 0/project 0.fmproj";
        }

    }
}
