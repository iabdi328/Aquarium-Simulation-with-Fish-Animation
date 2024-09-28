/**
 * @file FishGoldeen.cpp
 * @author Ismail Abdi
 */


#include "pch.h"
#include "FishGoldeen.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishGoldeenImageName = L"images/goldeen.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishGoldeen::FishGoldeen(Aquarium *aquarium) : Fish(aquarium, FishGoldeenImageName)
{
 // Increase the speed to make it super fast
 std::uniform_real_distribution<> distributionX(100, 200); // Higher speed range
 mSpeedX = distributionX(GetAquarium()->GetRandom());

 // Keep some variation for Y speed
 std::uniform_real_distribution<> distributionY(-50, 50);
 mSpeedY = distributionY(GetAquarium()->GetRandom());


}



/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that represents this fish in XML
 */
wxXmlNode* FishGoldeen::XmlSave(wxXmlNode* node)
{
 // Call the base class's XmlSave to save x and y
 auto itemNode = Item::XmlSave(node);

 // Add the 'type' attribute specific to FishGoldeen
 itemNode->AddAttribute(L"type", L"goldeen");

 return itemNode;  // Return the updated node
}


