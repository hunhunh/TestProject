// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	bWantsInitializeComponent = true;
	Level = 1;
}


void UMyActorComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMyActorComponent::SetLevel(int32 Lv)
{
	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		auto CharacterData = GameInstance->GetCharacterData(Lv);
		if (CharacterData)
		{
			Level = CharacterData->Level;
			MaxHp = CharacterData->MaxHp;
			Hp = MaxHp;

		}
	}
}

void UMyActorComponent::OnDamaged(float DamageAmount)
{
	int32 NewHp = Hp - DamageAmount;
	SetHp(NewHp);
}

void UMyActorComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
	{
		Hp = 0;
	}

	OnHpChange.Broadcast();
}

float UMyActorComponent::GetHpRatio()
{
	if (MaxHp == 0 || Hp == 0)
	{
		return 0.f;
	}
	return (float)Hp / (float)MaxHp;
}



