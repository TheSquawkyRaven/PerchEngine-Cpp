#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "SDL_ttf.h"

#include "Sprite2D.h"

#include "../../Structs/Texture.h"
#include "../../Structs/Font.h"
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
	class Text2D : public Sprite2D
	{

		// # Variables + Getters/Setters
	private:

		std::string text = "";
		std::shared_ptr<Font> font = nullptr;

	public:

		PERCH_API inline std::string GetText() const { return text; }
		PERCH_API void SetText(std::string text);

		PERCH_API inline std::shared_ptr<Font> GetFont() const { return font; }
		PERCH_API void SetFont(std::shared_ptr<Font> font);

	public:

		int fontSize = 32;

		// ###


		// # Functions

	protected:

		PERCH_API void UpdateTexture();

	public:

		PERCH_API Text2D(Engine* engine) : Sprite2D(engine) {};

		PERCH_API virtual void Ready() override;
		PERCH_API virtual void OnDestroy() override;

		// ###

	};


}
