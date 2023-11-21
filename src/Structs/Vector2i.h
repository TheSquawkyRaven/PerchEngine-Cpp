#pragma once

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

		operator Vector2() const;

		Vector2i();
		Vector2i(int x, int y);
		Vector2i(int val);

	};


}
