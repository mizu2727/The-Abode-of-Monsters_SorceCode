#include "GameOverUW.h"
#include <Components/Button.h>
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h" 


void UGameOverUW::SetImage(UTexture2D* NewTexture)
{
	if (GameOverImage && NewTexture)
	{
		// 画像を設定
		GameOverImage->SetBrushFromTexture(NewTexture);
	}

}

void UGameOverUW::NativeConstruct()
{
	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(
			this, &UGameOverUW::OnClickedReturnButton);
	}

	if (GameEndButton)
	{
		GameEndButton->OnClicked.AddDynamic(
			this, &UGameOverUW::OnClickedGameEndButton);
	}
}


//ゲームを最初からやり直すボタン押下時の処理
void UGameOverUW::OnClickedReturnButton()
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
void UGameOverUW::OnClickedGameEndButton()
{
	UKismetSystemLibrary::QuitGame(this,
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);


}
