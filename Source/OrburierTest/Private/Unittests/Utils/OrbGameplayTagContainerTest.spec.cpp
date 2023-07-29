#include "Misc/AutomationTest.h"
#include "NativeGameplayTags.h"
#include "Utils/OrbGameplayTagContainer.h"

static FNativeGameplayTag TagMain("OrburierTest", "OrburierTest", "Test", TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD);
static FNativeGameplayTag TagBase("OrburierTest", "OrburierTest", "Test.Tag", TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD);
static FNativeGameplayTag TagName1("OrburierTest", "OrburierTest", "Test.Tag.1", TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD);
static FNativeGameplayTag TagName2("OrburierTest", "OrburierTest", "Test.Tag.2", TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD);
static FNativeGameplayTag TagName3("OrburierTest", "OrburierTest", "Test.Tag.3", TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD);
static FNativeGameplayTag TagName4("OrburierTest", "OrburierTest", "Test.Tag.4", TEXT(""), ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD);

BEGIN_DEFINE_SPEC(FOrbGameplayTagContainerTest, "Orburier.Utils.OrbGameplayTagContainerTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FOrbGameplayTagContainerTest)

void FOrbGameplayTagContainerTest::Define()
{
	It("Should succeed if containers start empty", [this]()
	{
		const FOrbGameplayTagContainer TagContainer1;
		TestTrue("IsEmpty", TagContainer1.IsEmpty());
	});
	
	It("Should succeed if containers are assigned", [this]()
	{
		FOrbGameplayTagContainer tagContainer1;
		tagContainer1.AddTag(TagName1);
		tagContainer1.AddTag(TagName2);
		tagContainer1.AddTag(TagName1);

		FOrbGameplayTagContainer tagContainer2 = tagContainer1;

		TestTrue("==", tagContainer1 == tagContainer2);
	});
	
	It("Should succeed if two empty containers are being compared", [this]()
	{
		const FOrbGameplayTagContainer tagContainer1;
		const FOrbGameplayTagContainer tagContainer2;
		TestTrue("==", tagContainer1 == tagContainer2);
		TestFalse("!=", tagContainer1 != tagContainer2);
	});
	
	It("Should succeed if tags can be added", [this]()
	{
		FOrbGameplayTagContainer TagContainer1;
		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName3);

		TestEqual("Has all TagContainer3", TagContainer1.Num(), 4);
		TestEqual("Has all TagContainer3", TagContainer1.NumExact(), 2);
	});

	It("Should succeed if the number of added tag-types gets tracked correctly", [this]()
	{
		FOrbGameplayTagContainer TagContainer1;
		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName3);

		TestEqual("Has implicit & explicit", TagContainer1.Num(), 4);
		TestEqual("Has explicit", TagContainer1.NumExact(), 2);

		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName2);

		TestEqual("Has implicit & explicit after adding more", TagContainer1.Num(), 5);
		TestEqual("Has explicit after adding more", TagContainer1.NumExact(), 3);

		TagContainer1.RemoveTag(TagName4);

		TestEqual("Has implicit & explicit after removing not contained", TagContainer1.Num(), 5);
		TestEqual("Has explicit after removing not contained", TagContainer1.NumExact(), 3);

		TagContainer1.RemoveTag(TagName1);
		
		TestEqual("Has implicit & explicit after removing double", TagContainer1.Num(), 5);
		TestEqual("Has explicit after removing double", TagContainer1.NumExact(), 3);
		
		TagContainer1.RemoveTag(TagName1);
		TagContainer1.RemoveTag(TagName3);
		TagContainer1.RemoveTag(TagName2);
		
		TestEqual("Has implicit & explicit after removing all", TagContainer1.Num(), 0);
		TestEqual("Has explicit after removing all", TagContainer1.NumExact(), 0);
	});

	It("Should succeed if tags can be removed", [this]()
	{
		FOrbGameplayTagContainer TagContainer1;
		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName3);
		
		TagContainer1.RemoveTag(TagName3);

		TestEqual("Has all TagContainer3", TagContainer1.NumExact(), 1);
		TestEqual("Has all TagContainer3", TagContainer1.Num(), 3);
	});

	It("Should succeed if two equally filled containers are being compared", [this]()
	{
		FOrbGameplayTagContainer tagContainer1;
		tagContainer1.AddTag(TagName1);
		tagContainer1.AddTag(TagName2);
		tagContainer1.AddTag(TagName1);
		
		FOrbGameplayTagContainer tagContainer2;
		tagContainer2.AddTag(TagName1);
		tagContainer2.AddTag(TagName1);
		tagContainer2.AddTag(TagName2);
		
		TestTrue("==", tagContainer1 == tagContainer2);
		TestFalse("!=", tagContainer1 != tagContainer2);
	});

	It("Should succeed if two differently filled containers are being compared", [this]()
	{
		FOrbGameplayTagContainer tagContainer1;
		tagContainer1.AddTag(TagName1);
		tagContainer1.AddTag(TagName2);
		tagContainer1.AddTag(TagName3);
	
		FOrbGameplayTagContainer tagContainer2;
		tagContainer2.AddTag(TagName1);
		tagContainer2.AddTag(TagName1);
		tagContainer2.AddTag(TagName2);
	
		TestFalse("==", tagContainer1 == tagContainer2);
		TestTrue("!=", tagContainer1 != tagContainer2);
	});

	It("Should succeed if the container has added the tag", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);

		TestTrue("HasTagExact", tagContainer.HasTagExact(TagName1));
		TestTrue("HasTag Parent", tagContainer.HasTag(TagBase));
		TestTrue("HasTag Parent Parent", tagContainer.HasTag(TagMain));
		TestFalse("IsEmpty", tagContainer.IsEmpty());
	});

	It("Should succeed if the container has the added tag AND parent tags in counting", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);

		TestEqual("Num before adding more", tagContainer.Num(), 3);

		tagContainer.AddTag(TagName2);
		
		TestEqual("Num after new tag is added", tagContainer.Num(), 4);
	});

	It("Should succeed if the container has the added the tag the right amount of times (??WORDING)", [this]()
	{
		FOrbGameplayTagContainer TagContainer;
		TagContainer.AddTag(TagName1);

		TestEqual("Num before adding more", TagContainer.Num(TagName1), 1);
		TestEqual("Num before adding more", TagContainer.Num(TagBase), 1);
		TestEqual("NumExact before adding more", TagContainer.NumExact(TagName1), 1);
		TestEqual("NumExact before adding more", TagContainer.NumExact(TagBase), 0);

		TagContainer.AddTag(TagName2);
		TagContainer.AddTag(TagName1);
		
		TestEqual("Num after adding more", TagContainer.Num(TagName1), 2);
		TestEqual("Num after adding more", TagContainer.Num(TagName2), 1);
		TestEqual("Num after adding more", TagContainer.Num(TagBase), 3);
		TestEqual("NumExact after adding more", TagContainer.NumExact(TagName1), 2);
		TestEqual("NumExact after adding more", TagContainer.Num(TagName2), 1);
		TestEqual("NumExact after adding more", TagContainer.NumExact(TagBase), 0);
	});
	
	It("Should succeed if the container handles IsValid & IsEmpty right...", [this]()
	{
		FOrbGameplayTagContainer TagContainer;

		TestFalse("IsValid when empty", TagContainer.IsValid());
		TestTrue("IsEmpty when empty", TagContainer.IsEmpty());

		TagContainer.AddTag(TagName1);

		TestTrue("IsValid when filled", TagContainer.IsValid());
		TestFalse("IsEmpty when filled", TagContainer.IsEmpty());
		
		TagContainer.Reset();

		TestFalse("IsValid when empty again", TagContainer.IsValid());
		TestTrue("IsEmpty when empty again", TagContainer.IsEmpty());
	});

	It("Should succeed if the container can check if it has tags", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName3);

		TestTrue("HasTag 1", tagContainer.HasTag(TagName1));
		TestTrue("HasTag 3", tagContainer.HasTag(TagName3));
		TestTrue("HasTag Base", tagContainer.HasTag(TagBase));
		TestTrue("HasTag Main", tagContainer.HasTag(TagMain));
		TestFalse("HasTag 2", tagContainer.HasTag(TagName2));

		TestTrue("HasTagExact 1", tagContainer.HasTagExact(TagName1));
		TestTrue("HasTagExact 3", tagContainer.HasTagExact(TagName3));
		TestFalse("HasTagExact Base", tagContainer.HasTagExact(TagBase));
		TestFalse("HasTagExact Main", tagContainer.HasTagExact(TagMain));
		TestFalse("HasTagExact 2", tagContainer.HasTagExact(TagName2));
	});

	It("Should succeed if the container has any of the FGameplayTagContainer tags", [this]()
	{
		FGameplayTagContainer container1;
		container1.AddTag(TagName1);
		container1.AddTag(TagName2);
		
		FGameplayTagContainer container2;
		container2.AddTag(TagName3);
		container2.AddTag(TagName4);
		
		FGameplayTagContainer container3;
		container3.AddTag(TagBase);
		container3.AddTag(TagName4);
		
		FGameplayTagContainer container4;
		container4.AddTag(TagName2);
		container4.AddTag(TagName4);
		
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName3);

		TestTrue("HasAny", tagContainer.HasAny(container1));
		TestTrue("HasAny", tagContainer.HasAny(container2));
		TestTrue("HasAny", tagContainer.HasAny(container3));
		TestFalse("HasAny", tagContainer.HasAny(container4));

		TestTrue("HasAnyExact", tagContainer.HasAnyExact(container1));
		TestTrue("HasAnyExact", tagContainer.HasAnyExact(container2));
		TestFalse("HasAnyExact", tagContainer.HasAnyExact(container3));
		TestFalse("HasAnyExact", tagContainer.HasAnyExact(container4));
	});

	It("Should succeed if the container has any of the FOrbGameplayTagContainer tags", [this]()
	{
		FOrbGameplayTagContainer container1;
		container1.AddTag(TagName1);
		container1.AddTag(TagName2);
		
		FOrbGameplayTagContainer container2;
		container2.AddTag(TagName3);
		container2.AddTag(TagName4);
		
		FOrbGameplayTagContainer container3;
		container3.AddTag(TagBase);
		container3.AddTag(TagName4);
		
		FOrbGameplayTagContainer container4;
		container4.AddTag(TagName2);
		container4.AddTag(TagName4);
		
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName3);

		TestTrue("HasAny", tagContainer.HasAny(container1));
		TestTrue("HasAny", tagContainer.HasAny(container2));
		TestTrue("HasAny", tagContainer.HasAny(container3));
		TestFalse("HasAny", tagContainer.HasAny(container4));

		TestTrue("HasAnyExact", tagContainer.HasAnyExact(container1));
		TestTrue("HasAnyExact", tagContainer.HasAnyExact(container2));
		TestFalse("HasAnyExact", tagContainer.HasAnyExact(container3));
		TestFalse("HasAnyExact", tagContainer.HasAnyExact(container4));
	});

	It("Should succeed if the container has all of the FGameplayTagContainer tags", [this]()
	{
		FGameplayTagContainer container1;
		container1.AddTag(TagName1);
		container1.AddTag(TagName3);
		
		FGameplayTagContainer container2;
		container2.AddTag(TagBase);
		container2.AddTag(TagName3);
		
		FGameplayTagContainer container3;
		container3.AddTag(TagBase);
		container3.AddTag(TagName2);
		
		FGameplayTagContainer container4;
		container4.AddTag(TagName2);
		container4.AddTag(TagName4);
		
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName3);

		TestTrue("HasAll", tagContainer.HasAll(container1));
		TestTrue("HasAll", tagContainer.HasAll(container2));
		TestFalse("HasAll", tagContainer.HasAll(container3));
		TestFalse("HasAll", tagContainer.HasAll(container4));

		TestTrue("HasAllExact", tagContainer.HasAllExact(container1));
		TestFalse("HasAllExact", tagContainer.HasAllExact(container2));
		TestFalse("HasAllExact", tagContainer.HasAllExact(container3));
		TestFalse("HasAllExact", tagContainer.HasAllExact(container4));
	});

	It("Should succeed if the container has all of the FOrbGameplayTagContainer tags", [this]()
	{
		FOrbGameplayTagContainer container1;
		container1.AddTag(TagName1);
		container1.AddTag(TagName3);
		
		FOrbGameplayTagContainer container2;
		container2.AddTag(TagBase);
		container2.AddTag(TagName3);
		
		FOrbGameplayTagContainer container3;
		container3.AddTag(TagBase);
		container3.AddTag(TagName2);
		
		FOrbGameplayTagContainer container4;
		container4.AddTag(TagName2);
		container4.AddTag(TagName4);
		
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName3);

		TestTrue("HasAll", tagContainer.HasAll(container1));
		TestTrue("HasAll", tagContainer.HasAll(container2));
		TestFalse("HasAll", tagContainer.HasAll(container3));
		TestFalse("HasAll", tagContainer.HasAll(container4));

		TestTrue("HasAllExact", tagContainer.HasAllExact(container1));
		TestFalse("HasAllExact", tagContainer.HasAllExact(container2));
		TestFalse("HasAllExact", tagContainer.HasAllExact(container3));
		TestFalse("HasAllExact", tagContainer.HasAllExact(container4));
	});

	It("Should succeed if container can be appended", [this]()
	{
		FOrbGameplayTagContainer TagContainer1;
		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName3);

		FOrbGameplayTagContainer TagContainer2;
		TagContainer2.AddTag(TagName1);
		TagContainer2.AddTag(TagName2);

		TagContainer1.AppendTags(TagContainer2);
		
		TestTrue("Has all TagContainer2", TagContainer1.HasAll(TagContainer2));

		FGameplayTagContainer TagContainer3;
		TagContainer3.AddTag(TagName3);
		TagContainer3.AddTag(TagName4);

		TagContainer1.AppendTags(TagContainer3);

		TestTrue("Has all TagContainer3", TagContainer1.HasAll(TagContainer3));
	});

	It("Should succeed if tags can be removed with FOrbGameplayTagContainer", [this]()
	{
		FOrbGameplayTagContainer TagContainer1;
		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName1);
		TagContainer1.AddTag(TagName3);
	
		FOrbGameplayTagContainer TagContainer2;
		TagContainer2.AddTag(TagName1);
		TagContainer2.AddTag(TagName2);
		TagContainer2.AddTag(TagName3);

		TagContainer1.RemoveTags(TagContainer2);

		TestEqual("Has 1 Tag1 left", TagContainer1.Num(TagName1), 1);
		TestFalse("Doesn't have Tag3", TagContainer1.HasTag(TagName3));
		TestFalse("Doesn't have Tag2", TagContainer1.HasTag(TagName2));
	});
	
	It("Should succeed if the container can be emptied", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName2);
		tagContainer.AddTag(TagName3);
		tagContainer.Empty();

		TestTrue("IsEmpty", tagContainer.IsEmpty());
	});

	It("Should succeed if the container can be reset", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName2);
		tagContainer.AddTag(TagName3);
		tagContainer.PauseTagChangedEvent();
		tagContainer.OnTagCountChanged().AddLambda([this](const FGameplayTag& tag, int32 count) { });
		tagContainer.OnExactTagCountChanged().AddLambda([this](const FGameplayTag& tag, int32 count) { });

		tagContainer.Reset();

		TestTrue("IsEmpty", tagContainer.IsEmpty());
		TestFalse("Is the tag count changed event unpaused", tagContainer.IsChangedEventPaused());
		TestFalse("RegisterTagCountChanged IsBound", tagContainer.OnTagCountChanged().IsBound());
		TestFalse("RegisterExactTagCountChanged IsBound", tagContainer.OnExactTagCountChanged().IsBound());
	});

	It("Should succeed if the container can handle events", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		int32 TagCountChangedCalledCount = 0;
		int32 ExactTagCountChangedCalledCount = 0;
		
		tagContainer.OnTagCountChanged().AddLambda([this, &tagContainer, &TagCountChangedCalledCount](const FGameplayTag& tag, int32 count)
		{
			TagCountChangedCalledCount++;
			
			if(tag == TagName1)
			{
				TestEqual("Add Event Tag is Right TagName1 -" + FString::FromInt(TagCountChangedCalledCount), tagContainer.Num(tag), tagContainer.Num(TagName1));
				TestEqual("Container has 2 TagName1 after Add Event -" + FString::FromInt(TagCountChangedCalledCount), tagContainer.Num(tag), 2);
				TestEqual("Add Event Count is Right TagName1 -" + FString::FromInt(TagCountChangedCalledCount), count, 2);
			}
			else if(tag == TagBase)
			{
				TestEqual("Add Event Tag is Right TagBase -" + FString::FromInt(TagCountChangedCalledCount), tagContainer.Num(tag), tagContainer.Num(TagBase));
				TestEqual("Container has 2 TagBase after Add Event -" + FString::FromInt(TagCountChangedCalledCount), tagContainer.Num(tag), 2);
				TestEqual("Add Event Count is Right TagBase -" + FString::FromInt(TagCountChangedCalledCount), count, 2);
			}
			else if(tag == TagMain)
			{
				TestEqual("Add Event Tag is Right TagMain -" + FString::FromInt(TagCountChangedCalledCount), tagContainer.Num(tag), tagContainer.Num(TagMain));
				TestEqual("Container has 2 TagMain after Add Event -" + FString::FromInt(TagCountChangedCalledCount), tagContainer.Num(tag), 2);
				TestEqual("Add Event Count is Right TagMain -" + FString::FromInt(TagCountChangedCalledCount), count, 2);
			}
			else
			{
				TestTrue("Unexpected tag event! -" + FString::FromInt(TagCountChangedCalledCount), false);
			}
		});
		tagContainer.OnExactTagCountChanged().AddLambda([this, &tagContainer, &ExactTagCountChangedCalledCount](const FGameplayTag& tag, int32 count)
		{
			ExactTagCountChangedCalledCount++;
			TestTrue("Add Event Tag is Right 1 EXACT -" + FString::FromInt(ExactTagCountChangedCalledCount), tag == TagName1);
			TestEqual("Container has 2 TagName1 after Add Event EXACT -" + FString::FromInt(ExactTagCountChangedCalledCount), tagContainer.NumExact(tag), 2);
			TestEqual("Add Event Count is Right EXACT -" + FString::FromInt(ExactTagCountChangedCalledCount), count, 2);
		});

		tagContainer.AddTag(TagName1);

		TestEqual("Tag count changed was called 3 times", TagCountChangedCalledCount, 3);
		TestEqual("Exact tag count changed was called once", ExactTagCountChangedCalledCount, 1);

		tagContainer.SendTagCountStateAsChange();

		TestEqual("Tag count changed was called 6 times", TagCountChangedCalledCount, 6);
		TestEqual("Exact tag count changed was called twice", ExactTagCountChangedCalledCount, 2);

		tagContainer.PauseTagChangedEvent();

		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName2);
		tagContainer.RemoveTag(TagName2);

		TestEqual("Tag count changed is still just called 6 times", TagCountChangedCalledCount, 6);
		TestEqual("Exact tag count changed  is still just called twice", ExactTagCountChangedCalledCount, 2);

		tagContainer.ContinuePauseTagChangedEvent();

		tagContainer.RemoveTag(TagName1); // Remove should trigger it aswell

		TestEqual("Tag count changed was called 9 times", TagCountChangedCalledCount, 9);
		TestEqual("Exact tag count changed was called 3 times", ExactTagCountChangedCalledCount, 3);
	});

	It("Should succeed if the container can fill TagContainer", [this]()
	{
		FOrbGameplayTagContainer tagContainer;
		tagContainer.AddTag(TagName1);
		tagContainer.AddTag(TagName2);
		tagContainer.AddTag(TagName3);

		FGameplayTagContainer targetContainer;
		tagContainer.Fill(targetContainer);

		TestTrue("FGameplayTagContainer HasTag 1", targetContainer.HasTag(TagName1));
		TestTrue("FGameplayTagContainer HasTag 2", targetContainer.HasTag(TagName2));
		TestTrue("FGameplayTagContainer HasTag 3", targetContainer.HasTag(TagName3));
	});
}

