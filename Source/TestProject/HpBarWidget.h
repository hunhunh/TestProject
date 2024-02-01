// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UMyActorComponent* MyActorComp;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

public:
	void BindHp(class UMyActorComponent* ActorComp);
	void UpdateHp();

};
