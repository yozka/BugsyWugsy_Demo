//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"
#include "engine/render/eSpriteBatch.h"
#include "engine/input/eControls.h"

namespace Engine::GUI
{


	// Общий виджет всего гуи
	class EWidget
	{
	public:
		using Ptr		= std::shared_ptr<EWidget>;
		using WeakPtr	= std::weak_ptr<EWidget>;
		using UPtr		= std::unique_ptr<EWidget>;

	public:
		EWidget() = default;
		virtual ~EWidget() = default;

	public:
		virtual bool IsInputCaptured() const = 0;
		virtual bool Input(const Engine::Input::TControls &controls) = 0;
		
		virtual void Update(const double dt) = 0;
		virtual void Render(const Engine::Render::ESpriteBatch::UPtr& context) = 0;

	};


}
