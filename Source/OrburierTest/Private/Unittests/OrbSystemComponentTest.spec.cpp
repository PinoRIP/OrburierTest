#include "OrbSystemComponent.h"
#include "Help/OteTestAction.h"
#include "Help/OteTestActor.h"
#include "Help/MyTestObject.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

class UOteTestAction;
BEGIN_DEFINE_SPEC(FOrbSystemComponentTest, "Orburier.OrbSystemComponentTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UWorld* TestWorld;
	AOteTestActor* TestActor;
	UOrbSystemComponent* Component;
END_DEFINE_SPEC(FOrbSystemComponentTest)

void FOrbSystemComponentTest::Define()
{
	TestWorld = FAutomationEditorCommonUtils::CreateNewMap();
	
	BeforeEach([this]()
	{
		TestActor = TestWorld->SpawnActor<AOteTestActor>();
		Component = TestActor->OrbSystemComponent;
	});

	Describe("OrbSystemComponent", [this]()
	{
		Describe("Actions", [this]()
		{
			It("should not have any by default", [this]()
			{
				int32 actionsCount = Component->GetGrantedActionCount();

				TestEqual("Actions count", actionsCount, 0);
			});

			It("should be added when granted", [this]()
			{
				Component->GrantAction(TSubclassOf<UOteTestAction>(UOteTestAction::StaticClass()));
				int32 actionsCount = Component->GetGrantedActionCount();
				TestEqual("Actions count", actionsCount, 1);
			});

			It("should not be grant able when the action is public", [this]()
			{
				Component->GrantAction(TSubclassOf<UOtePublicTestAction>(UOtePublicTestAction::StaticClass()));
				int32 actionsCount = Component->GetGrantedActionCount();
				TestEqual("Actions count", actionsCount, 0);
			});

			It("should invoke the callback after granting", [this]()
			{
				UMyTestObject* MyObject = NewObject<UMyTestObject>(TestWorld);
				FOrbActionGranted callbackDelegate;
				callbackDelegate.BindUFunction(MyObject, FName("SetHandle"));
				
				Component->GrantAction(TSubclassOf<UOteTestAction>(UOteTestAction::StaticClass()), callbackDelegate);

				TestTrue("Valid handle", MyObject->Handle.IsValid());
			});

			It("should be get able when granted", [this]()
			{
				Component->GrantAction(TSubclassOf<UOteTestAction>(UOteTestAction::StaticClass()));
				FOrbActionHandle handle = Component->GetActionHandle(TSubclassOf<UOteTestAction>(UOteTestAction::StaticClass()));
				TestTrue("Valid handle", handle.IsValid());
			});

			It("should get invalid handle when not granted", [this]()
			{
				FOrbActionHandle handle = Component->GetActionHandle(TSubclassOf<UOteTestAction>(UOteTestAction::StaticClass()));
				TestFalse("Valid handle", handle.IsValid());
			});
		});
	});
}
