#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "Branch.h"

#include "../Structs/Clip.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Audio : public Branch
	{

		// # Variables + Getters/Setters
	private:

		std::shared_ptr<Clip> clip = nullptr;

	public:

		PERCH_API void SetClip(std::shared_ptr<Clip> clip);
		PERCH_API inline std::shared_ptr<Clip> GetClip() { return clip; }

		// ###

		// # Functions

	private:
		
	public:

		PERCH_API Audio(Engine* engine) : Branch(engine) {};

		PERCH_API virtual void OnDestroy() override;

		PERCH_API void Play();
		PERCH_API void Stop();

		// ###

	};


}
