
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUW.generated.h"


UCLASS()
class HORROR07_API UGameOverUW : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 画像を表示するためのUImage変数
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* GameOverImage;

	// 画像を設定する関数
	void SetImage(UTexture2D* NewTexture);

	//ゲームを最初からやり直すボタン
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;

	//ゲームを終了するボタン
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* GameEndButton;

	void NativeConstruct() override;

	//ゲームを最初からやり直すボタン押下時の処理
	UFUNCTION()
	void OnClickedReturnButton();

	//ゲームを終了するボタン押下時の処理
	UFUNCTION()
	void OnClickedGameEndButton();

};
