﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using FM3D_Designer.src.ToolWindows.FileBrowser;

namespace FM3D_Designer.src
{
    public class ResourceFile {

        private const string HEADER = @"#pragma once
#include <map.h>
#include <Engine.h>

";
        private const string RESOURCE_CLASS = @"
class Resources {
private:
	std::map<unsigned int, FM3D::Texture*> m_textures;
	std::map<unsigned int, FM3D::Mesh*> m_meshes;
	std::map<unsigned int, FM3D::Model*> m_models;
	std::map<unsigned int, FM3D::Skeleton*> m_skeleton;
	std::map<unsigned int, FM3D::Material*> m_materials;
public:
	inline FM3D::Texture* GetTexture(uint id) { return m_textures.at(id); }
	inline FM3D::Mesh* GetMesh(uint id) { return m_meshes.at(id); }
	inline FM3D::Model* GetModel(uint id) { return m_models.at(id); }
	inline FM3D::Skeleton* GetSkeleton(uint id) { return m_skeleton.at(id); }
	inline FM3D::Material* GetMaterial(uint id) { return m_materials.at(id); }

	void LoadResources();
};";

        public string Path { get; set; }

        public ResourceFile(string path)
        {
            this.Path = path;
        }

        public bool WriteFile()
        {
            try
            {
                if (!File.Exists(Path)) File.Create(Path);
                using (FileStream fstream = new FileStream(Path, FileMode.Truncate, FileAccess.Write, FileShare.None))
                {
                    using (StreamWriter file = new StreamWriter(fstream))
                    {
                        file.Write(HEADER);
                        uint i = 0;
                        foreach (var f in Item.AllItems[ItemTypes.TextureFile])
                        {
                            file.WriteLine("#define TEXTURE_" + f.Name.ToUpper() + " " + i++.ToString());
                        }
                        i = 0;
                        foreach (var f in Item.AllItems[ItemTypes.MeshFile])
                        {
                            file.WriteLine("#define MESH_" + f.Name.ToUpper() + " " + i++.ToString());
                        }
                        i = 0;
                        foreach (var f in Item.AllItems[ItemTypes.ModelFile])
                        {
                            file.WriteLine("#define MODEL_" + f.Name.ToUpper() + " " + i++.ToString());
                        }
                        i = 0;
                        foreach (var f in Item.AllItems[ItemTypes.MaterialFile])
                        {
                            file.WriteLine("#define MATERIAL_" + f.Name.ToUpper() + " " + i++.ToString());
                        }
                        i = 0;
                        foreach (var f in Item.AllItems[ItemTypes.SkeletonFile])
                        {
                            file.WriteLine("#define SKELETON_" + f.Name.ToUpper() + " " + i++.ToString());
                        }
                        file.Write(RESOURCE_CLASS);
                    }
                }
            }
            catch
            {
                return false;
            }
            return true;
        }
    }
}
