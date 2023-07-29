#include "OrbSystemComponent.h"
#include "Help/OteOpenOrbSystemComponent.h"
#include "Help/Actions/OteTestAction.h"
#include "Help/OteTestActor.h"
#include "Help/Attributes/OteTestInputAttributeContainer.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

class UOteTestAction;
BEGIN_DEFINE_SPEC(FOrbSystemComponentTest, "Orburier.OrbSystemComponentTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UWorld* TestWorld;
	AOteTestActor* TestActor;
	UOteOpenOrbSystemComponent* Component;
END_DEFINE_SPEC(FOrbSystemComponentTest)

void FOrbSystemComponentTest::Define()
{
	BeforeEach([this]()
	{
		TestWorld = FAutomationEditorCommonUtils::CreateNewMap();
		TestActor = TestWorld->SpawnActor<AOteTestActor>();
		Component = static_cast<UOteOpenOrbSystemComponent*>(TestActor->OrbSystemComponent);
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

			It("should return valid handle when the action is granted", [this]()
			{
				const FOrbActionHandle handle = Component->GrantAction(TSubclassOf<UOteTestAction>(UOteTestAction::StaticClass()));

				TestTrue("Valid handle", handle.IsValid());
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

		Describe("Attributes", [this]()
		{
			It("should not have any by default", [this]()
			{
				const FOrbAttributeContainerArchetype* inputArchetype = Component->GetInputArchetype();
				const FOrbAttributeContainerArchetype* syncArchetype = Component->GetSyncArchetype();
				const FOrbAttributeContainerArchetype* auxArchetype = Component->GetAuxArchetype();

				TestNotNull("inputArchetype ptr", inputArchetype);
				TestNotNull("syncArchetype ptr", syncArchetype);
				TestNotNull("auxArchetype ptr", auxArchetype);
				TestEqual("inputArchetype num", inputArchetype->Num(), 0);
				TestEqual("syncArchetype num", syncArchetype->Num(), 0);
				TestEqual("auxArchetype num", auxArchetype->Num(), 0);
			});

			It("should have correctly typed archetypes", [this]()
			{
				const FOrbAttributeContainerArchetype* inputArchetype = Component->GetInputArchetype();
				const FOrbAttributeContainerArchetype* syncArchetype = Component->GetSyncArchetype();
				const FOrbAttributeContainerArchetype* auxArchetype = Component->GetAuxArchetype();

				TestEqual("inputArchetype num", inputArchetype->GetType(), EOrbAttributeContainerArchetypeType::Input);
				TestEqual("syncArchetype num", syncArchetype->GetType(), EOrbAttributeContainerArchetypeType::Sync);
				TestEqual("auxArchetype num", auxArchetype->GetType(), EOrbAttributeContainerArchetypeType::Aux);
			});
			
			It("ConfigureParticipants should configure the archetypes", [this]()
			{
				Component->CallConfigureParticipants();
				
				const FOrbAttributeContainerArchetype* inputArchetype = Component->GetInputArchetype();
				const FOrbAttributeContainerArchetype* syncArchetype = Component->GetSyncArchetype();
				const FOrbAttributeContainerArchetype* auxArchetype = Component->GetAuxArchetype();

				TestEqual("inputArchetype num", inputArchetype->Num(), 1);
				TestEqual("syncArchetype num", syncArchetype->Num(), 1);
				TestEqual("auxArchetype num", auxArchetype->Num(), 2);

				TestTrue("inputArchetype type", inputArchetype->Has(FOteTestInputAttributeContainer1::StaticStruct()));
				TestTrue("syncArchetype type", syncArchetype->Has(FOteTestSyncAttributeContainer1_1::StaticStruct()));
				TestTrue("auxArchetype type1", auxArchetype->Has(FOteTestAuxAttributeContainer1::StaticStruct()));
				TestTrue("auxArchetype type2", auxArchetype->Has(FOteTestAuxAttributeContainer2::StaticStruct()));
			});
		});
	});
}
