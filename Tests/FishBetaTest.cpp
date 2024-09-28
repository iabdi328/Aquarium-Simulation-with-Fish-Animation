#include <pch.h>
#include <gtest/gtest.h>
#include <FishBeta.h>
#include <Aquarium.h>

TEST(FishBetaTest, Constructor) {
 // Create a mock aquarium for the fish
 Aquarium aquarium;

 // Construct a FishBeta object
 FishBeta fishBeta(&aquarium);

 // Verify the FishBeta object was created successfully
 ASSERT_NE(&fishBeta, nullptr);
}

TEST(FishBetaTest, HitTest) {
 // Create an aquarium object
 Aquarium aquarium;

 // Create a fish object for testing
 FishBeta fish(&aquarium);

 // Set the fish's location
 fish.SetLocation(100, 200);

 // Test: The center of the fish should return true (a hit)
 ASSERT_TRUE(fish.HitTest(100, 200));

 // Test: Left of the fish, should return false (no hit)
 ASSERT_FALSE(fish.HitTest(10, 200));

 // Test: Right of the fish, should return false (no hit)
 ASSERT_FALSE(fish.HitTest(200, 200));

 // Test: Above the fish, should return false (no hit)
 ASSERT_FALSE(fish.HitTest(100, 0));

 // Test: Below the fish, should return false (no hit)
 ASSERT_FALSE(fish.HitTest(100, 300));

 // Test: On a transparent pixel of the fish
 ASSERT_FALSE(fish.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16));
}