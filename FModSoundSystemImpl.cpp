#include "FModSoundSystemImpl.h"

//TODO setup release, and both x86 dlls etc in proj settings.

namespace Internal
{
	FModSoundSystem::FModSoundSystemImpl::FModSoundSystemImpl(std::string_view dataPath) :
		m_DataPath{ dataPath }
	{
		FMOD::Studio::System::create(&m_pStudio);

		int constexpr MAX_CHANNELS{ 512 };

		m_pStudio->initialize(MAX_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);
		m_pStudio->getCoreSystem(&m_pSystem);
	}

	FModSoundSystem::FModSoundSystemImpl::~FModSoundSystemImpl()
	{
		m_pStudio->unloadAll();
		m_pStudio->release();
	}
	void FModSoundSystem::FModSoundSystemImpl::Update() noexcept
	{

	}
}