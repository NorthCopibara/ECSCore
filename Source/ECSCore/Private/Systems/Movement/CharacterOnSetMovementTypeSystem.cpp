#include "Systems/Movement/CharacterOnSetMovementTypeSystem.h"

#include "Components/Movement/MovementTypeComponent.h"
#include "Components/Movement/MoveSpeedComponent.h"
#include "Extensions/EcsExtenstions.h"


void CharacterOnSetMovementTypeSystem::Initialize(AMechanism* Mechanism)
{
	ReactiveAddSystem::Initialize(Mechanism);
	TriggerOnAdd = FMovementTypeComponent::StaticStruct();
}

void CharacterOnSetMovementTypeSystem::Execute(AMechanism* Mechanism, FUnsafeSubjectHandle Subject)
{
	const auto MoveType = Subject.GetTrait<FMovementTypeComponent>().Value;
	//const auto CharacterType = Subject.GetTrait<FCharacterTypeComponent>().Value; //TODO: {REF}
	//const auto DataBase = EcsExtensions::GetDataBase(Mechanism);
	//const auto CharacterBase = DataBase->CharactersStatesBase.GetDefaultObject();
	//const auto SLCharacter = CharacterBase->GetCharactersBaseByType(CharacterType);
	/*switch (MoveType)
	{
	case EMovementType::Walk:
		Subject.SetTrait(FMoveSpeedComponent(SLCharacter.WalkSpeed));
		break;

	case EMovementType::Run:
		Subject.SetTrait(FMoveSpeedComponent(SLCharacter.MoveSpeed));
		break;

	default:
		break;
	}*/
}

bool CharacterOnSetMovementTypeSystem::HasComponents(const FSubjectHandle Subject)
{
	return Subject.HasTrait<FMoveSpeedComponent>();
}
