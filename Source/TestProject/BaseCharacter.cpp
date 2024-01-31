// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "MyActorComponent.h"
#include "BaseAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "HpBarWidget.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("ActorComponent"));
	
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UHpBarWidget> HpBar_Ref(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (HpBar_Ref.Succeeded())
	{
		HpBar->SetWidgetClass(HpBar_Ref.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 30.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	}

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

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("Take Damage : %f"), DamageAmount);
	ActorComponent->OnDamaged(DamageAmount);

	return DamageAmount;
}
