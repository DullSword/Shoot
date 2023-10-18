// Shoot Game. All Rights Reserved.


#include "ShootGameInstance.h"
#include "Sound/ShootSoundFunctionLibrary.h"

void UShootGameInstance::ToggleVolume()
{
	UShootSoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
