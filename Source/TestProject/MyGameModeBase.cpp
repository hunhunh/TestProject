// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<ACharacter> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/BP_MyCharacter.BP_MyCharacter_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

}