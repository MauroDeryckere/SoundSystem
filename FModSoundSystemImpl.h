#ifndef FMODSOUNDSYSTEMIMPL
#define FMODSOUNDSYSTEMIMPL

#include "FModSoundSystem.h"

#include <string>

#include <fmod.hpp>
#include <fmod_studio.hpp>

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

		[[nodiscard]] std::string_view GetDataPath() const noexcept;

		FModSoundSystemImpl(const FModSoundSystemImpl&) = delete;
		FModSoundSystemImpl(FModSoundSystemImpl&&) = delete;
		FModSoundSystemImpl& operator=(const FModSoundSystemImpl&) = delete;
		FModSoundSystemImpl& operator=(const FModSoundSystemImpl&&) = delete;
	
	private:
		std::string const m_DataPath{ };

		//Max audio channels for fmod initialization
		int static constexpr MAX_CHANNELS{ 1024 };

		FMOD::Studio::System* m_pStudio{ nullptr };
		//Core API
		FMOD::System* m_pSystem{ nullptr };

		FMOD::ChannelGroup* m_pMasterGroup{ nullptr };

		static void ErrorCheck(FMOD_RESULT result, char const* file, int line) noexcept;
		#define ERRCHECK(result) ErrorCheck(result, __FILE__, __LINE__)
	};
}

#endif