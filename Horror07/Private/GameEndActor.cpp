#include "GameEndActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Horror07/Player01.h"


AGameEndActor::AGameEndActor()
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

        //プレイヤーが触れた場合、ゲームを終了する
        if (Player)
        {
            UKismetSystemLibrary::QuitGame(this,
                GetWorld()->GetFirstPlayerController(),
                EQuitPreference::Quit, true);
        }
    }
}

