#include "AmmoBox.h"

#include "Components/BoxComponent.h"
#include "DestructiveForce/Pawns/TankPawn.h"

AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnActorOverlapBegin);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxCollision);
}

void AAmmoBox::OnActorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	const auto PlayerPawn = Cast<ATankPawn>(OtherActor);
	if (!PlayerPawn) return;

	for (const auto& Item : AmmoMap)
		PlayerPawn->AddAmmoToWeapon(Item.Key, Item.Value);

	Destroy();
}
