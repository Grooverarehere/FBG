// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGBombBlast.h"
#include "Kismet/KismetSystemLibrary.h"
#include "IDamage.h"

// Sets default values
AFBGBombBlast::AFBGBombBlast()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;

	Blast_Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Blast_Particle"));
	Blast_Particle->SetupAttachment(CollisionComponent);
	Blast_Particle->SetFloatParameter("ParticleSpawnRate", 0.f);


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 2500.f;
	ProjectileMovementComponent->MaxSpeed = 2500.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->bAutoActivate = false;
	ProjectileMovementComponent->Velocity = FVector(2500.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AFBGBombBlast::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFBGBombBlast::Initiate_BombBlast(float BlastLength)
{
	Blast_Particle->SetFloatParameter("ParticleSpawnRate", 300);
	m_BlastLength = BlastLength;
	InitPosition = GetActorLocation();
	SetDamage();
	
}

void AFBGBombBlast::SetDamage()
{
	FVector EndPosition = InitPosition + (GetActorForwardVector() * m_BlastLength);
	TArray<FHitResult>Hits;
	TArray<AActor*> Ignore;
	ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	bool m_collision=UKismetSystemLibrary::BoxTraceMulti(GetWorld(), InitPosition, EndPosition, FVector(35.f, 35.f, 35.f), FRotator(0.f, 0.f, 0.f), MyTraceType, false, Ignore, EDrawDebugTrace::None, Hits, true, FLinearColor::Blue, FLinearColor::Blue);
	for (int i = 0; i < Hits.Num(); i++)
	{
		if (m_collision)
		{
			m_BlastLength = Hits[i].Distance;
		}
		bCanMove = true;
		IIDamage* DamageInterface = Cast<IIDamage>(Hits[i].GetActor());
		if (DamageInterface)
		{
			DamageInterface->Damage();
		}
	}
	bCanMove = true;
	GetWorldTimerManager().SetTimer(BlastTimer, this, &AFBGBombBlast::SetDamage, 0.1f, true);
}

void AFBGBombBlast::StopBlast()
{
	Blast_Particle->SetFloatParameter("ParticleSpawnRate", 0);
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AFBGBombBlast::DestroyBlast, 0.7f, false);
}

void AFBGBombBlast::DestroyBlast()
{
	Destroy();
}

// Called every frame
void AFBGBombBlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCanMove)
	{
		if (bStop)
		{
			ProjectileMovementComponent->StopMovementImmediately();
		}
		else
		{
			float dist = (InitPosition - GetActorLocation()).Size();
			if (dist >= m_BlastLength)
			{
				bStop = true;
				GetWorldTimerManager().SetTimer(StopBlastTimer, this, &AFBGBombBlast::StopBlast, 0.1f, false);
			}
			ProjectileMovementComponent->Activate();
		}
	}
}

