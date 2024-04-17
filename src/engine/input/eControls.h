//◦ EggEngine ◦
#pragma once
#include <memory>
#include "engine/common/eV2.h"


namespace Engine::Input
{

	// Кнопки
	struct TKey
	{
		bool pressed 	= {}; //Нажали
		bool released 	= {}; //Отпустили
	};

	// Система кнопок
	struct TKeyControls
	{
		TKey up;
		TKey down;
		TKey left;
		TKey right;
		TKey jump;
		TKey action;
		TKey menu;
	};

	// Нажатие на экран
	struct TTouch : public TKey
	{
		bool moving = {}; //Движение
		IPoint pos; //Кординаты экранные
	};

	// Система управления
	struct TControls : public TKeyControls
	{
		TTouch	touch;
	};

}
