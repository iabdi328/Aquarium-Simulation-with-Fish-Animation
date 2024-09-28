/**
 * @file AquariumView.cpp
 * @author Ismail Abdi
 */
#include "pch.h"

#include "AquariumView.h"
#include "FishBeta.h"
#include "FishNemo.h"
#include  "FishGoldeen.h"
#include "DecorCastle.h"
#include <wx/dcbuffer.h>
#include "ids.h"  // Include IDs for menu items
#include <memory>
#include <wx/log.h>

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;


/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
    // Set up the window
    Create(parent, wxID_ANY);

    // Set the background style for better painting
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind the paint event for rendering the aquarium
    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);

    // Bind the mouse events for dragging items
    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);

    // Bind the menu options to handlers
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishNemo, this, IDM_ADDFISHNEMO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishGoldeen, this, IDM_ADDFISHGOLDEEN);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDecorCastle, this, IDM_ADDDECORCASTLE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);  // Save as menu

	mTimer.SetOwner(this);
	mTimer.Start(FrameDuration);

	// Bind the timer event for the OnTimer handler
	Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);

	// Start the stopwatch for tracking time
	mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);  // Create a buffered device context

	// Compute the time that has elapsed
	// since the last call to OnPaint.
	auto newTime = mStopWatch.Time();
	auto elapsed = (double)(newTime - mTime) * 0.001;
	mTime = newTime;


	// Update the aquarium state based on elapsed time
	mAquarium.Update(elapsed);

    wxBrush background(*wxWHITE);  // Set the background to white
    dc.SetBackground(background);
    dc.Clear();  // Clear the window with the background

    // Draw the aquarium and all its items
    mAquarium.OnDraw(&dc);
}

/**
 * Menu handler for Add Fish > Beta Fish
 * @param event The wxCommandEvent triggered by the menu
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = std::make_shared<FishBeta>(&mAquarium);  // Create a new Beta fish
    mAquarium.Add(fish);  // Add the fish to the aquarium
    Refresh();  // Refresh the view to display the new fish
}

/**
 * Menu handler for Add Fish > Nemo Fish
 * @param event The wxCommandEvent triggered by the menu
 */
void AquariumView::OnAddFishNemo(wxCommandEvent& event)
{
    auto fish = std::make_shared<FishNemo>(&mAquarium);  // Create a new Nemo fish
    mAquarium.Add(fish);  // Add the fish to the aquarium
    Refresh();  // Refresh the view to display the new fish
}

/**
 * Menu handler for Add Fish > Goldeen Fish
 * @param event The wxCommandEvent triggered by the menu
 */
void AquariumView::OnAddFishGoldeen(wxCommandEvent& event)
{
    auto fish = std::make_shared<FishGoldeen>(&mAquarium);  // Create a new Goldeen fish
    mAquarium.Add(fish);  // Add the fish to the aquarium
    Refresh();  // Refresh the view to display the new fish
}

/**
 * Menu handler for Add Decor > Castle
 * @param event The wxCommandEvent triggered by the menu
 */
void AquariumView::OnAddDecorCastle(wxCommandEvent& event)
{
    auto decor = std::make_shared<DecorCastle>(&mAquarium);  // Create a new castle decor
    mAquarium.Add(decor);  // Add the decor to the aquarium
    Refresh();  // Refresh the view to display the new decor
}

/**
 * Handle the left mouse button down event for dragging items.
 * @param event Mouse event
 */
void AquariumView::OnLeftDown(wxMouseEvent& event)
{
    // Perform a hit test to see if we clicked on an item
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());

    // If we clicked on an item, bring it to the top
    if (mGrabbedItem != nullptr)
    {
        mAquarium.MoveToEnd(mGrabbedItem);  // Move the item to the end of the list
    }
}

/**
 * Handle the left mouse button up event.
 * @param event Mouse event
 */
void AquariumView::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);  // Handle the final mouse position
}

/**
 * Handle mouse movement for dragging items.
 * @param event Mouse event
 */
void AquariumView::OnMouseMove(wxMouseEvent& event)
{
    // If an item is being dragged
    if (mGrabbedItem != nullptr)
    {
        if (event.LeftIsDown())  // Move the item if the left mouse button is pressed
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());  // Set the new location of the grabbed item
        }
        else
        {
            mGrabbedItem = nullptr;  // Release the grabbed item when the button is released
        }
        Refresh();  // Refresh the view to show the updated item position
    }
}

/**
 * Save the aquarium to a file.
 * @param event The wxCommandEvent triggered by the menu
 */
void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
	// Create a wxFileDialog to allow the user to select where to save the file
	wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
			L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	// If the user cancels the dialog, return early
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	// Get the selected filename
	auto filename = saveFileDialog.GetPath();

	// Call the Save function of Aquarium to handle saving the file
	mAquarium.Save(filename);
}
/**
 * Save the aquarium to the specified filename.
 * @param filename The path to save the aquarium data
 */
void AquariumView::SaveAquarium(const wxString& filename)
{
    // Implement the saving functionality here. This would involve writing the aquarium data to a file.
    wxLogDebug("Saving aquarium to %s", filename);
}


/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
	wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
								L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
	if (loadFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	auto filename = loadFileDialog.GetPath();
	mAquarium.Load(filename);

	// Trigger a refresh to redraw the view after loading the aquarium
	Refresh();
}


/**
 * Handle the timer event for animation.
 * @param event Timer event object
 */
void AquariumView::OnTimer(wxTimerEvent &event)
{
	Refresh();  // Repaint the window every time the timer event is triggered
}
