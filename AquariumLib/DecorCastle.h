/**
 * @file DecorCastle.h
 * @author ismail
 *
 *
 */
 
#ifndef DECORCASTLE_H
#define DECORCASTLE_H

#include "Item.h"



class DecorCastle: public Item {
private:

public:
 DecorCastle(Aquarium* aquarium);

 /**
     * Save this decor item to an XML node
     * @param node The parent node we are going to be a child of
     * @return wxXmlNode* that represents this decor in XML
     */
 wxXmlNode* XmlSave(wxXmlNode* node) override;

};



#endif //DECORCASTLE_H
