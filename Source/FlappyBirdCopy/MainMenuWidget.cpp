// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnButtonClicked);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0),this);
}

void UMainMenuWidget::OnButtonClicked()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	RemoveFromParent();

	InfoMenu = CreateWidget<UInfoWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameInfoClass);

	if (InfoMenu)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		InfoMenu->InitializeHUD();
		InfoMenu->AddToViewport(0);
		UGameplayStatics::SetGamePaused(UGameplayStatics::GetPlayerController(GetWorld(), 0), false);
		InfoMenu->OnInputRegistered();
	}
}

void UMainMenuWidget::InitializeHUD()
{
	MainText->SetText(FText::FromString("Flappy Bird Copy"));
	PlayText->SetText(FText::FromString("Start Game"));
}
