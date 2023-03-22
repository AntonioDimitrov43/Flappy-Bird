// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"
#include "Components/TextBlock.h"

void UGameplayWidget::InitializeOrUpdateHUD(int BirdPoints)
{
	CurrentPointsBird->SetText(FText::FromString("Final Points: " + FString::FromInt(BirdPoints)));
}
