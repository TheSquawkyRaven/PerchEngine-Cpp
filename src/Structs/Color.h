#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	struct Color
	{

	public:

		// Default white & opaque
		Uint8 R = 255;
		Uint8 G = 255;
		Uint8 B = 255;
		Uint8 A = 255;


	public:

		PERCHENGINECPP_API Color();
		PERCHENGINECPP_API Color(Uint8 gray);
		PERCHENGINECPP_API Color(Uint8 gray, Uint8 a);
		PERCHENGINECPP_API Color(Uint8 r, Uint8 g, Uint8 b);
		PERCHENGINECPP_API Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		PERCHENGINECPP_API inline static Color Black() { return Color(0, 0, 0, 255); }
		PERCHENGINECPP_API inline static Color White() { return Color(255, 255, 255, 255); }
		PERCHENGINECPP_API inline static Color Gray() { return Color(128, 128, 128, 255); }
		PERCHENGINECPP_API inline static Color Silver() { return Color(192, 192, 192, 255); }
		PERCHENGINECPP_API inline static Color Maroon() { return Color(128, 0, 0, 255); }
		PERCHENGINECPP_API inline static Color Red() { return Color(255, 0, 0, 255); }
		PERCHENGINECPP_API inline static Color Purple() { return Color(128, 0, 128, 255); }
		PERCHENGINECPP_API inline static Color Pink() { return Color(255, 0, 255); }
		PERCHENGINECPP_API inline static Color Green() { return Color(0, 128, 0, 255); }
		PERCHENGINECPP_API inline static Color Lime() { return Color(0, 255, 0, 255); }
		PERCHENGINECPP_API inline static Color Olive() { return Color(128, 128, 0, 255); }
		PERCHENGINECPP_API inline static Color Yellow() { return Color(255, 255, 0, 255); }
		PERCHENGINECPP_API inline static Color Navy() { return Color(0, 0, 128, 255); }
		PERCHENGINECPP_API inline static Color Blue() { return Color(0, 0, 255, 255); }
		PERCHENGINECPP_API inline static Color Teal() { return Color(0, 128, 128, 255); }
		PERCHENGINECPP_API inline static Color Cyan() { return Color(0, 255, 255, 255); }

		PERCHENGINECPP_API operator SDL_Color() const;

		PERCHENGINECPP_API bool operator==(Color const& other);
		PERCHENGINECPP_API bool operator!=(Color const& other);

	};

}
