// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
	// 언리얼에서 프레임마다 Tick을 돌려야 하는 액터는
	// PrimaryActorTick.bCanEverTick = true; 로 만들어줘야 Tick을 돌릴수가 있습니다.
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 생성자에서 보통 설정해주는게 일반적인데. 
	// 틱을 돌릴거냐 말거냐
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
// LHE [이동]
void ASnakeHead::LeftAction()
{
	// 마지막 움직임의 방향과 반대 방향의 움직임 방지
	if (lastInputKey == Right)
	{
		return;
	}
	lastInputKey = Left;

	FVector MovePos = FVector::LeftVector * 100.0f;

	// LHE 현재위치 + 이동 = 벽이라면 이동하지 않음
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	// LHE 이동 직전의 위치 저장
	//beforePosition = GetActorLocation();
	// 꼬리가 없을 때는 나의 직전 위치, 있을 때는 꼬리의 직전 위치 저장
	if (myTail == nullptr)
	{
		tailBeforePosition = GetActorLocation();
	}
	else
	{
		tailBeforePosition = myTail->GetActorLocation();
	}

	// Head의 이동 직전 위치 저장
	headBeforePosition = GetActorLocation();

	// LHE 현재위치 + 이동 != 벽이라면 이동
	AddActorLocalOffset(FVector::LeftVector * 100.0f);

	// 몸통의 움직임
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// 여기에 Body가 있는지 확인해야 한다.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// LHE: tailBeforePosition 자리에 Body 생성
		// => SnakeGameMode.cpp에서 수행

		// 여기서 Body 생성
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray에 Add
		wholeSnake.Add(myTail);


		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}
}
void ASnakeHead::RightAction()
{
	// 마지막 움직임의 방향과 반대 방향의 움직임 방지
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

	// Head의 이동 직전 위치 저장
	headBeforePosition = GetActorLocation();

	AddActorLocalOffset(FVector::RightVector * 100.0f);

	// 몸통의 움직임
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// 여기에 Body가 있는지 확인해야 한다.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// 여기서 Body 생성
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray에 Add
		wholeSnake.Add(myTail);

		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}

}
void ASnakeHead::UpAction()
{
	// 마지막 움직임의 방향과 반대 방향의 움직임 방지
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

	// Head의 이동 직전 위치 저장
	headBeforePosition = GetActorLocation();

	AddActorLocalOffset(FVector::UpVector * 100.0f);

	// 몸통의 움직임
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// 여기에 Body가 있는지 확인해야 한다.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// 여기서 Body 생성
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray에 Add
		wholeSnake.Add(myTail);

		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}
}
void ASnakeHead::DownAction()
{
	// 마지막 움직임의 방향과 반대 방향의 움직임 방지
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

	// Head의 이동 직전 위치 저장
	headBeforePosition = GetActorLocation();

	// 이동을 하고 나서
	AddActorLocalOffset(FVector::DownVector * 100.0f);

	// 몸통의 움직임
	if (wholeSnake.Num() != 0)
	{
		for (int i = wholeSnake.Num() - 1; i > 0; i--)
		{
			wholeSnake[i]->SetActorLocation(wholeSnake[i - 1]->GetActorLocation());
		}
		wholeSnake[0]->SetActorLocation(headBeforePosition);
	}

	// 여기에 Body가 있는지 확인해야 한다.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		// 여기서 Body 생성
		FTransform tailTrans;
		tailTrans.SetLocation(ASnakeHead::tailBeforePosition);
		ASnakeHead::myTail = GetWorld()->SpawnActor<AActor>(BodyType, tailTrans);
		// TArray에 Add
		wholeSnake.Add(myTail);

		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();
	}
}
