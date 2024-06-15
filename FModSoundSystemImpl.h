#ifndef FMODSOUNDSYSTEMIMPL
#define FMODSOUNDSYSTEMIMPL

#include "FModSoundSystem.h"

namespace Internal
{
	class FModSoundSystem::FModSoundSystemImpl final
	{
	public:
		FModSoundSystemImpl(std::string_view dataPath);
		~FModSoundSystemImpl();

	private:
		const std::string m_DataPath;
	};
}

#endif