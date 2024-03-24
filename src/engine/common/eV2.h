//◦ EggEngine ◦
#pragma once
#include <memory>

namespace Engine
{


	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct TV2
	{
		union
		{
			struct { T x, y; };
			T v[2];
		};
		
		TV2() : x(0), y(0) {}
		TV2( const T &_x, const T &_y ) : x(_x), y(_y) {}
		
		friend bool operator==	( const TV2& v1, const TV2& v2 )		{ return v1.x==v2.x && v1.y==v2.y; }
		friend bool operator!=	( const TV2& v1, const TV2& v2 )		{ return v1.x!=v2.x || v1.y!=v2.y; }
		friend TV2 operator*	( const TV2& v1, const TV2& v2 )		{ return { v1.x * v2.x, v1.y * v2.y }; }
		friend TV2 operator*	( const T scale, const TV2& v1 )		{ return { v1.x * scale, v1.y * scale }; }
		friend TV2 operator*	( const TV2& v1, const T scale )		{ return { v1.x * scale, v1.y * scale }; }
		friend TV2 operator/	( const TV2& v1, const T scale )		{ return { v1.x / scale, v1.y / scale }; }
		friend TV2 operator+	( const TV2& v1, const TV2& v2 )		{ return { v1.x + v2.x, v1.y + v2.y }; }
		friend TV2 operator-	( const TV2& v1, const TV2& v2 )		{ return { v1.x - v2.x, v1.y - v2.y }; }
		friend TV2 operator-	( TV2& v1 )								{ return { -v1.x, -v1.y }; }
		friend TV2 operator*=	( TV2& v1, const T scale )				{ v1.x *= scale; v1.y *= scale; return v1; }
		friend TV2 operator/=	( TV2& v1, const T scale )				{ v1.x /= scale; v1.y /= scale; return v1; }
		friend TV2 operator+=	( TV2& v1, const TV2& v2 )				{ v1.x += v2.x; v1.y += v2.y; return v1; }
		friend TV2 operator-=	( TV2& v1, const TV2& v2 )				{ v1.x -= v2.x; v1.y -= v2.y; return v1; }
	};

	using iV2 = TV2<int>;
	using fV2 = TV2<float>;
	using IPoint = TV2<int>;
	using FPoint = TV2<float>;

}

//extern 	Engine::iV2 iv2_0;
//extern 	Engine::iV2 iv2_1;
