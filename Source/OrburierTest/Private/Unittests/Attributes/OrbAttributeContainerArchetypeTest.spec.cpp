#include "Attributes/OrbAttributeContainerArchetype.h"
#include "Help/Attributes/OteTestInputAttributeContainer.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FOrbAttributeContainerArchetypeTest, "Orburier.Attributes.OrbAttributeContainerArchetypeTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	void ForArchetypeTypes(TFunction<void(EOrbAttributeContainerArchetypeType)> DoWork);
	const UScriptStruct* GetCorrectScriptStruct(EOrbAttributeContainerArchetypeType archetypeType);
	const UScriptStruct* GetCorrectScriptStruct2(EOrbAttributeContainerArchetypeType archetypeType);
	const UScriptStruct* GetCorrectScriptStructChild(EOrbAttributeContainerArchetypeType archetypeType);
	const UScriptStruct* GetWrongScriptStruct(EOrbAttributeContainerArchetypeType archetypeType);
	const UScriptStruct* GetWrongScriptStructChild(EOrbAttributeContainerArchetypeType archetypeType);
	FString GetArchetypeTypeName(EOrbAttributeContainerArchetypeType archetypeType);
END_DEFINE_SPEC(FOrbAttributeContainerArchetypeTest)

void FOrbAttributeContainerArchetypeTest::Define()
{
	Describe("OrbAttributeContainerArchetype", [this]()
	{
		It("should", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
			});
		});
		
		It("GetType should return Input given no type was set", [this]()
		{
			FOrbAttributeContainerArchetype archetype;

			EOrbAttributeContainerArchetypeType type = archetype.GetType();
			
			TestEqual("GetType", type, EOrbAttributeContainerArchetypeType::Input);
		});

		It("Num should return 0 given the archetype is has no containers", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);

				int32 count = archetype.Num();
				
				TestEqual(GetArchetypeTypeName(archetypeType) + "Num", count, 0);
			});
		});

		It("Num should return 1 given the archetype is based on one struct", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType, 1);

				int32 count = archetype.Num();
			
				TestEqual(GetArchetypeTypeName(archetypeType) + "Num", count, 1);
			});
		});

		It("Change should change the archetype given the attribute container was not already part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				FOrbAttributeContainerArchetypeId prevId = archetype.GetId();

				archetype.Change(GetCorrectScriptStruct(archetypeType));
				
				TestNotEqual(GetArchetypeTypeName(archetypeType) + "GetId", archetype.GetId(), prevId);
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetCorrectScriptStruct(archetypeType)), true);
			});
		});

		It("Change should not change the archetype given the attribute container is already part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				archetype.Change(GetCorrectScriptStruct(archetypeType));
				
				FOrbAttributeContainerArchetypeId prevId = archetype.GetId();

				archetype.Change(GetCorrectScriptStruct(archetypeType));
				
				TestEqual(GetArchetypeTypeName(archetypeType) + "GetId", archetype.GetId(), prevId);
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetCorrectScriptStruct(archetypeType)), true);
			});
		});

		It("Change should not change the archetype given the attribute container is of the wrong type", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				FOrbAttributeContainerArchetypeId prevId = archetype.GetId();

				archetype.Change(GetWrongScriptStruct(archetypeType));
				
				TestEqual(GetArchetypeTypeName(archetypeType) + "GetId", archetype.GetId(), prevId);
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetWrongScriptStruct(archetypeType)), false);
			});
		});

		It("Change should swap out attribute containers given a child of an already added container is added", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				
				archetype.Change(GetCorrectScriptStruct(archetypeType));
				FOrbAttributeContainerArchetypeId prevId = archetype.GetId();
				
				archetype.Change(GetCorrectScriptStructChild(archetypeType));

				
				TestNotEqual(GetArchetypeTypeName(archetypeType) + "GetId", archetype.GetId(), prevId);
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has parent explicit", archetype.Has(GetCorrectScriptStruct(archetypeType), true), false);
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has child", archetype.Has(GetCorrectScriptStructChild(archetypeType)), true);
			});
		});

		It("Has should return true given the attribute container is part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);

				archetype.Change(GetCorrectScriptStruct(archetypeType));
				
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetCorrectScriptStruct(archetypeType)), true);
			});
		});

		It("Has should return false given the attribute container is not part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetCorrectScriptStruct(archetypeType)), false);
			});
		});

		It("Has should return true given a child attribute container to the checked type is part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);

				archetype.Change(GetCorrectScriptStructChild(archetypeType));
				
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetCorrectScriptStruct(archetypeType)), true);
			});
		});

		It("Has should return false given a child attribute container to the checked type is part of the archetype and explicitly is true", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);

				archetype.Change(GetCorrectScriptStructChild(archetypeType));
				
				TestEqual(GetArchetypeTypeName(archetypeType) + "Has", archetype.Has(GetCorrectScriptStruct(archetypeType), true), false);
			});
		});

		It("AllocateInstanceData should allocate memory for the data of the the AttributeContainerArchetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				archetype.Change(GetCorrectScriptStructChild(archetypeType));
				archetype.Change(GetCorrectScriptStruct2(archetypeType));

				auto ptr = archetype.AllocateInstanceData();
				
				TestNotNull(GetArchetypeTypeName(archetypeType) + "Ptr", ptr);

				archetype.DisposeInstanceData(ptr);
			});
		});

		It("GetStruct should use given data ptrs to access the attribute containers", [this]()
		{
			int32 a = 0;
			int32 b = 12;
			int32 c = 1212;
			int32 d = 121212;
			int32 e = 121212;
			int32 f = 121212;
			FVector g = FVector(123, 123, 123);
			
			FOrbAttributeContainerArchetype archetype;
			archetype.Change(FOteTestInputAttributeContainer1_1::StaticStruct());
			archetype.Change(FOteTestInputAttributeContainer2::StaticStruct());

			auto ptr = archetype.AllocateInstanceData();

			FOteTestInputAttributeContainer1_1* structData1 = archetype.GetStruct<FOteTestInputAttributeContainer1_1>(ptr);
			structData1->A = a;
			structData1->B = b;
			structData1->C = c;
			structData1->D = d;

			FOteTestInputAttributeContainer2* structData2 = archetype.GetStruct<FOteTestInputAttributeContainer2>(ptr);
			structData2->E = e;
			structData2->F = f;
			structData2->G = g;

			void* testData = FMemory::MallocZeroed(12);

			FOteTestInputAttributeContainer1_1* structData1_next = archetype.GetStruct<FOteTestInputAttributeContainer1_1>(ptr);
			FOteTestInputAttributeContainer2* structData2_next = archetype.GetStruct<FOteTestInputAttributeContainer2>(ptr);

			TestEqual("A", structData1_next->A, a);
			TestEqual("B", structData1_next->B, b);
			TestEqual("C", structData1_next->C, c);
			TestEqual("D", structData1_next->D, d);
			TestEqual("E", structData2_next->E, e);
			TestEqual("F", structData2_next->F, f);
			TestEqual("G", structData2_next->G, g);

			archetype.DisposeInstanceData(ptr);
			FMemory::Free(testData);
		});

		It("GetStruct should return nullptr given the passed struct is not part of the archetype", [this]()
		{
			FOrbAttributeContainerArchetype archetype;
			archetype.Change(FOteTestInputAttributeContainer2::StaticStruct());

			auto ptr = archetype.AllocateInstanceData();

			FOteTestInputAttributeContainer1* actual = archetype.GetStruct<FOteTestInputAttributeContainer1>(ptr);

			TestNull("Ptr", actual);

			archetype.DisposeInstanceData(ptr);
		});

		It("GetStruct should return nullptr given the passed index is less than 0", [this]()
		{
			FOrbAttributeContainerArchetype archetype;
			archetype.Change(FOteTestInputAttributeContainer1::StaticStruct());

			auto ptr = archetype.AllocateInstanceData();

			FOteTestInputAttributeContainer1* actual = archetype.GetStruct<FOteTestInputAttributeContainer1>(ptr, -1);

			TestNull("Ptr", actual);

			archetype.DisposeInstanceData(ptr);
		});

		It("GetStruct should return nullptr given the passed index is out of range", [this]()
		{
			FOrbAttributeContainerArchetype archetype;
			archetype.Change(FOteTestInputAttributeContainer1::StaticStruct());

			auto ptr = archetype.AllocateInstanceData();

			FOteTestInputAttributeContainer1* actual = archetype.GetStruct<FOteTestInputAttributeContainer1>(ptr, archetype.Num());

			TestNull("Ptr", actual);

			archetype.DisposeInstanceData(ptr);
		});

		It("GetStructIndex should return the attribute container struct index given it is part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				archetype.Change(GetCorrectScriptStruct(archetypeType));

				int32 actual = archetype.GetStructIndex(GetCorrectScriptStruct(archetypeType) );

				TestEqual("Index", actual, 0);
			});
		});

		It("GetStructIndex should return -1 given the attribute container struct is not part of the archetype", [this]()
		{
			ForArchetypeTypes([this](EOrbAttributeContainerArchetypeType archetypeType)
			{
				FOrbAttributeContainerArchetype archetype(archetypeType);
				archetype.Change(GetCorrectScriptStruct(archetypeType));

				int32 actual = archetype.GetStructIndex(GetCorrectScriptStruct2(archetypeType));

				TestEqual("Index", actual, -1);
			});
		});
	});
}

