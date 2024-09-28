/**
 * @file AquariumView.h
 * @author Ismail Abdi
 *
 * View class for our aquarium
 */

#ifndef AQUARIUM_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMVIEW_H

#include "Aquarium.h"
#include <wx/window.h>



/**
 * View class for our aquarium
 */
class AquariumView : public wxWindow {
private:
	void OnPaint(wxPaintEvent &event);  // Event handler for painting the view

	/// The aquarium we are viewing
	Aquarium mAquarium;

	/// Menu handlers for adding fish and decor
	void OnAddFishBetaFish(wxCommandEvent& event);
	void OnAddFishNemo(wxCommandEvent& event);
	void OnAddFishGoldeen(wxCommandEvent& event);
	void OnAddDecorCastle(wxCommandEvent& event);  // Moved to private section (already declared in public)

	/// Mouse event handlers for dragging items
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);

	std::shared_ptr<Item> mGrabbedItem;  // The item being dragged, if any

	/// The timer that allows for animation
	wxTimer mTimer;

	/// Handle the timer event for animation
	void OnTimer(wxTimerEvent& event);  // Declare OnTimer event handler here

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;


	/// The last stopwatch time
	long mTime = 0;

public:
	void Initialize(wxFrame *parent);  // Initialization method

	/// File handling
	void OnFileSaveAs(wxCommandEvent& event);  // Public save handler

	/// Method to save the aquarium to a file
	void SaveAquarium(const wxString& filename);


	/// Menu handler for File > Open
	void OnFileOpen(wxCommandEvent& event);
};

#endif //AQUARIUM_AQUARIUMVIEW_H
