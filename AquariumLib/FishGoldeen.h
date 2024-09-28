/**
 * @file FishGoldeen.h
 * @author Ismail Abdi
 *
 *
 */
 
#ifndef FISHGOLDEEN_H
#define FISHGOLDEEN_H


#include "Fish.h"


/**
 * A class that represents a Goldeen fish in the aquarium.
 */
class FishGoldeen : public Fish {
private:


public:
 /// Constructor
 FishGoldeen(Aquarium* aquarium);

 wxXmlNode* XmlSave(wxXmlNode* node) override;





};



#endif //FISHGOLDEEN_H
