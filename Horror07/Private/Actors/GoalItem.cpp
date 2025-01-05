#include "Horror07/Public/Actors/GoalItem.h"
#include "Components/StaticMeshComponent.h"
#include "Horror07/Player01.h"


AGoalItem::AGoalItem()
{
	PrimaryActorTick.bCanEverTick = false;

	//メッシュの設定
	GoalItemMesh =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("StaticMeshComponent"));

	RootComponent = GoalItemMesh;

	GoalItemActorData.GoalItemClass = StaticClass();
}

//アイテムを拾った場合の処理
void AGoalItem::Interact(APlayer01* Player)
{
	if (Player)
	{
		Player->AddGoalItem(GoalItemActorData);		
	}

	Destroy();
}



