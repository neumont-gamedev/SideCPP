// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//CollisionComponent->bGenerateOverlapEvents = true;
	//RootComponent = CollisionComponent;

	// Create actor mesh
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	VisualMesh->BodyInstance.SetResponseToAllChannels(ECR_Overlap);
	//VisualMesh->SetCollisionObjectType(ECC_Pawn);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	
	// Create particle system
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	ParticleSystem->SetupAttachment(VisualMesh);
	ParticleSystem->bAutoActivate = true;
	ParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		ParticleSystem->SetTemplate(ParticleAsset.Object);
	}
	

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float RunningTime = GetGameTimeSinceCreation();

	WaveTime = WaveTime + DeltaTime * WaveRate;
	float Wave = FMath::Sin(WaveTime);
	FVector NewLocation = StartLocation + FVector::UpVector * (Wave * WaveAmplitude);

	FRotator NewRotation = GetActorRotation();
	float DeltaRotation = DeltaTime * RotationSpeed;

	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

