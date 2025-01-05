

#include "BTTask_ChasePlayer.h"
#include "AIController01.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(
	FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ ObjectInitializer }
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (auto* const cont 
		= Cast<AAIController01>(OwnerComp.GetAIOwner())) 
	{
		//プレイヤーの位置をブラックボードから取得
		auto const playerLocation
			= OwnerComp.GetBlackboardComponent()
			->GetValueAsVector(GetSelectedBlackboardKey());

		//プレイヤーの位置へ移動
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(
			cont, playerLocation);

		FinishLatentTask(OwnerComp,
			EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
