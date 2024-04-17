//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include "engine/CoreSDL.h"

namespace Game::Map
{

	//Один тайл
	struct ATileData
	{
		int tileId 					= { 0 }; 	//Индификатор тайла
		int tilesetIndex 			= {-1 }; 	//Тайлсет где находится тайл
		SDL_Rect tileSource			= {}; 		//Область в тайлсете
		ATileData() = default;
		ATileData(const int tileId) : tileId(tileId) {}
	};

	//тайл с анимацией
	struct ATileAnimationData : public ATileData
	{
		float time = {}; // длительность анимации
		ATileAnimationData(const int tileId, const float time) : ATileData(tileId), time(time) {}
	};


	struct ATileInfo
	{
		ATileData tile;
		bool animation = {}; //включена или нет анимации
		int animationIndex = {}; //какой тайл для отрисовки
		float time = {}; //Текущее время для анимации
		std::vector<ATileAnimationData> animationTiles; //тайлы для анимации
	};


}
