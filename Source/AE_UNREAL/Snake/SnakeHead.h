// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakePart.h"
#include "SnakeHead.generated.h"

UCLASS()
class AE_UNREAL_API ASnakeHead : public ASnakePart
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeHead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �𸮾��� �������Ʈ�� �����Ҽ� �ְ� �� �Լ��� ��Ͻ������ �մϴ�.
	// �������Ʈ�� �� c++�Լ��� �˼��ְ� �������� �Ѵ�.
	// �Լ��� ��쿡�� 

	// �� UFUNCTION �𸮾��� �ν��ϰ� ���ذ� ���̰�
	// �������� �� �Լ��� ��� ���ϰ����� () �־���� �մϴ�.



	UFUNCTION(BlueprintCallable)
	void LeftMove(float _Value);

	UFUNCTION(BlueprintCallable)
	void RightMove(float _Value);

	UFUNCTION(BlueprintCallable)
	void UpMove(float _Value);

	UFUNCTION(BlueprintCallable)
	void DownMove(float _Value);

	UFUNCTION(BlueprintCallable)
		void LeftAction();

	UFUNCTION(BlueprintCallable)
		void RightAction();

	UFUNCTION(BlueprintCallable)
		void UpAction();

	UFUNCTION(BlueprintCallable)
		void DownAction();

// LHE
public:
	AActor* myTail = nullptr;
	FVector tailBeforePosition;
	FVector headBeforePosition;

	UPROPERTY(Category = "Create Body", EditAnywhere, DisplayName = "�ٵ� ������Ʈ Ŭ����")
		TSubclassOf<AActor> BodyType;

	// snake ��ü ������ ��� TArray
	// Head ������ Body���� ���, ������ actor�� ������ �� �ִ� ������ Prev�� Next�� ����������Ѵ�
	TArray<AActor*> wholeSnake;
	AActor* Prev = nullptr;
	AActor* Next = nullptr;

	enum LastInputKey
	{
		Left,
		Right,
		Up,
		Down
	};
	LastInputKey lastInputKey;
};
