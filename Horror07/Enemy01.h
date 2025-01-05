

#pragma once

#include "CoreMinimal.h"
#include "PatrolPath.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Player01.h"
#include "Enemy01.generated.h"

UCLASS()
class HORROR07_API AEnemy01 : public ACharacter
{
	GENERATED_BODY()

public:	
	AEnemy01();

	virtual void Tick(float DeltaTime) override;

	
	UBehaviorTree* GetBehaviorTree() const;

	APatrolPath* GetPatrolPath();


	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void OnEnemyComponentHit(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpuls,
		const FHitResult& SweepResult);


	//視線の先にコンポーネントを配置
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UCapsuleComponent* InteractCapsuleComponent;


	//攻撃力
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "HP")
	float Attack = 1;

	//プレイヤーを攻撃する
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void EnemyAttack(APlayer01* Player);

	// プレイヤーを検出する範囲
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "DetectionRadius")
	float DetectionRadius = 500.0f;


	// 走る速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "RunSpeed")
	float RunSpeed = 1.0f;

	//警戒時SEのコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VigilanceModeAudioComponent")
	UAudioComponent* VigilanceModeAudioComponent;

	//警戒時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VigilanceModeSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* VigilanceModeSE;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, 
		Category = "AI", meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;
};
