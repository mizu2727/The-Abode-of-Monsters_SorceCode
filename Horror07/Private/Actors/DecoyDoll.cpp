
#include "Actors/DecoyDoll.h"
#include "Horror07/Player01.h"


ADecoyDoll::ADecoyDoll()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

//アイテム使用時の処理
void ADecoyDoll::Use(APlayer01* Player)
{
	if (Player)
	{
		Player->SpawnItemActors();
	}
}


