#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
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

		PERCH_API inline int GetSpriteColumns() const { return _SpriteColumns; }
		PERCH_API void SetSpriteColumns(int spriteColumns);
		PERCH_API inline int GetSpriteRows() const { return _SpriteRows; }
		PERCH_API void SetSpriteRows(int spriteRows);
		PERCH_API inline int GetSpriteIndex() const { return _SpriteIndex; }
		PERCH_API void SetSpriteIndex(int spriteIndex);

	public:

		// Position transform applied relative to texture size. In percentage form (0.5f, 0.5f) is the center
		Vector2 PositionPivot = Vector2();
		// Rotation pivot relative to texture size. In percentage form (0.5f, 0.5f) is the center
		Vector2 RotatePivot = Vector2(0.5f, 0.5f);
		double Angle = 0;
		// SDL do not support flipping at both axes at the same time
		bool FlipX = false;
		bool FlipY = false;

		std::shared_ptr<Texture> GetTexture() { return _Texture; }
		PERCH_API inline Color GetColor() const { return _Color; }
		PERCH_API inline void SetColor(Color color) { _Color = color; }

		// ###


		// # Functions

	private:

		void UpdateCutRect();
		
	protected:

		PERCH_API SDL_RendererFlip GetSDLFlip() const;
		PERCH_API std::shared_ptr<SDL_Point> GetRotateOrigin();
		PERCH_API Vector2 GetPositionPivotOrigin();

	public:

		PERCH_API Sprite2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual Vector2 GetSize();
		PERCH_API virtual Vector2 GetGlobalSize();
		PERCH_API Rect2 GetGlobalRect();
		PERCH_API Rect2 GetCutRect();

		PERCH_API virtual void SetTexture(std::shared_ptr<Texture> texture);

		PERCH_API virtual void Update() override;
		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		PERCH_API virtual void OnDestroy() override;

		// ###

	};


}
