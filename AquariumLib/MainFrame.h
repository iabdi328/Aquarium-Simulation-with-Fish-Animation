/**
 * @file MainFrame.h
 * @author Ismail Abdi
 *
 * The top-level (main) frame of the application
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

class AquariumView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our aquarium
    AquariumView *mAquariumView;

	void CreateMenu();

	/// Event handler for the "Exit" menu item
	void OnExit(wxCommandEvent& event);

	/// Event handler for the "About" menu item
	void OnAbout(wxCommandEvent& event);



public:
    void Initialize();
};

#endif //_MAINFRAME_H_
