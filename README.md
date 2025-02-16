# FdF - 42 School Project

## Introduction
FdF is a wireframe 3D height-map representation project for 42 School. The goal is to represent a 3D terrain from a given map file using the MiniLibX library. This project helps in understanding graphics programming, 3D projections, and file parsing.

## Features
- Parse a `.fdf` file to extract height data.
- Render a 3D wireframe projection using isometric or parallel views.
- Implement rotation, zoom, and movement controls.
- Handle color gradients for elevation effects.

## Installation
### Prerequisites
- A Unix-based system (Linux/macOS)
- `gcc` compiler
- `make`
- MiniLibX (available in 42’s environment)

### Build Instructions
```sh
make
```
This will generate the `fdf` executable.

## Usage
Run the program with:
```sh
./fdf maps/42.fdf
```
Replace `maps/42.fdf` with your own `.fdf` file.

## Controls
- `Arrow keys` → Move the map
- `+/-` → Zoom in/out
- `WASD` → Rotate the map
- `ESC` → Exit the program

## Guide & Explanation
For a detailed guide on implementing FdF, check out this article:
[Medium Guide to FdF](https://medium.com/@gamerazer007/fdf-42-guide-febb0e64da6e)

## Credits
Developed as part of the 42 School curriculum.
