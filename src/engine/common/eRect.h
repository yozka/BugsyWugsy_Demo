//◦ EggEngine ◦
#pragma once
#include <memory>
#include "eV2.h"
namespace Engine
{


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// rectangle
	///////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct TRect
	{
		union
		{
			struct { T x1, y1, x2, y2; };
			struct { T left, top, right, bottom; };
			T v[4];
		};

		TRect()	: x1(0), y1(0), x2(0), y2(0) {}
		TRect(const T &_x1, const T &_y1, const T &_x2, const T &_y2 )	: x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
		
		template<typename TT>
		TRect(const TT &old) : x1(old.x1), y1(old.y1), x2(old.x2), y2(old.y2) {}

		T Width() const 	{ return x2-x1; }
		T Height() const	{ return y2-y1; }

		TV2<T>	Center() const						{ return {(x1+x2)/2.0f, (y1+y2)/2.0f}; }
		void	Inflate(const TV2<T> &_v) const		{ x1+=_v.x; y1+=_v.y; x2-=_v.x; y2-=_v.y; }
		void	Deflate(const TV2<T> &_v) const		{ x1-=_v.x; y1-=_v.y; x2+=_v.x; y2+=_v.y; }
		void	Offset(const TV2<T> &_v) const		{ x1+=_v.x; y1+=_v.y; x2+=_v.x; y2+=_v.y; }
		bool	IsInside(const TV2<T> &_v) const	{ return (x1<=_v.x && _v.x<x2 && y1<=_v.y && _v.y<y2); }

		// если один из прямоугольников левее, правее, выше или ниже другого, то они не пересекаются
		bool	IsIntersect(const TRect& _v) const { return !(x1 > _v.x2 || x2 < _v.x1 || y1 > _v.y2 || y2 < _v.y1); }
		
		friend bool  operator==	(const TRect& r1, const TRect& r2) { return (r1.x1 == r2.x1 && r1.y1 == r2.y1 && r1.x2 == r2.x2 && r1.y2 == r2.y2); }
		friend bool	 operator!=	(const TRect& r1, const TRect& r2) { return (r1.x1 != r2.x1 || r1.y1 != r2.y1 || r1.x2 != r2.x2 || r1.y2 != r2.y2); }
		friend TRect operator+	(const TRect& r1, const TRect& r2) { return TRect ((r1.x1 < r2.x1) ? r1.x1 : r2.x1, (r1.y1 < r2.y1) ? r1.y1 : r2.y1, (r1.x2 > r2.x2) ? r1.x2 : r2.x2, (r1.y2 > r2.y2) ? r1.y2 : r2.y2) ; }
		friend TRect operator+=	(TRect& r1, const TRect& r2) { if (r2.x1 < r1.x1) r1.x1 = r2.x1; if (r2.y1 < r1.y1) r1.y1 = r2.y1; if (r2.x2 > r1.x2) r1.x2 = r2.x2; if (r2.y2 > r1.y2) r1.y2 = r2.y2; return r1; }
		friend TRect operator*	(const TRect& r1, const TRect& r2) { return TRect ((r1.x1 > r2.x1) ? r1.x1 : r2.x1, (r1.y1 > r2.y1) ? r1.y1 : r2.y1, (r1.x2 < r2.x2) ? r1.x2 : r2.x2, (r1.y2 < r2.y2) ? r1.y2 : r2.y2); }
		friend TRect operator*=	(TRect& r1, const TRect& r2) { if (r2.x1 > r1.x1) r1.x1 = r2.x1; if (r2.y1 > r1.y1) r1.y1 = r2.y1; if (r2.x2 < r1.x2) r1.x2 = r2.x2; if (r2.y2 < r1.y2) r1.y2 = r2.y2; return r1; }

	};

	using iRect = TRect<int>;
	using fRect = TRect<float>;


	template<typename T>
	bool RECT2RECT(const T &r1, const T &r2)
	{
		return !( (r1.x2 <= r2.x1) || (r1.x1 >= r2.x2) || (r1.y2 <= r2.y1) || (r1.y1 >= r2.y2) );
	}

}
