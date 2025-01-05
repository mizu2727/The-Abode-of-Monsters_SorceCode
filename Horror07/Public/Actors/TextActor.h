
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextActor.generated.h"

class UTextRenderComponent;

UCLASS()
class HORROR07_API ATextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATextActor();

	//コンポーネント
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderComponent;

	//表示したいテキストの内容
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "DisplayText")
	FString DisplayText;

	//テキストのサイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TextSize")
	float TextSize = 100.0f;


	//表示したいテキストの位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TextLocationX")
	float TextLocationX = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TextLocationY")
	float TextLocationY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TextLocationZ")
	float TextLocationZ = 0.0f;

};
