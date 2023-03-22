// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlappyBirdCopyGameModeBase.h"
#include "InfoWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCOPY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* MainText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PlayText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* PlayButton;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameInfoClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UInfoWidget* InfoMenu;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnButtonClicked();
public:

	UFUNCTION(BlueprintCallable)
		void InitializeHUD();

	
	
};
