
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player01.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Sound/SoundBase.h"
#include "PlayerController01.generated.h"


UCLASS()
class HORROR07_API APlayerController01 : public APlayerController
{
	GENERATED_BODY()
	
public:
    APlayerController01();

protected:
    APlayer01* m_pAPlayer01;

    virtual void BeginPlay() override;

   
};
