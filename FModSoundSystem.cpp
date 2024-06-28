#include "FModSoundSystemImpl.h"

namespace Internal
{
	FModSoundSystem::FModSoundSystem(std::string_view dataPath) noexcept :
		m_pImpl{ std::make_unique<FModSoundSystem::FModSoundSystemImpl>(dataPath) }
	{ }

	FModSoundSystem::~FModSoundSystem() noexcept = default;

	void FModSoundSystem::Update() noexcept { m_pImpl->Update(); }
}