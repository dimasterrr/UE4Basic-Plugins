#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableItem.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class DESTRUCTIVEFORCE_API UDraggableItem : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Components
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ObjectNameTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ObjectIconImage;

	// Settings
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Settings")
	FName ObjectName;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Settings")
	FText ObjectDescription;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Settings")
	UTexture2D* ObjectIcon;

protected:
	virtual void NativePreConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                              UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                          UDragDropOperation* InOperation) override;

	UFUNCTION()
	void RestoreWidgetStyles(UDragDropOperation* Operation);
};
