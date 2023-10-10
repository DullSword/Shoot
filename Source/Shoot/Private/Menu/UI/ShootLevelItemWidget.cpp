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
		LevelSelectButton->OnHovered.AddDynamic(this, &UShootLevelItemWidget::OnLevelItemHovered);
		LevelSelectButton->OnUnhovered.AddDynamic(this, &UShootLevelItemWidget::OnLevelItemUnHovered);
	}
}

void UShootLevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}

void UShootLevelItemWidget::OnLevelItemHovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UShootLevelItemWidget::OnLevelItemUnHovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}
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
	if (LevelThumb)
	{
		LevelThumb->SetColorAndOpacity(bIsSelected ? FLinearColor::White : FLinearColor(.1f, .1f, .1f));
	}
}
