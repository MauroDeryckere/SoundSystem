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

		FMOD::Studio::System* m_pStudio{ nullptr };
		FMOD::System* m_pSystem{ nullptr }; //Core API
	};
}

#endif