
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Horror07/Public/DoorInterface.h"
#include "GoalDoorActor.generated.h"

UCLASS()
class HORROR07_API AGoalDoorActor : public AActor,
	public IDoorInterface
{
	GENERATED_BODY()
	
public:	
	AGoalDoorActor();

	//�h�A���J��
	UFUNCTION()
	virtual void OpenDoor() override;

	//�h�A�����
	UFUNCTION()
	virtual void CloseDoor() override;

	//�h�A�̊J�̔���
	bool IsOpenDoor;

	//�����|�����Ă��邩�𔻒肷��
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "Door")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeX = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeY = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeZ = 1.0f;


	//�h�A�̃��b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UStaticMeshComponent* DoorMesh;


	//�h�A���J���鎞��SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* OpenDoorSE;

	//�h�A����鎞��SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloseDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* CloseDoorSE;

	//�����������Ă��鎞��SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnLockDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* UnLockDoorSE;

};
