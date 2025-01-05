//敵をランダムに徘徊させる場合のソースコード

#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "AIController01.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(
	FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ ObjectInitializer }
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) 
{
	//get AIController and its npc
	if (auto* const cont
		= Cast<AAIController01>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = cont->GetPawn()) 
		{
			//obtain npc location to use as on origin
			auto const Origin = npc->GetActorLocation();

			//get the navigation system and generate a random location
			if (auto* const NavSys = 
				UNavigationSystemV1::GetCurrent(GetWorld())) 
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(
						Origin, SearchRadius, Loc)) 
				{
					OwnerComp.GetBlackboardComponent()
						->SetValueAsVector(
							GetSelectedBlackboardKey(),
							Loc.Location);
				}

				//finish with success
				FinishLatentTask(OwnerComp, 
					EBTNodeResult::Succeeded);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}