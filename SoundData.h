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

		bool const is3D{ true };
		bool const isLooping{ false };
		bool const isStream{ false };

		SoundData(std::string_view path, bool is3D = true, bool isLooping = false, bool isStream = false) :
			soundPath{ path },

			is3D{ is3D },
			isLooping{ isLooping },
			isStream{ isStream }
		{
			assert(std::filesystem::exists(ServiceLocator::GetSoundSystem().GetDataPath() / path) 
			    && std::filesystem::is_regular_file(ServiceLocator::GetSoundSystem().GetDataPath() / path));
		}

		~SoundData() = default;
	};
}

#endif