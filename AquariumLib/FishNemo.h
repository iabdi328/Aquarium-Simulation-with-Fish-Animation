/**
 * @file FishNemo.h
 * @author Ismail Abdi
 *
 *
 */
 
#ifndef FISHNEMO_H
#define FISHNEMO_H

#include "Fish.h"




class FishNemo : public Fish {
private:


public:
 /// Constructor
 FishNemo(Aquarium* aquarium);

 wxXmlNode* XmlSave(wxXmlNode* node) override;

 void Update(double elapsed);


};



#endif //FISHNEMO_H
