/**
 * @file Aquarium.cpp
 * @author Ismail Abdi
 */


#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "DecorCastle.h"
#include "FishNemo.h"
#include "FishGoldeen.h"
#include <memory>

using namespace std;


// Initial fish X and Y location
const int InitialX = 200;
const int InitialY = 200;

// The offset to use when a fish is bumped
const double NextFishOffset = 10.0;

/**
 * Perform hit testing to see if a mouse click hit any item in the aquarium.
 * @param x X coordinate of the mouse click.
 * @param y Y coordinate of the mouse click.
 * @return The item that was clicked on, or nullptr if none.
 */
std::shared_ptr<Item> Aquarium::HitTest(int x, int y) {
    // Iterate through items in reverse order to check the top-most item first
    for (auto i = mItems.rbegin(); i != mItems.rend(); ++i) {
        if ((*i)->HitTest(x, y)) {
            return *i;  // Return the first item that is hit
        }
    }
    return nullptr;  // Return nullptr if no item was hit
}

/**
 * Move an item to the end of the list.
 * This ensures it is drawn on top of other items.
 * @param item The item to move.
 */
void Aquarium::MoveToEnd(std::shared_ptr<Item> item)
{
    // Find the item in the vector
    auto loc = std::find(mItems.begin(), mItems.end(), item);

    // If found, erase it and push it to the back of the vector
    if (loc != mItems.end())
    {
        mItems.erase(loc);   // Remove the item from its current location
        mItems.push_back(item);  // Add it to the end (topmost)
    }
}

/**
 * Aquarium Constructor
 */
Aquarium::Aquarium()
{
    mBackground = make_unique<wxBitmap>(
            L"images/background1.png", wxBITMAP_TYPE_ANY);
}

/**
 * Draw the aquarium and its items.
 * @param dc The device context to draw on.
 */
void Aquarium::OnDraw(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);

    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 64, 0));
    dc->DrawText(L"Under the Sea!", 10, 10);

    for (auto item : mItems)
    {
        item->Draw(dc);
    }
}

/**
 * Add an item to the aquarium.
 * This function ensures that new items do not overlap with existing ones.
 * If an overlap is detected, the item is "bumped" downwards and to the right.
 * @param item The item to add (e.g., a fish).
 */
void Aquarium::Add(std::shared_ptr<Item> item)
{
    item->SetLocation(InitialX, InitialY);  // Set initial location

    // Check for overlaps and bump the item if necessary
    bool bumped = false;
    do
    {
        bumped = false;  // Reset the flag

        // Check if the new item overlaps with any existing items
        for (auto existing : mItems)
        {
            if (item->DistanceTo(existing) < 1)
            {
                // If too close, move the item by the NextFishOffset
                item->SetLocation(item->GetX() + NextFishOffset, item->GetY() + NextFishOffset);
                bumped = true;  // Set the flag to indicate a bump occurred
                break;  // Exit the loop and check again after bumping
            }
        }
    } while (bumped);  // Repeat until no more bumps are needed

    mItems.push_back(item);  // Finally, add the item to the list
}

/**
 * Get the list of items in the aquarium.
 * @return A vector of shared pointers to items.
 */
const std::vector<std::shared_ptr<Item>>& Aquarium::GetItems() const
{
    return mItems;
}


/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
void Aquarium::Save(const wxString &filename)
{
    wxXmlDocument xmlDoc;

    // Create the root node
    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);

    // Iterate over all items and save them
    for (auto item : mItems)
    {
        item->XmlSave(root);
    }

    // Save the XML document to the file
    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}


/**
 * Load the aquarium from a .aqua file.
 *
 * Open the file and read the aquarium data into the system.
 * @param filename The name of the file to load
 */
/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
 */
void Aquarium::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Aquarium file");
        return;
    }

    // Clear the current aquarium data
    Clear();

    // Get the root node (should be <aqua>)
    auto root = xmlDoc.GetRoot();
    if (!root || root->GetName() != L"aqua")
    {
        wxMessageBox(L"Invalid aquarium file");
        return;
    }

    // Traverse the children of the root node
    auto child = root->GetChildren();
    for (; child; child = child->GetNext())
    {
        // Check if the child is an <item> node
        if (child->GetName() == L"item")
        {
            XmlItem(child);
        }
    }
}





void Aquarium::Clear()
{
    // Clear the vector that holds all items (fish, decor, etc.)
    mItems.clear();
}


/**
 * Handle a node of type item.
 * @param node XML node
 */
void Aquarium::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    if (type == L"beta")
    {
        item = std::make_shared<FishBeta>(this);
    }
    else if (type == L"nemo")
    {
        item = std::make_shared<FishNemo>(this);
    }
    else if (type == L"goldeen")
    {
        item = std::make_shared<FishGoldeen>(this);
    }
    else if (type == L"castle")
    {
        item = std::make_shared<DecorCastle>(this);
    }

    // If an item was created, add it to the aquarium and load its attributes
    if (item != nullptr)
    {
        Add(item);
        item->XmlLoad(node);  // Load common attributes like x, y
    }
}


/**
 * Handle updates for animation.
 * @param elapsed The time since the last update
 */
void Aquarium::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);  // Call the Update function on each item
    }
}

// Getter for the random number generator
std::mt19937& Aquarium::GetRandom()
{
    return mRandom;
}