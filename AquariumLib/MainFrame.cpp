/**
 * @file MainFrame.cpp
 * @author Ismail Abdi
 */

#include "pch.h"
#include "MainFrame.h"
#include "AquariumView.h"
#include "DecorCastle.h"
#include "ids.h"  // Include the ids.h file where IDM_ADDFISHBETA is defined

/**
 * Initialize the MainFrame window and its components.
 */
void MainFrame::Initialize()
{
    // Create the main window frame
    Create(nullptr, wxID_ANY, L"Aquarium", wxDefaultPosition, wxSize(1000, 800));

    // Create a vertical box sizer
    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Initialize the AquariumView
    mAquariumView = new AquariumView();
    mAquariumView->Initialize(this);  // Pass the main frame as the parent

    // Add the AquariumView to the sizer
    sizer->Add(mAquariumView, 1, wxEXPAND | wxALL);

    // Set the sizer for the main frame
    SetSizer(sizer);
    Layout();

    // Create the menu bar and set it
    CreateMenu();

    // Create the status bar at the bottom of the window
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
}

/**
 * Create the menu bar and bind events to the corresponding handlers.
 */
void MainFrame::CreateMenu()
{
    // Create a new menu bar
    auto menuBar = new wxMenuBar();

    // Create File, Add Fish, Add Decor, and Help menus
    auto fileMenu = new wxMenu();
    auto fishMenu = new wxMenu();
    auto decorMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // Add "Save As" and "Exit" options to the File menu
    fileMenu->Append(wxID_SAVEAS, L"Save &As...\tCtrl-S", L"Save aquarium as...");
    fileMenu->Append(wxID_EXIT, L"E&xit\tAlt-X", L"Quit this program");

    // Add fish options to the Add Fish menu
    fishMenu->Append(IDM_ADDFISHBETA, L"&Beta Fish", L"Add a Beta Fish");
    fishMenu->Append(IDM_ADDFISHNEMO, L"&Nemo Fish", L"Add a Nemo Fish");
    fishMenu->Append(IDM_ADDFISHGOLDEEN, L"&Goldeen Fish", L"Add a Goldeen Fish");
	fileMenu->Append(wxID_OPEN, L"Open &File...\tCtrl-F", L"Open aquarium file...");

    // Add decor options to the Add Decor menu
    decorMenu->Append(IDM_ADDDECORCASTLE, L"&Castle Decor", L"Add a Castle");

    // Add "About" option to the Help menu
    helpMenu->Append(wxID_ABOUT, L"&About\tF1", L"Show about dialog");

    // Append the menus to the menu bar
    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(fishMenu, L"&Add Fish");
    menuBar->Append(decorMenu, L"&Add Decor");
    menuBar->Append(helpMenu, L"&Help");

    // Set the menu bar for the main frame
    SetMenuBar(menuBar);

    // Bind the menu events to their corresponding event handlers
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, mAquariumView, wxID_OPEN);
}

/**
 * Event handler for the "Exit" menu item.
 * Closes the application.
 * @param event The wxCommandEvent triggered by the menu.
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);  // Close the window
}

/**
 * Event handler for the "About" menu item.
 * Shows an About dialog with information about the Aquarium application.
 * @param event The wxCommandEvent triggered by the menu.
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Aquarium!", L"About Aquarium", wxOK, this);
}