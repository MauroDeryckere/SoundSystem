#include "FModSoundSystemImpl.h"

#include <iostream>
#include <filesystem>

#include <cassert>

namespace Internal
{
	FModSoundSystem::FModSoundSystemImpl::FModSoundSystemImpl(std::string_view dataPath) :
		m_DataPath{ dataPath }
	{
		assert(std::filesystem::exists(dataPath));
		assert(std::filesystem::is_directory(dataPath));

		ERRCHECK(FMOD::Studio::System::create(&m_pStudio));

		ERRCHECK(m_pStudio->initialize(MAX_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));
		ERRCHECK(m_pStudio->getCoreSystem(&m_pSystem));

		ERRCHECK(m_pSystem->getMasterChannelGroup(&m_pMasterGroup));
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

	std::filesystem::path const& FModSoundSystem::FModSoundSystemImpl::GetDataPath() const noexcept
	{
		return m_DataPath;
	}

	void FModSoundSystem::FModSoundSystemImpl::ErrorCheck(FMOD_RESULT result, char const* file, int line) noexcept
	{
		if (result != FMOD_OK)
		{
			std::cerr << "FMOD error! (" << result << "): in file " << file << " at line " << line << std::endl;
		}
	}
}