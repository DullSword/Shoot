// Shoot Game. All Rights Reserved.

#include "Menu/UI/ShootLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UShootLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UShootLevelItemWidget::OnLevelItemClicked);
	}
}

void UShootLevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}

void UShootLevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if (LevelThumb)
	{
		LevelThumb->SetBrushFromTexture(Data.LevelThumbnail);
	}
}

void UShootLevelItemWidget::SetSelected(bool bIsSelected)
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
