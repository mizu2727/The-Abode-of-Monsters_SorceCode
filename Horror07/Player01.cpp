
#include "Player01.h"
#include "Horror07/Public/Actors/ItemActor.h"
#include "Horror07/Public/Actors/GoalItem.h"
#include "Actors/DecoyDoll.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Enemy01.h"
#include "Actors/DoorActor.h"
#include "Actors/GoalDoorActor.h"
#include <UObject/UObjectGlobals.h>
#include "Kismet/KismetSystemLibrary.h" 
#include "Kismet/GameplayStatics.h" 
#include "Perception/AISense_Hearing.h"
#include "ai_tags.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Components/InputComponent.h" 
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"




APlayer01::APlayer01()
{
	PrimaryActorTick.bCanEverTick = true;

	//カメラコンポーネントを作成
	CameraComponent =
		CreateDefaultSubobject<UCameraComponent>(
			TEXT("PlayerCamera"));
	check(CameraComponent != nullptr);

	//カメラコンポーネントをカプセルコンポーネントにアタッチ
	CameraComponent->
		SetupAttachment(
			CastChecked<USceneComponent, UCapsuleComponent>(
				GetCapsuleComponent()));

	//カメラを設置(目の高さより少し上に置く)
	CameraComponent->
		SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	//ポーンを有効にしてカメラの回転を制御する
	CameraComponent->bUsePawnControlRotation = true;


	//プレイヤーのメッシュコンポーネントを作成
	PlayerMesh =
		CreateDefaultSubobject<USkeletalMeshComponent>(
			TEXT("PlayerMesh"));
	check(PlayerMesh != nullptr);


	PlayerMesh->SetOnlyOwnerSee(true);


	PlayerMesh->SetupAttachment(CameraComponent);

	
	PlayerMesh->bCastDynamicShadow = false;
	PlayerMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

	SetupStimulusSorce();


	// Input Actionを読込
	IA_Interact =
		LoadObject<UInputAction>(
			NULL, TEXT("IA_Interact"), NULL, LOAD_None, NULL);

	IA_StopRun =
		LoadObject<UInputAction>(
			NULL, TEXT("IA_StopRun"), NULL, LOAD_None, NULL);

	IA_ItemInventory =
		LoadObject<UInputAction>(
			NULL, TEXT("IA_ItemInventory"), NULL, LOAD_None, NULL);


	// Input Mapping Contextを読込
	DefaultMappingContext =
		LoadObject<UInputMappingContext>(
			NULL, TEXT("IMC_Interact"), NULL, LOAD_None, NULL);

	MoveAudioComponent =
		CreateDefaultSubobject<UAudioComponent>(TEXT("MoveAudioComponent"));

	// 最初は自動で再生しない
	MoveAudioComponent->bAutoActivate = false;

	SpawnedActor = nullptr;
}

void APlayer01::BeginPlay()
{
	Super::BeginPlay();

	APlayer01::SetupInput();

	CloseItemInventory();
}

void APlayer01::Interact()
{
	//IA_Interactの操作が反映される範囲を設定
	FVector startVector = CameraComponent->GetComponentLocation();
	FVector endVector = startVector + CameraComponent->GetForwardVector() * 500.f;
	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);


	//十字の範囲内でIA_Interactの操作をした場合の処理
	if (GetWorld()->
		LineTraceSingleByChannel(
			hitResult, startVector, endVector, ECC_Visibility, params)) 
	{
		//アイテムを拾う
		if (IInteractableInterface* interface = 
			Cast<IInteractableInterface>(hitResult.GetActor()))
		{	
			interface->Interact(this);
			UGameplayStatics::PlaySound2D(GetWorld(), PickUpItemSE);
		}


		//ゴール用ドアの開閉
		if (AGoalDoorActor* GoalDoor = Cast<AGoalDoorActor>(hitResult.GetActor()))
		{
			if (GoalDoor->IsOpenDoor)
			{
				GoalDoor->CloseDoor();
			}
			else
			{

				for (FGoalItemActorStructs& Item : GoalItems)
				{

					//ゴール用アイテムを5つ集めた状態の場合の処理
					if ((Item.ItemStackCount >= 5)
						&& (GoalDoor->IsNeedKeyDoor))
					{
						UGameplayStatics::PlaySound2D(GetWorld(), GoalDoor->UnLockDoorSE);
						
						GoalDoor->IsNeedKeyDoor = false;

						break;
					}
					else if (!GoalDoor->IsNeedKeyDoor)
					{
						GoalDoor->OpenDoor();
						break;
					}
					else
					{

						break;
					}
				}
			}
		}

		//ドアの開閉
		if (ADoorActor* Door = Cast<ADoorActor>(hitResult.GetActor()))
		{

			if (Door->IsOpenDoor)
			{
				Door->CloseDoor();
			}
			else
			{
				//鍵がかかっているかを判定
				if (Door->IsNeedKeyDoor && IsHoldKey)
				{

					IsHoldKey = false;
					Door->IsNeedKeyDoor = false;
				}
				else if (!Door->IsNeedKeyDoor)
				{
					Door->OpenDoor();
				}
				else
				{

				}
			}
		}
	}
}

