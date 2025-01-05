#include "GameOverGMB.h"
#include "GameOverUW.h"
#include <UObject/UObjectGlobals.h>
#include "Kismet/GameplayStatics.h" 
#include "Horror07/Horror07GameMode.h"


void AGameOverGMB::BeginPlay()
{
	//�}�E�X�J�[�\����\������
	TObjectPtr<APlayerController> PlayerController =
		UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().OnCursorSet();

	//�Q�[���I�[�o�[��ʂ�UI��\��
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
