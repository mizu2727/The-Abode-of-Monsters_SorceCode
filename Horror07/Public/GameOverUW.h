
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUW.generated.h"


UCLASS()
class HORROR07_API UGameOverUW : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// �摜��\�����邽�߂�UImage�ϐ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* GameOverImage;

	// �摜��ݒ肷��֐�
	void SetImage(UTexture2D* NewTexture);

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
