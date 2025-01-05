
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DoorInterface.generated.h"


UINTERFACE(MinimalAPI)
class UDoorInterface : public UInterface
{
	GENERATED_BODY()
};

class APlayer01;
class AEnemy01;

class HORROR07_API IDoorInterface
{
	GENERATED_BODY()

	public:
		//�h�A���J��
		UFUNCTION()
		virtual void OpenDoor() {};

		//�G���h�A���J��
		UFUNCTION()
		virtual void OpenEnemyDoor(AEnemy01* enemy) {};


		//�h�A�����
		UFUNCTION()
		virtual void CloseDoor() {};

};
