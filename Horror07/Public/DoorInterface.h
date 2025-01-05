
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
		//ドアを開く
		UFUNCTION()
		virtual void OpenDoor() {};

		//敵がドアを開く
		UFUNCTION()
		virtual void OpenEnemyDoor(AEnemy01* enemy) {};


		//ドアを閉じる
		UFUNCTION()
		virtual void CloseDoor() {};

};
