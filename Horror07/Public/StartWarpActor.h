
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StartWarpActor.generated.h"

UCLASS()
class HORROR07_API AStartWarpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStartWarpActor();

protected:
	//ワープ位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TargetLocationX")
	float TargetLocationX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TargetLocationY")
	float TargetLocationY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TargetLocationZ")
	float TargetLocationZ;


	//コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UBoxComponent* BoxComponent;


	//コンポーネントのサイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "BoxSizeX")
	float BoxSizeX = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "BoxSizeY")
	float BoxSizeY = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "BoxSizeZ")
	float BoxSizeZ = 1.0f;



	UFUNCTION(BlueprintCallable, Category = "StartWarpActor")
	void OnStartWarpActorComponentHit(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpuls,
		const FHitResult& SweepResult);


	//ステージのBGMのオーディオコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StageBGMAudioComponent")
	UAudioComponent* StageBGMAudioComponent;

	//ステージのBGM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageBGM",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* StageBGM;

	//音量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BGMVolume",
		meta = (AllowPrivateAccess = "true"))
	float BGMVolume = 0.5f;
};
