﻿using EnvDTE;
using Microsoft.VisualStudio.Shell.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace VS_Extension
{
    public class FM3DPropertyFile
    {

        public bool Load(IVsSolution solution)
        {
            string directory, file, optsFile;
            solution.GetSolutionInfo(out directory, out file, out optsFile);

            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreWhitespace = true;
            XmlReader xml;
            try
            {
                xml = XmlReader.Create(directory + "/fm3d.xml", settings);
            }
            catch (System.IO.FileNotFoundException)
            {
                return false;
            }
            xml.ReadToDescendant("FM3D_Project");
            xml.MoveToAttribute("Name");
            FM3DName = xml.Value;
            xml.MoveToElement();
            LoadXmlFile(xml.ReadSubtree());
            return true;
        }

        private void LoadXmlFile(XmlReader xml)
        {
            while (xml.Read())
            {
                if ((xml.NodeType == XmlNodeType.Element) && (xml.Depth == 1))
                {
                    if (xml.Name == "MainProject")
                    {
                        xml.MoveToAttribute("Name");
                        MainProjectName = xml.Value;
                    }
                    else if (xml.Name == "Pipe")
                    {
                        xml.MoveToAttribute("Name");
                        PipeName = xml.Value;
                    }
                }
            }
            xml.Close();
        }

        public string MainProjectName { get; private set; }
        public string PipeName { get; private set; }
        public string FM3DName { get; private set; }
    }
}