//アイテムインベントリを開く場合の処理
void APlayer01::OpenItemInventory()
{

	if (!IsOpenItemInventory)
	{
		RunSpeed = 0.0f;

		BPOpenItemInventory();

		IsOpenItemInventory = true;
	}
}

//アイテムインベントリを閉じる(BPから連携される)
void APlayer01::BPCloseItemInventory()
{
	CloseItemInventory();
}

//アイテムインベントリを閉じる場合の処理
void APlayer01::CloseItemInventory()
{
	if (IsOpenItemInventory)
	{
		RunSpeed = 1.0f;

		IsOpenItemInventory = false;
	}
}



void APlayer01::Tick(float DeltaTime)
{
	OnMoveSE();
}

void APlayer01::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis(
		"MoveForward", this, &APlayer01::MoveForward);

	PlayerInputComponent->BindAxis(
		"MoveRight", this, &APlayer01::MoveRight);


	//マウスでの視界操作
	PlayerInputComponent->
		BindAxis("Turn", this, &APlayer01::AddControllerYawInput);
	PlayerInputComponent->
		BindAxis("LookUp", this, &APlayer01::AddControllerPitchInput);	
}

//前後操作
void APlayer01::MoveForward(float moveForward)
{
	FVector Direction 
		= FRotationMatrix(
			Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, moveForward * RunSpeed);
}

//左右操作
void APlayer01::MoveRight(float moveRight)
{
	FVector Direction 
		= FRotationMatrix(
			Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, moveRight * RunSpeed);
}

//ダッシュ
void APlayer01::Run()
{
	IsRun = true;
	RunSpeed = 5.0f;
}

//ダッシュを止める関数
void APlayer01::StopRun()
{
	IsRun = false;
	RunSpeed = 1.0f;
}

//歩行SEを鳴らす処理
void APlayer01::OnMoveSE()
{
	if (GetCharacterMovement()->Velocity.Size() > 0.0f &&
		!MoveAudioComponent->IsPlaying())
	{

		MoveAudioComponent->SetSound(MoveSE);

		// 再生速度を変更 (ピッチを変更することで再生速度が変わる)
		MoveAudioComponent->SetPitchMultiplier(MoveAudioComponentSpeed);

		MoveAudioComponent->Play();
	}
	else if (GetCharacterMovement()->Velocity.Size() == 0.0f
		&& MoveAudioComponent->IsPlaying() )
	{
		// 止まったら音を停止
		MoveAudioComponent->Stop();
	}
}

void APlayer01::OnPlayerComponentHit(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpuls, const FHitResult& SweepResult)
{
	//デバッグ用
	GEngine->AddOnScreenDebugMessage(
		-1, 5.f, FColor::Red,
		TEXT("OnPlayerComponentHit"));
}

//インベントリ内のアイテムを使用した場合の処理(BPから連携される)
void APlayer01::UseItem(TSubclassOf<AItemActor> ItemSubclass)
{
	if (IsSpawnItem)
	{
		if (ItemSubclass)
		{
			AItemActor* MassegeItem = ItemSubclass.GetDefaultObject();

			//特定のアイテムcppファイル内のUse関数を処理する
			if (MassegeItem)
			{
				MassegeItem->Use(this);
			}

			for (FItemActorStructs& Item : InventoryItems)
			{

				if (Item.ItemClass == ItemSubclass)
				{
					//アイテム所持数を-1
					--Item.ItemStackCount;

					UpdateToInventoryWidget(InventoryItems);

					break;
				}
			}
		}
	}
	else 
	{
		//デバッグ用
		GEngine->AddOnScreenDebugMessage(
			-1, 5.f, FColor::Blue,FString::Printf(TEXT("生成アイテムの数が上限に達したため、生成不可")));
	}

	
}

