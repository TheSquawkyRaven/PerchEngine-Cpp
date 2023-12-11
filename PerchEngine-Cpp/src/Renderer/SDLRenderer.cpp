#include "pch.h"

#include "SDLRenderer.h"

#include "../Squawk/Log.h"

#include "../Structs/Color.h"
#include "../Structs/Texture.h"
#include "../Structs/Rect2.h"
#include "../Structs/Viewport.h"

#include "../Branch/Branch.h"


using namespace std;
using namespace Perch;
using namespace Squawk;


int SDLRenderer::RendererLayerConfig::GetIndexByLayerName(const char* name)
{
	/*for (int i = 0; i < layerNames.size(); i++)
	{
		if (layerNames[i] == name)
		{
			return i;
		}
	}*/
	return -1;
}

bool SDLRenderer::DrawSorter::DrawLayer::DrawOrder::operator<(const DrawOrder& order) const
{
	return (index < order.index);
}

void SDLRenderer::DrawSorter::DrawLayer::DrawOrder::Add(Branch* branch)
{
	branches.push_back(branch);
}

void SDLRenderer::DrawSorter::DrawLayer::DrawOrder::Draw(Renderer* renderer)
{
	for (int i = 0; i < branches.size(); i++)
	{
		branches[i]->_Draw(renderer);
	}
}

void SDLRenderer::DrawSorter::DrawLayer::DrawOrder::Clear()
{
	branches.clear();
}

bool SDLRenderer::DrawSorter::DrawLayer::operator<(const DrawLayer& layer) const
{
	return (order < layer.order);
}

void SDLRenderer::DrawSorter::DrawLayer::Add(Branch* branch, int order)
{
	DrawOrder* dOrder = nullptr;
	for (int i = 0; i < drawOrder.size(); i++)
	{
		if (drawOrder[i].index == order)
		{
			dOrder = &drawOrder[i];
			break;
		}
	}
	if (dOrder == nullptr)
	{
		drawOrder.push_back(DrawLayer::DrawOrder{ order });
		dOrder = &drawOrder[drawOrder.size() - 1];
	}
	dOrder->Add(branch);
}

void SDLRenderer::DrawSorter::DrawLayer::Sort()
{
	for (int i = 0; i < drawOrder.size(); i++)
	{
		sort(drawOrder.begin(), drawOrder.end());
	}
}

void SDLRenderer::DrawSorter::DrawLayer::Draw(Renderer* renderer)
{
	for (int i = 0; i < drawOrder.size(); i++)
	{
		drawOrder[i].Draw(renderer);
	}
}

void SDLRenderer::DrawSorter::DrawLayer::Clear()
{
	for (int i = 0; i < drawOrder.size(); i++)
	{
		drawOrder[i].Clear();
	}
	drawOrder.clear();
}

void SDLRenderer::DrawSorter::Add(Branch* branch, int layer, int order)
{
	DrawLayer* dLayer = nullptr;
	for (int i = 0; i < drawLayers.size(); i++)
	{
		if (drawLayers[i].order == layer)
		{
			dLayer = &drawLayers[i];
			break;
		}
	}
	if (dLayer == nullptr)
	{
		drawLayers.push_back(DrawLayer{ layer });
		dLayer = &drawLayers[drawLayers.size() - 1];
	}
	dLayer->Add(branch, order);
}

void SDLRenderer::DrawSorter::Sort()
{
	for (int i = 0; i < drawLayers.size(); i++)
	{
		drawLayers[i].Sort();
	}
	sort(drawLayers.begin(), drawLayers.end());
}

void SDLRenderer::DrawSorter::Draw(Renderer* renderer)
{
	for (int i = 0; i < drawLayers.size(); i++)
	{
		drawLayers[i].Draw(renderer);
	}
}

void SDLRenderer::DrawSorter::Clear()
{
	for (int i = 0; i < drawLayers.size(); i++)
	{
		drawLayers[i].Clear();
	}
	drawLayers.clear();
}

bool SDLRenderer::InitializeRenderer()
{
	Log::Error("This initialization function is not supported!");
	return false;
}

