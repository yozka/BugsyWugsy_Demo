//◦ EggEngine ◦
#pragma once
#include <string>
#include "GameScene.h"
namespace Game
{


	//Управление сценами
	class AScenesController
	{
	public:
		AScenesController() = default;
		virtual ~AScenesController() = default;
		
		
	public:
		virtual void PushScene(const AGameScene::Ptr &scene) = 0;
		virtual void PopScene() = 0;



	};

}
