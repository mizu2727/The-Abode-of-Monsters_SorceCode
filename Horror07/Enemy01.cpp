

#include "Enemy01.h"
#include "AIController01.h"
#include "Player01.h"
#include "PlayerController01.h"
#include "GameFramework/PlayerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


class APlayer01;

AEnemy01::AEnemy01()
{

	InteractCapsuleComponent = 
		CreateOptionalDefaultSubobject<UCapsuleComponent>
			(TEXT("InteractCapsuleComponent"));



	//カプセルコンポーネントを設置(視線の先に置く)
	InteractCapsuleComponent->
		SetRelativeLocation(
			FVector(10.0f, 0.0f, 0.0f));

	//サイズ
	InteractCapsuleComponent->
		InitCapsuleSize(3.0f,1.0f);


	InteractCapsuleComponent->
		SetCollisionEnabled(
			ECollisionEnabled::QueryOnly);

	InteractCapsuleComponent->
		SetCollisionResponseToAllChannels(
			ECollisionResponse::ECR_Overlap);

	VigilanceModeAudioComponent = 
		CreateDefaultSubobject<UAudioComponent>(TEXT("VigilanceModeAudioComponent"));

	// 最初は自動で再生しない
	VigilanceModeAudioComponent->bAutoActivate = false;
}

void AEnemy01::BeginPlay()
{
	Super::BeginPlay();	
	InteractCapsuleComponent->SetActive(true);	
}



void AEnemy01::Tick(float DeltaTime)
{
	AAIController01* AIController01 = Cast<AAIController01>(GetController());

	Super::Tick(DeltaTime);


	APlayerController* PlayerController = 
		UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		APlayer01* Player =Cast<APlayer01>(PlayerController->GetPawn());

		float Distance =
			FVector::Dist(Player->GetActorLocation(),
				GetActorLocation());

		//敵の近くでプレイヤーがダッシュした場合、警戒音SEを鳴らす
		if (Distance <= DetectionRadius)
		{
			if (Player->IsRun && !VigilanceModeAudioComponent->IsPlaying())
			{
				VigilanceModeAudioComponent->SetSound(VigilanceModeSE);

				VigilanceModeAudioComponent->Play();
			}
			else if (!Player->IsRun && VigilanceModeAudioComponent->IsPlaying())
			{
				VigilanceModeAudioComponent->Stop();
			}
		}
	}
}


UBehaviorTree* AEnemy01::GetBehaviorTree()const 
{
	return Tree;
}

APatrolPath* AEnemy01::GetPatrolPath()
{
	return PatrolPath;
}

void AEnemy01::OnEnemyComponentHit(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpuls, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (APlayer01* Player = Cast<APlayer01>(OtherActor))
		{
			EnemyAttack(Player);
		}
	}
}

void AEnemy01::EnemyAttack(APlayer01* Player)
{
	if (Player->HP > 0)
	{
		Player->HP = Player->HP - Attack;

		if (Player->HP <= 0)
		{
			Player->GameOverPlayer();
		}
	}
}