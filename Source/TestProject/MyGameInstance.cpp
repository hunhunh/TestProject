// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Ref(TEXT("/Script/Engine.DataTable'/Game/Data/DT_Character.DT_Character'"));
	if (DT_Ref.Object)
	{
		DTCharacter = DT_Ref.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("Character Data : %d"), GetCharacterData(1)->MaxHp);
}

FCharacterData* UMyGameInstance::GetCharacterData(int32 Level)
{
	FName RowName = FName(*FString::Printf(TEXT("Lv%d"), Level));

	return DTCharacter->FindRow<FCharacterData>(RowName, TEXT(""));
}
