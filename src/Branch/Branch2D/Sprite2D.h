#pragma once

#include "Branch2D.h"

#include "../../Structs/Texture.h"
#include "../../Structs/Rect2.h"
#include "../../Structs/Vector2.h"
#include "../../Structs/Vector2i.h"

#include <SDL.h>

#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Sprite2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		std::shared_ptr<Texture> _Texture = NULL;
		Color _Color = Color();

	public:

		Vector2 RotatePivot = Vector2(0.5f, 0.5f);
		double Angle = 0;
		// SDL do not support flipping at both axes at the same time
		bool FlipX = false;
		bool FlipY = false;

		std::shared_ptr<Texture> GetTexture() { return _Texture; }
		inline Color GetColor() const { return _Color; }
		inline void SetColor(Color color) { _Color = color; }

		// ###


		// # Functions

	private:
		
	protected:

		SDL_RendererFlip GetSDLFlip() const;
		std::shared_ptr<SDL_Point> GetRotateOrigin();

	public:

		virtual Vector2 GetSize();
		virtual Vector2 GetGlobalSize();

		virtual void SetTexture(std::shared_ptr<Texture> texture);

		virtual void Update() override;
		virtual void Draw(SDL_Renderer* renderer) override;

		virtual void OnDestroy() override;

		// ###

	};


}
