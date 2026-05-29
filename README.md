_This project has been created as part of the 42 curriculum by mnieto-m & agnesgar_

---

## Description

A 3D raycasting engine written in C, inspired by **Wolfenstein 3D (1992)**. From a 2D text map, the program renders a first-person view with textures, depth and real-time movement.

**Features:**
- Raycasting with optimized DDA algorithm
- Custom textures per wall orientation (N/S/E/W)
- Depth effect: distant walls appear darker (fog)
- Dynamic minimap
- Robust `.cub` file handling with full validation
- Keyboard events integrated with the MLX42 library

---

## Instructions and compilation

```bash
make
./cub3D maps/good/map_name.cub
```

Example:
```bash
./cub3D maps/good/cheese_maze.cub
```

| Action | Command |
|---|---|
| Clean objects | `make clean` |
| Clean everything | `make fclean` |
| Recompile | `make re` |

---

## Controls

| Key | Action |
|---|---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera |
| `ESC` or `X` | Quit |

---

## .cub file format

The map file has two sections: **header** and **map**.

```
NO textures/north.png       <- north wall texture
SO textures/south.png       <- south wall texture
WE textures/west.png        <- west wall texture
EA textures/east.png        <- east wall texture

F 220,100,0                 <- floor color (R,G,B)
C 225,30,0                  <- ceiling color (R,G,B)

        1111111111111
        1000000000001
        1011000N00001       <- N/S/E/W = player start position and orientation
        1000000000001
        1111111111111
```

**Valid map characters:**
| Character | Meaning |
|---|---|
| `1` | Wall |
| `0` | Walkable floor |
| `N` `S` `E` `W` | Player start position (orientation) |
| ` ` | Space (outside the map) |

**Parser validations:**
- File extension must be `.cub`
- Textures must exist and be valid PNG files
- F and C colors must have RGB values between 0 and 255
- The map must be fully enclosed by walls (`1`)
- There must be exactly one player
- The player cannot be on the map border
- No characters other than `01NSEW` and spaces are allowed
- Map normalization: padded into a rectangular shape

---

## Raycasting system

For each pixel column on screen, a ray is cast from the player's position. The ray angle varies based on `cam_x`, which goes from `-1` (leftmost column) to `+1` (rightmost column):

```
ray.dir = player.dir + player.plane * cam_x
```

The camera plane (`plane`) is perpendicular to the player's direction and its length determines the FOV (~66°).

### DDA algorithm

Instead of advancing the ray pixel by pixel, DDA jumps directly from grid line to grid line. At each step it compares which intersection is closer (X axis or Y axis) and only advances that one:

```
is side_x < side_y?
  yes → advance in X, side_x += delta_x
  no  → advance in Y, side_y += delta_y
```

`delta_x`/`delta_y` are the distance the ray travels between two consecutive grid lines on each axis.

### Perpendicular distance

When a wall is hit, the **perpendicular distance** (not Euclidean) is calculated to avoid the fish-eye effect: walls at the screen edges don't appear farther than walls at the center, even though the ray travels a longer path.

```
wall_dist → line_height = HEIGHT / wall_dist
```

The greater the distance, the smaller the vertical wall strip on screen.

### Textures

`wall_x` (the fractional part of where the ray hit the wall) determines which column of the texture to paint:

```
tex_x = wall_x * texture.width
```

The texture column is stretched or compressed vertically based on `line_height`.

---

## Project structure

```
cub3D/
├── src/
│   ├── main.c                      — entry point, argument validation
│   ├── init/
│   │   ├── init.c                  — t_data initialization
│   │   └── read_map.c              — .cub file reading
│   ├── parser/
│   │   ├── parse.c                 — parsing coordinator
│   │   ├── parse_textures.c        — texture path parsing
│   │   ├── parse_textures_utils.c  — texture utilities
│   │   ├── parse_color.c           — F/C color parsing
│   │   ├── validate_textures.c     — texture validation
│   │   ├── valid_map.c             — map validation and player position
│   │   └── normalize_map.c         — map normalization (space padding)
│   ├── exec/
│   │   ├── exec.c                  — MLX init, textures and main loop
│   │   ├── render.c                — core raycasting (DDA, distance, cam_x)
│   │   ├── draw.c                  — RGBA pixel writing to image buffer
│   │   ├── background.c            — ceiling and floor rendering
│   │   ├── orientation.c           — texture selection based on wall orientation
│   │   ├── player.c                — player movement and rotation
│   │   └── hooks.c                 — keyboard events and window close
│   └── error/
│       ├── error.c                 — error handling and exit
│       └── frees.c                 — memory cleanup
├── Include/
│   ├── cube.h                      — main structs (t_data, t_player, t_path)
│   ├── render.h                    — engine structs (t_game, t_ray, t_old)
│   ├── parsing.h                   — parser prototypes
│   └── error.h                     — error prototypes
├── maps/
│   ├── good/                       — valid test maps
│   └── bad/                        — invalid maps for parser testing
├── textures/                       — wall PNG textures
├── Libft/                          — custom library (ft_printf, ft_split, etc.)
└── MLX42/                          — graphics library (Codam)
```

## Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — main reference for the DDA algorithm
- [Ray Casting in C — Medium](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13)
- [MLX42 — Codam](https://github.com/codam-coding-college/MLX42)
- Beqa Tvildiani on YouTube
- OneLoneCoder on YouTube
- 3DSage on YouTube

---

_Project developed at 42 Madrid_
