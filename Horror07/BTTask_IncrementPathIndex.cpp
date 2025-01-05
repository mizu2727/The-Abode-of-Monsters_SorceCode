

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
	//敵AIのControllerを取得
	if (auto* const cont = 
		Cast<AAIController01>(OwnerComp.GetAIOwner())) 
	{
		//敵を取得
		if (auto* const npc = Cast<AEnemy01>(cont->GetPawn())) 
		{
			//ブラックボードを取得
			if (auto* const bc = OwnerComp.GetBlackboardComponent()) 
			{
				
				//徘徊場所の要素数をすべて取得
				auto const noOfPoints = npc->GetPatrolPath()->Num();

				//要素数の最低値
				auto const minIndex = 0;

				//要素数の最高値
				auto const maxIndex = noOfPoints - 1;

				//現在の要素番号
				auto index = 
					bc->GetValueAsInt(GetSelectedBlackboardKey());

				
				if (bBiDirectional) 
				{
					//要素番号が最初または最後の場合、徘徊順番を変更する
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

				//要素番号の新しい値をブラックボードに書き込む
				bc->SetValueAsInt(
					GetSelectedBlackboardKey(), 
					(Direction == EDirectionType::Forward ? ++index : --index) 
					% noOfPoints);


				//デバッグ用
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
