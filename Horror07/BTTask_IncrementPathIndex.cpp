

#include "BTTask_IncrementPathIndex.h"
#include "AIController01.h"
#include "Enemy01.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(
	FObjectInitializer const& ObjectInitializer):
	UBTTask_BlackboardBase{ ObjectInitializer }
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�GAI��Controller���擾
	if (auto* const cont = 
		Cast<AAIController01>(OwnerComp.GetAIOwner())) 
	{
		//�G���擾
		if (auto* const npc = Cast<AEnemy01>(cont->GetPawn())) 
		{
			//�u���b�N�{�[�h���擾
			if (auto* const bc = OwnerComp.GetBlackboardComponent()) 
			{
				
				//�p�j�ꏊ�̗v�f�������ׂĎ擾
				auto const noOfPoints = npc->GetPatrolPath()->Num();

				//�v�f���̍Œ�l
				auto const minIndex = 0;

				//�v�f���̍ō��l
				auto const maxIndex = noOfPoints - 1;

				//���݂̗v�f�ԍ�
				auto index = 
					bc->GetValueAsInt(GetSelectedBlackboardKey());

				
				if (bBiDirectional) 
				{
					//�v�f�ԍ����ŏ��܂��͍Ō�̏ꍇ�A�p�j���Ԃ�ύX����
					if (index >= maxIndex && 
						Direction == EDirectionType::Forward) 
					{
						Direction = EDirectionType::Reverse;
					}
					else if (index == minIndex &&
						Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}

				//�v�f�ԍ��̐V�����l���u���b�N�{�[�h�ɏ�������
				bc->SetValueAsInt(
					GetSelectedBlackboardKey(), 
					(Direction == EDirectionType::Forward ? ++index : --index) 
					% noOfPoints);


				//�f�o�b�O�p
				FString indexAsString = FString::Printf(TEXT("%d"), index);

				GEngine->AddOnScreenDebugMessage(
					-1, 5.f, FColor::Red,
					TEXT("Set the Icrement  index:") + indexAsString);

				UE_LOG(LogTemp, Warning,
					TEXT("Set the Icrement  index: %s"), *indexAsString);


				FinishLatentTask(OwnerComp,
					EBTNodeResult::Succeeded);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
