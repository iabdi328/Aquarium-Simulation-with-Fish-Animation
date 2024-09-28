/**
 * @file Fish.cpp
 * @author ismail
 */

#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"



// Maximum speed in the X direction in pixels per second
const double MaxSpeedX = 50;

// Minimum speed in the X direction in pixels per second
const double MinSpeedX = 20;

Fish::Fish(Aquarium *aquarium, const std::wstring &filename) : Item(aquarium, filename)
{
 std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
 mSpeedX = distribution(aquarium->GetRandom());
 mSpeedY = 0;
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
 // Move the fish based on elapsed time and speed
 SetLocation(GetX() + mSpeedX * elapsed,
             GetY() + mSpeedY * elapsed);

 // Get the aquarium width and height, and fish dimensions
 double fishWidth = mItemBitmap->GetWidth();
 double fishHeight = mItemBitmap->GetHeight();
 double aquariumWidth = GetAquarium()->GetWidth();
 double aquariumHeight = GetAquarium()->GetHeight();

 // Reverse direction when the fish reaches within 10 pixels of the right edge
 if (mSpeedX > 0 && GetX() >= aquariumWidth - 10 - fishWidth / 2)
 {
  mSpeedX = -mSpeedX;
  SetMirror(true); // Mirror when the fish turns left
 }
 // Reverse direction when the fish reaches within 10 pixels of the left edge
 else if (mSpeedX < 0 && GetX() <= 10 + fishWidth / 2)
 {
  mSpeedX = -mSpeedX;
  SetMirror(false); // Unmirror when the fish turns right
 }

 // Adjust vertical movement with random Y speed
 if (mSpeedY == 0)
 {
  // Set an initial random Y speed
  std::uniform_real_distribution<> distributionY(-30, 30); // Vertical speed between -30 and 30
  mSpeedY = distributionY(GetAquarium()->GetRandom());
 }

 // Ensure the fish stays within the top and bottom boundaries
 if (GetY() <= 10 + fishHeight / 2 || GetY() >= aquariumHeight - 10 - fishHeight / 2)
 {
  // Reverse vertical direction if we hit the top or bottom of the aquarium
  mSpeedY = -mSpeedY;
 }
}

void Fish::SetSpeed(double speedX, double speedY)
{
 mSpeedX = speedX;
 mSpeedY = speedY;
}


