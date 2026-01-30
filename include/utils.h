#ifndef H_UTILS
#define H_UTILS

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 300
#define SCREEN_CENTER_X SCREEN_WIDTH / 2
#define SCREEN_CENTER_Y SCREEN_HEIGHT / 2

#define FULL_SCREEN_RECT (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}

#define CENTERED_RECT(ref, r_width, r_height, x_off, y_off) (Rectangle){(ref.width / 2 + ref.x) - r_width/2 + x_off, (ref.height / 2 + ref.y) - r_height/2 + y_off, r_width, r_height}

#endif