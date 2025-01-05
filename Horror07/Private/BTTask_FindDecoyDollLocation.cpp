//’Ç‰Á—v‘f
#include "BTTask_FindDecoyDollLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/DecoyDoll.h"


UBTTask_FindDecoyDollLocation::UBTTask_FindDecoyDollLocation(
	FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find DecoyDoll Location");
}

EBTNodeResult::Type UBTTask_FindDecoyDollLocation::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get DecoyDoll
	if (auto* const DecoyDoll =
		UGameplayStatics::GetActorOfClass(
			GetWorld(), ADecoyDoll::StaticClass()))

	{
		//get DecoyDoll location to use as on origin
		auto const DecoyDollLocation =
			DecoyDoll->GetActorLocation();

		if (SearchRandom)
		{
			FNavLocation Loc;

			//get the navigation system and generator a random location near the DecoyDoll
			if (auto* const NavSys =
				UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				//try to get a random location near the DecoyDoll
				if (NavSys->
					GetRandomPointInNavigableRadius(
						DecoyDollLocation, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()
						->SetValueAsVector(
							GetSelectedBlackboardKey(), Loc.Location);

					//finish with success
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
					GetSelectedBlackboardKey(), DecoyDollLocation);

			FinishLatentTask(OwnerComp,
				EBTNodeResult::Succeeded);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
