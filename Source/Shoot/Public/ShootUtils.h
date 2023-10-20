#pragma once

class ShootUtils
{
public:
	template <typename T>
	static T* GetShootPlayerComponent(AActor* SomeActor)
	{
		if (!SomeActor)
		{
			return nullptr;
		}

		const auto Component = SomeActor->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};