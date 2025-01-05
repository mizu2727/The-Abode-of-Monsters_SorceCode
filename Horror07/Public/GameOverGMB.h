
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameOverGMB.generated.h"


UCLASS()
class HORROR07_API AGameOverGMB : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "GameOverWidgetClass")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameOverUW* GameOverUW;

	void BeginPlay() override;

	//ゲームオーバー時のSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameOverSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* GameOverSE;
};
