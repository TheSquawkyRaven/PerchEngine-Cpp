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

	private:

		// Private because this may not be the latest value. Use GetCutRect instead.
		Rect2 _CutRect = Rect2();

		// Sprite Sheet
		int _SpriteColumns = 1;
		int _SpriteRows = 1;
		int _SpriteIndex = 0;

	public:

		PERCHENGINECPP_API inline int GetSpriteColumns() const { return _SpriteColumns; }
		PERCHENGINECPP_API void SetSpriteColumns(int spriteColumns);
		PERCHENGINECPP_API inline int GetSpriteRows() const { return _SpriteRows; }
		PERCHENGINECPP_API void SetSpriteRows(int spriteRows);
		PERCHENGINECPP_API inline int GetSpriteIndex() const { return _SpriteIndex; }
		PERCHENGINECPP_API void SetSpriteIndex(int spriteIndex);

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

		void UpdateCutRect();
		
	protected:

		PERCHENGINECPP_API SDL_RendererFlip GetSDLFlip() const;
		PERCHENGINECPP_API std::shared_ptr<SDL_Point> GetRotateOrigin();

	public:

		PERCHENGINECPP_API virtual Vector2 GetSize();
		PERCHENGINECPP_API virtual Vector2 GetGlobalSize();
		PERCHENGINECPP_API Rect2 GetCutRect();

		PERCHENGINECPP_API virtual void SetTexture(std::shared_ptr<Texture> texture);

		PERCHENGINECPP_API virtual void Update() override;
		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		PERCHENGINECPP_API virtual void OnDestroy() override;

		// ###

	};


}
