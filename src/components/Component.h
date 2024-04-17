//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include "objects/GameObject.h"


namespace Game::Components
{

	//Компанент для игрового объекта
	class AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponent>;
		using Ptr		= std::shared_ptr<AComponent>;
		using WeakPtr	= std::weak_ptr<AComponent>;

	public:
		AComponent() = default;
		virtual ~AComponent() = default;
		virtual void Start() {};
		virtual void Destroy() = 0;
		virtual void ComponentAttached() {}; //К системе добавился компанент
		
		void SetParent(Game::AGameObject *obj) { parent = obj; }
		
		template<typename T>
		std::shared_ptr<T> GetComponent() const
		{
			if (parent) {
				return parent->GetComponent<T>();
			}
			return {};
		}
		
	private:
		Game::AGameObject *parent = {};
	};

}
