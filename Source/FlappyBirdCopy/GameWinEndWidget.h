// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWinEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCOPY_API UGameWinEndWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* FinalScore;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* GameWinLose;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PlayAgainText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* QuitText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* PlayAgain;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Quit;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnPlayAgainClicked();

	UFUNCTION()
		void OnQuitClicked();
public:

	UFUNCTION(BlueprintCallable)
		void InitializeHUDLost();

	UFUNCTION(BlueprintCallable)
		void InitializeHUDWon();

};
