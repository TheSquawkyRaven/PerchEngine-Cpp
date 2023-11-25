#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


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
		PERCHENGINECPP_API inline Color GetColor() const { return _Color; }
		PERCHENGINECPP_API inline void SetColor(Color color) { _Color = color; }

		// ###


		// # Functions

	private:
		
	protected:

		PERCHENGINECPP_API SDL_RendererFlip GetSDLFlip() const;
		PERCHENGINECPP_API std::shared_ptr<SDL_Point> GetRotateOrigin();

	public:

		PERCHENGINECPP_API virtual Vector2 GetSize();
		PERCHENGINECPP_API virtual Vector2 GetGlobalSize();

		PERCHENGINECPP_API virtual void SetTexture(std::shared_ptr<Texture> texture);

		PERCHENGINECPP_API virtual void Update() override;
		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		PERCHENGINECPP_API virtual void OnDestroy() override;

		// ###

	};


}
