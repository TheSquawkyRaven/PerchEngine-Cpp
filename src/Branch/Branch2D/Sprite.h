#pragma once

#include "Branch2D.h"

#include "../../Resources/Texture.h"
#include "../../Structs/Rect2D.h"
#include "../../Structs/Vector2.h"
#include "../../Structs/Vector2i.h"

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

		std::shared_ptr<Texture> _Texture = NULL;

	public:

		std::shared_ptr<Texture> GetTexture() { return _Texture; }
		Vector2 GetSize();

		// ###


		// # Functions

	private:
		
	public:

		void SetTexture(std::shared_ptr<Texture> texture);

		virtual void Update() override;
		virtual void Draw(SDL_Renderer* renderer) override;

		virtual void OnDestroy() override;

		// ###

	};


}
