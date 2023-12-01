#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include <unordered_map>
#include <string>
#include <memory>


namespace Perch
{

	struct Texture;
	struct Font;
	struct Clip;

	class Resource
	{

		// # Variables + Getters/Setters

	private:

		std::unordered_map<std::string, std::weak_ptr<Texture>> loadedTextureMap;
		std::unordered_map<std::string, std::weak_ptr<Font>> loadedFontMap;
		std::unordered_map<std::string, std::weak_ptr<Clip>> loadedClipMap;

	public:

		// ###


		// # Functions

	private:

	public:

		std::shared_ptr<Texture> TryGetLoadedTexture(std::string path);
		void AddLoadedTexture(std::string path, std::weak_ptr<Texture> textureW);

		std::shared_ptr<Font> TryGetLoadedFont(std::string path);
		void AddLoadedFont(std::string path, std::weak_ptr<Font> fontW);

		std::shared_ptr<Clip> TryGetLoadedClip(std::string path);
		void AddLoadedClip(std::string path, std::weak_ptr<Clip> clipW);


		// ###
	};
}
