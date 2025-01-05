

#include "BTService_ChangeSpeed.h"
#include "AIController.h"
#include "Enemy01.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Chage Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	//“G‚ÌˆÚ“®‘¬“x‚ğ•ÏX
	if (auto const cont = OwnerComp.GetAIOwner())
	{
		if (auto* const npc = Cast<AEnemy01>(cont->GetPawn())) 
		{
			npc->GetCharacterMovement()->MaxWalkSpeed = speed;
		}
	}
}
