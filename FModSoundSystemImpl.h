#ifndef FMODSOUNDSYSTEMIMPL
#define FMODSOUNDSYSTEMIMPL

#include "FModSoundSystem.h"

#include <string>

#include <fmod.hpp>
#include <fmod_studio.hpp>


namespace Internal
{
	class FModSoundSystem::FModSoundSystemImpl final
	{
	public:
		FModSoundSystemImpl(std::string_view dataPath);
		~FModSoundSystemImpl();

		void Update() noexcept;

	private:
		std::string const m_DataPath;

		//Max audio channels for fmod initialization
		int static constexpr MAX_CHANNELS{ 1024 };

		FMOD::Studio::System* m_pStudio{ nullptr };
		FMOD::System* m_pSystem{ nullptr }; //Core API

		static void ErrorCheck(FMOD_RESULT result, const char* file, int line) noexcept;
		#define ERRCHECK(result) ErrorCheck(result, __FILE__, __LINE__)
	};

}

#endif