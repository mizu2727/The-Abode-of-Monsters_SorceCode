
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructs.h"
#include "Horror07/Public/InteractableInterface.h"
#include "GoalItem.generated.h"

UCLASS()
class HORROR07_API AGoalItem : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AGoalItem();

	//�A�C�e�����E�����ꍇ�̏���
	virtual void Interact(class APlayer01* Player) override;


	FGoalItemActorStructs GetItemActorStructs() const
	{
		return GoalItemActorData;
	}



protected:
	//���b�V��
	UPROPERTY(EditDefaultsOnly, Category = "GoalItemMesh")
	UStaticMeshComponent* GoalItemMesh;

	//�S�[���A�C�e���f�[�^
	UPROPERTY(EditDefaultsOnly, Category = "GoalItemActorData")
	FGoalItemActorStructs GoalItemActorData;

	//�S�[���A�C�e���̃e�N�X�`��
	UPROPERTY(EditDefaultsOnly, Category = "GoalItemTexture")
	UTexture2D* GoalItemTexture;

};
