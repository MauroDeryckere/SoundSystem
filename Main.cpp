#include "ServiceLocator.h"

#include "FModSoundSystem.h"

#include "SoundData.h"

#include <filesystem>
#include <cassert>
#include <iostream>

int main()
{
	Internal::ServiceLocator::RegisterSoundSystem(std::make_unique<Internal::FModSoundSystem>("Data/Audio"));
	
	Internal::SoundData testSound{ "Gunshot.wav" };

	auto const result = Internal::ServiceLocator::GetSoundSystem().LoadSound(testSound);
	assert(result);

	//Simple loop to be replaced with the game engine loop
	while (true)
	{
		Internal::ServiceLocator::GetSoundSystem().Update();
	}

	return 0;
}