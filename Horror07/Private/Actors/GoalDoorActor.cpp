#include "Actors/GoalDoorActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 


AGoalDoorActor::AGoalDoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

    //���b�V����ݒ�
    DoorMesh =
        CreateDefaultSubobject<UStaticMeshComponent>
        (TEXT("DoorMesh"));


    DoorMesh->SetVisibility(true);


    DoorMesh->SetupAttachment(RootComponent);

    //���b�V���T�C�Y��ݒ�
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
        // �h�A���J������
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
        // �h�A����鏈��
        FRotator NewRotation = FRotator(0.0f, CloseDirenctionValue, 0.0f);
        DoorMesh->SetRelativeRotation(NewRotation);

        UGameplayStatics::PlaySound2D(GetWorld(), CloseDoorSE);

        IsOpenDoor = false;
    }
}

