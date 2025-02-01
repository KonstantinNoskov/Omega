// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibraries/OmegaFunctionLibrary.h"

#include "PaperSprite.h"

FVector2D UOmegaFunctionLibrary::GetSourceSize(UPaperSprite* Sprite)
{
	return Sprite->GetSourceSize();
}
