#ifndef FMODSOUNDSYSTEM
#define FMODSOUNDSYSTEM

#include "SoundSystem.h"

#include <memory>
#include <string_view>

namespace Internal
{
	class FModSoundSystem final : public SoundSystem
	{
	public:
		FModSoundSystem(std::string_view dataPath) noexcept;
		~FModSoundSystem() noexcept;

		void Update() noexcept;

		std::filesystem::path const& GetDataPath() const noexcept;

	private:
		class FModSoundSystemImpl;
		const std::unique_ptr<FModSoundSystemImpl> m_pImpl;
	};
}

#endif