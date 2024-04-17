//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "GameObject.h"
#include "engine/common/eProperty.h"

namespace Game
{
	//Фабрика создания компонента
	namespace Components
	{
		class AFactory
		{
		public:
			virtual ~AFactory() = default;
			virtual void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) = 0;
		};
	}
	//

	//Фабрика создания объекта
	class AFactoryObject
	{
	public:
		using FactoryObject =  std::function<Game::AGameObject::UPtr(const Engine::Property& prop)>;
		
		template<typename T, typename... Args>
		void Create(const Args... args)
		{
			m_factorys.push_back(std::make_unique<T>(args...));
		}
		
		FactoryObject Creator() const
		{
			return [this](const Engine::Property &prop) -> AGameObject::UPtr
			{
				auto name = prop.GetString("name");
				if (name.empty()) return {};
				auto obj = std::make_unique<AGameObject>(name);
				for (const auto& factory : m_factorys) {
					factory->Create(obj, prop);
				}
				return obj;
			};
		}
		
	private:
		std::vector<std::unique_ptr<Components::AFactory>> m_factorys;
	};

}
