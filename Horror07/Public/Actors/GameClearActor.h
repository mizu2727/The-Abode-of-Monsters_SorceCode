
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameClearActor.generated.h"

UCLASS()
class HORROR07_API AGameClearActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameClearActor();

protected:
	//コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UBoxComponent* BoxComponent;


	//コンポーネントのサイズ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "BoxSizeX")
	float BoxSizeX = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "BoxSizeY")
	float BoxSizeY = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "BoxSizeZ")
	float BoxSizeZ = 1.0f;


	UFUNCTION(BlueprintCallable, Category = "GameClearActor")
	void OnGameClearActorComponentHit(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpuls,
		const FHitResult& SweepResult);


private:
	//GameClearLevelへ移動する処理
	void GameClearLevel();
};
