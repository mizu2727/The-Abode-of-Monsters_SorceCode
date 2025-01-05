
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

	//�A�C�e�����E�����ꍇ�̏���
	virtual void Interact(APlayer01* Player)  = 0;

	//�A�C�e���g�p���̏���
	virtual void Use(APlayer01* Player) {}
};
