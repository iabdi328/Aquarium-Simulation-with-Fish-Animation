/**
 * @file FishNemo.cpp
 * @author Ismail Abdi
 */
 
#include "pch.h"
#include "FishNemo.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishNemoImageName = L"images/nemo.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishNemo::FishNemo(Aquarium *aquarium) : Fish(aquarium, FishNemoImageName)
{
  // Set Nemo's speed to be faster than other fish
    std::uniform_real_distribution<> distributionX(60, 100);  // Faster range for horizontal speed
    std::uniform_real_distribution<> distributionY(-20, 20);  // Vertical speed range

    // Set the speed using the random distribution
    SetSpeed(distributionX(aquarium->GetRandom()), distributionY(aquarium->GetRandom()));

}


/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that represents this fish in XML
 */
wxXmlNode* FishNemo::XmlSave(wxXmlNode* node)
{
 // Call the base class's XmlSave to save x and y
 auto itemNode = Item::XmlSave(node);

 // Add the 'type' attribute specific to FishNemo
 itemNode->AddAttribute(L"type", L"nemo");

 return itemNode;  // Return the updated node
}


void FishNemo::Update(double elapsed)
{
 // First, call the base class Update to maintain the original logic
 Fish::Update(elapsed);

 // Add unique zig-zag or wave-like movement for Nemo on the Y-axis
 double waveAmplitude = 50;   // Amplitude of the wave in pixels
 double waveFrequency = 2;    // Frequency of the wave
 double offsetY = waveAmplitude * sin(waveFrequency * GetX() * 0.01);

 // Apply the wave offset to the Y-position
 SetLocation(GetX(), GetY() + offsetY * elapsed);
}





