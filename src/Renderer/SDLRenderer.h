#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"

#include <memory>


namespace Perch
{

	class SDLRenderer : public Renderer
	{

		friend class Engine;

		// # Variables + Getters/Setters

	private:

		SDL_Renderer* sdlRenderer;

	public:

		// ###


		// # Functions

	protected:

		virtual bool InitializeRenderer() override;
		virtual bool InitializeRenderer(SDL_Window* sdlWindow, int index, Uint32 flags);

	public:

		virtual void SetDrawColor(Color* color) override;
		virtual void Clear() override;

		virtual void Flush() override;

		virtual void DrawTexture(Texture* texture, Color* color,
			Rect2* sourceRect, Rect2* destinationRect) override;
		virtual void DrawTexture(Texture* texture, Color* color,
			Rect2* sourceRect, Rect2* destinationRect,
			double angle, Vector2* rotateOrigin,
			bool flipX, bool flipY) override;

		virtual void DrawPoint(int x, int y, Color* color) override;
		virtual void DrawLine(int x1, int y1, int x2, int y2, Color* color) override;
		virtual void DrawRect(Rect2* rect, Color* color) override;

		virtual void UseViewport(Viewport* viewport) override;

		virtual void Destroy() override;


		Texture* LoadTexture(const char* path);
		Texture* LoadFontTexture(Font* font, const char* text, Color* color);

		SDL_RendererFlip GetSDLFlip(bool flipX, bool flipY) const;

		// ###
	};

}
