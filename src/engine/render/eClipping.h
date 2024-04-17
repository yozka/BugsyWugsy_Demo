//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include "engine/common/eRect.h"


namespace Engine
{


	// Система обрезки прямоугольной области
	class EClipping
	{
	public:
		EClipping() = default;
		virtual ~EClipping() = default;
		
	public:
		// clipping
		FRect GetClipping() const { return m_cliprect; }
		bool IsClipping() const { return ((m_cliprect.x1 < m_cliprect.x2) && (m_cliprect.y1 < m_cliprect.y2)); }
		void SetClipping(const FRect& rect) { m_cliprect = rect; }
		void AddClipping(const FRect& rect);
		void ClipBar(FRect& dst) const;								// clip destination rect (dst must be ordered)
		void ClipQuad(FRect& dst, FRect& src) const;					// clip destination rect and source mapping rect (dst must be ordered, src coordinates can be flipped)
		void ClipSprite(FRect& dst, FRect& src, const int flip = 0) const;	// clip destination rect and source mapping rect (dst and src must have the same sizes; src coordinates can't be flipped); rotation not supported
		void ResetClipping();
		
		
	private:
		Engine::FRect m_cliprect; // clipping rect (clipping is performed if rect is valid)

	};


}
