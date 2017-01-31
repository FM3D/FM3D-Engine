#pragma once
#define NO_FM3D
#include "../pch.h"
#include "FoundResource.h"
#pragma managed(push, off)
#include "ResourceLoader.h"
#pragma managed(pop)

using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;
using namespace System::Collections::Generic;

namespace DesignerLib {

	ref class Mesh;

	public ref class ExternResource : INotifyPropertyChanged {
	private:
		ResourceLoader* m_loader;
		Dictionary<FoundResource^, uint>^ m_meshPartMap;
	public:
		property ObservableCollection<FoundResource^>^ Resources;
		property IResourceContainer^ Master;

		ExternResource();
		~ExternResource();
		void Load(System::String^ path);

		virtual event PropertyChangedEventHandler^ PropertyChanged;

		ObservableCollection<Mesh^>^ GetMeshes();

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}
	};
}