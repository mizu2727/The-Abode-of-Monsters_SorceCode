#include "GameOverGMB.h"
#include "GameOverUW.h"
#include <UObject/UObjectGlobals.h>
#include "Kismet/GameplayStatics.h" 
#include "Horror07/Horror07GameMode.h"


void AGameOverGMB::BeginPlay()
{
	//マウスカーソルを表示する
	TObjectPtr<APlayerController> PlayerController =
		UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().OnCursorSet();

	//ゲームオーバー画面のUIを表示
	if (IsValid(GameOverWidgetClass))
	{
		GameOverUW =
			Cast<UGameOverUW>(
				CreateWidget(GetWorld(), GameOverWidgetClass));

		if (GameOverUW != nullptr)
		{
			GameOverUW->AddToViewport();
		}

		if (GameOverSE)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), GameOverSE);
		}
	}
}
