

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Horror07GameMode.generated.h"

UCLASS(minimalapi)
class AHorror07GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHorror07GameMode();

	virtual void BeginPlay() override;	

private:


};



