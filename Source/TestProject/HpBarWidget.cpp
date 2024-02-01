// Fill out your copyright notice in the Description page of Project Settings.


#include "HpBarWidget.h"
#include "MyActorComponent.h"
#include "Components/ProgressBar.h"

void UHpBarWidget::BindHp(UMyActorComponent* ActorComp)
{
	MyActorComp = ActorComp;
	MyActorComp->OnHpChange.AddUObject(this, &UHpBarWidget::UpdateHp);
	UpdateHp();
}

void UHpBarWidget::UpdateHp()
{
	PB_HpBar->SetPercent(MyActorComp->GetHpRatio());
}