void FOrbAttributeContainerArchetypeTest::ForArchetypeTypes(TFunction<void(EOrbAttributeContainerArchetypeType)> DoWork)
{
	DoWork(EOrbAttributeContainerArchetypeType::Input);
	DoWork(EOrbAttributeContainerArchetypeType::Sync);
	DoWork(EOrbAttributeContainerArchetypeType::Aux);
}

const UScriptStruct* FOrbAttributeContainerArchetypeTest::GetCorrectScriptStruct(EOrbAttributeContainerArchetypeType archetypeType)
{
	switch (archetypeType)
	{
	case EOrbAttributeContainerArchetypeType::Input: return FOteTestInputAttributeContainer1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Sync: return FOteTestSyncAttributeContainer1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Aux: return FOteTestAuxAttributeContainer1::StaticStruct();
	default: return nullptr;
	}
}

const UScriptStruct* FOrbAttributeContainerArchetypeTest::GetCorrectScriptStruct2(EOrbAttributeContainerArchetypeType archetypeType)
{
	switch (archetypeType)
	{
	case EOrbAttributeContainerArchetypeType::Input: return FOteTestInputAttributeContainer2::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Sync: return FOteTestSyncAttributeContainer2::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Aux: return FOteTestAuxAttributeContainer2::StaticStruct();
	default: return nullptr;
	}
}

