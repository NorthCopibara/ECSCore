#pragma once

class ViewExtensions
{
public:
	template <typename T>
	static T* GetComponent(AActor* Actor)
	{
		if (!Actor) return nullptr;
		const auto Component = Actor->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}

	template <typename T>
	static T* GetSceneComponentByName(AActor* Actor, FName Name)
	{
		if (!Actor) return nullptr;
		const auto Components = Actor->GetComponents();
		for (const auto Component : Components)
		{
			const auto SceneComponent = Cast<USceneComponent>(Component);
			if(!SceneComponent) continue;
			if(SceneComponent->GetFName() == Name)
			{
				return Cast<T>(SceneComponent);
			}
		}
		return nullptr;
	}
};
