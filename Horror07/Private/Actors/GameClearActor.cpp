#include "Actors/GameClearActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Horror07/Player01.h"



AGameClearActor::AGameClearActor()
{
 	PrimaryActorTick.bCanEverTick = true;

    //�R���|�[�l���g��ݒ�
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
            this, &AGameClearActor::OnGameClearActorComponentHit);
}

void AGameClearActor::OnGameClearActorComponentHit(
    UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, FVector NormalImpuls, 
    const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        APlayer01* Player = Cast<APlayer01>(OtherActor);

        //�v���C���[���G�ꂽ�ꍇ�̏���
        if (Player) 
        {
            GameClearLevel();
        }
    }
}

//GameClearLevel�ֈړ����鏈��
void AGameClearActor::GameClearLevel()
{
    UGameplayStatics::OpenLevel(
        this, FName(TEXT("GameClearLevel")));
}

