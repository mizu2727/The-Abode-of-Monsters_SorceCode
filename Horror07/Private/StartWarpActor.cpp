#include "StartWarpActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/AudioComponent.h"
#include "Horror07/Player01.h"


AStartWarpActor::AStartWarpActor()
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
            this, &AStartWarpActor::OnStartWarpActorComponentHit);


    //�X�e�[�W��BGM�̃I�[�f�B�I�R���|�[�l���g��ݒ�
    StageBGMAudioComponent =
        CreateDefaultSubobject<UAudioComponent>(TEXT("StageBGMAudioComponent"));
}

void AStartWarpActor::OnStartWarpActorComponentHit(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpuls, 
	const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        APlayer01* Player = Cast<APlayer01>(OtherActor);

        //�v���C���[���w��̈ʒu�Ƀ��[�v���鏈��
        if (Player)
        {
            Player->SetActorLocation(FVector(
                TargetLocationX, TargetLocationY, TargetLocationZ));

            if (StageBGM)
            {
                StageBGMAudioComponent->SetSound(StageBGM);

                //���ʒ���
                StageBGMAudioComponent->SetVolumeMultiplier(BGMVolume);

                StageBGMAudioComponent->Play();

                //BGM�����[�v������
                StageBGM->IsLooping();
            }
        }
    }
}




