// #include "../inc/cub3d.h"
// #include <stdio.h>
// #include <math.h>

// // Custom function to place a pixel at (x, y) on the window
// void placePixel(int x, int y, int color) {
//     // Your window management framework should provide a way to set pixels
//     // Example: SetPixel(x, y, color);
//     printf("Placing pixel at (%d, %d) with color %d\n", x, y, color);
// }

// // Custom function to load an image at (x, y) on the window
// void placeImage(int x, int y, const char* imageName) {
//     // Your window management framework should provide a way to display images
//     // Example: LoadImage(imageName, x, y);
//     printf("Loading image '%s' at (%d, %d)\n", imageName, x, y);
// }

// char map[8][8] = {
//     "11111111",
//     "10000001",
//     "10000001",
//     "10000001",
//     "10000001",
//     "10000001",
//     "10000001",
//     "11111111"
// };

// // Raycasting function
// void raycast(mlx_image_t *img) {
//     for (int x = 0; x < WIDTH; x++) {
//         // Calculate ray direction and initial position
//         double cameraX = 2 * x / (double)WIDTH - 1;
//         double rayDirX = 1;
//         double rayDirY = 0;

//         // Position of the camera/player
//         double posX = 6;
//         double posY = 6;

//         // Length of the ray from current position to next x or y-side
//         double sideDistX;
//         double sideDistY;

//         // Length of ray from one x or y-side to next x or y-side
//         double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
//         // double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

//         // Length of the ray
//         double perpWallDist;

//         // Direction to step in x or y
//         int stepX;
//         int stepY;

//         // Hit wall indicator
//         int hit = 0;

//         // Determine the direction to step in x and y
//         if (rayDirX < 0) {
//             stepX = -1;
//             sideDistX = (posX - floor(posX)) * deltaDistX;
//         } else {
//             stepX = 1;
//             sideDistX = (ceil(posX) - posX) * deltaDistX;
//         }
//         if (rayDirY < 0) {
//             stepY = -1;
//             sideDistY = (posY - floor(posY)) * deltaDistX;
//         } else {
//             stepY = 1;
//             sideDistY = (ceil(posY) - posY) * deltaDistX;
//         }

//         // DDA algorithm loop
//         while (!hit) {
//             // Jump to the next map square, either in x or y direction
//             if (sideDistX < sideDistY) {
//                 sideDistX += deltaDistX;
//                 posX += stepX;
//                 perpWallDist = (posX - cameraX + (1 - stepX) / 2) / rayDirX;
//             } else {
//                 sideDistY += deltaDistX;
//                 posY += stepY;
//                 perpWallDist = (posY - cameraX + (1 - stepY) / 2) / rayDirX;
//             }

//             // Check if the ray hit a wall
//             // You should implement your own logic to check for collisions with the map
//             // For simplicity, I'm assuming a hit when posX and posY are integers
//             int mapX = (int)posX/10;
//             int mapY = (int)posY/10;
//             if (mapX >= 0 && mapX < 8 && mapY >= 0 && mapY < 8 && map[mapX][mapY] == '1') {
//                 hit = 1;
//             }
//         }

//         // Calculate the height of the wall slice to draw
//         int lineHeight = (int)(HEIGHT / perpWallDist);

//         // Calculate the starting and ending positions for drawing the wall slice
//         int drawStart = -lineHeight / 2 + HEIGHT / 2;
//         if (drawStart < 0) {
//             drawStart = 0;
//         }
//         int drawEnd = lineHeight / 2 + HEIGHT / 2;
//         if (drawEnd >= HEIGHT) {
//             drawEnd = HEIGHT - 1;
//         }

//         // Draw the wall slice
//         // For simplicity, just draw a vertical line at position x
//         for (int y = drawStart; y <= drawEnd; y++) {
//             mlx_put_pixel(img, x, y, 0xFFFFFFFF);  // You can set the color as needed
//         }
//     }
// }

