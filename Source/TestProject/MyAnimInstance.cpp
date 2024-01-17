// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		MyCharacter = Cast<AMyCharacter>(Pawn);
		if (IsValid(MyCharacter))
		{
			CharacterMovement = MyCharacter->GetCharacterMovement();
		}
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(MyCharacter))
	{
		FVector Velocity = CharacterMovement->Velocity;
		FRotator Rotation = MyCharacter->GetActorRotation();
		FVector UnRotateVector = Rotation.UnrotateVector(Velocity);

		Vertical = UnRotateVector.X;
		Horizontal = UnRotateVector.Y;
		Speed = MyCharacter->GetVelocity().Size2D();

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		bShouldMove = Speed > 3.f && Acceleration != FVector::Zero();

	}
}
