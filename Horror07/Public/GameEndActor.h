
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameEndActor.generated.h"

UCLASS()
class HORROR07_API AGameEndActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameEndActor();

protected:
	//�R���|�[�l���g
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UBoxComponent* BoxComponent;

	//�R���|�[�l���g�̃T�C�Y
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "BoxSizeX")
	float BoxSizeX = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "BoxSizeY")
	float BoxSizeY = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "BoxSizeZ")
	float BoxSizeZ = 1.0f;



	UFUNCTION(BlueprintCallable, Category = "GameEndActor")
	void OnGameEndActorActorComponentHit(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpuls,
		const FHitResult& SweepResult);

};
