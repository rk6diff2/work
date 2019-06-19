//
// Created by astronaut on 11.05.19.
//
#include "rotate_line.h"
#include <X11/Xutil.h>
#include <math.h>
#include <stdio.h>

const int PAUSE = -1;
const int STOP = 0;
const int RESUME = 1;

/* Check maximal (extern) semi-circle angle */
int max_size(XPiAr2 *pr, char *R0xN, unsigned int *width,
             unsigned int *height) {
  int empty = 0; /* for x & y */
  XParseGeometry(R0xN, &empty, &empty, (unsigned int *)width,
                 (unsigned int *)height);
  if (*height / 3 > *width / 2) {
    pr->length = *width / 2;
  } else {
    pr->length = *height / 3;
  }

  pr->angle = M_PI_2;
  pr->c.x = *width / 2;
  pr->c.y = *height / 2;
  pr->height = 1;
  pr->dPhy = atanf(pr->height * 2. / pr->length);
  pr->radios = sqrt(pr->height * pr->height + pr->length * pr->length / 4.);
  pr->alpha[0] = M_PI + pr->dPhy;
  pr->alpha[1] = -pr->dPhy;
  pr->alpha[2] = pr->dPhy;
  pr->alpha[3] = M_PI - pr->dPhy;

  for (int i = 0; i < 2; ++i) {
    pr->line[i].x = pr->c.x - pr->length / 2 + pr->length * i * 2 / 2;
    pr->line[i].y = pr->c.y - pr->height;
  }
  for (int i = 3; i >= 2; --i) {
    pr->line[i].x = pr->line[3 - i].x;
    pr->line[i].y = pr->c.y + pr->height;
  }
  for (int i = 0; i < 4; ++i) {
    printf("%d). x - %d; y - %d; alpha = %lf \n", i, pr->line[i].x,
           pr->line[i].y, pr->alpha[i]);
  }
  for (int i = 0; i < 4; ++i) {
    printf("%d). x - %f; y - %f; radios = %lf \n", i,
           pr->c.x + pr->radios * cosf(pr->alpha[i] + pr->dPhy),
           pr->c.y + pr->radios * sinf(pr->alpha[i] + pr->dPhy), pr->radios);
  }
  return pr->length; /* return maximal angle */
}

/* Reset circle from center */
int reset(XPiAr2 *pr) {
  //  pr->dPhy = atanf(pr->height * 2. / pr->length);
  //  pr->radios[0] = sqrt(pr->height * pr->height + pr->length * pr->length
  //  / 4.); pr->alpha[0] = M_PI + pr->dPhy; pr->alpha[1] = -pr->dPhy;
  //  pr->alpha[2] = pr->dPhy;
  //  pr->alpha[3] = M_PI - pr->dPhy;
  //  pr->angle = 0;
  //  pr->height = 0;
  //  pr->angle += pr->dPhy;
  //  return (2 * (pr->c.y)); /* return frame height */
  return 0;
}

/**
 * Rotate line points
 * @param {XPiAr2*} line
 */
void rotate(XPiAr2 *line) {
  for (int i = 0; i < 4; ++i) {
    line->line[i].x = line->c.x + line->radios * cosf(line->alpha[i] +
                                                      line->dPhy + line->angle);
    line->line[i].y = line->c.y + line->radios * sinf(line->alpha[i] +
                                                      line->dPhy + line->angle);
  }
}

/* redraw exposed circle fragment from center */
int redraw(XEvent *ev, GC gc, XPiAr2 *pr) {
  int y; /* ALT-X script y-location */
  y = reset(pr);
  int is_inc = 1;
  pr->angle = M_PI_2 - 3 * pr->dPhy;
  twist(ev->xexpose.display, ev->xexpose.window, gc, pr, &is_inc);
  XDrawString(ev->xexpose.display, ev->xexpose.window, gc, 8, y, "CTRL-C", 5);
  XSetClipMask(ev->xexpose.display, gc, None);
  return 0;
}

/* Change center for semi-circle (semi-step) */
int recent(XPiAr2 *pr, int is_inc) {
  if (is_inc) {
    pr->angle += 2 * pr->dPhy;
  } else {
    pr->angle -= 2 * pr->dPhy;
  }
  return 0;
}

/* 1 arc step by circle track */
int twist(Display *dpy, Window win, GC gc, XPiAr2 *pr, const int *is_inc) {
  int i = recent(pr, *is_inc);
  rotate(pr);
  XFillPolygon(dpy, win, gc, pr->line, 4, Convex, CoordModeOrigin);
  XFlush(dpy);
  return (pr->angle);
}

/* Turn On/Off autorepeat plus or minus key */
int rep5355(Display *dpy, int r) {
  XKeyboardControl kbval;
  kbval.key = XKeysymToKeycode(dpy, XK_KP_Add);
  kbval.auto_repeat_mode = r;
  XChangeKeyboardControl(dpy, (KBKey | KBAutoRepeatMode), &kbval);
  kbval.key = XKeysymToKeycode(dpy, XK_KP_Subtract);
  XChangeKeyboardControl(dpy, (KBKey | KBAutoRepeatMode), &kbval);
  return (r);
}

/* Keyboard Control to ac(de)celerate circle get_event_code or exit */
void get_event_code(XEvent *event, int *prev_code) {
  KeySym code[1]; /* key pressed symbol X code */
  XLookupString((XKeyEvent *)event, NULL, 0, code, NULL);
  switch (code[0]) {
  case XK_Pause: {
    *prev_code = PAUSE;
    break;
  }
  case XK_Return: {
    *prev_code = RESUME;
    break;
  }
  case XK_V:
  case XK_v: {
    if (event->xkey.state & ControlMask) {
      *prev_code = STOP; /* Ctrl-C to exit */
      break;
    }
  }
  }
}

/* Check Main Window Visibility to (un)freeze */
int overlap(XEvent *ev) {
  if (ev->xvisibility.state != VisibilityUnobscured)
    return (-32);
  return (0);
}

void delay_func(int number_of_seconds) {
  int milli_seconds = 1000 * number_of_seconds;
  clock_t start_time = clock();
  while (clock() < start_time + milli_seconds) {}
}

