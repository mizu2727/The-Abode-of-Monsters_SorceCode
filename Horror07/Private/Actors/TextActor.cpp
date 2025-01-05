#include "Actors/TextActor.h"
#include "Components/TextRenderComponent.h"


ATextActor::ATextActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//コンポーネントを設定
	TextRenderComponent = 
		CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));

	RootComponent = TextRenderComponent;

	//テキスト内容を設定
	TextRenderComponent->SetText(FText::FromString(DisplayText));

	//テキストの色を設定
	TextRenderComponent->SetTextRenderColor(FColor::White); 

	//テキストのサイズを設定
	TextRenderComponent->SetWorldSize(TextSize);

	//テキストを指定の位置に表示
	TextRenderComponent->
		SetRelativeLocation(
			FVector(TextLocationX, TextLocationY, TextLocationZ));

}



