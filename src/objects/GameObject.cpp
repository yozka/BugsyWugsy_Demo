//◦ EggEngine ◦
#include "GameObject.h"
#include "components/Component.h"

using namespace Game;


AGameObject::AGameObject(const std::string& name)
	:
		m_name(name)
{

}


AGameObject::~AGameObject()
{

}


void AGameObject::Destroy()
{
	for (const auto&[type, component] : m_components) {
		component->Destroy();
		component->SetParent(nullptr);
	}
	m_components.clear();
}


void AGameObject::ComponentAttached()
{
	for (const auto&[type, component] : m_components) {
		component->ComponentAttached();
	}
	/*
	if (m_start) {
		attached->Start();
	}*/
}


void AGameObject::Start()
{
	if (m_start) return;
	for (const auto&[type, component] : m_components) {
		component->Start();
	}
	m_start = true;
}
