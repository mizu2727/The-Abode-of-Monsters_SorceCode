
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearUW.generated.h"


UCLASS()
class HORROR07_API UGameClearUW : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// �摜��\�����邽�߂�UImage�ϐ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* GameClearImage;

	// �摜��ݒ肷��֐�
	void SetImage(UTexture2D* NewTexture);

	//�e�L�X�g
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* GameClearTextBlock;

	//�Q�[�����ŏ������蒼���{�^��
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;

	//�Q�[�����I������{�^��
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* GameEndButton;

	void NativeConstruct() override;

	//�Q�[�����ŏ������蒼���{�^���������̏���
	UFUNCTION()
	void OnClickedReturnButton();

	//�Q�[�����I������{�^���������̏���
	UFUNCTION()
	void OnClickedGameEndButton();
};
