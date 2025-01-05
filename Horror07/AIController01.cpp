

#include "AIController01.h"
#include "Enemy01.h"
#include "Player01.h"
#include "Actors/DecoyDoll.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "ai_tags.h"
#include "BlackboardKeyList.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AAIController01::AAIController01(FObjectInitializer
	const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

void AAIController01::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AEnemy01* const npc = Cast<AEnemy01>(InPawn))
	{
		if (UBehaviorTree* const tree
			= npc->GetBehaviorTree()) {
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}

void AAIController01::SetupPerceptionSystem()
{

	SightConfig =
		CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	if (SightConfig)
	{
		SetPerceptionComponent(
			*CreateDefaultSubobject<UAIPerceptionComponent>(
				TEXT("Perception Component")));

		SightConfig->SightRadius = SeeRange;
		SightConfig->LoseSightRadius = SightConfig->SightRadius * 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->
			SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->
			OnTargetPerceptionUpdated.AddDynamic(
				this, &AAIController01::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AAIController01::OnTargetDetected(
	AActor* Actor, FAIStimulus const Stimulus)
{
	auto* const CppPlayer01 = Cast<APlayer01>(Actor);

	//プレイヤー発見時の処理
	if (CppPlayer01)
	{
		GetBlackboardComponent()->
			SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());

		if (SeePlayerSE)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SeePlayerSE);
		}
	}
}


