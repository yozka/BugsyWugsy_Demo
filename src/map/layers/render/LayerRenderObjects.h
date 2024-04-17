//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "map/layers/Layer.h"
#include "objects/GameObject.h"



namespace Game::Map
{

	//Объекты на игровой карте
	class ALayerRenderObjects : public ALayer
	{
	public:
		using UPtr		= std::unique_ptr<ALayerRenderObjects>;
		using Ptr		= std::shared_ptr<ALayerRenderObjects>;
		using WeakPtr	= std::weak_ptr<ALayerRenderObjects>;

	public:
		ALayerRenderObjects(const std::string& name);
		~ALayerRenderObjects() override;
		
	public:
		void Start();
		void Destroy();
		
	public:
		AGameObject::Ptr FindObject(const std::string &name) const;
		void Append(const AGameObject::Ptr &obj);
		const std::vector<AGameObject::Ptr>& Objects() const { return m_objects; }
		
	private:
		std::string m_name;
		std::vector<AGameObject::Ptr> m_objects;
		
		
	};

}
