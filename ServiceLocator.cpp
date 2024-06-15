#include "ServiceLocator.h"

namespace Internal
{
	std::unique_ptr<SoundSystem> ServiceLocator::m_pSoundSystem{ std::make_unique<NullSoundSystem>() };
}