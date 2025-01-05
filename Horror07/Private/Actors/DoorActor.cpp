#include "Actors/DoorActor.h"
#include "Horror07/Enemy01.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 



ADoorActor::ADoorActor()
{
 	PrimaryActorTick.bCanEverTick = true;

    //メッシュを設定
    DoorMesh =
        CreateDefaultSubobject<UStaticMeshComponent>
        (TEXT("DoorMesh"));

    DoorMesh->SetVisibility(true);

    DoorMesh->SetupAttachment(RootComponent);

    //メッシュサイズを設定
    DoorMesh->
        SetWorldScale3D(
            FVector(MeshSizeX, MeshSizeY, MeshSizeZ));


    DoorMesh->
        SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DoorMesh->
        SetCollisionResponseToAllChannels(ECR_Block);


    IsOpenDoor = false;


    DoorMesh->
        OnComponentHit.AddDynamic(
            this, &ADoorActor::OnDoorComponentHit);
}


//ドアを開く
void ADoorActor::OpenDoor()
{
    if (!IsOpenDoor)
    {
        // ドアを回転して開く処理
        FRotator NewRotation = 
            FRotator(0.0f, OpenDirenctionValue, 0.0f);
        DoorMesh->SetRelativeRotation(NewRotation);

        UGameplayStatics::PlaySound2D(GetWorld(), OpenDoorSE);

        IsOpenDoor = true;
    }
}

//敵がドアを開く
void ADoorActor::OpenEnemyDoor(AEnemy01* enemy)
{
    if (enemy)
    {
        OpenDoor();
    }
}

//ドアを閉じる
void ADoorActor::CloseDoor()
{
    if (IsOpenDoor)
    {
        // ドアを回転して閉じる処理
        FRotator NewRotation = 
            FRotator(0.0f, CloseDirenctionValue, 0.0f);
        DoorMesh->SetRelativeRotation(NewRotation);

        UGameplayStatics::PlaySound2D(GetWorld(), CloseDoorSE);

        IsOpenDoor = false;
    }
}

void ADoorActor::OnDoorComponentHit(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpuls, const FHitResult& SweepResult)
{

    //敵がドアに触れた場合の処理
    if (OtherActor)
    {
        AEnemy01* Enemy = Cast<AEnemy01>(OtherActor);
        if (Enemy && !IsNeedKeyDoor && !IsOpenDoor)
        {
            OpenDoor();
        }
    }
}

