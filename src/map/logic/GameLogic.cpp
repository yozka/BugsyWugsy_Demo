//◦ EggEngine ◦
#include "GameLogic.h"


using namespace Game::Map;


AGameLogic::AGameLogic()
{

}


AGameLogic::~AGameLogic()
{

}


void AGameLogic::Append(const AGameObject::Ptr &obj)
{
	//добавим компаненты
	auto comps = obj->GetComponents<Components::AComponentUpdater>();
	m_components.insert(m_components.end(), comps.begin(), comps.end());
	
	m_objects.push_back(obj);
}

void AGameLogic::Start()
{
	for (auto obj : m_objects) {
		obj->Start();
	}
}

void AGameLogic::Destroy()
{
	m_objects.clear();
	m_components.clear();
}


Game::AGameObject::Ptr AGameLogic::FindObject(const std::string &name) const
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


void AGameLogic::Update(const double dt)
{
	for (const auto& comp : m_components) {
		comp->Update(dt);
	}
}
