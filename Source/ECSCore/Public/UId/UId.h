#pragma once
#include "UId.generated.h"

USTRUCT(BlueprintType)
struct ECSCORE_API FUId
{
	GENERATED_BODY()

	explicit FUId(const int32 ID = 0): ID(ID) {}
	
	FORCEINLINE bool operator==(const FUId& Other) const	{
		return ID == Other.ID;
	}
	
	FORCEINLINE bool operator!=(const FUId& Other) const	{
		return ID != Other.ID;
	}
	
	FORCEINLINE bool operator!=(const uint32& Other) const	{
		return ID != Other;
	}
	
	FORCEINLINE bool operator<(const FUId& Other) const	{
		return ID < Other.ID;
	}
	
	FORCEINLINE bool operator>(const FUId& Other) const	{
		return ID > Other.ID;
	}

	friend uint32 GetTypeHash (const FUId& Other)
	{
		return GetTypeHash(Other.ID);
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;
};
