#include "Actors/GameClearActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Horror07/Player01.h"



AGameClearActor::AGameClearActor()
{
 	PrimaryActorTick.bCanEverTick = true;

    //コンポーネントを設定
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

        //プレイヤーが触れた場合の処理
        if (Player) 
        {
            GameClearLevel();
        }
    }
}

//GameClearLevelへ移動する処理
void AGameClearActor::GameClearLevel()
{
    UGameplayStatics::OpenLevel(
        this, FName(TEXT("GameClearLevel")));
}

