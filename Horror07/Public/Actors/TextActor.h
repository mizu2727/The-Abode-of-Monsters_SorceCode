
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

	//�R���|�[�l���g
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderComponent;

	//�\���������e�L�X�g�̓��e
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "DisplayText")
	FString DisplayText;

	//�e�L�X�g�̃T�C�Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "TextSize")
	float TextSize = 100.0f;


	//�\���������e�L�X�g�̈ʒu
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
