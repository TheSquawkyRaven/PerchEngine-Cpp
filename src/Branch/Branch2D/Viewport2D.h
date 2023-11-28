#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "Branch2D.h"

#include "../../Structs/Vector2.h"
#include "../../Structs/Rect2.h"

#include <SDL.h>
#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	// Children are drawn on this viewport
	class Viewport2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:
		std::shared_ptr<Viewport> viewport;

	public:

		PERCH_API inline std::shared_ptr<Viewport> GetViewport() const { return viewport; }
		PERCH_API inline void SetViewport(std::shared_ptr<Viewport> viewport) { this->viewport = viewport; }

		// ###

		// # Functions

	private:

	public:

		PERCH_API Viewport2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void Update() override;
		PERCH_API virtual void UpdateOut() override;

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;
		PERCH_API virtual void DrawOut(SDL_Renderer* renderer) override;

		// ###

	};


}
