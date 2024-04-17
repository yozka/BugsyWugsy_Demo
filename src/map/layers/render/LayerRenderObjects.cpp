//◦ EggEngine ◦
#include "LayerRenderObjects.h"
#include "engine/debug/eAssert.h"


using namespace Game::Map;


ALayerRenderObjects::ALayerRenderObjects(const std::string& name)
	:
		m_name(name)
{

}


ALayerRenderObjects::~ALayerRenderObjects()
{

}

void ALayerRenderObjects::Start()
{
	for (auto& obj : m_objects) {
		obj->Start();
	}
}

void ALayerRenderObjects::Destroy()
{
	m_name.clear();
	for (auto& obj : m_objects) {
		obj->Destroy();
	} 
	m_objects.clear();
}

void ALayerRenderObjects::Append(const AGameObject::Ptr &obj)
{
	m_objects.push_back(obj);
}


Game::AGameObject::Ptr ALayerRenderObjects::FindObject(const std::string &name) const
{
	const auto it = std::find_if(m_objects.begin(), m_objects.end(), [name](const AGameObject::Ptr& obj)
	{
		return name == obj->Name();
	});
	if (it != m_objects.end()) {
		return *it;
	}
	return {};
}
