#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "MouseOverUI.h"
#include "../Branch2D/Sprite2D.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class ButtonUI : public MouseOverUI
	{

		// # Variables + Getters/Setters

	private:

		Rect2 rect = Rect2();

		bool isHeld = false;

		std::shared_ptr<Texture> texture = nullptr;

		std::shared_ptr<Texture> baseTexture = nullptr;
		std::shared_ptr<Texture> hoverTexture = nullptr;
		std::shared_ptr<Texture> holdTexture = nullptr;

		std::function<void()> onClick = nullptr;

	public:

		PERCH_API void SetTextures(std::shared_ptr<Texture> base, std::shared_ptr<Texture> hover, std::shared_ptr<Texture> hold);
		PERCH_API inline void SetOnClick(std::function<void()> onClick) { this->onClick = onClick; }

	public:

		Color color = Color();


		// ###


		// # Functions
		// ###

	public:

		PERCH_API ButtonUI(Engine* engine) : MouseOverUI(engine) {};

		// Mouse position in rect
		PERCH_API virtual void OnMouseHover() override;
		// Mouse position left rect (when stopped hovering)
		PERCH_API virtual void OnMouseExit() override;
		// Click starts in rect
		PERCH_API virtual void OnMouseDown() override;
		// Click released (may or may not still be in rect, runs if click started in rect)
		PERCH_API virtual void OnMouseUp() override;
		// Click started and released in rect (both started and released in rect)
		PERCH_API virtual void OnMouseClick() override;

		PERCH_API virtual void SetupDraw(Renderer* renderer) override;
		PERCH_API virtual void Draw(Renderer* renderer) override;
		PERCH_API virtual void OnDestroy() override;

		PERCH_API virtual Vector2 GetGlobalSize(std::shared_ptr<Texture> texture);


	};


}
