#pragma once
#include "Engine.h"
#include "freetrackBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

typedef struct
{
	unsigned long int dataID;
	long int camWidth;
	long int camHeight;

	float yaw;
	float pitch;
	float roll;
	float x;
	float y;
	float z;

	float rawyaw;
	float rawpitch;
	float rawroll;
	float rawx;
	float rawy;
	float rawz;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;
}FreeTrackData;

UCLASS()
class UfreetrackBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	static void* DLLHandle;
	static FreeTrackData data;
	static FreeTrackData *pData;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "get Freetrack Data", Keywords = "freetrack get data"), Category = "freetrack")
		static void getFreetrackData(const float TranslationSensitivity, const float RotationSensitivity, FVector& translation, FRotator& rotation, bool& enabled);
};