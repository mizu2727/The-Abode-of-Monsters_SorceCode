

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPathPoint.generated.h"

UCLASS()
class HORROR07_API UBTTask_FindPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_FindPathPoint(
		FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	//úpújà íuÇÃç¿ïWÉLÅ[
	UPROPERTY(
		EditAnywhere, Category = "Blackboard", 
		meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector PatrolPathVectorKey;
};
