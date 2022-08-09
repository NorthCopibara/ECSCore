#pragma once
#include "UId.h"

class ECSCORE_API UidSubjectManager
{
	inline static TMap<FUId, FSubjectHandle> _ids {};

public:
	static FUId Next(FSubjectHandle Subject)
	{
		TArray<FUId> Keys;
		_ids.GetKeys(Keys);
		FUId NextUid{0};		
		if(Keys.Num() > 0)
			NextUid.ID = Keys.Last().ID;
		NextUid.ID++;
		_ids.Add(NextUid, Subject);
		return NextUid;
	}

	static void Dispose(){_ids.Reset();}
	static void AddIdToArray(const FUId Id, const FSubjectHandle Subject)
	{
		_ids.Add(Id, Subject);		
	}

	static void SortKeys()
	{
		_ids.KeySort([](const FUId A, const FUId B)
		{
			return A < B;
		});	
	}

	static void RemoveSubject(const FUId Key)
	{
		if(_ids.Contains(Key))
			_ids.Remove(Key);
	}

	static FSubjectHandle GetSubject(const FUId Key)
	{
		if(!_ids.Contains(Key))
		{
			UE_LOG(LogTemp, Warning, TEXT("ID NOT FOUND: %d"), Key.ID)
			return FSubjectHandle();
		}
			
		return _ids[Key];
	}
};
