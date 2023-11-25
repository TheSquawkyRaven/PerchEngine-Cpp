#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
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
		std::shared_ptr<Viewport> _Viewport;

	public:

		PERCHENGINECPP_API inline std::shared_ptr<Viewport> GetViewport() const { return _Viewport; }
		PERCHENGINECPP_API inline void SetViewport(std::shared_ptr<Viewport> viewport) { _Viewport = viewport; }

		// ###

		// # Functions

	private:

	public:

		PERCHENGINECPP_API virtual void Update() override;
		PERCHENGINECPP_API virtual void UpdateOut() override;

		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer) override;
		PERCHENGINECPP_API virtual void DrawOut(SDL_Renderer* renderer) override;

		// ###

	};


}
