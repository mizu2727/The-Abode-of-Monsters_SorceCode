#include "Actors/GoalDoorActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 


AGoalDoorActor::AGoalDoorActor()
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
}


void AGoalDoorActor::OpenDoor()
{
    if (!IsOpenDoor)
    {
        // ドアを開く処理
        FRotator NewRotation = FRotator(0.0f, OpenDirenctionValue, 0.0f);
        DoorMesh->SetRelativeRotation(NewRotation);

        UGameplayStatics::PlaySound2D(GetWorld(), OpenDoorSE);

        IsOpenDoor = true;
    }
}

void AGoalDoorActor::CloseDoor()
{
    if (IsOpenDoor)
    {
        // ドアを閉じる処理
        FRotator NewRotation = FRotator(0.0f, CloseDirenctionValue, 0.0f);
        DoorMesh->SetRelativeRotation(NewRotation);

        UGameplayStatics::PlaySound2D(GetWorld(), CloseDoorSE);

        IsOpenDoor = false;
    }
}

