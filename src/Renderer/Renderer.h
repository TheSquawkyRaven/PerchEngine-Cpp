#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


namespace Perch
{

	class Engine;
	class Branch;

	struct Color;
	struct Vector2;
	struct Texture;
	struct Rect2;
	struct Viewport;
	struct Font;

	class Renderer
	{

		friend Engine;

		// # Variables + Getters/Setters

	private:


	protected:

		Color* clearColor = nullptr;


	public:

		// ###


		// # Functions

	protected:

		virtual bool InitializeRenderer() = 0;

	public:

		inline virtual void SetClearColor(Color* color) { clearColor = color; };
		virtual void SetDrawColor(Color* color) = 0;
		virtual void Clear() = 0;

		virtual void SetDrawOrder(Branch* branch, int layer, int order) = 0;
		virtual void Draw() = 0;
		virtual void Flush() = 0;

		virtual void DrawTexture(Texture* texture, Color* color,
			Rect2* sourceRect, Rect2* destinationRect) = 0;
		virtual void DrawTexture(Texture* texture, Color* color, 
			Rect2* sourceRect, Rect2* destinationRect, 
			double angle, Vector2* rotateOrigin, 
			bool flipX, bool flipY) = 0;

		virtual void DrawPoint(int x, int y, Color* color) = 0;
		virtual void DrawLine(int x1, int y1, int x2, int y2, Color* color) = 0;
		virtual void DrawRect(Rect2* rect, Color* color) = 0;

		virtual void UseViewport(Viewport* viewport) = 0;

		virtual void Destroy() = 0;

		// ###
	};
}
