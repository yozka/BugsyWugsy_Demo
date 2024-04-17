//◦ EggEngine ◦
#include "eClipping.h"

using namespace Engine;


void EClipping::ResetClipping()
{
	m_cliprect = {};
}


void EClipping::AddClipping(const FRect& rect)
{
	if (!IsClipping()) {
		m_cliprect = rect;
	}
	else {
		m_cliprect = m_cliprect * rect;
	}
}


void EClipping::ClipBar(FRect& dst) const
{
	if (!IsClipping()) return;

	if (dst.x1 < m_cliprect.x1) dst.x1 = m_cliprect.x1;	else
		if (dst.x1 > m_cliprect.x2) dst.x1 = m_cliprect.x2;

	if (dst.y1 < m_cliprect.y1) dst.y1 = m_cliprect.y1;	else
		if (dst.y1 > m_cliprect.y2) dst.y1 = m_cliprect.y2;

	if (dst.x2 > m_cliprect.x2) dst.x2 = m_cliprect.x2;	else
		if (dst.x2 < m_cliprect.x1) dst.x2 = m_cliprect.x1;

	if (dst.y2 > m_cliprect.y2) dst.y2 = m_cliprect.y2;	else
		if (dst.y2 < m_cliprect.y1) dst.y2 = m_cliprect.y1;
}

void EClipping::ClipQuad(FRect& dst, FRect& src) const
{
	if (!IsClipping()) return;

	float f = 0.0f;
	FRect dst0 = dst;
	float srcw = src.x2 - src.x1;
	float srch = src.y2 - src.y1;
	float dstw = dst.x2 - dst.x1;
	float dsth = dst.y2 - dst.y1;

	if (dst.x1 < m_cliprect.x1) dst.x1 = m_cliprect.x1;
	if (dst.y1 < m_cliprect.y1) dst.y1 = m_cliprect.y1;
	if (dst.x2 > m_cliprect.x2) dst.x2 = m_cliprect.x2;
	if (dst.y2 > m_cliprect.y2) dst.y2 = m_cliprect.y2;

	if (dstw > 0.0f) f = (dst.x1 - dst0.x1) / dstw; else f = 0.0f;
	src.x1 += srcw * f;

	if (dstw > 0.0f) f = (dst0.x2 - dst.x2) / dstw; else f = 0.0f;
	src.x2 -= srcw * f;

	if (dsth > 0.0f) f = (dst.y1 - dst0.y1) / dsth; else f = 0.0f;
	src.y1 += srch * f;

	if (dsth > 0.0f) f = (dst0.y2 - dst.y2) / dsth; else f = 0.0f;
	src.y2 -= srch * f;
}


void EClipping::ClipSprite(FRect& dst, FRect& src, const int flip) const
{
	if (!IsClipping()) return;
	if (flip & 1)
	{
		if (dst.x1 < m_cliprect.x1) { src.x2 -= (m_cliprect.x1 - dst.x1); dst.x1 = m_cliprect.x1; }
		if (dst.x2 > m_cliprect.x2) { src.x1 += (dst.x2 - m_cliprect.x2); dst.x2 = m_cliprect.x2; }
	}
	else
	{
		if (dst.x1 < m_cliprect.x1) { src.x1 += (m_cliprect.x1 - dst.x1); dst.x1 = m_cliprect.x1; }
		if (dst.x2 > m_cliprect.x2) { src.x2 -= (dst.x2 - m_cliprect.x2); dst.x2 = m_cliprect.x2; }
	}
	if (flip & 2)
	{
		if (dst.y1 < m_cliprect.y1) { src.y2 -= (m_cliprect.y1 - dst.y1); dst.y1 = m_cliprect.y1; }
		if (dst.y2 > m_cliprect.y2) { src.y1 += (dst.y2 - m_cliprect.y2); dst.y2 = m_cliprect.y2; }
	}
	else
	{
		if (dst.y1 < m_cliprect.y1) { src.y1 += (m_cliprect.y1 - dst.y1); dst.y1 = m_cliprect.y1; }
		if (dst.y2 > m_cliprect.y2) { src.y2 -= (dst.y2 - m_cliprect.y2); dst.y2 = m_cliprect.y2; }
	}
}
