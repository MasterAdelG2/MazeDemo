// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeHUD.h"

// Called when the game starts or when spawned
void AMazeHUD::BeginPlay()
{
	Super::BeginPlay();
	//
	OnJoinServer();
}