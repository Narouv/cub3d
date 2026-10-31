*This project has been created as part of the 42 curriculum by rnauke.*

# cub3D

## Description

cub3D is a small 3D game built from scratch in C, inspired by *Wolfenstein 3D*, the game that popularized the first-person-shooter genre. The goal of the project is to render a first-person view of a 2D maze — a technique known as "raycasting" — without any real 3D engine or game library.

The program reads a scene description file (`.cub`) containing a top-down map of the maze, wall texture paths, and floor/ceiling colors. It then opens a window and displays the maze from the player's point of view. The player can walk around the maze and look in different directions, with the view updating smoothly in real time.

Features:

- Raycasting engine rendering textured walls (north, south, east, west faces), floor, and ceiling
- Smooth movement and rotation with keyboard (WASD / arrow keys) and mouse look
- Minimap overlay showing the maze layout and player position
- Strict map parsing with extensive error handling (unclosed maps, invalid characters, duplicate or missing identifiers, and more)

## Instructions

### Dependencies

- A C compiler (clang/gcc)
- `make`, `cmake`, and `git`
- [GLFW](https://www.glfw.org/) (installed via Homebrew on macOS: `brew install glfw`)
- The [MLX42](https://github.com/codam-coding-college/MLX42) graphics library (cloned and built automatically by the Makefile)
- Developed and tested on macOS (Apple Silicon), with GLFW paths in the Makefile currently hard-coded to Homebrew

### Compilation

```sh
git clone https://github.com/Narouv/cub3d.git
cd cub3d
make
```

The first build clones MLX42 and compiles it with CMake, builds the bundled libft, and then compiles cub3D itself into the `cub3D` executable.

### Execution

```sh
./cub3D <map.cub>
```

Example maps can be found in the `maps/` directory:

```sh
./cub3D maps/map.cub
```

Controls:

| Key / Input      | Action                    |
| ---------------- | ------------------------- |
| `W` / `S`        | Move forward / backward   |
| `A` / `D`        | Strafe left / right       |
| `←` / `→`        | Rotate the camera         |
| Mouse            | Look around (mouse look)  |
| `ESC`            | Close the window and exit |

### Map file format

A valid `.cub` file consists of:

- Four texture paths, one per direction: `NO`, `SO`, `WE`, `EA`
- Two colors in `R,G,B` format: `F` (floor) and `C` (ceiling)
- A map made of `0` (empty space), `1` (wall), and exactly one player spawn (`N`, `S`, `E`, or `W`), fully enclosed by walls

```text
NO ./assets/north.png
SO ./assets/south.png
WE ./assets/west.png
EA ./assets/east.png

F 148,54,0
C 0,132,252

1111111111
1000000001
10000N0001
1111111111
```

The program must be given a valid map; invalid maps are rejected with a clear error message. Some maps in `maps/` are intentionally invalid and are kept for evaluation purposes.

## Resources

### References and documentation

- [Lode Vandevenne — Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html) — the classic step-by-step guide to raycasting, which the rendering engine is based on
- [Permadi's Raycasting FAQ](https://permadi.com/1996/05/ray-casting-tutorial-fs/) — another foundational raycasting walkthrough
- [MLX42 documentation](https://codam-coding-college.github.io/MLX42/) — the graphics library used for windowing and pixel drawing

### Use of AI

This project was made without any AI assistance 
