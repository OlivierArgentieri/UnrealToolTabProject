#include "CamSettingTabFilter.h"

#include "CamSettingTabFilterObject.h"


TArray<FDetailsViewObjectRoot> CamSettingTabFilter::FilterObjects(const TArray<UObject*>& SourceObjects)
{
	TArray<FDetailsViewObjectRoot> _toReturn = TArray<FDetailsViewObjectRoot>();
	UCamSettingTabFilterObject* MyFilter = NewObject<UCamSettingTabFilterObject>();


	return _toReturn;
}
