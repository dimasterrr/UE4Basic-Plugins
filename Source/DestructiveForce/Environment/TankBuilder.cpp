#include "TankBuilder.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "DestructiveForce/Base/Health/HealthComponent.h"
#include "DestructiveForce/GameModes//DestroyFactoryGameMode.h"
#include "DestructiveForce/Controllers/TankAIController.h"
#include "DestructiveForce/Pawns/EnemyTankPawn.h"
#include "Kismet/GameplayStatics.h"

ATankBuilder::ATankBuilder()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(BoxComponent);

	SpawnEffectsComponent = CreateDefaultSubobject<UArrowComponent>("Spawn Effects Component");
	SpawnEffectsComponent->SetupAttachment(MeshComponent);

	SpawnPointComponent = CreateDefaultSubobject<UArrowComponent>("Spawn Actor Component");
	SpawnPointComponent->SetupAttachment(MeshComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	HealthComponent->OnDieDelegate.AddUObject(this, &ATankBuilder::OnDie);
	
	// TODO: Add spawning pool
}

void ATankBuilder::BeginPlay()
{
	Super::BeginPlay();

	if (const auto GameMode = Cast<ADestroyFactoryGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RegisterBuilder(this);
	}

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

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEmitterTemplate,
	                                         SpawnEffectsComponent->GetComponentTransform());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SpawnSoundTemplate,
	                                       SpawnEffectsComponent->GetComponentLocation());
}

bool ATankBuilder::TakeDamage(const FDamageData& Data)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamagedEmitterTemplate, Data.HitPoint);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DamagedSoundTemplate, GetActorLocation());

	const auto CurrentHealth = HealthComponent->GetHealth();
	HealthComponent->SetHealth(CurrentHealth - Data.Damage);

	return HealthComponent->IsDie();
}

void ATankBuilder::OnDie_Implementation()
{
	GetWorldTimerManager().ClearTimer(FSpawnTimerHandle);
}

UHealthComponent* ATankBuilder::GetHealthComponent() const
{
	return HealthComponent;
}
