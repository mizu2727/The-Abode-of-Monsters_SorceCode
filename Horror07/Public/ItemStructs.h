
#pragma once

#include "CoreMinimal.h"
#include "ItemStructs.generated.h"

//�A�C�e���̍\���̂��쐬
USTRUCT(BlueprintType)
struct HORROR07_API FItemActorStructs
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AItemActor> ItemClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* ItemImage;

	UPROPERTY(BlueprintReadWrite)
	int32 ItemStackCount = 1;

	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "ItemName")
	FString ItemName;

	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "ItemExplanation")
	FString ItemExplanation;
};


//�S�[���p�A�C�e���̍\���̂��쐬
USTRUCT(BlueprintType)
struct HORROR07_API FGoalItemActorStructs
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AGoalItem> GoalItemClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* ItemImage;

	UPROPERTY(BlueprintReadWrite)
	int32 ItemStackCount = 1;

	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "ItemName")
	FString ItemName;

	UPROPERTY(
		EditAnywhere, BlueprintReadwrite, Category = "ItemExplanation")
	FString ItemExplanation;
};
