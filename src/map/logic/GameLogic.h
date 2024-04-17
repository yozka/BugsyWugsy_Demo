//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include "objects/GameObject.h"
#include "components/ComponentUpdater.h"


namespace Game::Map
{

	//Объекты для игровой логики
	class AGameLogic
	{
	public:
		using UPtr		= std::unique_ptr<AGameLogic>;
		using Ptr		= std::shared_ptr<AGameLogic>;
		using WeakPtr	= std::weak_ptr<AGameLogic>;

	public:
		AGameLogic();
		virtual ~AGameLogic();
		
	public:
		void Start();
		void Append(const AGameObject::Ptr &obj);
		void Destroy();
		
		void Update(const double dt);
		
	public:
		AGameObject::Ptr FindObject(const std::string &name) const;
		
		template<typename T>
		std::vector<std::shared_ptr<T>> GetComponents() const
		{
			std::vector<std::shared_ptr<T>> list;
			for (auto obj: m_objects) {
				auto comps = obj->GetComponents<T>();
				list.insert(list.end(), comps.begin(), comps.end());
			}
			return list;
		}
		
	private:
		std::vector<AGameObject::Ptr> m_objects;
		std::vector<Components::AComponentUpdater::Ptr> m_components;
	};

}
