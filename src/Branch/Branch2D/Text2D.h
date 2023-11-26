#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
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

		std::string _Text = "";
		std::shared_ptr<Font> _Font = NULL;

	public:

		PERCHENGINECPP_API inline std::string GetText() const { return _Text; }
		PERCHENGINECPP_API void SetText(std::string text);

		// ###


		// # Functions

	protected:

		PERCHENGINECPP_API void UpdateTexture();

	public:

		PERCHENGINECPP_API Text2D(Engine* engine) : Sprite2D(engine) {};

		PERCHENGINECPP_API virtual void Ready() override;
		PERCHENGINECPP_API void SetFont(std::shared_ptr<Font> font);

		// ###

	};


}
