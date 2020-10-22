// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestFilterUObject.generated.h"

/**
 * 
 */
UCLASS()
class TOOLEXAMPLEEDITOR_API UTestFilterUObject : public UObject
{
	GENERATED_BODY()
public:

	/** Indicates where to get the light contribution from. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Light)
	TEnumAsByte<enum ESkyLightSourceType> SourceType;

	/** Cubemap to use for sky lighting if SourceType is set to SLS_SpecifiedCubemap. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Light)
	class UTextureCube* Cubemap;

	/** Angle to rotate the source cubemap when SourceType is set to SLS_SpecifiedCubemap. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Light, meta = (UIMin = "0", UIMax = "360"))
	float SourceCubemapAngle;

	/** Maximum resolution for the very top processed cubemap mip. Must be a power of 2. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Light)
	int32 CubemapResolution;
};
