#include "ServiceLocator.h"

#include "FModSoundSystem.h"

#include "SoundData.h"

#include <filesystem>
#include <cassert>
#include <iostream>

int main()
{
	Internal::ServiceLocator::RegisterSoundSystem(std::make_unique<Internal::FModSoundSystem>("Data/Audio"));
	
	Internal::SoundData testSound{"Gunshot.wav"};

	//Simple loop to be replaced with the game engine loop in engine
	while (true)
	{
		Internal::ServiceLocator::GetSoundSystem().Update();
	}

	return 0;
}