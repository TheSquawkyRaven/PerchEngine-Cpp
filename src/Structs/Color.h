#pragma once

#include <SDL_stdinc.h>

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

		Color();
		Color(Uint8 gray);
		Color(Uint8 gray, Uint8 a);
		Color(Uint8 r, Uint8 g, Uint8 b);
		Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);


		inline static Color Black() { return Color(0, 0, 0, 255); }
		inline static Color White() { return Color(255, 255, 255, 255); }
		inline static Color Gray() { return Color(128, 128, 128, 255); }
		inline static Color Silver() { return Color(192, 192, 192, 255); }
		inline static Color Maroon() { return Color(128, 0, 0, 255); }
		inline static Color Red() { return Color(255, 0, 0, 255); }
		inline static Color Purple() { return Color(128, 0, 128, 255); }
		inline static Color Pink() { return Color(255, 0, 255); }
		inline static Color Green() { return Color(0, 128, 0, 255); }
		inline static Color Lime() { return Color(0, 255, 0, 255); }
		inline static Color Olive() { return Color(128, 128, 0, 255); }
		inline static Color Yellow() { return Color(255, 255, 0, 255); }
		inline static Color Navy() { return Color(0, 0, 128, 255); }
		inline static Color Blue() { return Color(0, 0, 255, 255); }
		inline static Color Teal() { return Color(0, 128, 128, 255); }
		inline static Color Cyan() { return Color(0, 255, 255, 255); }


		bool operator==(Color const& other);
		bool operator!=(Color const& other);

	};

}
