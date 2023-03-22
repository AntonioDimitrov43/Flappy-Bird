// Fill out your copyright notice in the Description page of Project Settings.


#include "InfoWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FlappyBirdController.h"
#include "Kismet/GameplayStatics.h"

void UInfoWidget::NativeConstruct()
{
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0),this);
}

void UInfoWidget::OnInputRegistered()
{
	AFlappyBirdController* CurrentController = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APW_SkippyBird* CurrentBird = Cast<APW_SkippyBird>(CurrentController->GetPawn());
	if (CurrentBird)
	{
			CurrentController->bShowMouseCursor = false;
			RemoveFromParent();
	}
	
}

void UInfoWidget::InitializeHUD()
{
	InformationText->SetText(FText::FromString("Tip: Use Spacebar or Left Mouse button \n to Jump and Begin the Game"));
}
