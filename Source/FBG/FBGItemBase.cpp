// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGItemBase.h"

// Sets default values
AFBGItemBase::AFBGItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetWorldScale3D(FVector(1.3f, 1.3f, 1.3f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Mesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	Mesh_Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Arrow"));
	Mesh_Arrow->SetupAttachment(RootComponent);
	Mesh_Arrow->SetRelativeLocation(FVector(-30.f, 40.f, 20.f));
	Mesh_Arrow->SetRelativeRotation(FRotator(0.f, 90.f, -30.f));
	Mesh_Arrow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	TimelineComponent->SetLooping(true);

	static ConstructorHelpers::FObjectFinder<UCurveFloat>rotationcurve(TEXT("'/Game/TopDownCPP/Curves/RotationItemCurve.RotationItemCurve'"));
	if (rotationcurve.Succeeded())
	{
		RotationTimelineCurve = rotationcurve.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat>updowncurve(TEXT("'/Game/TopDownCPP/Curves/UpDownItem.UpDownItem'"));
	if (updowncurve.Succeeded())
	{
		UpDownTimelineCurve = updowncurve.Object;
	}
}

// Called when the game starts or when spawned
void AFBGItemBase::BeginPlay()
{
	Super::BeginPlay();
	RotationFunctionFloat.BindDynamic(this, &AFBGItemBase::RotationTimelineFunction);
	UpDownFunctionFloat.BindDynamic(this, &AFBGItemBase::UpDownTimelineFunction);
	if (TimelineComponent)
	{
		TimelineComponent->AddInterpFloat(RotationTimelineCurve, RotationFunctionFloat);
		TimelineComponent->AddInterpFloat(UpDownTimelineCurve, UpDownFunctionFloat);
	}
	TimelineComponent->PlayFromStart();
}

void AFBGItemBase::RotationTimelineFunction(float Output)
{
	Mesh->SetRelativeRotation(FRotator(0.f, Output, 0.f));
}

void AFBGItemBase::UpDownTimelineFunction(float Output)
{
	Mesh_Arrow->SetRelativeLocation(FVector(-30.f, 40.f, Output));
}

// Called every frame
void AFBGItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

