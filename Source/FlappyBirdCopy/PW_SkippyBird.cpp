// Fill out your copyright notice in the Description page of Project Settings.

#include "PW_SkippyBird.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
APW_SkippyBird::APW_SkippyBird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

	bHasStarted = false;

	BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(RootComponent);
	BirdMesh->SetGenerateOverlapEvents(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/Meshes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CylinderMaterial(TEXT("/Game/Materials/MAT_Bird"));

	if (CylinderAsset.Succeeded() && CylinderMaterial.Succeeded())
	{
		BirdMesh->SetStaticMesh(CylinderAsset.Object);
		BirdMesh->SetMaterial(0, CylinderMaterial.Object);
		BirdMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		FRotator Rotation;
		Rotation.ZeroRotator;
		Rotation.Roll = 90.f;
		BirdMesh->SetWorldRotation(Rotation);
		BirdMesh->SetWorldScale3D(FVector(1.f));
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(BirdMesh);
	CameraBoom->TargetArmLength = 700.f;
	CameraBoom->SocketOffset.Y = 650.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 1700.f;
	Camera->bConstrainAspectRatio = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->InitBoxExtent(FVector(52.f, 52.f, 52.f));
	HitBox->SetCollisionProfileName(TEXT("Bird Collision"));
	HitBox->SetupAttachment(BirdMesh);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &APW_SkippyBird::OnOverlapBeginWithMesh);

	static ConstructorHelpers::FClassFinder<UGameWinEndWidget> WinEndWidget(TEXT("/Game/UI/W_WinOrEndGame"));
	if (WinEndWidget.Class!=NULL)
	{
		GameWinEndClass = WinEndWidget.Class;
	}
	
}

// Called when the game starts or when spawned
void APW_SkippyBird::BeginPlay()
{
	Super::BeginPlay();
	
	FlappyPoints = 0;

	BirdMesh->SetSimulatePhysics(true);
	BirdMesh->BodyInstance.bLockXTranslation = true;
	BirdMesh->BodyInstance.bLockYTranslation = true;
	BirdMesh->BodyInstance.bLockRotation = true;
}

// Called every frame
void APW_SkippyBird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APW_SkippyBird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Flappy Jump", IE_Pressed, this, &APW_SkippyBird::BirdJump);
	PlayerInputComponent->BindAction("Flappy Jump", IE_Pressed, this, &APW_SkippyBird::BirdMoveStart);
	PlayerInputComponent->BindAction("Flappy Jump 2", IE_Pressed, this, &APW_SkippyBird::BirdJump);
	PlayerInputComponent->BindAction("Flappy Jump 2", IE_Pressed, this, &APW_SkippyBird::BirdMoveStart);
	this->SetTickableWhenPaused(true);

}

void APW_SkippyBird::OnOverlapBeginWithMesh(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(Cast<UStaticMeshComponent>(OtherComp)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Checking Floor"));
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		WinEndMenu = CreateWidget<UGameWinEndWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameWinEndClass);

		if (WinEndMenu)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
			WinEndMenu->InitializeHUDLost();
			WinEndMenu->AddToViewport();
			//UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		//UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
	}
}

void APW_SkippyBird::AddPointsToBird()
{
	FlappyPoints += 1;
	FString CurrentPoints = FString::FromInt(FlappyPoints);
	UE_LOG(LogTemp, Warning, TEXT("My Points are: %d"), FlappyPoints);

}

int APW_SkippyBird::GetPoints()
{
	return FlappyPoints;
}

void APW_SkippyBird::BirdJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
	BirdMesh->BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, true);
}

void APW_SkippyBird::BirdMoveStart()
{
	bHasStarted = true;
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
}
