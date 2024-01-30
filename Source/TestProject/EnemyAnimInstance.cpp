// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackRef(TEXT("/Script/Engine.AnimMontage'/Game/ParagonYin/Characters/Heroes/Yin/Animations/E_Ability_Attack_A_Montage.E_Ability_Attack_A_Montage'"));
	if (AttackRef.Object)
	{
		AttackMontage = AttackRef.Object;
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		bShouldMove = Speed > 3.f;
	}
}
