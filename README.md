# Aquarium-Simulation-with-Fish-Animation

This project is an interactive aquarium simulation built using C++ and wxWidgets, where animated fish move within the aquarium. The fish dynamically adjust their speed, direction, and behavior based on their proximity to the aquarium boundaries. The project demonstrates object-oriented programming concepts, animation techniques, and file handling through XML serialization.

Features: 

Animated Fish: Fish swim within the aquarium, changing direction when they reach the edges of the screen.

Unique Fish Behaviors: Different types of fish exhibit unique speeds and movement patterns, such as faster or more erratic swimming.

Collision Handling: Fish reverse direction when they reach the aquarium edges.

Save and Load Aquarium State: Fish positions and speeds are saved in an XML file, and the aquarium can be restored to a previous state.

Randomized Fish Speeds: Fish speeds are randomly generated, providing unique behaviors each time the simulation runs.

Technologies Used
C++: Core programming language for object-oriented design and logic.
wxWidgets: GUI library for rendering the aquarium, handling events, and creating the user interface.
XML: Used for saving and loading the state of the aquarium, including fish positions and speeds.


Key Concepts:
Object-Oriented Programming (OOP): The fish and aquarium are modeled as objects with encapsulated behaviors and attributes.

Animation: Fish movement is updated frame-by-frame based on elapsed time and randomized speeds.

File Serialization: Saving and loading fish states (position, speed) in XML format for persistence.


How to Use:
Add Fish: Add different types of fish to the aquarium from the menu.

Animate Fish: Fish will automatically swim within the aquarium, reversing direction when they reach the edges.

Save/Load: Save the current aquarium state to an XML file and load it later.

Future Enhancements:
Add additional fish species with more unique behaviors.
Introduce interaction features where users can feed the fish or change the aquarium environment.
Add more decorations and obstacles in the aquarium.


Screenshots

![Aquriumimg1](https://github.com/user-attachments/assets/0623fc5c-4b68-401e-9035-802f9b13b78d)
