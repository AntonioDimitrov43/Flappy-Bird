// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PW_SkippyBird.h"
#include "GameFramework/DefaultPawn.h"
#include "FlappyBirdController.h"
#include "BirdCamera.h"
#include "Delegates/Delegate.h"
#include "A_SpawningCube.h"
#include "FlappyBirdCopyGameModeBase.generated.h"

UCLASS()
class FLAPPYBIRDCOPY_API AFlappyBirdCopyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Player Objects")
		APW_SkippyBird* CurrentBird;

	UPROPERTY(EditAnywhere, Category = "Player Objects")
		AFlappyBirdController* MainController;

	UPROPERTY(EditAnywhere, Category = "Player Objects")
		ABirdCamera* MainCamera;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		AA_SpawningCube* SpawnBox;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed = 450.f;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
		FVector SpawnBoxLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
		int SpawnedObstacleBoxes;

	

protected:
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameHudClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UMainMenuWidget* MainMenu;

	FVector MovementDirection;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameWinEndClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UGameWinEndWidget* WinEndMenu;

public:
	AFlappyBirdCopyGameModeBase();

	bool bHasBegun;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnCharacter();

	UFUNCTION()
		void SpawnMainCamera();
	
	UFUNCTION()
		void StartGameMovement(float Time);

	UFUNCTION()
		void SpawnObstacleBox();
};
