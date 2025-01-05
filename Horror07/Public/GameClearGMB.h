
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameClearGMB.generated.h"


UCLASS()
class HORROR07_API AGameClearGMB : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "GameClearWidgetClass")
	TSubclassOf<UUserWidget> GameClearWidgetClass;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameClearUW* GameClearUW;

	void BeginPlay() override;

	//ÉQÅ[ÉÄÉNÉäÉAéûSE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameClearSE",
		meta = (AllowPrivateAccess = "true"))
	USoundBase* GameClearSE;
};
