#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "MouseOver2D.h"
#include "../Branch2D/Sprite2D.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Button2D : public MouseOver2D
	{

		// # Variables + Getters/Setters

	private:

		bool isHeld = false;

		Perch::Sprite2D* linkedSprite = nullptr;
		bool swapTexture = false;
		std::shared_ptr<Texture> baseTexture = nullptr;
		std::shared_ptr<Texture> hoverTexture = nullptr;
		std::shared_ptr<Texture> holdTexture = nullptr;

		std::function<void()> onClick = nullptr;

	public:

		PERCH_API inline void SetOnClick(std::function<void()> onClick) { this->onClick = onClick; }

	public:

		Color color = Color();


		// ###


		// # Functions
		// ###

	protected:

		PERCH_API virtual void Hover();
		PERCH_API virtual void Exit();
		PERCH_API virtual void Down();
		PERCH_API virtual void Up();
		PERCH_API virtual void Click();

	public:

		PERCH_API Button2D(Engine* engine) : MouseOver2D(engine) {};

		PERCH_API virtual void OnMouseOver(MouseOverState state) override;

		// Make sure to set Sprite Rows or Sprite Order. 0 - base, 1 - hover, 2 - held
		PERCH_API virtual void LinkSprite(Sprite2D* sprite);
		PERCH_API virtual void LinkSprite(Sprite2D* sprite, std::shared_ptr<Texture> base, std::shared_ptr<Texture> hover, std::shared_ptr<Texture> hold);

		PERCH_API virtual void OnDestroy() override;

	};


}
