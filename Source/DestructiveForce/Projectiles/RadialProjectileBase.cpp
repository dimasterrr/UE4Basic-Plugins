#include "RadialProjectileBase.h"

#include "DestructiveForce/Pawns/TankPawn.h"
#include "Kismet/KismetSystemLibrary.h"

void ARadialProjectileBase::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	const auto StartTrace = ImpactResult.ImpactPoint;
	const auto EndTrace = ImpactResult.ImpactPoint + FVector::OneVector;

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(this, StartTrace, EndTrace, ExplodeRadius, TraceChannel, false, {},
	                                       EDrawDebugTrace::None, HitResults, false);

	for (auto HitResult : HitResults)
	{
		const auto TargetActor = HitResult.GetActor();
		if (!TargetActor) continue;

		auto TargetIsDead = false;
		ApplyDamage(HitResult, TargetIsDead);

		if (TargetIsDead) ApplyScore(HitResult);

		TArray<UPrimitiveComponent*> TargetComponents;
		TargetActor->GetComponents(TargetComponents);

		for (const auto TargetComponent : TargetComponents)
		{
			if (!TargetComponent->IsSimulatingPhysics()) continue;

			const auto ForceDirection = TargetActor->GetActorLocation() - GetActorLocation();
			TargetComponent->AddImpulse(ForceDirection * PushForce);
		}
	}

	Release();
}
