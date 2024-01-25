// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

public:
	UEnemyAnimInstance();

public:
	void PlayAttackMontage();

};
