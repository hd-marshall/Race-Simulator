# Race-Simulator

Description:
This race simulation tool is designed to provide users with a realistic experience of racing on a track. It incorporates features such as generating a digital representation of the track, determining the optimal racing line, and simulating tire degradation based on mathematical calculations.

Features:

Track Representation:
The tool generates a digital representation of the track, allowing users to visualize the layout and characteristics of the circuit.

Displaying the Track in a Tool:
The tool provides a graphical interface to display the track, enabling users to interact with it and analyze various aspects such as corners, straights, and elevation changes.

Optimal Racing Line:
Utilizing algorithms and racing principles, the tool calculates the optimal racing line for each corner of the track. This includes determining the ideal braking points, turn-in, apex, and exit points to maximize speed and minimize lap times.

Tire Degradation Modeling:
The tool incorporates mathematical models to simulate tire degradation throughout a race. Factors such as tire compound, track surface, driving style, and environmental conditions are considered to estimate the rate of tire wear and its impact on performance.

Notes for Development:

    Completed notes:
        - Basic Track DS Completed
            - However creating accurate turns angles to simulate the car at the moment im not sure how it will work
        - Basic Car DS Completed
        - SFML library included
        - Make file completed
        - Add a background in SFML
        - Create the track layout
        - Track points working from the object
        - Using splines ot create the edges between the vertices
        - Move nodes with keyboard

    Current in head thoughts:
        - ReDo code to make all the calls of the track to change the private class
        - create a make track visuals file to make the visual loop simpler
        - Add in a move the nodes with drag feature

    Weaknesses to improve on:
        - learn make files (better)
        - Best loop functions for different data types
