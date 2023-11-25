#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include "Sprite2D.h"

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
	class CutSprite2D : public Sprite2D
	{

		// # Variables + Getters/Setters
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

		// ###


		// # Functions

	private:
		
		void UpdateCutRect();

	public:

		PERCHENGINECPP_API CutSprite2D();

		PERCHENGINECPP_API virtual void SetTexture(std::shared_ptr<Texture> texture) override;

		PERCHENGINECPP_API virtual Vector2 GetSize() override;
		PERCHENGINECPP_API virtual Vector2 GetGlobalSize() override;

		PERCHENGINECPP_API Rect2 GetCutRect();
		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;

		// ###

	};


}
