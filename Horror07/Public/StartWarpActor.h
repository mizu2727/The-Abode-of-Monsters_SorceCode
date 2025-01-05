
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
	//���[�v�ʒu
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TargetLocationX")
	float TargetLocationX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TargetLocationY")
	float TargetLocationY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TargetLocationZ")
	float TargetLocationZ;


	//�R���|�[�l���g
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UBoxComponent* BoxComponent;


	//�R���|�[�l���g�̃T�C�Y
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


	//�X�e�[�W��BGM�̃I�[�f�B�I�R���|�[�l���g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StageBGMAudioComponent")
	UAudioComponent* StageBGMAudioComponent;

	//�X�e�[�W��BGM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageBGM",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* StageBGM;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BGMVolume",
		meta = (AllowPrivateAccess = "true"))
	float BGMVolume = 0.5f;
};
