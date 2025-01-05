
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"


UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


class APlayer01;


class HORROR07_API IInteractableInterface
{
	GENERATED_BODY()

	public:

	//アイテムを拾った場合の処理
	virtual void Interact(APlayer01* Player)  = 0;

	//アイテム使用時の処理
	virtual void Use(APlayer01* Player) {}
};
