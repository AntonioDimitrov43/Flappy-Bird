// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWinEndWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FlappyBirdController.h"
#include "PW_SkippyBird.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UGameWinEndWidget::NativeConstruct()
{
	if (PlayAgain)
	{
		PlayAgain->OnClicked.AddDynamic(this, &UGameWinEndWidget::OnPlayAgainClicked);
	}
	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &UGameWinEndWidget::OnQuitClicked);
	}


	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UGameWinEndWidget::OnPlayAgainClicked()
{
	UWorld* CurrentWorld = GetWorld();
	AFlappyBirdCopyGameModeBase* CurrentGameMode = Cast<AFlappyBirdCopyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	CurrentGameMode->ResetLevel();
	RemoveFromParent();
}

void UGameWinEndWidget::OnQuitClicked()
{
	RemoveFromParent();
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

void UGameWinEndWidget::InitializeHUDLost()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GameWinLose->SetText(FText::FromString("YOU HAVE LOST!"));
	PlayAgainText->SetText(FText::FromString("Play Again"));
	QuitText->SetText(FText::FromString("Quit"));
	AFlappyBirdController* CurrentController = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APW_SkippyBird* CurrentBird = Cast<APW_SkippyBird>(CurrentController->GetPawn());
	int Score = CurrentBird->GetPoints();
	FinalScore->SetText(FText::FromString("Final Points: " + FString::FromInt(Score)));

}
void UGameWinEndWidget::InitializeHUDWon()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GameWinLose->SetText(FText::FromString("YOU HAVE WON!"));
	PlayAgainText->SetText(FText::FromString("Play Again"));
	QuitText->SetText(FText::FromString("Quit"));
	AFlappyBirdController* CurrentController = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APW_SkippyBird* CurrentBird = Cast<APW_SkippyBird>(CurrentController->GetPawn());
	int Score = CurrentBird->GetPoints();
	FinalScore->SetText(FText::FromString("Final Points: " + FString::FromInt(Score)));

}
