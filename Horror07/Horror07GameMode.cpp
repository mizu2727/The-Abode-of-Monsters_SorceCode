

#include "Horror07GameMode.h"
#include "Kismet/GameplayStatics.h" 
#include "UObject/ConstructorHelpers.h"

AHorror07GameMode::AHorror07GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AHorror07GameMode::BeginPlay()
{
	//マウスカーソルを非表示
	TObjectPtr<APlayerController> PlayerController =
		UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetShowMouseCursor(false);
	FSlateApplication::Get().OnCursorSet();
}
