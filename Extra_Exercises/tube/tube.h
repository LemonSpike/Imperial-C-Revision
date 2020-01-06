#ifndef TUBE_H
#define TUBE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <map>
#include <vector>
#include <cstdlib>

using namespace std;

enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

/* error codes for Question 3 */
#define ERROR_START_STATION_INVALID -1
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width);

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width);

/* pre-supplied helper function to describe errors for Question 3 */
const char *error_description(int code);

/* presupplied helper function for converting string to Direction enum */
Direction string_to_direction(const char *token);

bool get_symbol_position(char **m, int h, int w, char target, int &r, int &c);

char get_symbol_for_station_or_line(const char *name);

int validate_route(char **m, int h, int w, const char *station, string route,
                   char *dest, int num_lines = 0, char curr_line = ' ',
                   int dir_index = 0);

#endif
