#pragma once

#include "IDamageableActor.generated.h"

UINTERFACE(MinimalAPI)
class UDamageableActor : public UInterface
{
	GENERATED_BODY()
};

class ECSCORE_API IDamageableActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnDamaged(float CurrentHealth, float MaxHealth);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnBulletHit(FHitResult HitResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DestructObject();
};

