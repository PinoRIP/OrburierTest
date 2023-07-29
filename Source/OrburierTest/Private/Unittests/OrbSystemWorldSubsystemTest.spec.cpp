#include "OrbSystemWorldSubsystem.h"
#include "Help/Actions/OteGrantedAction.h"
#include "Help/Actions/OtePublicAction.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

BEGIN_DEFINE_SPEC(OrbSystemWorldSubsystemTest, "Orburier.OrbSystemWorldSubsystemTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UWorld* TestWorld;
END_DEFINE_SPEC(OrbSystemWorldSubsystemTest)

void OrbSystemWorldSubsystemTest::Define()
{
	BeforeEach([this]()
 	{
 		TestWorld = FAutomationEditorCommonUtils::CreateNewMap();
 	});

	Describe("OrbSystemWorldSubsystem", [this]()
	{
		It("GetSubsystem should return the subsystem", [this]()
		{
			const UOrbSystemWorldSubsystem* subsystem = TestWorld->GetSubsystem<UOrbSystemWorldSubsystem>();
			TestNotNull("Instance ptr", subsystem);
		});
		
		Describe("Actions", [this]()
		{
			It("GetPublicActionHandle should return a valid action handle given a public action is requested by UClass", [this]()
			{
				const UOrbSystemWorldSubsystem* subsystem = TestWorld->GetSubsystem<UOrbSystemWorldSubsystem>();
				FOrbActionHandle handle = subsystem->GetPublicActionHandle(UOtePublicAction::StaticClass());
				
				TestTrue("IsValid", handle.IsValid());
			});

			It("GetPublicActionHandle should return a valid action handle given a public action is requested by TSubclassOf", [this]()
			{
				const UOrbSystemWorldSubsystem* subsystem = TestWorld->GetSubsystem<UOrbSystemWorldSubsystem>();
				FOrbActionHandle handle = subsystem->GetPublicActionHandle(TSubclassOf<UOrbAction>(UOtePublicAction::StaticClass()));
				
				TestTrue("IsValid", handle.IsValid());
			});

			It("GetPublicActionHandle should return an invalid action handle given a granted action is requested by UClass", [this]()
			{
				const UOrbSystemWorldSubsystem* subsystem = TestWorld->GetSubsystem<UOrbSystemWorldSubsystem>();
				FOrbActionHandle handle = subsystem->GetPublicActionHandle(UOteGrantedAction::StaticClass());
				
				TestFalse("IsValid", handle.IsValid());
			});

			It("GetPublicActionHandle should return an invalid action handle given a granted action is requested by TSubclassOf", [this]()
			{
				const UOrbSystemWorldSubsystem* subsystem = TestWorld->GetSubsystem<UOrbSystemWorldSubsystem>();
				FOrbActionHandle handle = subsystem->GetPublicActionHandle(TSubclassOf<UOrbAction>(UOteGrantedAction::StaticClass()));
				
				TestFalse("IsValid", handle.IsValid());
			});

			It("GetPublicActionHandle should return an invalid action handle given an invalid type is requested by UClass", [this]()
			{
				const UOrbSystemWorldSubsystem* subsystem = TestWorld->GetSubsystem<UOrbSystemWorldSubsystem>();
				FOrbActionHandle handle = subsystem->GetPublicActionHandle(UOrbSystemWorldSubsystem::StaticClass());
				
				TestFalse("IsValid", handle.IsValid());
			});
		});
	});
}