const UScriptStruct* FOrbAttributeContainerArchetypeTest::GetCorrectScriptStructChild(EOrbAttributeContainerArchetypeType archetypeType)
{
	switch (archetypeType)
	{
	case EOrbAttributeContainerArchetypeType::Input: return FOteTestInputAttributeContainer1_1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Sync: return FOteTestSyncAttributeContainer1_1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Aux: return FOteTestAuxAttributeContainer1_1::StaticStruct();
	default: return nullptr;
	}
}

const UScriptStruct* FOrbAttributeContainerArchetypeTest::GetWrongScriptStruct(EOrbAttributeContainerArchetypeType archetypeType)
{
	switch (archetypeType)
	{
	case EOrbAttributeContainerArchetypeType::Input: return FOteTestAuxAttributeContainer1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Sync: return FOteTestInputAttributeContainer1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Aux: return FOteTestSyncAttributeContainer1::StaticStruct();
	default: return nullptr;
	}
}

const UScriptStruct* FOrbAttributeContainerArchetypeTest::GetWrongScriptStructChild(EOrbAttributeContainerArchetypeType archetypeType)
{
	switch (archetypeType)
	{
	case EOrbAttributeContainerArchetypeType::Input: return FOteTestAuxAttributeContainer1_1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Sync: return FOteTestInputAttributeContainer1_1::StaticStruct();
	case EOrbAttributeContainerArchetypeType::Aux: return FOteTestSyncAttributeContainer1_1::StaticStruct();
	default: return nullptr;
	}
}

FString FOrbAttributeContainerArchetypeTest::GetArchetypeTypeName(EOrbAttributeContainerArchetypeType archetypeType)
{
	switch (archetypeType)
	{
	case EOrbAttributeContainerArchetypeType::Input: return "Input ";
	case EOrbAttributeContainerArchetypeType::Sync: return "Sync ";
	case EOrbAttributeContainerArchetypeType::Aux: return "Aux ";
	default: return "ERROR";
	}
}
