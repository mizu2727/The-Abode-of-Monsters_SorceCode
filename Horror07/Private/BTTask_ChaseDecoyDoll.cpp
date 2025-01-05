//’Ç‰Á—v‘f
#include "BTTask_ChaseDecoyDoll.h"
#include "Horror07/AIController01.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UBTTask_ChaseDecoyDoll::UBTTask_ChaseDecoyDoll(
	FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase DecoyDoll");
}

EBTNodeResult::Type UBTTask_ChaseDecoyDoll::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get target location from blackboard via the NPC's controller
	if (auto* const cont
		= Cast<AAIController01>(OwnerComp.GetAIOwner()))
	{
		auto const DecoyDollLocation
			= OwnerComp.GetBlackboardComponent()
			->GetValueAsVector(GetSelectedBlackboardKey());

		//move to the DecoyDoll's location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(
			cont, DecoyDollLocation);

		FinishLatentTask(OwnerComp,
			EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
