#include "WeaponBox.h"

#include "Components/BoxComponent.h"
#include "DestructiveForce//Weapons/WeaponBase.h"
#include "DestructiveForce/Pawns/TankPawn.h"

AWeaponBox::AWeaponBox()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBox::OnActorOverlapBegin);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxCollision);
}

void AWeaponBox::OnActorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	const auto PlayerPawn = Cast<ATankPawn>(OtherActor);
	if (!PlayerPawn) return;

	PlayerPawn->SetWeapon(DefaultWeaponClass);
	Destroy();
}
