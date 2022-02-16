#include "UI/MediaBrowseWidget.h"

#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"

void UMediaBrowseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BrowseButton)
	{
		BrowseButton->OnPressed.AddDynamic(this, &UMediaBrowseWidget::OnButtonPressed);
	}

	if (MediaPlayer)
	{
		MediaPlayer->OnMediaOpened.AddDynamic(this, &UMediaBrowseWidget::OnMediaOpened);
	}

	if (Material)
	{
		MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Material);
	}
}

void UMediaBrowseWidget::OnButtonPressed()
{
	if (!MediaPlayer) return;

	TArray<FString> OutFilePaths;

	if (const auto DesktopPlatform = FDesktopPlatformModule::Get())
	{
		const auto FileTypes = "All Files(*.PNG; *.JPG; *.MP4)|*.PNG; *.JPG; *.MP4|"
			"Images(*.PNG; *.JPG)|*.PNG; *.JPG|"
			"Video(*.MP4)|*.MP4";

		DesktopPlatform->OpenFileDialog(FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
		                                "Select Content",
		                                FPaths::GameSourceDir(),
		                                "",
		                                FileTypes,
		                                0,
		                                OutFilePaths);
	}

	if (OutFilePaths.Num() <= 0) return;

	// Close prev content
	MediaPlayer->Close();

	const auto TargetPath = OutFilePaths.Top();
	
	if (TargetPath.EndsWith(".JPG") || TargetPath.EndsWith(".PNG"))
	{
		const auto TargetImage = UKismetRenderingLibrary::ImportFileAsTexture2D(this, TargetPath);
		if (!TargetImage) return;

		MaterialInstanceDynamic->SetTextureParameterValue("Texture", TargetImage);
		MaterialInstanceDynamic->SetScalarParameterValue("IsVideo", 0);
		RenderImage->SetBrushFromMaterial(MaterialInstanceDynamic);

		const auto ContentSize = FVector2D(TargetImage->GetSizeX(), TargetImage->GetSizeY());
		RenderImage->SetBrushSize(ContentSize);

		UE_LOG(LogTemp,Warning,TEXT("ContentSize = %s"), *ContentSize.ToString());
	}
	else if (TargetPath.EndsWith(".MP4"))
	{
		const auto MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = TargetPath;
		MediaPlayer->OpenSource(MediaSource);

		const auto SoundComponent = NewObject<UMediaSoundComponent>(GetOwningPlayerPawn());
		SoundComponent->SetMediaPlayer(MediaPlayer);
		SoundComponent->RegisterComponent();

		MaterialInstanceDynamic->SetTextureParameterValue("Texture", nullptr);
		MaterialInstanceDynamic->SetScalarParameterValue("IsVideo", 1);
		RenderImage->SetBrushFromMaterial(MaterialInstanceDynamic);
	}
}

void UMediaBrowseWidget::OnMediaOpened(FString Path)
{
	if (!MediaPlayer || !RenderImage) return;

	const auto ContentDimensions = MediaPlayer->GetVideoTrackDimensions(INDEX_NONE, INDEX_NONE);
	const auto ContentSize = FVector2D(ContentDimensions.X, ContentDimensions.Y);
	RenderImage->SetBrushSize(ContentSize);
	
	UE_LOG(LogTemp,Warning,TEXT("ContentSize = %s"), *ContentSize.ToString());
}
