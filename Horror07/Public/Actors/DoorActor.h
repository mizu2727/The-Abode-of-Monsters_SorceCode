
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Horror07/Public/DoorInterface.h"
#include "DoorActor.generated.h"

UCLASS()
class HORROR07_API ADoorActor : public AActor,
	public IDoorInterface
{
	GENERATED_BODY()
	
public:	
	ADoorActor();



	//�h�A���J��
	UFUNCTION()
	virtual void OpenDoor() override;

	//�G���h�A���J��
	UFUNCTION(BlueprintCallable, Category = "Door")
	virtual void OpenEnemyDoor(AEnemy01* enemy) override;

	//�h�A�����
	UFUNCTION()
	virtual void CloseDoor() override;

	//�h�A�̊J�̔���
	bool IsOpenDoor;


	//�����|�����Ă��邩�𔻒肷��
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "IsNeedKeyDoor")
	bool IsNeedKeyDoor = false;

	//�h�A���J����p�x
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "OpenDirenctionValue")
	float OpenDirenctionValue = 90.0f;

	//�h�A�����p�x
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "CloseDirenctionValue")
	float CloseDirenctionValue = 0.0f;


	//���b�V���T�C�Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeX = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeY = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeZ = 1.0f;


	//�h�A�̃��b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UStaticMeshComponent* DoorMesh;


	UFUNCTION(BlueprintCallable, Category = "Door")
	void OnDoorComponentHit(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpuls,
		const FHitResult& SweepResult);


	//�h�A���J���鎞��SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* OpenDoorSE;

	//�h�A����鎞��SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloseDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* CloseDoorSE;
};
