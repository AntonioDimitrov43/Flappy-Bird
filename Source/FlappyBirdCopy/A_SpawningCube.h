// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "A_BirdObstacle.h"
#include "A_SpawningCube.generated.h"

UCLASS()
class FLAPPYBIRDCOPY_API AA_SpawningCube : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere)
		TArray<AA_BirdObstacle*> ObstacleArray;
	
public:	
	// Sets default values for this actor's properties
	AA_SpawningCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateBoxWithObstacles(FVector Location, FRotator Rotation);

};
