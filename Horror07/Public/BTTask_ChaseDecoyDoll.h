
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChaseDecoyDoll.generated.h"


UCLASS()
class HORROR07_API UBTTask_ChaseDecoyDoll : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_ChaseDecoyDoll(
		FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
};
