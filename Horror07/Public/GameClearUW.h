
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearUW.generated.h"


UCLASS()
class HORROR07_API UGameClearUW : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 画像を表示するためのUImage変数
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* GameClearImage;

	// 画像を設定する関数
	void SetImage(UTexture2D* NewTexture);

	//テキスト
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* GameClearTextBlock;

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
