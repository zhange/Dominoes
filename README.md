Domsim
======
A Dominoes Simulator

User Guide
----------

The two topmost buttons in the menu will bring you to Draw Mode and Run Mode, respectively.  The mode in which you are currently operating has its button highlighted with inverted colors. Below, we see Draw Mode highlighted.


In Draw Mode, you can draw a line on the canvas which will segment into distinct dominoes upon releasing the mouse button. Exiting the canvas area while drawing will automatically end the line you are drawing at the time. Above shows the line still being drawn; although, the mouse cursor was omitted from the screenshot. The below image shows the segmented line representing the dominoes in their correct positions.




In Run Mode, you will see the currently loaded line of dominoes in 3D with red wireframe dominoes on a blue floor. You can click "Play Sequence" to begin tilting the first domino and start the sequence of toppling. You can also click "Reset Dominoes" to reset all dominoes to a standing position. Finally, you can click "Freeze" at any time during the falling of dominoes to freeze or unfreeze their motion. Above, Run Mode is highlighted, and the wireframe dominoes from another pattern are shown, some having already fallen. Below, more dominoes have fallen. In both cases, the “Freeze” button has been clicked to stop the animation for the screenshot.


When in Run Mode, you can press the 1 or 2 key on the keyboard in order to switch to camera mode 1 and camera mode 2, respectively. Camera mode 1 follows the lead domino, and camera mode 2 views the action from a fixed point in space. For additional camera control, you can press the z key and the x key to increment and decrement the x coordinate of the camera position, respectively. Similarly, you can press the v key and the b key to increment and decrement the y coordinate of the camera position, respectively. These controls are available in both camera mode 1 and camera mode 2 and are held when transitioning between the modes. Below, the camera has been switched from camera mode 2 to camera mode 1 and is, therefore, following the lead domino.

In either mode, you can click the "Load Setup" and "Save Setup" buttons to load the most recently saved domino setup and save a new one, respectively. The below image is the setup.dsx file that was loaded into the above instance of the program. The file contains 3725 lines, which hold the necessary information for 745 dominoes, and it saves and loads instantaneously.


Design
------

Run Mode
--------

We chose to allow only single strip of dominoes to simplify physics simulation and camera control. With one line of dominoes, we can allow the camera to follow the one lead domino at any given moment, and we can concern ourselves only with collision detection between adjacent dominoes. These dominoes were stored in a vector of domino objects. We hope to change this in the future and allow for branching paths and even completely separate strips of dominoes. 

We chose to draw wireframe dominoes because there was an issue with lighting where dominoes were all lit as if they were standing in the standard position, facing the positive x axis at the origin. We hope to improve the lighting in the future to remedy this and create a better overall 3D visual experience. We also hope to add textures and shadow effects with shading to aid in this effort. 

We chose to use an older version of OpenGL because it is what we used in class and were familiar with; however, we hope to port it to the newest version to keep up with standards.
	 	 	
Another decisions we made was to use a glutWireCube instead of drawing it using vertices and GL_QUADS. There were a few reasons for this, involving ease of use, overall aesthetics, and code consistency. Using the OpenGL functions to render our dominoes seemed to be the best idea, because it is important to use the tools at one’s disposal. If OpenGL has a function to create a cube, then making our own would be unnecessary. Also, performing transformations on our created cube was simple using the OpenGL functions of gluRotatef, gluScalef, glTranslatef. To create a domino, we passed an instance of a domino object to a function that took into account the location, tilt, and normal to the next domino. This function created a glutWireCube with the necessary transformations applied to it. Inside this function, proper lighting effects were denoted so that the dominoes looked good when rendered in 3D. We decided to use a wireframe cube for our dominoes instead of a solid cube and with the implementation we had in place, it was simple to change one line of code back and forth. If we had implemented the glutSolidCube/glutWireCube differently, this might not have been the case.

We also decided to draw a floor. This was to help us debug where the dominoes were located when testing lighting and falling. After implementing the floor, the consensus of the group was that the dominoes looked much better with the floor as opposed to without it. The floor is created using GL_QUADS and four glVertex3f points in 3D space. Originally the floor was wireframe, but when we changed our dominoes to wireframe instead of solid, it was confusing to the user what was floor and what was domino. Using a solid floor also created a better aesthetic when combined with the lighting effects we implemented.


Canvas Mode
-----------

We chose to use a dynamic canvas tool to draw user created lines over straight lines or preloaded figures because in real life, players will not be able to make perfectly straight lines. We wanted to try to make it as close to real life as possible.
The lines are drawn based on the user’s mouse locations on the screen when they hold down the mouse button. The line is actually a series of points drawn every frame. We chose this over drawing a single line because points better represent the discrete dominoes.

An interpolation algorithm was also used to fill in the space between the last two points drawn. The algorithm draws 12 points between every point drawn by the user to account for very fast mouse movement. Since multiple points can be drawn in the same place if the user holds the mouse in the same position for periods of time, we also needed to clean out all points drawn. This process was simply removing doubles from the list so that they would not be counted, as well as making computations cheaper in the future. After cleaning the points, we used a distance algorithm to choose certain points to represent as the actual dominoes in the simulation. We had all dominoes equally far apart from each other to ease calculations and have a nice flow to the falling.
The angle for each domino is calculated by facing the current domino towards the next domino (as you would in real life). After the user is done drawing his or her line, the program automatically calculates the angle for each domino and displays the dominoes in a 2D top-down view. This is to give the user a better view of what they have actually drawn before running it in 3D.

If the user chooses to do so, he or she can save the current setup to an output file. This allows the user to save favorite setups that he or she has previously created, and view them quickly. The output file is formatted in XML for easy understanding for humans. The user can also load a previous file. The program itself will read the xml and load it into appropriate data structure so that it can be run in 3D. This method can create and load very large files very quickly, so it is a good solution.


