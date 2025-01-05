

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
		//�v���C���[�̈ʒu���u���b�N�{�[�h����擾
		auto const playerLocation
			= OwnerComp.GetBlackboardComponent()
			->GetValueAsVector(GetSelectedBlackboardKey());

		//�v���C���[�̈ʒu�ֈړ�
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(
			cont, playerLocation);

		FinishLatentTask(OwnerComp,
			EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
