// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Ref(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_Enemy.BT_Enemy'"));
	if (BT_Ref.Object)
	{
		BehaviorTree = BT_Ref.Object;
		UE_LOG(LogTemp, Log, TEXT("BehaviorTree Succeeded"));
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD_Ref(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_Enemy.BB_Enemy'"));
	if (BD_Ref.Object)
	{
		BlackboardData = BD_Ref.Object;
		UE_LOG(LogTemp, Log, TEXT("BlackboadData Succeded"));
	}
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (RunBehaviorTree(BehaviorTree))
	{
		UE_LOG(LogTemp, Log, TEXT("Run Behavior Tree"));
	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}
