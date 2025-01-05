//’Ç‰Á—v‘f
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StopInvestigating.generated.h"


UCLASS()
class HORROR07_API UBTTask_StopInvestigating : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_StopInvestigating(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
