/**
 * @file Item.h
 * @author Ismail Abdi
 *
 * Base class for items in the aquarium
 */

#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

class Aquarium;

/**
 * Base class for any item in our aquarium.
 */
class Item {
private:
    /// The aquarium this item is contained in
    Aquarium* mAquarium;

    // Item location in the aquarium
    double mX = 0;     ///< X location for the center of the item
    double mY = 0;     ///< Y location for the center of the item

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;




    bool mMirror = false;   ///< True mirrors the item image


protected:
 /// The bitmap we can display for this item
 std::unique_ptr<wxBitmap> mItemBitmap;

public:
    /**
     * Constructor for Item with image filename.
     * @param aquarium The aquarium this item is a member of
     * @param filename The name of the image file to display for this item
     */
    Item(Aquarium* aquarium, const std::wstring& filename);

    /// Destructor
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item&) = delete;

    /// Assignment operator (disabled)
    void operator=(const Item&) = delete;

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    virtual void Draw(wxDC* dc);

    /**
     * Perform hit testing
     * @param x X location in pixels
     * @param y Y location in pixels
     * @return true if hit, otherwise false
     */
    bool HitTest(int x, int y);

    /// Get the fish image
    wxImage* GetFishImage() const { return mItemImage.get(); }

    /// Get the fish bitmap
    wxBitmap* GetFishBitmap() const { return mItemBitmap.get(); }

    /// Set a new fish bitmap (optional, in case derived classes need to set a new bitmap)
    void SetFishBitmap(std::unique_ptr<wxBitmap> bitmap) { mItemBitmap = std::move(bitmap); }

 /**
     * Calculate the distance between this item and another item.
     * @param other The other item to calculate distance to.
     * @return The Euclidean distance between this item and the other item.
     */
    double DistanceTo(std::shared_ptr<Item> other);

    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    virtual void XmlLoad(wxXmlNode *node);

     /**
     * Handle updates for animation.
     * @param elapsed The time since the last update.
     */
    virtual void Update(double elapsed) {}


    /**
     * Get the pointer to the Aquarium object
     * @return Pointer to Aquarium object
     */
    Aquarium *GetAquarium() { return mAquarium;  }


    void SetMirror(bool m);
};
#endif //AQUARIUM_ITEM_H
