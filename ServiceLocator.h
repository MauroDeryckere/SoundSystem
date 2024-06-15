#ifndef SERVICE_LOCATOR
#define SERVICE_LOCATOR

#include "SoundSystem.h"

#include <memory>

namespace Internal
{
	class ServiceLocator final
	{
	public:
		[[nodiscard]] static SoundSystem& GetSoundSystem() { return (*m_pSoundSystem); }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& pSoundSystem)
		{
			m_pSoundSystem = ((!pSoundSystem) ? std::make_unique<NullSoundSystem>() : std::move(pSoundSystem));
		}

	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystem;
	};
}

#endif