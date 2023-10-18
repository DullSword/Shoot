// Shoot Game. All Rights Reserved.

#include "Sound/ShootSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

void UShootSoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass)
	{
		return;
	}

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UShootSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass)
	{
		return;
	}

	float NewVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	SetSoundClassVolume(SoundClass, NewVolume);
}
