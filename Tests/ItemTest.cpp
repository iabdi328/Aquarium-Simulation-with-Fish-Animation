#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Aquarium.h>

/** Mock class for testing the class Item */
class ItemMock : public Item
{
public:
    // Provide a valid image path for the mock item
    ItemMock(Aquarium *aquarium) : Item(aquarium, L"images/beta.png") {}

    /**
     * Draw this item (no need for functionality in the mock)
     * @param dc Device context to draw on
     */
    void Draw(wxDC *dc) override {
        // No operation needed for the mock
    }
};

TEST(ItemTest, Construct) {
    Aquarium aquarium;
    ItemMock item(&aquarium);
}

TEST(ItemTest, GettersSetters) {
    Aquarium aquarium;
    ItemMock item(&aquarium);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second set with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);
}

// Move the HitTest function test here
TEST(ItemTest, HitTest) {
    Aquarium aquarium;
    ItemMock item(&aquarium);

    // Set the item's location
    item.SetLocation(100, 200);

    // Ensure the mock image is properly loaded
    ASSERT_TRUE(item.GetFishImage()->IsOk()) << "Fish image not loaded correctly for testing HitTest.";

    // Test: The center of the item should return true (a hit)
    ASSERT_TRUE(item.HitTest(100, 200)) << "HitTest failed at the center of the item.";

    // Test: Left of the item, should return false (no hit)
    ASSERT_FALSE(item.HitTest(10, 200)) << "HitTest incorrectly returned true left of the item.";

    // Test: Right of the item, should return false (no hit)
    ASSERT_FALSE(item.HitTest(200, 200)) << "HitTest incorrectly returned true right of the item.";

    // Test: Above the item, should return false (no hit)
    ASSERT_FALSE(item.HitTest(100, 0)) << "HitTest incorrectly returned true above the item.";

    // Test: Below the item, should return false (no hit)
    ASSERT_FALSE(item.HitTest(100, 300)) << "HitTest incorrectly returned true below the item.";

    // Test: On a transparent pixel of the item (make sure the calculation is correct)
    ASSERT_FALSE(item.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16)) << "HitTest incorrectly returned true on a transparent pixel.";
}
