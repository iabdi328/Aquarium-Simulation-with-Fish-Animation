/**
 * @file Item.cpp
 * @author Ismail Abdi
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 * @param filename The name of the image file to display for this item
 */
Item::Item(Aquarium* aquarium, const std::wstring& filename) : mAquarium(aquarium)
{
	// Load the fish image from the given file
	mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);

	// Create a bitmap from the image
	mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
}

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Perform hit testing to see if we clicked on this item
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return true if the item was clicked, false otherwise
 */
bool Item::HitTest(int x, int y) {
	double width = mItemBitmap->GetWidth();
	double height = mItemBitmap->GetHeight();

	double testX = x - GetX() + width / 2;
	double testY = y - GetY() + height / 2;

	if (testX < 0 || testY < 0 || testX >= width || testY >= height) {
		return false;
	}

	return !mItemImage->IsTransparent(static_cast<int>(testX), static_cast<int>(testY));
}


/**
 * Draw this item
 * @param dc Device context to draw on
 */
void Item::Draw(wxDC* dc)
{
	// Get the width and height of the bitmap
	double width = mItemBitmap->GetWidth();
	double height = mItemBitmap->GetHeight();

	// Draw the bitmap centered at the item's location
	dc->DrawBitmap(*mItemBitmap, static_cast<int>(GetX() - width / 2), static_cast<int>(GetY() - height / 2));
}


double Item::DistanceTo(std::shared_ptr<Item> other)
{
	double dx = GetX() - other->GetX();
	double dy = GetY() - other->GetY();
	return sqrt(dx * dx + dy * dy);  // Euclidean distance
}


/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Item::XmlSave(wxXmlNode* node)
{
	auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
	node->AddChild(itemNode);

	itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
	itemNode->AddAttribute(L"y", wxString::FromDouble(mY));

	return itemNode;
}


/**
 * Load the attributes for an item node.
 *
 * This is the base class version that loads the attributes
 * common to all items (like x and y). Override this to load
 * custom attributes for specific items.
 *
 * @param node The XML node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
	node->GetAttribute(L"x", L"0").ToDouble(&mX);  // Load the x attribute
	node->GetAttribute(L"y", L"0").ToDouble(&mY);  // Load the y attribute
}




/**
 * Set the mirror status
 * @param m New mirror flag
 */
void Item::SetMirror(bool m) {
	if(m != mMirror)
	{
		mMirror = m;

		// Update the bitmap to reflect the mirrored status
		if(mMirror)
		{
			mItemBitmap = std::make_unique<wxBitmap>(mItemImage->Mirror());  // Create mirrored image
		}
		else
		{
			mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);  // Use the normal image
		}
	}
}