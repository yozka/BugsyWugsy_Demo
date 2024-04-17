//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"
#include "engine/gui/eWidget.h"
#include "engine/assets/font/eAssetFont.h"

namespace Engine::GUI
{

	enum class EAlign
	{
		center,
		left,
		right,
		top,
		bottom
	};

	// Текст
	class ELabel : public EWidget
	{
	public:
		using Ptr		= std::shared_ptr<ELabel>;
		using WeakPtr	= std::weak_ptr<ELabel>;
		using UPtr		= std::unique_ptr<ELabel>;

	public:
		ELabel();
		virtual ~ELabel();

	public:
		void SetPosition(const FPoint &pos);
		void SetScale(const FPoint &scale);
		void SetScale(const float scale);
		void SetColor(const SDL_Color &color);
		void SetText(const std::string &text);
		void SetFont(const Engine::Assets::EAssetFont::Ptr &font);
		void SetAlignH(const EAlign align);
		void SetAlignV(const EAlign align);
		
	public:
		bool IsInputCaptured() const override final { return false; }
		bool Input(const Engine::Input::TControls&) override final { return false; }
		void Update(const double) override final {}
		void Render(const Engine::Render::ESpriteBatch::UPtr& context) override;

	private:
		void CalcQuad();
		void Destroy();

	private:
		Engine::Assets::EAssetFont::Ptr m_font = {};
		FPoint m_position = {};
		FPoint m_scale = {1.0f, 1.0f};
		EAlign m_alignH = { EAlign::left };
		EAlign m_alignV = { EAlign::top };
		
		SDL_Texture* m_texture = {};
		IPoint m_sizeTexture = {};
		SDL_Vertex m_vx[4];
		SDL_Color m_color = { 00, 00, 00, 0xFF};

		std::string m_text;

	};


}
