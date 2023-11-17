#pragma once

#include "Branch2D.h"

#include "../../Resources/Texture.h"
#include "../../Structs/Rect2D.h"
#include "../../Structs/Vector2.h"

#include <SDL.h>

#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Sprite : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		Texture* _Texture = NULL;

	public:

		Perch::Texture& GetTexture() { return *_Texture; }
		Vector2 GetSize();

		// ###


		// # Functions

	private:
		
	public:

		void SetTexture(Texture* texture);

		virtual void Draw(SDL_Surface* MainSurface) override;

		// ###

	};


}
