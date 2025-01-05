#include "GameOverUW.h"
#include <Components/Button.h>
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h" 


void UGameOverUW::SetImage(UTexture2D* NewTexture)
{
	if (GameOverImage && NewTexture)
	{
		// �摜��ݒ�
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


//�Q�[�����ŏ������蒼���{�^���������̏���
void UGameOverUW::OnClickedReturnButton()
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
void UGameOverUW::OnClickedGameEndButton()
{
	UKismetSystemLibrary::QuitGame(this,
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);


}
