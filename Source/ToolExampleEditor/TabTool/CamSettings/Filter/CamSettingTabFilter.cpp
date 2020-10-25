#include "CamSettingTabFilter.h"

#include "CamSettingTabFilterObject.h"
#include "CineCameraActor.h"


TArray<FDetailsViewObjectRoot> CamSettingTabFilter::FilterObjects(const TArray<UObject*>& _sourceObjects)
{
	TArray<FDetailsViewObjectRoot> _toReturn = TArray<FDetailsViewObjectRoot>();
	UCamSettingTabFilterObject* _myFilter = NewObject<UCamSettingTabFilterObject>();
	
	if (_sourceObjects.Num() != 1)return _toReturn;

	ACineCameraActor* _myCamera = Cast<ACineCameraActor>(_sourceObjects[0]);
	if (!_myCamera) return _toReturn;

	//_myFilter->PostProcessSettings = _myCamera->GetCameraComponent()->PostProcessSettings;
///	_myCamera->GetCameraComponent()->PostProcessSettings = _myFilter->PostProcessSettings;
	//_myCamera->GetCameraComponent()->PostProcessSettings.BloomIntensity = 14;
	//_myCamera->GetCameraComponent()->PostProcessSettings.AmbientOcclusionBias = _myFilter->PostProcessSettings.AmbientOcclusionBias;



	
	FDetailsViewObjectRoot _rootObjectDetail = FDetailsViewObjectRoot();
	_rootObjectDetail.Objects.Add(_myFilter);
	_toReturn.Add(_rootObjectDetail);

	
	return _toReturn;
}
