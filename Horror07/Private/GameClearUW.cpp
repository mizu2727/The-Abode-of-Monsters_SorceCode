#include "GameClearUW.h"
#include <Components/Button.h>
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h" 


void UGameClearUW::SetImage(UTexture2D* NewTexture)
{
	if (GameClearImage && NewTexture)
	{
		// 画像を設定
		GameClearImage->SetBrushFromTexture(NewTexture);
	}
}


void UGameClearUW::NativeConstruct()
{
	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(
			this, &UGameClearUW::OnClickedReturnButton);
	}

	if (GameEndButton)
	{
		GameEndButton->OnClicked.AddDynamic(
			this, &UGameClearUW::OnClickedGameEndButton);
	}
}

//ゲームを最初からやり直すボタン押下時の処理
void UGameClearUW::OnClickedReturnButton()
{
	UGameplayStatics::OpenLevel(
		this, FName(TEXT("FirstFloor01")));

	//マウスカーソルを非表示
	TObjectPtr<APlayerController> PlayerController =
		UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetShowMouseCursor(false);
	FSlateApplication::Get().OnCursorSet();
}

//ゲームを終了するボタン押下時の処理
void UGameClearUW::OnClickedGameEndButton()
{
	UKismetSystemLibrary::QuitGame(this,
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}
