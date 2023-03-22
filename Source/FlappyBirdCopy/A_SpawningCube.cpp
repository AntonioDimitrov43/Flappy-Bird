// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SpawningCube.h"

// Sets default values
AA_SpawningCube::AA_SpawningCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Box"));
	RootComponent = SpawningBox;
	//SpawningBox->SetupAttachment(RootComponent);
	SpawningBox->SetBoxExtent(FVector(60.f, 450.f, 450.f));
	SpawningBox->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void AA_SpawningCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_SpawningCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_SpawningCube::CreateBoxWithObstacles(FVector Location, FRotator Rotation)
{
	int ObstaclesSpawned = 0;
	FVector CurrentObstacleLocation = Location;
	float YLocation = CurrentObstacleLocation.Y - 400.f;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 1; i <= 3; i++)
	{	
		CurrentObstacleLocation.Y = YLocation + (i - 1) * 400.f;
		int Variation = FMath::RandRange(1, 5);
		AA_BirdObstacle* ObstacleToSpawn;
		ObstacleToSpawn = GetWorld()->SpawnActor<AA_BirdObstacle>(CurrentObstacleLocation, Rotation, SpawnInfo);
		ObstacleToSpawn->SetObstaclesInPlace(Variation,CurrentObstacleLocation);
		ObstacleArray.Add(ObstacleToSpawn);
	}
}

