#ifndef SOUNDDATA
#define SOUNDDATA

#include "ServiceLocator.h"

#include <string>
#include <filesystem>
#include <cassert>

namespace Internal
{
	struct SoundData final
	{
		std::string const soundPath;

		SoundData(std::string_view path) :
			soundPath{ path }
		{
			assert(std::filesystem::exists(ServiceLocator::GetSoundSystem().GetDataPath() / path) 
			    && std::filesystem::is_regular_file(ServiceLocator::GetSoundSystem().GetDataPath() / path));
		}

		~SoundData() = default;
	};
}

#endif