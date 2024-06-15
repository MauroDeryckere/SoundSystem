#include "ServiceLocator.h"

#include "FModSoundSystem.h"

int main()
{
	Internal::ServiceLocator::RegisterSoundSystem(std::make_unique<Internal::FModSoundSystem>("Data/Audio"));

	//Simple loop to be replaced with the game engine loop in engine
	while (true)
	{
		
	}

	return 0;
}