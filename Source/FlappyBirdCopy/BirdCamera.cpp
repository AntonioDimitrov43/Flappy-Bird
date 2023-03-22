// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdCamera.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABirdCamera::ABirdCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CameraCapsule"));
	CameraCapsule->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("FlappyBoom"));
	CameraBoom->SetupAttachment(CameraCapsule);

	FlappyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FlappyCamera"));
	FlappyCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FlappyCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	FlappyCamera->OrthoWidth = 1480.f;
	FlappyCamera->bConstrainAspectRatio = true;

}

// Called when the game starts or when spawned
void ABirdCamera::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning, TEXT("Checking"));

	
}

// Called every frame
void ABirdCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

