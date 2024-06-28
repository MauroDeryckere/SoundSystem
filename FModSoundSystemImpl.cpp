#include "FModSoundSystemImpl.h"

#include <iostream>

namespace Internal
{
	FModSoundSystem::FModSoundSystemImpl::FModSoundSystemImpl(std::string_view dataPath) :
		m_DataPath{ dataPath }
	{
		ERRCHECK(FMOD::Studio::System::create(&m_pStudio));

		ERRCHECK(m_pStudio->initialize(MAX_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));
		ERRCHECK(m_pStudio->getCoreSystem(&m_pSystem));
	}

	FModSoundSystem::FModSoundSystemImpl::~FModSoundSystemImpl()
	{
		ERRCHECK(m_pStudio->unloadAll());
		ERRCHECK(m_pStudio->release());
	}

	void FModSoundSystem::FModSoundSystemImpl::Update() noexcept
	{
		ERRCHECK(m_pStudio->update());
	}

	void FModSoundSystem::FModSoundSystemImpl::ErrorCheck(FMOD_RESULT result, const char* file, int line) noexcept
	{
		if (result != FMOD_OK)
		{
			std::cerr << "FMOD error! (" << result << "): in file " << file << " at line " << line << std::endl;
		}
	}
}