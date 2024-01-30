// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UEnemyAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UEnemyAnimInstance();

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
