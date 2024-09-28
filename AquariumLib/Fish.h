/**
 * @file Fish.h
 * @author ismail
 *
 *
 */
 
#ifndef FISH_H
#define FISH_H

#include "Item.h"


/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item {
public:
 /// Default constructor (disabled)
 Fish() = delete;

 /// Copy constructor (disabled)
 Fish(const Fish&) = delete;

 /// Assignment operator
 void operator=(const Fish&) = delete;

 /// Handle updates in time of our fish
 void Update(double elapsed);

 ///  Set the speed of the fish in both X and Y directions
 void SetSpeed(double speedX, double speedY);


protected:
 /**
  * Constructor
  * @param aquarium The aquarium we are in
  * @param filename Filename for the image we use
  */
 Fish(Aquarium* aquarium, const std::wstring& filename);

 /// Fish speed in the X direction in pixels per second
 double mSpeedX = 0;

 /// Fish speed in the Y direction in pixels per second
 double mSpeedY = 0;
};




#endif //FISH_H
