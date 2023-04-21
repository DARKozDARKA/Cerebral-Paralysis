// Cerebral Paralysis. All right reserved. 


#include "UI/CPGameHUD.h"

#include "Blueprint/UserWidget.h"

void ACPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (!PlayerHudWidget)
		return;

	PlayerHudWidget->AddToViewport();
}
