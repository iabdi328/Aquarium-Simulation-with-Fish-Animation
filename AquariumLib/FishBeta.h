/**
 * @file FishBeta.h
 * @author Ismail Abdi
 *
 *
 */
 
#ifndef FISHBETA_H
#define FISHBETA_H

#include "Fish.h"

/**
 * Class for a fish of type Beta
 */
class FishBeta : public Fish {
private:

public:
	/// Default constructor (disabled)
	FishBeta() = delete;

	/// Copy constructor (disabled)
	FishBeta(const FishBeta &) = delete;

	/// Assignment operator
	void operator=(const FishBeta &) = delete;

	FishBeta(Aquarium* aquarium);

	/// Save this fish to an XML node.
	wxXmlNode* XmlSave(wxXmlNode* node) override;

	void Update(double elapsed);

};




#endif //FISHBETA_H
