
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLocation.generated.h"


UCLASS()
class HORROR07_API UBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_FindPlayerLocation(
		FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::
		Type ExecuteTask(
			UBehaviorTreeComponent& OwnerComp, 
			uint8* NodeMemory)override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Search", meta = (AllowPrivateAccess = "true"))
	bool SearchRandom = false;

	//プレイヤーを発見できる範囲
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Search", meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 150.f;
};
