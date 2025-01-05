
#include "Horror07/Public/Actors/ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Horror07/Player01.h"



AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	//���b�V���̐ݒ�
	ItemMesh =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("StaticMeshComponent"));

	RootComponent = ItemMesh;

	ItemActorData.ItemClass = StaticClass();
}

//�A�C�e�����E�����ꍇ�̏���
void AItemActor::Interact(class APlayer01* Player)
{
	if (Player)
	{
		Player->AddInventoryItem(ItemActorData);
	}

	Destroy();
}

//�A�C�e���g�p���̏���
void AItemActor::Use(APlayer01* Player)
{
	
	//�f�o�b�O�p
	UE_LOG(LogTemp, Warning, TEXT("Using Item: %s"), *GetName());

	
}



