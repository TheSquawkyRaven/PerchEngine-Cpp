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
	protected:

		std::shared_ptr<Texture> texture = nullptr;

		Rect2 rect = Rect2();
		// Private because this may not be the latest value. Use GetCutRect instead.
		Rect2 cutRect = Rect2();

		// Sprite Sheet
		int spriteColumns = 1;
		int spriteRows = 1;
		int spriteIndex = 0;

	public:

		PERCH_API std::shared_ptr<Texture> GetTexture() { return texture; }
		PERCH_API virtual void SetTexture(std::shared_ptr<Texture> texture);

		PERCH_API inline int GetSpriteColumns() const { return spriteColumns; }
		PERCH_API void SetSpriteColumns(int spriteColumns);
		PERCH_API inline int GetSpriteRows() const { return spriteRows; }
		PERCH_API void SetSpriteRows(int spriteRows);
		PERCH_API inline int GetSpriteIndex() const { return spriteIndex; }
		PERCH_API void SetSpriteIndex(int spriteIndex);

	public:
		
		Color color = Color();

		// Position transform applied relative to texture size. In percentage form (0.5f, 0.5f) is the center
		Vector2 positionPivot = Vector2();
		// Rotation pivot relative to texture size. In percentage form (0.5f, 0.5f) is the center
		Vector2 rotatePivot = Vector2(0.5f, 0.5f);
		double angle = 0;
		// SDL do not support flipping at both axes at the same time
		bool flipX = false;
		bool flipY = false;

		// ###


		// # Functions

	private:

		void UpdateCutRect();
		
	protected:

		PERCH_API SDL_RendererFlip GetSDLFlip() const;
		PERCH_API Vector2 GetRotateOrigin();
		PERCH_API Vector2 GetPositionPivotOrigin();

	public:

		PERCH_API Sprite2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void SetupDraw(Renderer* renderer) override;
		PERCH_API virtual void Draw(Renderer* renderer) override;
		PERCH_API virtual void OnDestroy() override;

		PERCH_API virtual Vector2 GetSize();
		PERCH_API virtual Vector2 GetGlobalSize();
		PERCH_API Rect2 GetGlobalRect();
		PERCH_API Rect2 GetCutRect();

		// ###

	};


}
