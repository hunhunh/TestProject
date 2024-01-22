// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(Category="Animation",EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	float Speed;

	//UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	//float Horizontal;

	//UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	//float Vertical;
	
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 bShouldMove : 1;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 bIsFalling : 1;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector Velocity;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float YawOffset;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FRotator AimRotation;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float RotateYaw;
public:
	UMyAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private: 
	UPROPERTY(VisibleAnywhere)
	class AMyCharacter* MyCharacter;

	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere)
	UAnimMontage* FireMontage;

	//Fire
public:
	void PlayFireMontage();

};
