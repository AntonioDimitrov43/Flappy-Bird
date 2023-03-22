// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "GameWinEndWidget.h"
#include "PW_SkippyBird.generated.h"

UCLASS()
class FLAPPYBIRDCOPY_API APW_SkippyBird : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category="Meshes")
		UStaticMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category="Camera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Hit Box")
		UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, Category="Jumping")
		float JumpForce = 750.f;

	UPROPERTY(EditAnywhere, Category = "Points")
		int FlappyPoints;

	

public:
	// Sets default values for this pawn's properties
	APW_SkippyBird();
	
	UPROPERTY(EditAnywhere, Category = "Points")
		bool bHasStarted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameWinEndClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UGameWinEndWidget* WinEndMenu;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBeginWithMesh(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
			, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void AddPointsToBird();

	UFUNCTION()
		int GetPoints();
		
	UFUNCTION()
		void BirdJump();
	
	UFUNCTION()
		void BirdMoveStart();

};
