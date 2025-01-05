#include "GameClearUW.h"
#include <Components/Button.h>
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h" 


void UGameClearUW::SetImage(UTexture2D* NewTexture)
{
	if (GameClearImage && NewTexture)
	{
		// �摜��ݒ�
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

//�Q�[�����ŏ������蒼���{�^���������̏���
void UGameClearUW::OnClickedReturnButton()
{
	UGameplayStatics::OpenLevel(
		this, FName(TEXT("FirstFloor01")));

	//�}�E�X�J�[�\�����\��
	TObjectPtr<APlayerController> PlayerController =
		UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetShowMouseCursor(false);
	FSlateApplication::Get().OnCursorSet();
}

//�Q�[�����I������{�^���������̏���
void UGameClearUW::OnClickedGameEndButton()
{
	UKismetSystemLibrary::QuitGame(this,
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}
