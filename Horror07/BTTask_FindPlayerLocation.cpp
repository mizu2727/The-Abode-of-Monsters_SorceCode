

#include "BTTask_FindPlayerLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerLocation::
UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ ObjectInitializer }
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::
ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (auto* const Player =
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))

	{
		//�v���C���[�̈ʒu���擾
		auto const PlayerLocation =
			Player->GetActorLocation();

		if (SearchRandom) 
		{
			FNavLocation Loc;

			if (auto* const NavSys = 
				UNavigationSystemV1::GetCurrent(GetWorld())) 
			{
				
				if (NavSys->
					GetRandomPointInNavigableRadius(
						PlayerLocation,SearchRadius,Loc)) 
				{
					OwnerComp.GetBlackboardComponent()
						->SetValueAsVector(
							GetSelectedBlackboardKey(), Loc.Location);

					FinishLatentTask(OwnerComp,
						EBTNodeResult::Succeeded);

					return EBTNodeResult::Succeeded;
				}
			}
		}
		else 
		{
			OwnerComp.GetBlackboardComponent()
				->SetValueAsVector(
					GetSelectedBlackboardKey(), PlayerLocation);

			FinishLatentTask(OwnerComp,
				EBTNodeResult::Succeeded);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
