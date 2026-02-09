*This project has been created as part of the 42 curriculum by ejakob & pjelinek*

**Description**
The objective of this project is to create a 3D representation of a 2D map from a first-person perspective.
This should be achieved by making use of raycasting, a semi-3D rendering technique. Raycasting is fast and relatively simple because it requires only a calculation per vertical line of the field of view. But it also has its limitations for example, it is not really suitable for stairs or other height differences.

**Instructions**
1. Compile the project by running:
```
```
```
make
```
```
```
2. Once that's done launch the game with:
```
./cub3D path/to/map.cub
```
```
```
Replace the `path/to/map.cub` with the path any valid `.cub` file.
3. Game controls:
	- W / A / S / D - Move forward, left, backward and right
	- Left / Right arrow - Rotate camera
	- ESC / Window close button - Exit the game

**Resources**
- [Article about raycasting (from 2004, very helpful)](https://lodev.org/cgtutor/raycasting.html)
- [Video about raycasting and DDA](https://youtu.be/NbSee-XM7WA?si=0FXNL3mGN3ZycY1X)
- [MiniLibX Docs](https://harm-smits.github.io/42docs/libs/minilibx)

AI was used for the exploratory part of this project (conceptual understanding of raycasting, etc.)
