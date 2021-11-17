#include "TankBuilder.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "DestructiveForce/Controllers/TankAIController.h"
#include "DestructiveForce/Pawns/EnemyTankPawn.h"
#include "Kismet/GameplayStatics.h"

ATankBuilder::ATankBuilder()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(BoxComponent);

	SpawnPointComponent = CreateDefaultSubobject<UArrowComponent>("Spawn Actor Component");
	SpawnPointComponent->SetupAttachment(MeshComponent);

	// TODO: Add spawning pool
}

void ATankBuilder::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FSpawnTimerHandle, this, &ATankBuilder::OnSpawnActor, SpawnTime, true, 0.f);
}

void ATankBuilder::OnSpawnActor()
{
	if (!DefaultSpawnActor) return;

	// TODO: Optimize this hard function
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DefaultSpawnActor, FoundActors);

	if (FoundActors.Num() >= SpawnMax) return;

	const auto SpawnedActor = GetWorld()->SpawnActorDeferred<AEnemyTankPawn>(DefaultSpawnActor,
	                                                                         SpawnPointComponent->
	                                                                         GetComponentTransform(),
	                                                                         this, nullptr,
	                                                                         ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	SpawnedActor->PatrolPoints = PatrolPoints;
	SpawnedActor->FinishSpawning(SpawnPointComponent->GetComponentTransform());
}
