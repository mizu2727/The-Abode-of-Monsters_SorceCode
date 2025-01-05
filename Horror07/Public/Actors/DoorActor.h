
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



	//ドアを開く
	UFUNCTION()
	virtual void OpenDoor() override;

	//敵がドアを開く
	UFUNCTION(BlueprintCallable, Category = "Door")
	virtual void OpenEnemyDoor(AEnemy01* enemy) override;

	//ドアを閉じる
	UFUNCTION()
	virtual void CloseDoor() override;

	//ドアの開閉の判定
	bool IsOpenDoor;


	//鍵が掛かっているかを判定する
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "IsNeedKeyDoor")
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeX = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeY = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "MeshSize")
	float MeshSizeZ = 1.0f;


	//ドアのメッシュ
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


	//ドアを開ける時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* OpenDoorSE;

	//ドアを閉じる時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloseDoorSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* CloseDoorSE;
};
