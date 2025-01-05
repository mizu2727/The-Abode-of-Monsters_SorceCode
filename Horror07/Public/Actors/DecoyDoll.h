
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructs.h"
#include "Actors/ItemActor.h"
#include "DecoyDoll.generated.h"


UCLASS()
class HORROR07_API ADecoyDoll : public AItemActor
{
	GENERATED_BODY()
	
public:
	ADecoyDoll();

	FItemActorStructs GetItemActorStructs() const
	{
		return ItemActorData;
	}

	//�A�C�e���g�p���̏���
	virtual void Use(APlayer01* Player) override;
};
