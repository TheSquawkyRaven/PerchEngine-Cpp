#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


namespace Perch
{

	struct Vector2;

	/// <summary>
	/// 
	/// </summary>
	struct Vector2i
	{

	public:
		int X = 0;
		int Y = 0;


	public:

		PERCHENGINECPP_API operator Vector2() const;

		PERCHENGINECPP_API Vector2i();
		PERCHENGINECPP_API Vector2i(int x, int y);
		PERCHENGINECPP_API Vector2i(int val);

	};


}
