
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

	//アイテムを拾った場合の処理
	virtual void Interact(class APlayer01* Player) override;


	FGoalItemActorStructs GetItemActorStructs() const
	{
		return GoalItemActorData;
	}



protected:
	//メッシュ
	UPROPERTY(EditDefaultsOnly, Category = "GoalItemMesh")
	UStaticMeshComponent* GoalItemMesh;

	//ゴールアイテムデータ
	UPROPERTY(EditDefaultsOnly, Category = "GoalItemActorData")
	FGoalItemActorStructs GoalItemActorData;

	//ゴールアイテムのテクスチャ
	UPROPERTY(EditDefaultsOnly, Category = "GoalItemTexture")
	UTexture2D* GoalItemTexture;

};
