// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdCopyGameModeBase.h"
#include "FlappyBirdController.h"
#include "PW_SkippyBird.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "MainMenuWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "InputCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


void AFlappyBirdCopyGameModeBase::BeginPlay()
{
	SpawnCharacter();
	SpawnMainCamera();
	//MainController = CreateDefaultSubobject<AFlappyBirdController>("Main Controller");
	MainController = Cast<AFlappyBirdController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainController->Possess(CurrentBird);
	MainController->SetViewTarget(MainCamera);
	SpawnObstacleBox();

	MainMenu = CreateWidget<UMainMenuWidget>(MainController, GameHudClass);

	if (MainMenu)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		MainMenu->InitializeHUD();
		MainMenu->AddToViewport();
		UGameplayStatics::SetGamePaused(MainController, true);
	}
}

void AFlappyBirdCopyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartGameMovement(DeltaTime);

	if (SpawnedObstacleBoxes < 25)
	{
		SpawnObstacleBox();
	}

	if (Cast<APW_SkippyBird>(MainController->GetPawn())->GetPoints() == 3)
	{
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		WinEndMenu = CreateWidget<UGameWinEndWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameWinEndClass);

		if (WinEndMenu)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
			WinEndMenu->InitializeHUDWon();
			WinEndMenu->AddToViewport();
			//UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}

}

AFlappyBirdCopyGameModeBase::AFlappyBirdCopyGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpawnBoxLocation.X = -450.f;
	SpawnBoxLocation.Y = 1050.f;
	SpawnBoxLocation.Z = 450.f;

	SpawnedObstacleBoxes = 0;

	PlayerControllerClass = AFlappyBirdController::StaticClass();
	MovementDirection.ZeroVector;
	MovementDirection.Y = 1.f;
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Game/BluePrints/BP_SkippyBird"));
	if (PlayerPawnClass.Class != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Testing1"));
		DefaultPawnClass = PlayerPawnClass.Class;
	}*/
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControlledClass(TEXT("/Game/BluePrints/BP_FlappyBirdController"));
	if (PlayerControlledClass.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Testing2"));
		PlayerControllerClass = PlayerControlledClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UMainMenuWidget> MenuHUD(TEXT("/Game/UI/W_Main_Menu"));
	if (MenuHUD.Class != NULL)
	{
		GameHudClass = MenuHUD.Class;
	}

	static ConstructorHelpers::FClassFinder<UGameWinEndWidget> WinEndWidget(TEXT("/Game/UI/W_WinOrEndGame"));
	if (WinEndWidget.Class != NULL)
	{
		GameWinEndClass = WinEndWidget.Class;
	}
	//FTimerHandle FuzeTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AFlappyBirdCopyGameModeBase::SpawnObstacleBox, 10, false);
}

void AFlappyBirdCopyGameModeBase::SpawnCharacter()
{
	//AActor* Start = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
	//FVector StartLocation = Start->GetActorLocation();
	//FRotator StartRotation = Start->GetActorRotation();
	FVector StartLocation;
	StartLocation.X = -450.f;
	StartLocation.Y = -340.f;
	StartLocation.Z = 530.f;
	FRotator StartRotation;
	StartRotation.ZeroRotator;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentBird = GetWorld()->SpawnActor<APW_SkippyBird>(StartLocation, StartRotation, SpawnInfo);
	if (CurrentBird->GetActorLocation() == StartLocation && CurrentBird->GetActorRotation() == StartRotation)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorTesting"));
	}
}

void AFlappyBirdCopyGameModeBase::SpawnMainCamera()
{
	FVector CameraLocation;
	CameraLocation.X = -1200.f;
	CameraLocation.Y = 160.f;
	CameraLocation.Z = 480.f;
	FRotator CameraRotation;
	CameraRotation.ZeroRotator;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MainCamera = GetWorld()->SpawnActor<ABirdCamera>(CameraLocation, CameraRotation, SpawnInfo);
	if (MainCamera->GetActorLocation() == CameraLocation && MainCamera->GetActorRotation() == CameraRotation)
	{
		UE_LOG(LogTemp, Warning, TEXT("CameraTesting"));
	}
}

void AFlappyBirdCopyGameModeBase::StartGameMovement(float Time)
{
	const FVector NewLocationCamera = MainCamera->GetActorLocation() + (MovementDirection * Time * MovementSpeed);
	MainCamera->SetActorLocation(NewLocationCamera);
	const FVector NewLocationBird = CurrentBird->GetActorLocation() + (MovementDirection * Time * MovementSpeed);
	CurrentBird->SetActorLocation(NewLocationBird);
}

void AFlappyBirdCopyGameModeBase::SpawnObstacleBox()
{
	if (SpawnedObstacleBoxes > 0)
	{
		SpawnBoxLocation.Y += 1200.f;
	}
	FRotator BoxRotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnBox = GetWorld()->SpawnActor<AA_SpawningCube>(SpawnBoxLocation, BoxRotation, SpawnInfo);
	SpawnBox->CreateBoxWithObstacles(SpawnBoxLocation, BoxRotation);
	SpawnedObstacleBoxes++;
}
