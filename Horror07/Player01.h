

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "ItemStructs.h"
#include "Public/GameOverUW.h"
#include "Sound/SoundBase.h"
#include "Player01.generated.h"

class AItemActor;
class AGaolItem;



UCLASS()
class HORROR07_API APlayer01 : public ACharacter
{
	GENERATED_BODY()

public:
	APlayer01();

	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;

	//前後操作関数
	UFUNCTION()
	void MoveForward(float moveForward);

	//左右操作関数
	UFUNCTION()
	void MoveRight(float moveRight);


	// ダッシュの速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunSpeed")
	float RunSpeed;

	//ダッシュ判定
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "IsRun")
	bool IsRun = false;


	//ダッシュ関数
	UFUNCTION()
	void Run();

	//ダッシュを止める関数
	UFUNCTION()
	void StopRun();


	//アイテムを追加する関数(BPへ連携する)
	UFUNCTION(BlueprintImplementableEvent, 
		Category = "ItemActorData")
	void AddItemToInventoryWidget(
		FItemActorStructs ItemActorData);

	//ゴール用アイテムを取得した数を数える関数(BPへ連携する)
	UFUNCTION(BlueprintImplementableEvent,
		Category = "GoalItemActorData")
	void AddGoalItemCount(
		FGoalItemActorStructs GoalItemActorData);


	//インベントリ内のアイテムを更新する関数(BPへ連携する)
	UFUNCTION(BlueprintImplementableEvent,
		Category = "UpdateToInventoryWidget")
	void UpdateToInventoryWidget(
		const TArray<FItemActorStructs>& NewInventoryItems);

	//ゴール用アイテムを更新する関数(BPへ連携する)
	UFUNCTION(BlueprintImplementableEvent,
		Category = "UpdateToGoalItem")
	void UpdateToGoalItem(
		const TArray<FGoalItemActorStructs>& NewGoalItems);


	//アイテムが新規で追加された場合の処理
	void AddInventoryItem(FItemActorStructs ItemActorData);

	//ゴール用アイテムが新規で追加された場合の処理
	void AddGoalItem(FGoalItemActorStructs GoalItemActorData);

	//アイテムリスト
	UPROPERTY(
		BlueprintReadWrite, Category = "InventoryItems")
	TArray<FItemActorStructs> InventoryItems;

	//ゴール用アイテム
	UPROPERTY(
		BlueprintReadWrite, Category = "GoalItems")
	TArray<FGoalItemActorStructs> GoalItems;

	//アイテムをインベントリ内に追加する関数
	void OnRep_InventoryItems();

	//ゴール用アイテムを追加する関数
	void OnRep_GoalItems();

	//インベントリから生成用アイテムを使用時、アイテムを生成する
	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	void SpawnItemActors();

	//生成したいアイテムのBP
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> actorBPToSpawns;

	// 生成したアクターを参照する
	AActor* SpawnedActor;

	//生成したアイテムの残存時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "DelaydTime")
	float DelaydTime = 10.0f;

	//生成アイテムがステージ上に存在するのかを判定する
	bool IsSpawnItem = true;

	//鍵の保持状態
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "Player")
	bool IsHoldKey = false;

	//HP
	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "HP")
	float HP = 1;

	//ゲームオーバーに関する関数
	void GameOverPlayer();

	//生成したアイテムを削除する関数
	void  DestructionItemActor();
	
	//歩行用のオーディオコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveAudioComponent")
	UAudioComponent* MoveAudioComponent;

	//歩行速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveAudioComponentSpeed",
		meta = (AllowPrivateAccess = "true"))
	float MoveAudioComponentSpeed = 1.0f;


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//カメラコンポーネント
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	//メッシュ
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* PlayerMesh;


	UFUNCTION(BlueprintCallable, Category = "Player")
	void OnPlayerComponentHit(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpuls,
		const FHitResult& SweepResult);

	//ドア開閉・アイテム拾う時の関数
	void Interact();


	//ドア開閉・アイテム拾う操作
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Interact;

	//ダッシュ操作
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Run;

	//ダッシュを止める操作
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_StopRun;

	//アイテムインベントリを開く操作
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_ItemInventory;

	//アイテムインベントリを開く場合の処理
	void OpenItemInventory();


	//アイテムインベントリを表示(BPへ連携する)
	UFUNCTION(BlueprintImplementableEvent,
		Category = "BPOpenItemInventory")
	void BPOpenItemInventory();

	//アイテムインベントリを強制的に閉じる(BPへ連携する)
	UFUNCTION(BlueprintImplementableEvent,
		Category = "BPCompulsionCloseItemInventory")
	void BPCompulsionCloseItemInventory();

	//アイテムインベントリを閉じる(BPから連携される)
	UFUNCTION(BlueprintCallable,
		Category = "BPCloseItemInventory")
	void BPCloseItemInventory();

	//アイテムインベントリを閉じる場合の処理
	void CloseItemInventory();

	//アイテムインベントリを開いているかを判定する
	bool IsOpenItemInventory;


	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* DefaultMappingContext;


	//インベントリ内のアイテムを使用した場合の処理(BPから連携される)
	UFUNCTION(BlueprintCallable,
		Category = "ItemSubclass")
	void UseItem(TSubclassOf<AItemActor> ItemSubclass);


private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimulusSorce();


	// Input設定
	void SetupInput();

	//歩行SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* MoveSE;

	//生成時SE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UseSpawnItemSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* UseSpawnItemSE;

	//アイテムを拾う時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUpItemSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* PickUpItemSE;

	//歩行SEを鳴らす処理
	void OnMoveSE();

};
