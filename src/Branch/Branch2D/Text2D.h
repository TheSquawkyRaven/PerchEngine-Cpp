#pragma once

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

		inline std::string GetText() const { return _Text; }
		void SetText(std::string text);

		// ###


		// # Functions

	protected:

		void UpdateTexture();

	public:

		virtual void Init() override;
		void SetFont(std::shared_ptr<Font> font);

		// ###

	};


}
