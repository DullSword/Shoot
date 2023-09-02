#pragma once

class AnimUtils
{
public:
	template <typename T>
	static T* FindFirstNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation)
		{
			return nullptr;
		}

		const auto& NotifyEvents = Animation->Notifies;
		for (const auto& NotifyEvent : NotifyEvents)
		{
			auto Notify = Cast<T>(NotifyEvent.Notify);
			if (Notify)
			{
				return Notify;
			}
		}

		return nullptr;
	}
};