//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "LayerRenderObjects.h"
#include "map/camera/Camera.h"

#include "engine/CoreSDL.h"
#include "engine/common/eV2.h"
#include "engine/render/eSpriteBatch.h"

namespace Game::Map
{

	//Отрисовка объектов
	class ARenderObjects
	{
	public:
		ARenderObjects(const int width, const int height, const int tilewidth, const int tileheight);
		virtual ~ARenderObjects();
		
	public:
		void Render(const ALayerRenderObjects::Ptr &layer,
					const Engine::Render::ESpriteBatch::UPtr &context,
					const ACamera::Ptr &camera);
		
	private:
		//Размер карты в тайлах
		const int m_width = {};
		const int m_height = {};
		
		//Размерность тайлов
		const int m_tilewidth = {};
		const int m_tileheight = {};
	};

}
