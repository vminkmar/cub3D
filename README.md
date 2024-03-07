# **cub3D - RayCaster with miniLibX**

cub3D is a project inspired by the iconic Wolfenstein 3D. Developed in C and utilizing the miniLibX library, this project aims to create a realistic 3D graphical representation of a maze from a first-person perspective, following the principles of Ray-Casting.

## **Program Overview**
cub3D aims to create a 3D graphical representation of a maze using Ray-Casting principles. Key features include:

- Smooth window management.
- Display of different wall textures based on orientation.
- Adjustable floor and ceiling colors.
- User-controlled navigation within the maze.
- Scene description through a dedicated file.
- Adhere to the Norm for coding standards.
- Avoid unexpected program termination (segmentation fault, bus error, etc.).
- Free all heap-allocated memory appropriately.

## **Usage**
To compile and run the program, use the provided Makefile:

`make`

`./cub3D path/to/your/map.cub`

### **User Controls:**

- Navigate through the maze using the W, A, S, and D keys for forward, left, backward, and right movements, respectively.

### Dynamic Textures:

- Render diverse wall textures based on orientation (North, South, East, West), creating a visually immersive 3D graphical representation.
Utilize Ray-Casting principles to dynamically apply textures, providing a realistic and engaging environment.

### Customizable Colors:

- Set distinct floor and ceiling colors to enhance the atmosphere of the maze.
Define colors using RGB values in the range [0, 255], allowing for personalized and visually appealing environments.

### Map:

- Define the maze using 6 possible characters: 0 for an empty space, 1 for a wall, and N/S/E/W for the player's start position and spawning orientation.
Map Integrity:

- Ensure the map is closed/surrounded by walls; otherwise, the program returns an error.

- Parse the map as it appears in the file, handling spaces as valid parts of the map.

- If misconfigurations are encountered, the program exits with an "Error\n" message, followed by an explicit error message for user understanding.
