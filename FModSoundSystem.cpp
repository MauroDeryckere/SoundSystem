#include "FModSoundSystemImpl.h"

namespace Internal
{
	FModSoundSystem::FModSoundSystem(std::string_view dataPath) noexcept :
		m_pImpl{ std::make_unique<FModSoundSystem::FModSoundSystemImpl>(dataPath) }
	{ }

	FModSoundSystem::~FModSoundSystem() noexcept = default;

	void FModSoundSystem::Update() noexcept { m_pImpl->Update(); }

	std::filesystem::path const& FModSoundSystem::GetDataPath() const noexcept { return m_pImpl->GetDataPath(); }

	bool FModSoundSystem::LoadSound(SoundData const& soundData) noexcept { return m_pImpl->LoadSound(soundData); }
	bool FModSoundSystem::UnloadSound(std::string_view sound) noexcept { return m_pImpl->UnloadSound(sound); }
}