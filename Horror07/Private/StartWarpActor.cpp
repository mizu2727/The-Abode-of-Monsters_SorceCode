#include "StartWarpActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/AudioComponent.h"
#include "Horror07/Player01.h"


AStartWarpActor::AStartWarpActor()
{
	PrimaryActorTick.bCanEverTick = true;

    //コンポーネント
    BoxComponent =
        CreateDefaultSubobject<UBoxComponent>
        (TEXT("BoxComponent"));

    //コンポーネントのサイズを設定
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


    //ステージのBGMのオーディオコンポーネントを設定
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

        //プレイヤーを指定の位置にワープする処理
        if (Player)
        {
            Player->SetActorLocation(FVector(
                TargetLocationX, TargetLocationY, TargetLocationZ));

            if (StageBGM)
            {
                StageBGMAudioComponent->SetSound(StageBGM);

                //音量調整
                StageBGMAudioComponent->SetVolumeMultiplier(BGMVolume);

                StageBGMAudioComponent->Play();

                //BGMをループさせる
                StageBGM->IsLooping();
            }
        }
    }
}




