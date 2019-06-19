/*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 * File Name : variant W12
 * Purpose : module exam
 * Creation Date : 18-06-2019
 * Last Modified : Вт 18 июн 2019 23:14:31
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*/

#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <stdio.h>
#include <stdlib.h>

#define BUTTON_NUM 33
#define true 1
#define false 0

const int step = 10;

typedef char bool;

typedef struct {
  int x[BUTTON_NUM];
  int y;
  unsigned int height;
  unsigned int size;
  int delta;
} Buttons;

int init_x(Display** display, Window* window, GC* gc) {
  *display = XOpenDisplay(NULL);
  int screen = DefaultScreen(*display);
  unsigned long black = BlackPixel(*display, screen);
  unsigned long white = WhitePixel(*display, screen);
  int width = DisplayWidth(*display, screen);
  int height = DisplayHeight(*display, screen) / 20;
  *window = XCreateSimpleWindow(*display, DefaultRootWindow(*display), 0, 0,
                                (unsigned int)width, (unsigned int)height, 2,
                                black, white);
  XSetStandardProperties(*display, *window, "Variant W12", "Hi", None, NULL, 0, NULL);
  XSelectInput(*display, *window,
               ExposureMask | ButtonPressMask | KeyPressMask);
  *gc = XCreateGC(*display, *window, 0, 0);
  XSetBackground(*display, *gc, white);
  XSetForeground(*display, *gc, black);
  XClearWindow(*display, *window);
  XMapRaised(*display, *window);
  return screen;
};

int btn_init(Buttons* buttons, int display_width, int display_heigth) {
  buttons->size = (unsigned int)(display_width / (BUTTON_NUM + 1));
  buttons->height = (unsigned int)(display_heigth / 2);
  buttons->y = 0;  // display_heigth - buttons->height;
  buttons->x[0] = 0;  // display_width - 5 * buttons->size;
  buttons->delta = 0;

  for (int i = 1; i < BUTTON_NUM; ++i) {
    buttons->x[i] = buttons->x[0] + i * buttons->size;
  }

  return 0;
}

int btn_handler(int ret[2], Buttons* buttons, int x, int y) {
  int f = 1;
  for (int i = 1; i < BUTTON_NUM - 1; ++i) {
    if (buttons->x[i] < x && x < buttons->x[i + 1]) {
      ret[0] = i;
      if (buttons->y + buttons->height < y) {
        ret[1] = 1;
        return 1;
      } else {
        ret[1] = 0;
        return 1;
      }
    }
    if (x < buttons->x[1] && y < buttons->y + buttons->height) {
      return -1;
    }
  }
  return 0;
}


int buttons_draw(Buttons *buttons, Display *display, const Window *window,
                const char btn_text[BUTTON_NUM][2][2], GC *gc) {
  for (int i = 0; i < BUTTON_NUM; ++i) {
    XDrawRectangle(display, *window, *gc, buttons->x[i], buttons->y, buttons->size,
                   buttons->height);
    XDrawRectangle(display, *window, *gc, buttons->x[i], buttons->y + buttons->height, buttons->size,
                   buttons->height);
    int shift_x = 20;
    int shift_y = 20;
    if (i != 0) {
      for (int j = 0; j < 2; ++j) {
        XDrawString(display, *window, *gc, buttons->x[i] + shift_x,
                    buttons->y + shift_y, btn_text[i][j],
                    (int)strlen(btn_text[i][j]));
        shift_y += buttons->height;
      }
    } else {
      XDrawString(display, *window, *gc, buttons->x[i] + shift_x,
                  buttons->y + shift_y, "Exit", 4);
    }

  }
  return 0;
}

int check(char c) { return c == '0'; }

int main(int argc, char** argv) {
  int height = 40;
  int width = 100;
  char* end = NULL;
  if (argc > 2) {
    height = (int)strtol(argv[1], &end, 10);
    width = (int)strtol(argv[2], &end, 10);
  }

  Display* display = NULL;
  GC gc;
  Window window;
  int scr_number = init_x(&display, &window, &gc);
  int display_width = DisplayWidth(display, scr_number);
  int display_height = DisplayHeight(display, scr_number);

  Buttons buttons;
  btn_init(&buttons, display_width, display_height / 20);

  XEvent event;

  int x = (display_width + width) / 2 - width;
  int y = (display_height + height) / 2 - height;

  int result = 0;
  bool sig_end = true;
  char btn_text[BUTTON_NUM][2][2] = {0};
  for (int i = 1; i < BUTTON_NUM; ++i) {
    btn_text[i][0][0] = '0';
    btn_text[i][1][0] = '1';
    for (int j = 0; j < 2; ++j) { btn_text[i][j][1] = '\0'; }
  }

  do {
    XNextEvent(display, &event);
    switch (event.type) {
      case ButtonPress: {
        int indexes[2];
        result = btn_handler(indexes, &buttons, event.xbutton.x, event.xbutton.y);
        if (result > 0) {
          int status = check(btn_text[indexes[0]][indexes[1]][0]);
          int col = 1 - indexes[1];
          btn_text[indexes[0]][indexes[1]][0] = status ? '1' : '0';
          btn_text[indexes[0]][col][0] = status ? '0' : '1';
          XClearWindow(display, window);
        } else if (result < 0) {
          sig_end = false;
        }
        break;
      }
    }

    buttons_draw(&buttons, display, &window, btn_text,&gc);
  } while (sig_end);

  return 0;
}