bool SDLRenderer::InitializeRenderer(SDL_Window* sdlWindow, int sdlIndex, Uint32 sdlFlags)
{
	// Hardware Accelerated renderer with VSync
	sdlRenderer = SDL_CreateRenderer(sdlWindow, sdlIndex, sdlFlags);

	if (sdlRenderer == nullptr)
	{
		Log::Errorf("SDL Renderer cannot be created! SDL_ERROR: %s", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);

	return true;
}

void SDLRenderer::InitializeConfig(RendererLayerConfig* config)
{
	/*for (int i = 0; i < config->layerNames.size(); i++)
	{
		drawLayers.push_back(new vector<Branch*>[config->maxLayers]);
	}*/
}

void SDLRenderer::SetDrawColor(Color* color)
{
	SDL_SetRenderDrawColor(sdlRenderer, color->r, color->g, color->b, color->a);
}

void SDLRenderer::Clear()
{
	SDL_SetRenderDrawColor(sdlRenderer, clearColor->r, clearColor->g, clearColor->b, clearColor->a);
	SDL_RenderClear(sdlRenderer);
}

void SDLRenderer::SetDrawOrder(Branch* branch, int layer, int order)
{
	drawSorter.Add(branch, layer, order);
}

void SDLRenderer::Draw()
{
	drawSorter.Sort();
	drawSorter.Draw(this);
	drawSorter.Clear();
}

void SDLRenderer::Flush()
{
	SDL_RenderPresent(sdlRenderer);
}

void SDLRenderer::DrawTexture(Texture* texture, Color* color, Rect2* sourceRect, Rect2* destinationRect)
{
	SDL_Texture* sdlTexture = texture->sdlTexture.get();
	SDL_Rect* destinationSDLRect = destinationRect->GetSDLRect().get();

	SDL_Rect* sourceSDLRect = nullptr;
	if (sourceRect != nullptr)
	{
		sourceSDLRect = sourceRect->GetSDLRect().get();
	}

	SDL_SetTextureColorMod(sdlTexture, color->r, color->g, color->b);
	SDL_SetTextureAlphaMod(sdlTexture, color->a);
	SDL_RenderCopy(sdlRenderer, sdlTexture, sourceSDLRect, destinationSDLRect);
}

void SDLRenderer::DrawTexture(Texture* texture, Color* color, Rect2* sourceRect, Rect2* destinationRect, double angle, Vector2* rotateOrigin, bool flipX, bool flipY)
{
	SDL_Texture* sdlTexture = texture->sdlTexture.get();
	shared_ptr<SDL_Rect> destinationSDLRect = destinationRect->GetSDLRect();

	shared_ptr<SDL_Rect> sourceSDLRect = nullptr;
	if (sourceRect != nullptr)
	{
		sourceSDLRect = sourceRect->GetSDLRect();
	}

	shared_ptr<SDL_Point> rotatePoint = nullptr;
	if (rotateOrigin != nullptr)
	{
		rotatePoint = rotateOrigin->GetSDLPoint();
	}

	SDL_SetTextureColorMod(sdlTexture, color->r, color->g, color->b);
	SDL_SetTextureAlphaMod(sdlTexture, color->a);
	SDL_RenderCopyEx(sdlRenderer, sdlTexture,
		sourceSDLRect.get(), destinationSDLRect.get(),
		angle, rotatePoint.get(),
		GetSDLFlip(flipX, flipY));
}

void SDLRenderer::DrawPoint(int x, int y, Color* color)
{
	SDL_SetRenderDrawColor(sdlRenderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(sdlRenderer, x, y);
}

void SDLRenderer::DrawLine(int x1, int y1, int x2, int y2, Color* color)
{
	SDL_SetRenderDrawColor(sdlRenderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}

void SDLRenderer::DrawRect(Rect2* rect, Color* color)
{
	SDL_SetRenderDrawColor(sdlRenderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(sdlRenderer, rect->GetSDLRect().get());
}

void SDLRenderer::UseViewport(Viewport* viewport)
{
	SDL_RenderSetViewport(sdlRenderer, viewport->GetSDLRect().get());
}

void SDLRenderer::Destroy()
{
	SDL_DestroyRenderer(sdlRenderer);
}

Texture* SDLRenderer::LoadTexture(const char* path)
{
	SDL_Texture* sdlTexture = IMG_LoadTexture(sdlRenderer, path);
	if (sdlTexture == nullptr)
	{
		Log::Errorf("Failed to load sdlTexture, path: %s! SDL_IMAGE_ERROR: %s", path, IMG_GetError());
		return nullptr;
	}

	Texture* texture = new Texture(sdlTexture);
	SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(sdlTexture, nullptr, nullptr, &texture->size.x, &texture->size.y);

	return texture;
}

Texture* SDLRenderer::LoadFontTexture(Font* font, const char* text, Color* color)
{
	SDL_Surface* sdlSurface = TTF_RenderText_Solid(font->GetSDLFont(), text, *color);
	if (sdlSurface == nullptr)
	{
		Log::Errorf("Failed to create surface from font! SDL_TTF_ERROR: %s", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);
	SDL_FreeSurface(sdlSurface);
	if (sdlTexture == nullptr)
	{
		Log::Errorf("Failed to convert surface to sdlTexture! SDL_IMAGE_ERROR: %s", IMG_GetError());
		return nullptr;
	}

	Texture* texture = new Texture(sdlTexture);
	SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(sdlTexture, nullptr, nullptr, &texture->size.x, &texture->size.y);

	return texture;
}

SDL_RendererFlip SDLRenderer::GetSDLFlip(bool flipX, bool flipY) const
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (flipX)
	{
		flip = SDL_FLIP_HORIZONTAL;
		return flip;
	}
	if (flipY)
	{
		flip = SDL_FLIP_VERTICAL;
		return flip;
	}
	return flip;
}

SDLRenderer::~SDLRenderer()
{
	/*for (vector<Branch*>* drawLayer : drawLayers)
	{
		delete[] drawLayer;
	}*/
}

