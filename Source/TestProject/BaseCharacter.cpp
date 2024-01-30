// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "MyActorComponent.h"
#include "BaseAnimInstance.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("ActorComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (BaseAnimInstance)
	{
		BaseAnimInstance->OnMontageEnded.AddDynamic(this, &ABaseCharacter::OnAttackMontageEnded);
		BaseAnimInstance->OnAttackHit.AddUObject(this, &ABaseCharacter::OnHit);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Attack()
{
	if (!IsAttacking)
	{
		IsAttacking = true;
		if (IsValid(BaseAnimInstance))
		{
			BaseAnimInstance->PlayAttackMontage();
		}
	}
}

void ABaseCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

void ABaseCharacter::OnHit()
{
	UE_LOG(LogTemp, Log, TEXT("Hit"));
}

