
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChangeSpeed.generated.h"


UCLASS()
class HORROR07_API UBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_ChangeSpeed();
	virtual void OnBecomeRelevant(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	//プレイヤー発見時の移動速度
	UPROPERTY(
		EditAnywhere, Category = "AI",
		meta = (AllowPrivateAccess = "yes"))
	float speed = 600.f;
};
