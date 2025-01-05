
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindDecoyDollLocation.generated.h"

/**
 * 
 */
UCLASS()
class HORROR07_API UBTTask_FindDecoyDollLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_FindDecoyDollLocation(
		FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::
		Type ExecuteTask(
			UBehaviorTreeComponent& OwnerComp,
			uint8* NodeMemory)override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Search", meta = (AllowPrivateAccess = "true"))
	bool SearchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Search", meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 150.f;
};