//アイテムが新規で追加された場合の処理
void APlayer01::AddInventoryItem(FItemActorStructs ItemData)
{
	
	bool bIsNewItem = true;
	for (FItemActorStructs& Item : InventoryItems)
	{

		//インベントリのアイテムとクラスのアイテムが一致するかを判定
		if (Item.ItemClass == ItemData.ItemClass)
		{
			++Item.ItemStackCount;
			bIsNewItem = false;
			break;
		}
	}

	//新しいアイテムであるかを判定する
	if (bIsNewItem)
	{
		InventoryItems.Add(ItemData);

		OnRep_InventoryItems();
	}
	else
	{
		UpdateToInventoryWidget(InventoryItems);
	}
}

//ゴール用アイテムが新規で追加された場合の処理
void APlayer01::AddGoalItem(FGoalItemActorStructs GoalItemActorData)
{

	bool bIsNewGoalItem = true;
	for (FGoalItemActorStructs& GoalItem : GoalItems)
	{

		//クラスのアイテムと一致するかを判定
		if (GoalItem.GoalItemClass == GoalItemActorData.GoalItemClass)
		{
			++GoalItem.ItemStackCount;

			bIsNewGoalItem = false;
			break;
		}
	}

	//新しいアイテムであるかを判定する
	if (bIsNewGoalItem)
	{
		GoalItems.Add(GoalItemActorData);

		OnRep_GoalItems();
	}
	else
	{
		UpdateToGoalItem(GoalItems);
	}
}


//アイテムをインベントリ内に追加する関数
void APlayer01::OnRep_InventoryItems()
{
	if (InventoryItems.Num())
	{
		AddItemToInventoryWidget(
			InventoryItems[InventoryItems.Num() - 1]);
	}
}

//ゴール用アイテムを追加する関数
void APlayer01::OnRep_GoalItems()
{
	if (GoalItems.Num())
	{
		AddGoalItemCount(
			GoalItems[GoalItems.Num() - 1]);
	}
}

//アイテム生成
void APlayer01::SpawnItemActors()
{
	//アイテムを生成
	IsSpawnItem = false;

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	SpawnedActor = GetWorld()->SpawnActor<AActor>(
		actorBPToSpawns, GetActorTransform(), spawnParams);

	UGameplayStatics::PlaySound2D(GetWorld(), UseSpawnItemSE);



	//デバッグ用
	FString ActorClassName =
		actorBPToSpawns ? actorBPToSpawns->GetClass()->GetName() : TEXT("Null Actor");

	UE_LOG(LogTemp, Warning,
		TEXT("Actor is of class: %s"), *ActorClassName);

	GEngine->AddOnScreenDebugMessage(
		-1, 5.f, FColor::Blue,
		FString::Printf(TEXT("Actor is of class: %s"), *ActorClassName));

		

	//生成したアイテムを削除する処理を遅延する
	FTimerHandle handle;
	
	GetWorldTimerManager().SetTimer(
		handle, this, &APlayer01::DestructionItemActor, DelaydTime, false);
}

//生成したアイテムを削除する処理
void APlayer01::DestructionItemActor()
{
	if (SpawnedActor)
	{
		// 生成したアクターを削除
		SpawnedActor->Destroy();

		// 参照を解除
		SpawnedActor = nullptr;  

		IsSpawnItem = true;
	}
}

//ゲームオーバーに関する関数
void APlayer01::GameOverPlayer()
{
	BPCompulsionCloseItemInventory();

	UGameplayStatics::OpenLevel(
		this, FName(TEXT("GameOverLevel")));
}



void APlayer01::SetupStimulusSorce()
{
	StimulusSource = 
		CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(
			TEXT("Stimulus"));

	if (StimulusSource)
	{
		StimulusSource->
			RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void APlayer01::SetupInput()
{
	// PlayerControllerを取得する
	APlayerController* controller
		= UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 入力を有効にする
	EnableInput(controller);

	if (InputComponent)
	{
		

		if (UEnhancedInputComponent* EIC
			= CastChecked<UEnhancedInputComponent>(InputComponent)) {

			EIC->
				BindAction(
					IA_Interact, ETriggerEvent::Triggered, this,
					&APlayer01::Interact);

			EIC->
				BindAction(
					IA_Run, ETriggerEvent::Triggered, this,
					&APlayer01::Run);

			EIC->
				BindAction(
					IA_StopRun, ETriggerEvent::Triggered, this,
					&APlayer01::StopRun);

			EIC->
				BindAction(
					IA_ItemInventory, ETriggerEvent::Triggered, this,
					&APlayer01::OpenItemInventory);
		}

		// Input Mapping Contextを登録する
		if (APlayerController* PlayerController =
			Cast<APlayerController>(controller))
		{

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
					PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
				UE_LOG(LogTemp, Warning, TEXT(
					"SetupInput_AddMappingContext"));
			}
		}
	}
}

