#include "UI/Widgets/OmegaUserWidget.h"



void UOmegaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;

	// Call the related logic on a blueprint
	OnWidgetControllerSet();
}