// void crtl(void *mlx)
// {
// 	if (mlx_is_key_down((mlx_t*)mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window((mlx_t*)mlx);
// 	if (mlx_is_key_down((mlx_t*)mlx, MLX_KEY_W))
// 		mlx_close_window((mlx_t*)mlx);
// }

// int main() {
//     // Initialize your custom window framework here
// 	mlx_t				*mlx;
// 	static mlx_image_t	*image;

// 	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
// 	if (!mlx)
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		exit(EXIT_FAILURE);
// 	}
// 	image = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	if (!image)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		exit(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		exit(EXIT_FAILURE);
// 	}
//     // Call the raycasting function to render the scene
//     raycast(image);

//     // Main loop for your custom window framework
// 	mlx_loop_hook(mlx, crtl, mlx);
// 	mlx_loop(mlx);


//     return 0;
// }
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 140
#define SCREEN_HEIGHT 40
#define FOV_ANGLE M_PI / 3
#define NUM_RAYS SCREEN_WIDTH
#define TILE_SIZE 1
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
    float angle;
} Player;

typedef struct {
    Vector2 wall_hit;
    float distance;
} RayHit;

Player player;

float normalize_angle(float angle) {
    angle = fmodf(angle, 2.0f * M_PI);
    if (angle < 0) {
        angle += 2.0f * M_PI;
    }
    return angle;
}

int cast_ray(float ray_angle, RayHit *hit) {
    float x = player.position.x;
    float y = player.position.y;
    // float slope = tanf(ray_angle);
    float dx, dy;
    
    if (ray_angle > M_PI && ray_angle < 2 * M_PI) {
        dx = TILE_SIZE;
        dy = -TILE_SIZE;
    } else if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI) {
        dx = TILE_SIZE;
        dy = -TILE_SIZE;
    } else if (ray_angle > 0.5 * M_PI && ray_angle < 1.5 * M_PI) {
        dx = -TILE_SIZE;
        dy = TILE_SIZE;
    } else {
        dx = -TILE_SIZE;
        dy = TILE_SIZE;
    }

    while (x >= 0 && x < 200 && x < MAP_WIDTH * TILE_SIZE && y >= 0 && y < MAP_HEIGHT * TILE_SIZE) {
        int map_x = (int)(x / TILE_SIZE);
        int map_y = (int)(y / TILE_SIZE);

        if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT) {
            if (map[map_x][map_y] == 1) {
                hit->wall_hit.x = x;
                hit->wall_hit.y = y;
                hit->distance = sqrtf((player.position.x - x) * (player.position.x - x) +
                                      (player.position.y - y) * (player.position.y - y));
                return 1;
            }
        }

        x += dx;
        y += dy;
    }

    return 0;
}

void render() {
    char screen[SCREEN_WIDTH][SCREEN_HEIGHT];

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float ray_angle = player.angle - (FOV_ANGLE / 2) + ((x / (float)SCREEN_WIDTH) * FOV_ANGLE);
        RayHit hit;
        if (cast_ray(normalize_angle(ray_angle), &hit)) {
            int wall_height = SCREEN_HEIGHT / (2 * hit.distance * cosf(ray_angle - player.angle));
			printf("%i  %i\n", wall_height, wall_height / 2);
            for (int y = 0; y < SCREEN_HEIGHT; y++) {
                if (y < SCREEN_HEIGHT / 2 - wall_height / 2) {
                    screen[x][y] = ' ';
                } else if (y < SCREEN_HEIGHT / 2 + wall_height / 2) {
                    screen[x][y] = '#';
                } else {
                    screen[x][y] = ' ';
                }
            }
        } else {
            for (int y = 0; y < SCREEN_HEIGHT; y++) {
                screen[x][y] = ' ';
            }
        }
    }

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            printf("%c", screen[x][y]);
        }
        printf("\n");
    }
}

int main() {
    player.position.x = 3.5;
    player.position.y = 3.5;
    player.angle = M_PI / 4;

	render();
    while (1) {
        // Update game logic
        // player.angle += 0.01;
        // Render the scene
		// system("clear");
        
		// usleep(50);
    }
	
    return 0;
}
