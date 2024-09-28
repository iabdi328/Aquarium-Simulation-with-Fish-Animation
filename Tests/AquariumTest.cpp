#include <pch.h>
#include <gtest/gtest.h>
#include <Item.h>
#include <Aquarium.h>
#include <FishBeta.h>
#include <DecorCastle.h>
#include <FishGoldeen.h>
#include <FishNemo.h>


#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

/**
 * Test fixture for Aquarium testing
 */
class AquariumTest : public ::testing::Test {
protected:
    /**
     * Create a path to a place to put temporary files
     * @return The temporary path
     */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
     * Read a file into a wstring and return it.
     * @param filename Name of the file to read
     * @return File contents
     */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     * @param filename The file to check
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        // Read the contents of the file
        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Test if the XML contains the expected elements using regular expressions
        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>"))) << "Missing XML declaration";
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>"))) << "Missing or incorrect <aqua/> tag";
    }

    /**
     * Populate an aquarium with three Beta fish
     * @param aquarium The aquarium to populate
     */
    void PopulateThreeBetas(Aquarium *aquarium)
    {
        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
    }

    void PopulateAllTypes(Aquarium *aquarium)
    {
        // Add a castle decor item
        auto castle = make_shared<DecorCastle>(aquarium);
        aquarium->Add(castle);
        castle->SetLocation(374, 183);

        // Add a Nemo fish
        auto nemo = make_shared<FishNemo>(aquarium);
        aquarium->Add(nemo);
        nemo->SetLocation(220, 398);

        // Add a Beta fish
        auto beta = make_shared<FishBeta>(aquarium);
        aquarium->Add(beta);
        beta->SetLocation(652, 307);

        // Add a Goldeen fish
        auto goldeen = make_shared<FishGoldeen>(aquarium);
        aquarium->Add(goldeen);
        goldeen->SetLocation(736, 661);
    }

    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure all four items are present in the XML
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>"))) << "Expected four <item> tags";

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"374\" y=\"183\" type=\"castle\""))) << "Expected castle at 374, 183";
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"220\" y=\"398\" type=\"nemo\""))) << "Expected Nemo fish at 220, 398";
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"652\" y=\"307\" type=\"beta\""))) << "Expected Beta fish at 652, 307";
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"736\" y=\"661\" type=\"goldeen\""))) << "Expected Goldeen fish at 736, 661";
    }


    /**
     * Test to ensure the aquarium has three Beta fish
     * @param filename The file to check
     */
    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")))
            << "Expected three <item> tags";

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")))
            << "Expected first fish at 100, 200";
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")))
            << "Expected second fish at 400, 400";
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")))
            << "Expected third fish at 600, 100";

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")))
            << "Expected three fish of type beta";
    }
};

// Tests
TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest) {
    // Create an aquarium object
    Aquarium aquarium;

    // Test hit detection on an empty aquarium
    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) << "Testing empty aquarium";

    // Create and add a FishBeta to the aquarium
    std::shared_ptr<FishBeta> fish1 = std::make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);

    // Set the fish's location
    fish1->SetLocation(100, 200);

    // Test hit detection on the fish
    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) << "Testing fish at 100, 200";
}

TEST_F(AquariumTest, SaveEmptyAquarium) {
    // Create an empty aquarium
    Aquarium aquarium;

    // Save the empty aquarium to a temporary file
    auto filename = TempPath() + L"/test1.aqua";
    aquarium.Save(filename);

    // Test if the file is saved correctly and is empty
    TestEmpty(filename);

    //
    // Now populate the aquarium with three Beta fish
    //
    PopulateThreeBetas(&aquarium);

    auto file2 = TempPath() + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);
}

TEST_F(AquariumTest, Save)
{
    wxString path = TempPath();

    //
    // Test empty aquarium save
    //
    Aquarium aquarium;
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);
    TestEmpty(file1);

    //
    // Test saving three Beta fish
    //
    Aquarium aquarium2;
    PopulateThreeBetas(&aquarium2);
    auto file2 = path + L"/test2.aqua";
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    //
    // Test saving all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);
}

TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    // Load the empty aquarium into a different object, save again, and test
    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium with three Beta fish
    //
    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    // Load the populated aquarium into a different object, save again, and test
    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    //
    // Test with all types of items (fish and decor)
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);

    // Load the aquarium with all types into a different object, save again, and test
    aquarium2.Load(file3);
    aquarium2.Save(file3);
    TestAllTypes(file3);
}


