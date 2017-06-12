#include "freetrackPrivatePCH.h"
#include "freetrackBPLibrary.h"

void* UfreetrackBPLibrary::DLLHandle;
FreeTrackData UfreetrackBPLibrary::data;
FreeTrackData* UfreetrackBPLibrary::pData;

typedef char*(*_FTProvider)(void);
typedef bool(*_FTGetData)(FreeTrackData * data);

UfreetrackBPLibrary::UfreetrackBPLibrary(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
{
	FString filePath;
	#if PLATFORM_64BITS
		filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("freetrack/"), TEXT("FreeTrackClient64.dll"));
	#else
		filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("freetrack/"), TEXT("FreeTrackClient.dll"));
	#endif
	
	if(!FPaths::FileExists(filePath))
	{
		UE_LOG(LogTemp, Fatal, TEXT("%s not found"), *filePath);
	}else{
		UE_LOG(LogTemp, Log, TEXT("loading freetrack"));
		DLLHandle = FPlatformProcess::GetDllHandle(*filePath);
		pData = &data;
	};
}


void UfreetrackBPLibrary::getFreetrackData(const float TranslationSensitivity, const float RotationSensitivity, FVector& translation, FRotator& rotation, bool& enabled){

	_FTGetData FTGetData = NULL;
	FString procName = "FTGetData";
	FTGetData = (_FTGetData)FPlatformProcess::GetDllExport(DLLHandle, *procName); // Export the DLL function.
	enabled=FTGetData(pData);
	translation = FVector(-data.z*TranslationSensitivity, -data.x*TranslationSensitivity, data.y*TranslationSensitivity);
	rotation = FRotator(-data.pitch*RotationSensitivity, -data.yaw * RotationSensitivity, -data.roll * RotationSensitivity);
};