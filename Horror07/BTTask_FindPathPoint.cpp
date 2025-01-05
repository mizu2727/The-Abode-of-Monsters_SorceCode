


#include "BTTask_FindPathPoint.h"
#include "AIController01.h"
#include "Enemy01.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(
	FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	


	//�GAI��Controller���擾
	if (auto* const cont = Cast<AAIController01>(OwnerComp.GetAIOwner()))
	{
		//�r�w�C�r�A�c���[����u���b�N�{�[�h�R���|�[�l���g���擾����
		if (auto* const bc = OwnerComp.GetBlackboardComponent()) 
		{
			//�u���b�N�{�[�h���猻�݂̜p�j�v�f�ԍ����擾����
			auto const index = 
				bc->GetValueAsInt(GetSelectedBlackboardKey());


			//�G���擾
			if (auto* npc = Cast<AEnemy01>(cont-> GetPawn())) 
			{
				//�G���猻�݂̜p�j�ʒu���擾����
				//�v�f�ԍ����瑊�Έʒu���擾
				auto const point = npc->GetPatrolPath()
					->GetPatrolPoint(index);

				//���Έʒu���烏�[���h�ʒu�֕ϊ�
				auto const globalPoint =
					npc->GetPatrolPath()->
					GetActorTransform().TransformPosition(point);
				bc->SetValueAsVector(
					PatrolPathVectorKey.SelectedKeyName, globalPoint);


				// PatrolPath ���������ݒ肳��Ă��邩�m�F(�f�o�b�O�p)
				FString indexAsString = FString::Printf(TEXT("%d"), index);

				if (npc)
				{
					if (npc->GetPatrolPath() == nullptr)
					{
						GEngine->AddOnScreenDebugMessage(
							-1, 5.f, FColor::Red,
							TEXT("Patrol path is not set correctly"));

						UE_LOG(LogTemp, Warning, TEXT("Patrol path is not set correctly"));
					}
					else 
					{

						GEngine->AddOnScreenDebugMessage(
							-1, 5.f, FColor::Red,
							TEXT("Set the Path Point  index:") + indexAsString);

						UE_LOG(LogTemp, Warning,
							TEXT("Set the Path Point  index: %s"), *indexAsString);
					}
				}

				FinishLatentTask(OwnerComp,
					EBTNodeResult::Succeeded);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
