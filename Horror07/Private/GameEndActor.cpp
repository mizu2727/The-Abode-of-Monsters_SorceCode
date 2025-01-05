#include "GameEndActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Horror07/Player01.h"


AGameEndActor::AGameEndActor()
{
	PrimaryActorTick.bCanEverTick = true;

    //�R���|�[�l���g
    BoxComponent =
        CreateDefaultSubobject<UBoxComponent>
        (TEXT("BoxComponent"));

    //�R���|�[�l���g�̃T�C�Y��ݒ�
    BoxComponent->
        SetWorldScale3D(
            FVector(BoxSizeX, BoxSizeY, BoxSizeZ));

    BoxComponent->
        SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->
        SetCollisionResponseToAllChannels(ECR_Block);

    BoxComponent->
        OnComponentHit.AddDynamic(
            this, &AGameEndActor::OnGameEndActorActorComponentHit);
}

void AGameEndActor::OnGameEndActorActorComponentHit(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpuls, 
	const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        APlayer01* Player = Cast<APlayer01>(OtherActor);

        //�v���C���[���G�ꂽ�ꍇ�A�Q�[�����I������
        if (Player)
        {
            UKismetSystemLibrary::QuitGame(this,
                GetWorld()->GetFirstPlayerController(),
                EQuitPreference::Quit, true);
        }
    }
}

