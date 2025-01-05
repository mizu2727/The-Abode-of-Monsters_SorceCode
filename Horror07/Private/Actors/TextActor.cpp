#include "Actors/TextActor.h"
#include "Components/TextRenderComponent.h"


ATextActor::ATextActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//�R���|�[�l���g��ݒ�
	TextRenderComponent = 
		CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));

	RootComponent = TextRenderComponent;

	//�e�L�X�g���e��ݒ�
	TextRenderComponent->SetText(FText::FromString(DisplayText));

	//�e�L�X�g�̐F��ݒ�
	TextRenderComponent->SetTextRenderColor(FColor::White); 

	//�e�L�X�g�̃T�C�Y��ݒ�
	TextRenderComponent->SetWorldSize(TextSize);

	//�e�L�X�g���w��̈ʒu�ɕ\��
	TextRenderComponent->
		SetRelativeLocation(
			FVector(TextLocationX, TextLocationY, TextLocationZ));

}



