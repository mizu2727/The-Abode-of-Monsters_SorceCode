#include "Actors/DoorActor.h"
#include "Horror07/Enemy01.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 



ADoorActor::ADoorActor()
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


    DoorMesh->
        OnComponentHit.AddDynamic(
            this, &ADoorActor::OnDoorComponentHit);
}


//�h�A���J��
void ADoorActor::OpenDoor()
{
    if (!IsOpenDoor)
    {
        // �h�A����]���ĊJ������
        FRotator NewRotation = 
            FRotator(0.0f, OpenDirenctionValue, 0.0f);
        DoorMesh->SetRelativeRotation(NewRotation);

        UGameplayStatics::PlaySound2D(GetWorld(), OpenDoorSE);

        IsOpenDoor = true;
    }
}

//�G���h�A���J��
void ADoorActor::OpenEnemyDoor(AEnemy01* enemy)
{
    if (enemy)
    {
        OpenDoor();
    }
}

//�h�A�����
void ADoorActor::CloseDoor()
{
    if (IsOpenDoor)
    {
        // �h�A����]���ĕ��鏈��
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

    //�G���h�A�ɐG�ꂽ�ꍇ�̏���
    if (OtherActor)
    {
        AEnemy01* Enemy = Cast<AEnemy01>(OtherActor);
        if (Enemy && !IsNeedKeyDoor && !IsOpenDoor)
        {
            OpenDoor();
        }
    }
}

