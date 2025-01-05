
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

	//ドアを開く
	UFUNCTION()
	virtual void OpenDoor() override;

	//ドアを閉じる
	UFUNCTION()
	virtual void CloseDoor() override;

	//ドアの開閉の判定
	bool IsOpenDoor;

	//鍵が掛かっているかを判定する
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "Door")
	bool IsNeedKeyDoor = false;


	//ドアを開ける角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "OpenDirenctionValue")
	float OpenDirenctionValue = 90.0f;

	//ドアを閉じる角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "CloseDirenctionValue")
	float CloseDirenctionValue = 0.0f;


	//メッシュサイズ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeX = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeY = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeZ = 1.0f;


	//ドアのメッシュ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
		Category = "Collision")
	UStaticMeshComponent* DoorMesh;


	//ドアを開ける時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* OpenDoorSE;

	//ドアを閉じる時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloseDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* CloseDoorSE;

	//鍵がかかっている時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnLockDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* UnLockDoorSE;

};
