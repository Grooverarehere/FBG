// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGBomb.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FBGCharacter.h"
#include "Components/CapsuleComponent.h"
#include "FBGBombBlast.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFBGBomb::AFBGBomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Fuse_Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Fuse_Particle"));
	Fuse_Particle->SetupAttachment(Mesh);

	BombCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BombCollision"));
	BombCollision->SetupAttachment(RootComponent);

	BombOverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BombOverlapCollision"));
	BombOverlapCollision->SetupAttachment(RootComponent);
	BombOverlapCollision->OnComponentEndOverlap.AddDynamic(this, &AFBGBomb::OnOverlapEnd);

	ExplodeTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("ExplodeTimeLine"));
}

void AFBGBomb::IgniteBomb(AFBGBombSpawner* Spawner, float BlastLength, AActor* OwnerSpawner)
{
	//UGameplayStatics::SpawnSoundAtLocation
	SpawnBlast();
	ActorSpawner = Spawner;
	m_BlastLength = BlastLength;
	BombOwner = OwnerSpawner;
	ActorSpawner->bIsOccupied = true;
	ExplodeTimeLine->PlayFromStart();
}

void AFBGBomb::Damage()
{
	
	GetWorldTimerManager().SetTimer(ExplodeTimer, this, &AFBGBomb::Explode, 0.1f, true);
	
}

// Called when the game starts or when spawned
void AFBGBomb::BeginPlay()
{
	Super::BeginPlay();
	TArray<FHitResult>Hits;
	FVector StartPoint(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z+50.f);
	FVector EndPoint(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f);
	ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	TArray<AActor*> Ignore;
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), StartPoint,EndPoint,FVector(45.f,45.f,45.f),FRotator(0.f,0.f,0.f),MyTraceType,false,Ignore,EDrawDebugTrace::None,Hits,true,FLinearColor::Blue,FLinearColor::Blue);
	for (int i = 0; i < Hits.Num(); i++)
	{
		ActorToIgnore.AddUnique(Hits[i].GetActor());
	}
	SetCollisionsToActorsToIgnore();
	UpdateEmissiveFloat.BindDynamic(this, &AFBGBomb::EmisiveUpdate);
	UpdateBombsizeFloat.BindDynamic(this, &AFBGBomb::BombSizeUpdate);
	FinishedFunctionFloat.BindUFunction(this, "FinishedTimelineFunction");
	if (ExplodeTimeLine)
	{
		ExplodeTimeLine->AddInterpFloat(EmissiveCurve, UpdateEmissiveFloat);
		ExplodeTimeLine->AddInterpFloat(BombSizeCurve, UpdateBombsizeFloat);
		ExplodeTimeLine->SetTimelineFinishedFunc(FinishedFunctionFloat);
	}
	
}

void AFBGBomb::SetCollisionsToActorsToIgnore()
{
	for (int i = 0; i < ActorToIgnore.Num(); i++)
	{
		AFBGCharacter* character = Cast<AFBGCharacter>(ActorToIgnore[i]);
		if (character->IsValidLowLevel())
		{
			character->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
		}
	}
	BombCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AFBGBomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFBGCharacter* character = Cast<AFBGCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		character->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	}
}

void AFBGBomb::SpawnBlast()
{
	TArray<FVector> Rotations;
	Rotations.Add(FVector(1.f,0.f,0.f));
	Rotations.Add(FVector(0.f,1.f,0.f));
	Rotations.Add(FVector(-1.f,0.f,0.f));
	Rotations.Add(FVector(0.f,-1.f,0.f));
	for (int i = 0; i < Rotations.Num(); i++)
	{
		FRotator rot = UKismetMathLibrary::MakeRotFromX(Rotations[i]);
		FVector loc = GetActorLocation();
		loc.Z += 50.f;
		FActorSpawnParameters SpawnParams;
		AFBGBombBlast* BombBlast= GetWorld()->SpawnActor<AFBGBombBlast>(BombBlastClass, loc, rot, SpawnParams);
		SpawnedBlast.Add(BombBlast);
	}
}

void AFBGBomb::EmisiveUpdate(float Output)
{
	Mesh->SetScalarParameterValueOnMaterials("Emissiveness", Output);
}

void AFBGBomb::BombSizeUpdate(float Output)
{
	Mesh->SetWorldScale3D(FVector(Output, Output, Output));
}

void AFBGBomb::FinishedTimelineFunction()
{
	Explode();
}

void AFBGBomb::Explode()
{
	if (!bExplode) {
		bExplode = true;
		//PlaySoundAtLocation
		ActorSpawner->bIsOccupied = false;
		BombOverlapCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Ignore);
		for (int i = 0; i < SpawnedBlast.Num(); i++)
		{
			SpawnedBlast[i]->Initiate_BombBlast(m_BlastLength);
		}
		AFBGCharacter* character = Cast<AFBGCharacter>(BombOwner);
		if (character)
		{
			character->m_AmountOfBombs += 1;
		}
		Destroy();
	}
	

}

// Called every frame
void AFBGBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

