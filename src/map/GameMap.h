//◦ EggEngine ◦
#pragma once
#include <string>
#include <variant>

#include "camera/Camera.h"
#include "tileset/Tileset.h"
#include "layers/Layers.h"
#include "logic/GameLogic.h"
#include "grid/GridCollision.h"

#include "engine/CoreSDL.h"
#include "engine/common/eV2.h"
#include "engine/render/eSpriteBatch.h"

namespace Game::Map
{

	//Игровая карта
	class AGameMap
	{
	public:
		using UPtr		= std::unique_ptr<AGameMap>;
		using Ptr		= std::shared_ptr<AGameMap>;
		using WeakPtr	= std::weak_ptr<AGameMap>;

	public:
		AGameMap(const std::string& name, const int width, const int height, const int tilewidth, const int tileheight);
		virtual ~AGameMap();
		
	public:
		const AGameLogic::Ptr		logic;
		const AGrigCollision::Ptr	grid;
		const ATilesets::Ptr		tilesets;
		const VLayers::Ptr			layers;
		
	public:
		void InitCamera(const ACamera::Ptr &camera);
		
	public:
		void Start();
		void Destroy();
		void Update(const double dt); //Игровой цикл
		void Render(const Engine::Render::ESpriteBatch::UPtr& context, const ACamera::Ptr &camera); //Отрисовка

	public:
		void SetGrid(const Engine::IPoint &pos, const EGridType type);
		void AppendObject(const AGameObject::Ptr &obj);
		void AppendTileset(ATileset::UPtr tileset);


		template<class T>
		void AppendLayer(const std::shared_ptr<T> &layer)
		{
			layers->push_back(layer);
		}
		
	public:
		AGameObject::Ptr FindObject(const std::string &name) const;
		
	private:
		//Размер карты в тайлах
		int m_width = {};
		int m_height = {};
		
		//Размерность тайлов
		int m_tilewidth		= {};
		int m_tileheight	= {};
		
		std::string m_name;
	};

}
