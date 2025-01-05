
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructs.h"
#include "Horror07/Public/InteractableInterface.h"
#include "ItemActor.generated.h"

UCLASS()
class HORROR07_API AItemActor : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AItemActor();

	//�A�C�e�����E�����ꍇ�̏���
	virtual void Interact(class APlayer01* Player) override;


	FItemActorStructs GetItemActorStructs() const
	{
		return ItemActorData;
	}

	//�A�C�e���g�p���̏���
	virtual void Use(APlayer01* Player) override;

protected:
	//���b�V��
	UPROPERTY(EditDefaultsOnly, Category = "ItemMesh")
	UStaticMeshComponent* ItemMesh;


	//�A�C�e���f�[�^
	UPROPERTY(EditDefaultsOnly, Category = "ItemActorData")
	FItemActorStructs ItemActorData;

	

};
