
#include "Actors/DecoyDoll.h"
#include "Horror07/Player01.h"


ADecoyDoll::ADecoyDoll()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

//�A�C�e���g�p���̏���
void ADecoyDoll::Use(APlayer01* Player)
{
	if (Player)
	{
		Player->SpawnItemActors();
	}
}


