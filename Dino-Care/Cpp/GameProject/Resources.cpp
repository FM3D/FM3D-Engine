//
//	DO NOT TOUCH THIS!!!
//	AUTOGENERATED FILE BY FM3D-DESIGNER!!!
//
#include "Resources.h"

void Resources::LoadResources(FM3D::RenderSystem* renderSystem) {
	m_meshes.insert(FM3D::FileManager::ReadMeshFile("C:/Users/Dyrax/Source/Repos/Project/Dino-Care/ProjectFiles/Models/Allosaurus.fm_mesh", renderSystem, m_skeleton));
	m_meshes.insert(FM3D::FileManager::ReadMeshFile("C:/Users/Dyrax/Source/Repos/Project/Dino-Care/ProjectFiles/Models/Argentavis.fm_mesh", renderSystem, m_skeleton));
}