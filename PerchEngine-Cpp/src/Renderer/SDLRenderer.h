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
#include <map>
#include <vector>


namespace Perch
{

	class SDLRenderer : public Renderer
	{

		friend class Engine;

	public:

		struct RendererLayerConfig
		{
		public:

			std::vector<const char*> layerNames;
			int maxLayers = 256;

			int GetIndexByLayerName(const char* name);

		};

		// # Variables + Getters/Setters

	private:
		
		struct DrawSorter
		{
			struct DrawLayer
			{
				struct DrawOrder
				{
					int index;
					std::vector<Branch*> branches;

					bool operator <(const DrawOrder& order) const;
					void Add(Branch* branch);
					void Draw(Renderer* renderer);
					void Clear();
				};

				int order;
				std::vector<DrawOrder> drawOrder;

				bool operator <(const DrawLayer& layer) const;
				void Add(Branch* branch, int order);
				void Sort();
				void Draw(Renderer* renderer);
				void Clear();
			};

			std::vector<DrawLayer> drawLayers;

			void Add(Branch* branch, int layer, int order);
			void Sort();
			void Draw(Renderer* renderer);
			void Clear();
		};

		SDL_Renderer* sdlRenderer;

		DrawSorter drawSorter;

	public:



		// ###


		// # Functions

	private:


	protected:

		virtual bool InitializeRenderer() override;
		virtual bool InitializeRenderer(SDL_Window* sdlWindow, int sdlIndex, Uint32 sdlFlags);
		void InitializeConfig(RendererLayerConfig* rendererLayerConfig);

	public:

		virtual void SetDrawColor(Color* color) override;
		virtual void Clear() override;

		virtual void SetDrawOrder(Branch* branch, int layer, int order) override;
		virtual void Draw() override;
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

		~SDLRenderer();

		// ###
	};

}
