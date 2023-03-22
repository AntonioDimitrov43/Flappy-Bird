// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PW_SkippyBird.h"
#include "A_BirdObstacle.generated.h"


UCLASS()
class FLAPPYBIRDCOPY_API AA_BirdObstacle : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottomCylinder;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BottomHitBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TopCylinder;

	UPROPERTY(EditAnywhere)
		UBoxComponent* TopHitBox;

	UPROPERTY(EditAnywhere)
		UBoxComponent* MiddlePassBox;

public:	
	// Sets default values for this actor's properties
	AA_BirdObstacle();

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

	UFUNCTION()
		void OnOverlapEndMiddle(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnOverlapBeginCylinders(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
			, bool bFromSweep, const FHitResult& SweepResult);

	void SetObstaclesInPlace(int SpawnVariation,FVector CurrentObstacleLocation);
	void SetCylindersOnVariation(float BottomLocation, float TopLocation, float BoxLocation, FVector CurrentObstacleLocation);

};
