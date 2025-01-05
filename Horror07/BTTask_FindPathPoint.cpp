


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
	


	//敵AIのControllerを取得
	if (auto* const cont = Cast<AAIController01>(OwnerComp.GetAIOwner()))
	{
		//ビヘイビアツリーからブラックボードコンポーネントを取得する
		if (auto* const bc = OwnerComp.GetBlackboardComponent()) 
		{
			//ブラックボードから現在の徘徊要素番号を取得する
			auto const index = 
				bc->GetValueAsInt(GetSelectedBlackboardKey());


			//敵を取得
			if (auto* npc = Cast<AEnemy01>(cont-> GetPawn())) 
			{
				//敵から現在の徘徊位置を取得する
				//要素番号から相対位置を取得
				auto const point = npc->GetPatrolPath()
					->GetPatrolPoint(index);

				//相対位置からワールド位置へ変換
				auto const globalPoint =
					npc->GetPatrolPath()->
					GetActorTransform().TransformPosition(point);
				bc->SetValueAsVector(
					PatrolPathVectorKey.SelectedKeyName, globalPoint);


				// PatrolPath が正しく設定されているか確認(デバッグ用)
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
