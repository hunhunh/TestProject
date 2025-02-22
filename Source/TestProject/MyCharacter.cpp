// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h"
#include "Arrow.h"
#include "MyActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));
	if (SkeletalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshRef.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->SocketOffset = FVector(0.f, 120.f, 75.f);
	SpringArm->bUsePawnControlRotation = true;

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ABP_MyCharacter.ABP_MyCharacter_C'"));
	if (AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
	}
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::KeyUpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::KeyLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyCharacter::MouseLookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &AMyCharacter::MouseLookUpDown);

	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::KeyUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::KeyLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::MouseLookLeftRight(float value)
{
	AddControllerYawInput(value);
}

void AMyCharacter::MouseLookUpDown(float value)
{
	AddControllerPitchInput(value);
}

void AMyCharacter::Attack()
{
	Super::Attack();

	
}

void AMyCharacter::OnHit()
{
	Super::OnHit();

	
	APlayerCameraManager* CamManger = UGameplayStatics::GetPlayerCameraManager(this,0);

	float AttackRange = 10000.f;
	FHitResult HitResult;
	FVector AimLocation = CamManger->GetCameraLocation();
	FVector TargetLocation = AimLocation + CamManger->GetActorForwardVector() * AttackRange;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool Result = GetWorld()->LineTraceSingleByChannel
	(
		OUT HitResult,
		AimLocation,
		TargetLocation,
		ECollisionChannel::ECC_GameTraceChannel3,
		params
	);

	FColor Color;

	if (Result)
	{
		TargetLocation = HitResult.ImpactPoint;
		UE_LOG(LogTemp, Log, TEXT("Hit"));
		Color = FColor::Green;
		DrawDebugLine(GetWorld(), AimLocation, TargetLocation, Color, true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not Hit"));
		Color = FColor::Red;
		DrawDebugLine(GetWorld(), AimLocation, TargetLocation, Color, true);
	}

	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->PlayAttackMontage();
		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("ArrowSocket"));
		FVector SocketVector = SocketTransform.GetLocation();
		FVector DeltaVector = TargetLocation - SocketVector;
		FRotator SocketRotator = FRotationMatrix::MakeFromX(DeltaVector).Rotator();
		FActorSpawnParameters Arrowparams;
		Arrowparams.Owner = this;
		Arrowparams.Instigator = this;

		auto MyArrow = GetWorld()->SpawnActor<AArrow>(SocketVector, SocketRotator, Arrowparams);
	}
}

