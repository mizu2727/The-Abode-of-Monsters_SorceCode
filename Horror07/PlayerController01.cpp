#include "PlayerController01.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Components/InputComponent.h" 
#include "Kismet/GameplayStatics.h" 


APlayerController01::APlayerController01()
    : APlayerController(), m_pAPlayer01(nullptr)
{

}


void APlayerController01::BeginPlay()
{
    Super::BeginPlay();
    APawn* pPawn = GetPawn();
    ensure(pPawn != nullptr);
    m_pAPlayer01 = Cast<APlayer01>(pPawn);
    ensure(m_pAPlayer01 != nullptr);
}

