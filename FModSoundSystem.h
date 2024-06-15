#ifndef FMODSOUNDSYSTEM
#define FMODSOUNDSYSTEM

#include "SoundSystem.h"

#include <memory>
#include <string>

namespace Internal
{
	class FModSoundSystem final : public SoundSystem
	{
	public:
		FModSoundSystem(std::string_view dataPath) noexcept;
		~FModSoundSystem() noexcept;

	private:
		class FModSoundSystemImpl;
		const std::unique_ptr<FModSoundSystemImpl> m_pImpl;
	};
}

#endif