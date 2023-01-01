#include "OrbSystemComponent.h"
#include "Help/MyTestAction.h"
#include "Help/MyTestActor.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

class UMyTestAction;
BEGIN_DEFINE_SPEC(FOrbSystemComponentTest, "Orburier.OrbSystemComponentTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UWorld* TestWorld;
	AMyTestActor* TestActor;
	UOrbSystemComponent* Component;
END_DEFINE_SPEC(FOrbSystemComponentTest)

void FOrbSystemComponentTest::Define()
{
	TestWorld = FAutomationEditorCommonUtils::CreateNewMap();
	
	BeforeEach([this]()
	{
		TestActor = TestWorld->SpawnActor<AMyTestActor>();
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
				Component->GrantAction(TSubclassOf<UMyTestAction>(UMyTestAction::StaticClass()));
				int32 actionsCount = Component->GetGrantedActionCount();
				TestEqual("Actions count", actionsCount, 1);
			});

			It("should not be grant able when the action is public", [this]()
			{
				Component->GrantAction(TSubclassOf<UMyPublicTestAction>(UMyPublicTestAction::StaticClass()));
				int32 actionsCount = Component->GetGrantedActionCount();
				TestEqual("Actions count", actionsCount, 0);
			});
		});
	});
}
