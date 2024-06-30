#ifndef FMODSOUNDSYSTEMIMPL
#define FMODSOUNDSYSTEMIMPL

#include "FModSoundSystem.h"

#include "ThreadsafeQueue.h"

#include <fmod.hpp>
#include <fmod_studio.hpp>

#include <filesystem>
#include <string>

#include <unordered_map>
#include <unordered_set>

//FMOD DOCUMENTATION
//https://www.fmod.com/docs/2.03/api/welcome.html
//------------------

namespace Internal
{
	class FModSoundSystem::FModSoundSystemImpl final
	{
	public:
		FModSoundSystemImpl(std::string_view dataPath);
		~FModSoundSystemImpl();

		void Update() noexcept;

		[[nodiscard]] std::filesystem::path const& GetDataPath() const noexcept;

		bool LoadSound(SoundData const& soundData) noexcept;
		bool UnloadSound(std::string_view sound) noexcept;

		FModSoundSystemImpl(const FModSoundSystemImpl&) = delete;
		FModSoundSystemImpl(FModSoundSystemImpl&&) = delete;
		FModSoundSystemImpl& operator=(const FModSoundSystemImpl&) = delete;
		FModSoundSystemImpl& operator=(const FModSoundSystemImpl&&) = delete;
	
	private:
		std::filesystem::path const m_DataPath{ };

		//Max audio channels for fmod initialization
		int static constexpr MAX_CHANNELS{ 1024 };

		FMOD::Studio::System* m_pStudio{ nullptr };
		//Core API
		FMOD::System* m_pSystem{ nullptr };

		//Channels
		FMOD::ChannelGroup* m_pMasterGroup{ nullptr };

		//--------

		//Sounds
		std::unordered_map<std::string, FMOD::Sound*> m_LoadingSounds{ };
		std::unordered_map<FMOD::Sound*, std::string> m_LoadingSoundsRevMap{ };

		std::unordered_map<std::string, FMOD::Sound*> m_LoadedSounds{ };

		//Sounds that were not in the correct state to be released (not finished opening) to prevent stalls
		//https://www.fmod.com/docs/2.03/api/core-api-sound.html#sound_release
		std::unordered_set<FMOD::Sound*> m_SoundsToRelease{ };

		ThreadSafeQueue<FMOD::Sound*> m_LoadedSoundsQueue{ };
		//------

		static void ErrorCheck(FMOD_RESULT result, char const* file, int line) noexcept;
		#define ERRCHECK(result) ErrorCheck(result, __FILE__, __LINE__)

		FMOD::Sound* LoadSoundImpl(const SoundData& soundData) noexcept;

		static FMOD_RESULT F_CALL NonBlockLoadCallback(FMOD_SOUND* sound, FMOD_RESULT);
	};
}

#endif