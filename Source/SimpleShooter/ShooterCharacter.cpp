// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "Launcher.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	// APawn* characterPawn = Cast<APawn>(this);

	// if (characterPawn) 
	// {
	// 	if (characterPawn == playerPawn) 
	// 	{
	// 		maxHealth *= 2;
	// 	}
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("character pawn null!"));
	// }

	health = maxHealth;

	weaponIndex = 1;	

	if (!gunClass) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun null!!"));
		return;
	}

	rifal = GetWorld()->SpawnActor<AGun>(gunClass);

	launcher = GetWorld()->SpawnActor<ALauncher>(launcherClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	rifal->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));

	rifal->SetOwner(this);

	launcher->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AShooterCharacter::moveLR);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AShooterCharacter::moveFB);

	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AShooterCharacter::moveCursorX);
	
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AShooterCharacter::upDown);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter::jump);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterCharacter::fire);

	PlayerInputComponent->BindAction(TEXT("Reload Gun"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);

	PlayerInputComponent->BindAction(TEXT("Switch to rifal"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SwitchToRifal);
	
	PlayerInputComponent->BindAction(TEXT("Switch to launcher"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SwitchToLauncher);
}

void AShooterCharacter::moveLR(float value)
{
	 float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	// FVector move = FVector(0, value * DeltaTime * speed, 0);

	// AddActorLocalOffset(move);

	AddMovementInput(GetActorRightVector() * value * DeltaTime * speed);
}

void AShooterCharacter::moveFB(float value)
{
	 float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	// FVector move = FVector(value * DeltaTime * speed, 0, 0);

	// AddActorLocalOffset(move);

	AddMovementInput(GetActorForwardVector() * value * DeltaTime * speed);
}

void AShooterCharacter::moveCursorX(float value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	AddControllerYawInput(value * DeltaTime * rotationRate);
}

void AShooterCharacter::upDown(float value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	AddControllerPitchInput(value * DeltaTime * rotationRate);
}

void AShooterCharacter::jump()
{
	Jump();
}

void AShooterCharacter::fire()
{
	switch (weaponIndex)
	{
	case 1:
		rifal->pullTrigger();
		break;
	case 2:
		launcher->pullTrigger();
	break;

	default:
		break;
	}
}

void AShooterCharacter::Reload()
{
	switch(weaponIndex)
	{
	case 1:
		rifal->Reload();
		break;
	case 2:
		launcher->Reload();
		break;
	}
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (isDeath()) 
	{
		return 0;
	}

	health -= damageAmount;

	UE_LOG(LogTemp, Display, TEXT("actor health: %f"), health);

	if (isDeath()) 
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();

		if (GameMode) 
		{
			GameMode->KillPawn(this);
		}

		DetachFromControllerPendingDestroy();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (health <= 0.f ) 
	{
		return damageAmount;
	}

	return damageAmount;
}

bool AShooterCharacter::isDeath() const
{
	return health <= 0;
}

float AShooterCharacter::GetPlayerHealthWithPercentage() const
{
	return health / maxHealth;
}

void AShooterCharacter::SwitchToRifal()
{
	if (weaponIndex == 1) 
	{
		return;
	}

	weaponIndex = 1;

	//launcher->SetHidden(true);

	launcher->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	//rifal->SetHidden(false);

	rifal->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
}

void AShooterCharacter::SwitchToLauncher()
{
	if (weaponIndex == 2) 
	{
		return;
	}

	weaponIndex = 2;

	//rifal->SetHidden(true);

	rifal->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	//launcher->SetHidden(false);

	launcher->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
}