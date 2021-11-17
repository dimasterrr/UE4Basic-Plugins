#include "LevelPortal.h"

#include "Components/BoxComponent.h"
#include "DestructiveForce/GameModes//DestroyFactoryGameMode.h"
#include "DestructiveForce/Pawns/PlayerTankPawn.h"
#include "Kismet/GameplayStatics.h"

ALevelPortal::ALevelPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelPortal::OnBeginOverlap);
}

void ALevelPortal::BeginPlay()
{
	Super::BeginPlay();

	if (const auto GameMode = Cast<ADestroyFactoryGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnDestroyFactoryEndedDelegate.AddUObject(this, &ALevelPortal::OnGameModeIsEnded);
	}
}

void ALevelPortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep,
                                  const FHitResult& SweepResult)
{
	if (!IsPortalEnabled) return;
	if (!Cast<APlayerTankPawn>(OtherActor)) return;

	OnLoadLevel();
}

void ALevelPortal::OnLoadLevel()
{
	UGameplayStatics::OpenLevel(this, *Level.GetAssetName());
}

void ALevelPortal::OnGameModeIsEnded()
{ 
	SetPortalEnable(true);
}

void ALevelPortal::SetPortalEnable(const bool Enable)
{
	if (IsPortalEnabled == Enable) return;

	IsPortalEnabled = Enable;
	OnPortalEnableChanged();
}
