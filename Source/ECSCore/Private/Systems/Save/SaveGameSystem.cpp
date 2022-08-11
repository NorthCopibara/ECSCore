#include "Systems/Save/SaveGameSystem.h"

#include "Components/UidComponent.h"
#include "Components/Events/SaveGameComponent.h"
#include "Components/Support/Emptic/LookEmpticComponent.h"
#include "Components/Support/Emptic/MoveEmpticComponent.h"
#include "DataBase/GameState/SaveState.h"
#include "DataBase/GameState/SubjectState.h"
#include "Link/ISavableActor.h"

void SaveGameSystem::Initialize(AMechanism* Mechanism)
{
	SetupTrigger(FSaveGameComponent::StaticStruct());
}

void SaveGameSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject)
{
	const auto UidFilter = FFilter::Make<FUidComponent>()
							.Exclude<FLookEmpticComponent>()
							.Exclude<FMoveEmpticComponent>();
	
	USaveState* SaveState = Cast<USaveState>(UGameplayStatics::CreateSaveGameObject(USaveState::StaticClass())); 
	Mechanism->Enchain(UidFilter)->Operate([&](const FSubjectHandle SaveSubject)
	{
		//TODO: {REF}
		//if(SaveSubject.HasTrait<FHPBarViewComponent>()) return; //TODO: Create template variant
		
		SaveFromViews(SaveSubject);
		FSubjectState SubState;
		SubState.WriteState(SaveSubject);
		SaveState->GameState.Add(SubState);
	});
	UGameplayStatics::SaveGameToSlot(SaveState, TEXT("FirstSlot"), 0);
}

void SaveGameSystem::SaveFromViews(FSubjectHandle Subject)
{
	if(Subject.HasTrait<FLinkComponent>())
	{
		const auto ObjectLink = Subject.GetTrait<FLinkComponent>().Value.GetObject();
		if(const auto Savable = Cast<ISavableActor>(ObjectLink))
			Savable->SaveOnSubject(Subject);		
	}
}