
#include "Horror07/Public/Actors/ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Horror07/Player01.h"



AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	//メッシュの設定
	ItemMesh =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("StaticMeshComponent"));

	RootComponent = ItemMesh;

	ItemActorData.ItemClass = StaticClass();
}

//アイテムを拾った場合の処理
void AItemActor::Interact(class APlayer01* Player)
{
	if (Player)
	{
		Player->AddInventoryItem(ItemActorData);
	}

	Destroy();
}

//アイテム使用時の処理
void AItemActor::Use(APlayer01* Player)
{
	
	//デバッグ用
	UE_LOG(LogTemp, Warning, TEXT("Using Item: %s"), *GetName());

	
}



