#include "CamSettingTabFilter.h"

#include "CamSettingTabFilterObject.h"
#include "CineCameraActor.h"


TArray<FDetailsViewObjectRoot> CamSettingTabFilter::FilterObjects(const TArray<UObject*>& _sourceObjects)
{
	TArray<FDetailsViewObjectRoot> _toReturn = TArray<FDetailsViewObjectRoot>();

	UCamSettingTabFilterObject* _myFilter = NewObject<UCamSettingTabFilterObject>();

	FDetailsViewObjectRoot _rootObjectDetail = FDetailsViewObjectRoot();
	_rootObjectDetail.Objects.Add(_myFilter);
	_toReturn.Add(_rootObjectDetail);
	
	return _toReturn;
}
