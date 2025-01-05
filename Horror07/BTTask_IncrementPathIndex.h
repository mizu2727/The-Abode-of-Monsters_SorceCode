
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncrementPathIndex.generated.h"


UCLASS()
class HORROR07_API UBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	explicit UBTTask_IncrementPathIndex(
		FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	//�p�j����
	enum class EDirectionType {Forward, Reverse};
	EDirectionType Direction = EDirectionType::Forward;

	UPROPERTY(
		EditAnywhere, BlueprintReadWrite, Category = "AI",
		meta = (AllowPrivateAccess = "true"))
	bool bBiDirectional = false;
};
