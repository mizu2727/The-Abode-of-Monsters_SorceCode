
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy01.h"
#include "AIController01.generated.h"


UCLASS()
class HORROR07_API AAIController01 : public AAIController
{
	GENERATED_BODY()
	
public:
	explicit AAIController01(
		FObjectInitializer const& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIBehaviorTree")
	UBehaviorTree* AIBehaviorTree;

	//視界範囲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SeeRange")
	float SeeRange = 500.0f;

protected:
	virtual void OnPossess(class APawn* InPawn) override;


private:
	//プレイヤー発見時SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SeePlayerSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* SeePlayerSE;

	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, 
		FAIStimulus const Stimulus);
};
