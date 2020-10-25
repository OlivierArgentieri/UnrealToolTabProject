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
	/** Post process settings to use for this camera. Don't forget to check the properties you want to override */
	UPROPERTY(Interp, BlueprintReadWrite, Category = PostProcess, meta = (ShowOnlyInnerProperties))
	struct FPostProcessSettings PostProcessSettings;

};