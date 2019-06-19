//
// Created by astronaut on 11.05.19.
//
#ifndef REFACTOR_PULSE_CIRCLE_H
#define REFACTOR_PULSE_CIRCLE_H

#include <X11/Xlib.h>
#include <time.h>

#define true 1
#define false 0

/* Semi-Circle (pi) circle structure */

typedef struct {
  XPoint line[4];
  XPoint c; // 2 Semi-circles centeres c[1].x - c[0].x = R0
  float alpha[4];
  float radios;
  int length;  // Max circle angle
  int height;  // Min circle angle
  float angle; // Semi-circle angle from 0 to length
  float dPhy;  // angle in(de)crement (+R0 or -R0)
} XPiAr2;

/* Spiral Implementation function */

/**
 * check max circle angle
 * @param pr
 * @param R0xN
 * @param width
 * @param height
 * @return
 */
int max_size(XPiAr2 *pr, char *R0xN, unsigned int *width, unsigned int *height);

/**
 * Reset circle from center & window height
 * @param line
 * @return
 */
int reset(XPiAr2 *line);

/**
 * Redraw line fragment
 * @param event
 * @param gc
 * @param line
 * @return
 */
int redraw(XEvent *event, GC gc, XPiAr2 *line);

/**
 * Rotate line points
 * @param {XPiAr2*} line
 */
void rotate(XPiAr2 *line);
/**
 * Change center for semi-circle
 * @param pr
 * @param is_inc
 * @return
 */
int recent(XPiAr2 *pr, int is_inc);

/**
 * Rotate by circle track
 * @param dpy
 * @param win
 * @param gc
 * @param pr
 * @param is_inc
 * @return
 */
int twist(Display *dpy, Window win, GC gc, XPiAr2 *pr, const int *is_inc);
/**
 * On/Off autorepeat + or - key
 * @return
 */
int rep5355(Display *, int);

/**
 * Control to circle temp & freeze or exit
 * @param event
 * @param prev_code
 */
void get_event_code(XEvent *event, int *prev_code);

/**
 * Check visibility status
 * @param event
 * @return
 */
int overlap(XEvent *event);

/**
 * Make time delay for render
 * @param number_of_seconds
 */
void delay_func(int number_of_seconds);

/**
 * Press Button1 new rubber fragment origin
 * @param ev
 * @return
 */
int rubin(Display *dpy, Window win, XEvent *ev);

#endif // REFACTOR_PULSE_CIRCLE_H
