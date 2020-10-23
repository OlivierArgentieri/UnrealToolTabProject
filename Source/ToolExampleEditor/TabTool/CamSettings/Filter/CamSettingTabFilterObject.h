#pragma once

#include "CoreMinimal.h"

#include "CineCameraComponent.h"
#include "UObject/NoExportTypes.h"
#include "CamSettingTabFilterObject.generated.h"


UCLASS()
class TOOLEXAMPLEEDITOR_API UCamSettingTabFilterObject : public UObject
{
	GENERATED_BODY()


public:
	/** Controls the camera's lens. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")
	FCameraLensSettings LensSettings;

	/** Controls the camera's focus. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Camera Settings")
	FCameraFocusSettings FocusSettings;


};