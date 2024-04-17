//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

//#include "components/Component.h"

namespace Game
{
	namespace Components
	{
		class AComponent;
	}

	//Объект
	class AGameObject
	{
	public:
		using UPtr		= std::unique_ptr<AGameObject>;
		using Ptr		= std::shared_ptr<AGameObject>;
		using WeakPtr	= std::weak_ptr<AGameObject>;

	public:
		AGameObject(const std::string& name);
		virtual ~AGameObject();
		void Start();
		void Destroy();
		
		std::string Name() const { return m_name; }
		
	public:
		template<typename T>
		std::shared_ptr<T> AppendComponent(std::shared_ptr<T> component)
		{
			component->SetParent(this);
			m_components[std::type_index(typeid(T))] = component;
			ComponentAttached();
			return component;
		}
		
		template<typename T, typename... Args>
		std::shared_ptr<T> CreateComponent(const Args... args)
		{
			return AppendComponent(std::make_shared<T>(args...));
		}
		
		template<typename T>
		std::shared_ptr<T> GetComponent() const
		{
			const auto it = m_components.find(std::type_index(typeid(T)));
			if (it != m_components.cend()) {
				return std::static_pointer_cast<T>(it->second);
			}
			return {};
		}
		
		template<typename T>
		std::vector<std::shared_ptr<T>> GetComponents() const
		{
			std::vector<std::shared_ptr<T>> list;
			for (auto[type, com] : m_components) {
				if (auto ptr = std::dynamic_pointer_cast<T>(com)) {
					list.push_back(ptr);
				}
			}
			return std::move(list);
		}
		
	private:
		void ComponentAttached();
		
	private:
		bool m_start = { false };
		std::string m_name;
		std::unordered_map<std::type_index, std::shared_ptr<Components::AComponent>> m_components;
		
	};

}
