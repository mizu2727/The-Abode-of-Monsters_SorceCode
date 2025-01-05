#include "GameClearGMB.h"
#include "GameClearUW.h"
#include <UObject/UObjectGlobals.h>
#include "Kismet/GameplayStatics.h" 


void AGameClearGMB::BeginPlay()
{
	//�Q�[���N���A��ʂ�UI��\��
	if (IsValid(GameClearWidgetClass))
	{
		GameClearUW =
			Cast<UGameClearUW>(
				CreateWidget(GetWorld(), GameClearWidgetClass));

		if (GameClearUW != nullptr)
		{
			GameClearUW->AddToViewport();
		}

		if (GameClearSE)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), GameClearSE);
		}

	}

	//�}�E�X�J�[�\����\������
	TObjectPtr<APlayerController> PlayerController =
		UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().OnCursorSet();
}
