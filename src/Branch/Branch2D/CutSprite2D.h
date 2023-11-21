#pragma once

#include "Sprite2D.h"

#include "../../Resources/Texture.h"
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

		inline int GetSpriteColumns() const { return _SpriteColumns; }
		void SetSpriteColumns(int spriteColumns);
		inline int GetSpriteRows() const { return _SpriteRows; }
		void SetSpriteRows(int spriteRows);
		inline int GetSpriteIndex() const { return _SpriteIndex; }
		void SetSpriteIndex(int spriteIndex);

		// ###


		// # Functions

	private:
		
		void UpdateCutRect();

	public:

		CutSprite2D();

		virtual void SetTexture(std::shared_ptr<Texture> texture) override;

		virtual Vector2 GetSize() override;
		virtual Vector2 GetGlobalSize() override;

		Rect2 GetCutRect();
		virtual void Draw(Engine* engine, SDL_Renderer* renderer) override;

		// ###

	};


}
