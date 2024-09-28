/**
 * @file DecorCastle.cpp
 * @author ismail
 */

#include "pch.h"
#include "DecorCastle.h"

/// DecorCastle image file
const std::wstring DecorCastleImageName = L"images/castle.png";

/**
 * Constructor
 * @param aquarium The aquarium this item is a part of
 */
DecorCastle::DecorCastle(Aquarium* aquarium) : Item(aquarium, DecorCastleImageName)
{
 // The base class constructor will load the image and handle all necessary initialization
}


wxXmlNode* DecorCastle::XmlSave(wxXmlNode* node)
{
 // Call the base class's XmlSave to save x and y
 auto itemNode = Item::XmlSave(node);

 // Add the 'type' attribute specific to DecorCastle
 itemNode->AddAttribute(L"type", L"castle");

 return itemNode;  // Return the updated node
}