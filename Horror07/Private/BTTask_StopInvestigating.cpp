//�ǉ��v�f
#include "BTTask_StopInvestigating.h"
#include "Horror07/AIController01.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackboardKeyList.h"


UBTTask_StopInvestigating::UBTTask_StopInvestigating(
	FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Stop Investigating");
}

EBTNodeResult::Type UBTTask_StopInvestigating::ExecuteTask(
	UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//�GAI�R���g���[���[���擾���A�u���b�N�{�[�h�L�[�uIsInvestigating�v��false�ɂ���
	auto const cont = Cast<AAIController01>(owner_comp.GetAIOwner());
	//cont->get_blackboard()->SetValueAsBool(bb_keys::is_investigating, false);

	// finish with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
