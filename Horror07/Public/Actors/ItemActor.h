
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

	//アイテムを拾った場合の処理
	virtual void Interact(class APlayer01* Player) override;


	FItemActorStructs GetItemActorStructs() const
	{
		return ItemActorData;
	}

	//アイテム使用時の処理
	virtual void Use(APlayer01* Player) override;

protected:
	//メッシュ
	UPROPERTY(EditDefaultsOnly, Category = "ItemMesh")
	UStaticMeshComponent* ItemMesh;


	//アイテムデータ
	UPROPERTY(EditDefaultsOnly, Category = "ItemActorData")
	FItemActorStructs ItemActorData;

	

};
