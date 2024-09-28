/**
 * @file FishBeta.cpp
 * @author Ismail Abdi
 */

#include "pch.h"
#include "FishBeta.h"
#include "Aquarium.h"


using namespace std;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium* aquarium) : Fish(aquarium, FishBetaImageName)
{
 // FishBeta has a medium speed range
 std::uniform_real_distribution<> distributionX(20, 50);  // Medium speed range
 std::uniform_real_distribution<> distributionY(-20, 20);  // Small vertical range
 SetSpeed(distributionX(aquarium->GetRandom()), distributionY(aquarium->GetRandom()));
}


/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return The XML node representing the fish
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
 // Call the base class's XmlSave to save x and y
 auto itemNode = Item::XmlSave(node);

 // Add the 'type' attribute specific to FishBeta
 itemNode->AddAttribute(L"type", L"beta");

 return itemNode;  // Return the updated node
}



void FishBeta::Update(double elapsed)
{
 // Increase speed gradually
 double acceleration = 8.0;
 mSpeedX += acceleration * elapsed;

 // Call base class Update to handle movement
 Fish::Update(elapsed);
}