#include "Misc/AutomationTest.h"
#include "Utils/OrbStructReferencerFunctionLibrary.h"
#include "Help/MyTestStructReferencer.h"


BEGIN_DEFINE_SPEC(FOrbStructReferencerFunctionLibraryTests, "Orburier.Utils.FOrbStructReferencerFunctionLibraryTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FOrbStructReferencerFunctionLibraryTests)



void FOrbStructReferencerFunctionLibraryTests::Define()
{
	It("Should read true booleans with GetBoolByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		bool result = false;
		Struct.BoolValue = true;
		UOrbStructReferencerFunctionLibrary::GetBoolByName(Referencer, FName("BoolValue"), result);

		TestTrue("Value get", result);
	});

	It("Should read false booleans with GetBoolByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		bool result = true;
		Struct.BoolValue = false;
		UOrbStructReferencerFunctionLibrary::GetBoolByName(Referencer, FName("BoolValue"), result);

		TestFalse("Value get", result);
	});

	It("Should set true booleans with SetBoolByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
				FMyTestStruct Struct;
				Referencer->Set(&Struct);
		
		bool result = false;
		UOrbStructReferencerFunctionLibrary::SetBoolByName(Referencer, FName("BoolValue"), true, result);

		TestTrue("Value set", Struct.BoolValue);
	});

	It("Should set false booleans with SetBoolByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		bool result = false;
		UOrbStructReferencerFunctionLibrary::SetBoolByName(Referencer, FName("BoolValue"), false, result);

		TestFalse("Value set", Struct.BoolValue);
	});

	
	It("Should read 22 floats with GetFloatByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		const float expected = 22.f;
		float result = 0.f;
		Struct.FloatValue = expected;
		UOrbStructReferencerFunctionLibrary::GetFloatByName(Referencer, FName("FloatValue"), result);

		TestEqual("Value get", result, expected);
	});

	It("Should read 626 floats with GetFloatByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		const float expected = 626.f;
		float result = 0.f;
		Struct.FloatValue = expected;
		UOrbStructReferencerFunctionLibrary::GetFloatByName(Referencer, FName("FloatValue"), result);

		TestEqual("Value get", result, expected);
	});

	It("Should set 22 floats with SetFloatByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		const float expected = 22.f;
		float result = 0.f;
		UOrbStructReferencerFunctionLibrary::SetFloatByName(Referencer, FName("FloatValue"), expected, result);

		TestEqual("Value set", Struct.FloatValue, expected);
		TestEqual("Value returns", result, expected);
	});

	It("Should set 626 floats with SetFloatByName", [this]()
	{
		auto Referencer = NewObject<UMyTestStructReferencer>();
		FMyTestStruct Struct;
		Referencer->Set(&Struct);
		
		const float expected = 626.f;
		float result = 0.f;
		UOrbStructReferencerFunctionLibrary::SetFloatByName(Referencer, FName("FloatValue"), expected, result);

		TestEqual("Value set", Struct.FloatValue, expected);
		TestEqual("Value returns", result, expected);
	});
}