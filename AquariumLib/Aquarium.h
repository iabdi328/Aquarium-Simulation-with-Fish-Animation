/**
 * @file Aquarium.h
 * @author Ismail Abdi
 *
 * The main aquarium class.
 */

#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H

#include <memory>   // For std::shared_ptr
#include <vector>   // For std::vector
#include <wx/bitmap.h>  // For wxBitmap
#include <random>

class Item;

/**
 * The main aquarium class.
 */
class Aquarium {
private:
    /// Background image
    std::unique_ptr<wxBitmap> mBackground;

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;

	// Declare XmlItem as a private method
	void XmlItem(wxXmlNode *node);


	/// Random number generator
	std::mt19937 mRandom;



public:
    Aquarium();

    void OnDraw(wxDC* graphics);

	void Add(std::shared_ptr<Item> item);

	std::shared_ptr<Item> HitTest(int x, int y);\

	/// Move an item to the end of the list (so it appears on top)
	void MoveToEnd(std::shared_ptr<Item> item);

	/**
	 * Get the list of items in the aquarium.
	 * @return Vector of shared pointers to items.
	 */
	const std::vector<std::shared_ptr<Item>>& GetItems() const;

	void Save(const wxString &filename);

	/// Load the aquarium from an XML file
	void Load(const wxString &filename);

	/// Deletes all known items in the aquarium.
	void Clear();

	/// Handle updates for animation
	void Update(double elapsed);


	/**
	 * Get the random number generator
	 * @return Reference to the random number generator
	 */
	std::mt19937 &GetRandom();

	/**
	 * Get the width of the aquarium
	 * @return Aquarium width in pixels
	 */
	int GetWidth() const { return mBackground->GetWidth(); }


	/**
	 * Get the height of the aquarium
	 * @return Aquarium height in pixels
	 */
	int GetHeight() const { return mBackground->GetHeight(); }
};

#endif //AQUARIUM_AQUARIUM_H
