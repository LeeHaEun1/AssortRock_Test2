// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
	// �𸮾󿡼� �����Ӹ��� Tick�� ������ �ϴ� ���ʹ�
	// PrimaryActorTick.bCanEverTick = true; �� �������� Tick�� �������� �ֽ��ϴ�.
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// �����ڿ��� ���� �������ִ°� �Ϲ����ε�. 
	// ƽ�� �����ų� ���ų�
	PrimaryActorTick.bCanEverTick = true;
	// PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;


}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// LHE
//AActor* ASnakeHead::myTail = nullptr;
//FVector ASnakeHead::tailBeforePosition = { 0, 0, 0 };

void ASnakeHead::LeftMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}

	AddActorLocalOffset(FVector::LeftVector);
}
void ASnakeHead::RightMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}

	AddActorLocalOffset(FVector::RightVector);
}
void ASnakeHead::UpMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}
	AddActorLocalOffset(FVector::UpVector);
}
void ASnakeHead::DownMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}
	AddActorLocalOffset(FVector::DownVector);
}


// **************************************************************
// **************************************************************
// LHE [�̵�]
void ASnakeHead::LeftAction()
{
	// ������ �������� ����� �ݴ� ������ ������ ����
	if (lastInputKey == Right)
	{
		return;
	}
	lastInputKey = Left;

	FVector MovePos = FVector::LeftVector * 100.0f;

	// LHE ������ġ + �̵� = ���̶�� �̵����� ����
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	// LHE �̵� ������ ��ġ ����
	//beforePosition = GetActorLocation();
	// ������ ���� ���� ���� ���� ��ġ, ���� ���� ������ ���� ��ġ ����
	if (myTail == nullptr)
	{
		tailBeforePosition = GetActorLocation();
	}
	else
	{
		tailBeforePosition = myTail->GetActorLocation();
	}

	// Head�� �̵� ���� ��ġ ����
	headBeforePosition = GetActorLocation();

	// LHE ������ġ + �̵� != ���̶�� �̵�
	AddActorLocalOffset(FVector::LeftVector * 100.0f);

	// ������ ������
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// ���⿡ Body�� �ִ��� Ȯ���ؾ� �Ѵ�.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// LHE: tailBeforePosition �ڸ��� Body ����
		// => SnakeGameMode.cpp���� ����

		// ���⼭ Body ����
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray�� Add
		wholeSnake.Add(myTail);


		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}
}
void ASnakeHead::RightAction()
{
	// ������ �������� ����� �ݴ� ������ ������ ����
	if (lastInputKey == Left)
	{
		return;
	}
	lastInputKey = Right;

	FVector MovePos = FVector::RightVector * 100.0f;

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (myTail == nullptr)
	{
		tailBeforePosition = GetActorLocation();
	}
	else
	{
		tailBeforePosition = myTail->GetActorLocation();
	}

	// Head�� �̵� ���� ��ġ ����
	headBeforePosition = GetActorLocation();

	AddActorLocalOffset(FVector::RightVector * 100.0f);

	// ������ ������
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// ���⿡ Body�� �ִ��� Ȯ���ؾ� �Ѵ�.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// ���⼭ Body ����
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray�� Add
		wholeSnake.Add(myTail);

		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}

}
void ASnakeHead::UpAction()
{
	// ������ �������� ����� �ݴ� ������ ������ ����
	if (lastInputKey == Down)
	{
		return;
	}
	lastInputKey = Up;

	FVector MovePos = FVector::UpVector * 100.0f;

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (myTail == nullptr)
	{
		tailBeforePosition = GetActorLocation();
	}
	else
	{
		tailBeforePosition = myTail->GetActorLocation();
	}

	// Head�� �̵� ���� ��ġ ����
	headBeforePosition = GetActorLocation();

	AddActorLocalOffset(FVector::UpVector * 100.0f);

	// ������ ������
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// ���⿡ Body�� �ִ��� Ȯ���ؾ� �Ѵ�.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// ���⼭ Body ����
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray�� Add
		wholeSnake.Add(myTail);

		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}
}
void ASnakeHead::DownAction()
{
	// ������ �������� ����� �ݴ� ������ ������ ����
	if (lastInputKey == Up)
	{
		return;
	}
	lastInputKey = Down;

	FVector MovePos = FVector::DownVector * 100.0f;

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (myTail == nullptr)
	{
		tailBeforePosition = GetActorLocation();
	}
	else
	{
		tailBeforePosition = myTail->GetActorLocation();
	}

	// Head�� �̵� ���� ��ġ ����
	headBeforePosition = GetActorLocation();

	// �̵��� �ϰ� ����
	AddActorLocalOffset(FVector::DownVector * 100.0f);

	// ������ ������
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// ���⿡ Body�� �ִ��� Ȯ���ؾ� �Ѵ�.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// ���⼭ Body ����
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray�� Add
		wholeSnake.Add(myTail);

		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}
}
