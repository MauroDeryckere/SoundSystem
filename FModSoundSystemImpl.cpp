#include "FModSoundSystemImpl.h"

#include "SoundData.h"

#include <iostream>
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
		FMOD::Sound* pSound{ nullptr };
		while (m_LoadedSoundsQueue.TryPop(pSound))
		{
			if (auto it{ m_LoadingSoundsRevMap.find(pSound) }; it != end(m_LoadingSoundsRevMap))
			{
				assert(m_LoadingSounds.contains(it->second));

				m_LoadedSounds[it->second] = pSound;

				m_LoadingSounds.erase(it->second);
				m_LoadingSoundsRevMap.erase(it);
			}
			else
			{
				assert(m_SoundsToRelease.contains(pSound));
				pSound->release();
				m_SoundsToRelease.erase(pSound);
			}
		}

		ERRCHECK(m_pStudio->update());
	}

	std::filesystem::path const& FModSoundSystem::FModSoundSystemImpl::GetDataPath() const noexcept
	{
		return m_DataPath;
	}

	bool FModSoundSystem::FModSoundSystemImpl::LoadSound(SoundData const& soundData) noexcept
	{
		if (soundData.isStream)
		{
			//Can't load a stream since it can only be played once per load
			return false;
		}

		if (m_LoadedSounds.find(soundData.soundPath) != end(m_LoadedSounds))
		{
			//Sound already loaded
			return false;
		}

		if (m_LoadingSounds.find(soundData.soundPath) != end(m_LoadingSounds))
		{
			//Sound already loading
			return false;
		}

		FMOD::Sound* pSound{ LoadSoundImpl(soundData) };

		m_LoadingSounds[soundData.soundPath] = pSound;
		m_LoadingSoundsRevMap[pSound] = soundData.soundPath;

		return true;
	}

	bool FModSoundSystem::FModSoundSystemImpl::UnloadSound(std::string_view sound) noexcept
	{
		if (auto it{ m_LoadedSounds.find(sound.data()) }; it != end(m_LoadedSounds))
		{
			FMOD_OPENSTATE openstate;
			ERRCHECK(it->second->getOpenState(&openstate, NULL, NULL, NULL));

			assert(openstate == FMOD_OPENSTATE::FMOD_OPENSTATE_READY);
			
			//TODO What if playing - when playSound function is added

			ERRCHECK(it->second->release());
			m_LoadedSounds.erase(it);

			return true;
		}

		if (auto it{ m_LoadingSounds.find(sound.data()) }; it != end(m_LoadingSounds))
		{
			FMOD_OPENSTATE openstate;
			ERRCHECK(it->second->getOpenState(&openstate, NULL, NULL, NULL));

			assert(openstate != FMOD_OPENSTATE_ERROR);
			if (openstate == FMOD_OPENSTATE::FMOD_OPENSTATE_READY)
			{
				ERRCHECK(it->second->release());
			}
			else
			{
				assert(!m_SoundsToRelease.contains(it->second));
				m_SoundsToRelease.insert(it->second);
			}

			assert(m_LoadingSoundsRevMap.contains(it->second));
			m_LoadingSoundsRevMap.erase(it->second);
			m_LoadingSounds.erase(it);

			return true;
		}
		
		return false;
	}

	void FModSoundSystem::FModSoundSystemImpl::ErrorCheck(FMOD_RESULT result, char const* file, int line) noexcept
	{
		if (result != FMOD_OK)
		{
			assert(result != FMOD_RESULT::FMOD_ERR_FORMAT && "Wrong file format!");

			std::cerr << "FMOD error! (" << result << "): in file " << file << " at line " << line << std::endl;
		}
	}

	FMOD::Sound* FModSoundSystem::FModSoundSystemImpl::LoadSoundImpl(const SoundData& soundData) noexcept
	{
		FMOD::Sound* pSound{ nullptr };

		std::filesystem::path const fullPath{ m_DataPath / soundData.soundPath };

		FMOD_MODE const flags = FMOD_DEFAULT
							| (soundData.is3D ? FMOD_3D : FMOD_2D)
							| (soundData.isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF)
							| (soundData.isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE)
							| FMOD_NONBLOCKING; //Loading on a separate thread

		FMOD_CREATESOUNDEXINFO exinfo;
		memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
		exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
		exinfo.nonblockcallback = &NonBlockLoadCallback;
		exinfo.userdata = this;

		ERRCHECK(m_pSystem->createSound(fullPath.string().c_str(), flags, &exinfo, &pSound));
		assert(pSound);

		return pSound;
	}

	FMOD_RESULT F_CALL FModSoundSystem::FModSoundSystemImpl::NonBlockLoadCallback(FMOD_SOUND* sound, FMOD_RESULT)
	{
		FMOD::Sound* pSound{ (FMOD::Sound*)sound };
		assert(pSound);

		FMOD_OPENSTATE state;
		ERRCHECK(pSound->getOpenState(&state, NULL, NULL, NULL));

		if (state == FMOD_OPENSTATE_SETPOSITION)
		{
			//ignore if callback is triggered by setposition
			return FMOD_OK;
		}

		void* userData{ nullptr };
		ERRCHECK(pSound->getUserData(&userData));
		assert(userData);

		FModSoundSystemImpl* pSys{ static_cast<FModSoundSystemImpl*>(userData) };

		if (state == FMOD_OPENSTATE_READY)
		{
			FMOD_MODE mode;
			ERRCHECK(pSound->getMode(&mode));

			if (mode & FMOD_CREATESTREAM)
			{
				
			}
			else
			{
				pSys->m_LoadedSoundsQueue.Emplace(pSound);
			}
		}
		return FMOD_OK;
	}
}