#include "Horror07/Public/Actors/GoalItem.h"
#include "Components/StaticMeshComponent.h"
#include "Horror07/Player01.h"


AGoalItem::AGoalItem()
{
	PrimaryActorTick.bCanEverTick = false;

	//���b�V���̐ݒ�
	GoalItemMesh =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("StaticMeshComponent"));

	RootComponent = GoalItemMesh;

	GoalItemActorData.GoalItemClass = StaticClass();
}

//�A�C�e�����E�����ꍇ�̏���
void AGoalItem::Interact(APlayer01* Player)
{
	if (Player)
	{
		Player->AddGoalItem(GoalItemActorData);		
	}

	Destroy();
}



