#include "tube.h"

map<string, char> station_mapping;
map<string, char> line_mapping;
map<char, string> symbol_mapping;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

bool get_symbol_position(char **m, int h, int w, char target, int &r, int &c) {
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (m[i][j] == target) {
        r = i;
        c = j;
        return true;
      }
    }
  }
  r = -1;
  c = -1;
  return false;
}

void get_symbols(const char *filename) {
  ifstream in(filename);

  if (!in)
    cout << "Failed opening '" << filename << "'!" << endl;
  assert(in);

  if (in.peek() == EOF)
    cout << "'" << filename << "' was empty!" << endl;

  while (!in.eof()) {
    char symbol;
    in >> symbol >> ws;
    if (in.eof())
      break;
    char desc[512];
    in.getline(desc, 512);
    (!strcmp(filename,"stations.txt") ? station_mapping : line_mapping).
      insert(pair<string, char>(desc, symbol));
    symbol_mapping.insert(pair<char, string>(symbol, desc));
  }
}

char get_symbol_for_station(const char *name) {
 if (station_mapping.count(name))
    return station_mapping[name];

  get_symbols("stations.txt");

  if (station_mapping.count(name))
    return station_mapping[name];

  return ' ';
}

char get_symbol_for_line(const char *name) {
 if (line_mapping.count(name))
    return line_mapping[name];

  get_symbols("lines.txt");

  if (line_mapping.count(name))
    return line_mapping[name];

  return ' ';
}

char get_symbol_for_station_or_line(const char *name) {

  if (get_symbol_for_station(name) != ' ')
    return get_symbol_for_station(name);

  if (get_symbol_for_line(name) != ' ')
    return get_symbol_for_line(name);

  return ' ';
}

int move(char **m, int h, int w, const char *move, int &r, int &c) {
  int orig_r = r;
  int orig_c = c;

  
  if (!strcmp(move, "N")) {
    r--;
  } else if (!strcmp(move, "S")) {
    r++;
  } else if (!strcmp(move, "W")) {
    c--;
  } else if (!strcmp(move, "E")) {
    c++;
  } else if (!strcmp(move, "NW")) {
    c--;
    r--;
  } else if (!strcmp(move, "NE")) {
    c++;
    r--;
  } else if (!strcmp(move, "SW")) {
    c--;
    r++;
  } else if (!strcmp(move, "SE")) {
    c++;
    r++;
  } else {
    return ERROR_INVALID_DIRECTION;
  }

  if (c >= w or c < 0)
    return ERROR_OUT_OF_BOUNDS;
  if (r >= h or r < 0)
    return ERROR_OUT_OF_BOUNDS;

  if (m[r][c] == ' ')
    return ERROR_OFF_TRACK;

  char sym = m[orig_r][orig_c];

  if (!isalnum(sym) and !isalnum(m[r][c]) and m[r][c] != sym)
    return ERROR_LINE_HOPPING_BETWEEN_STATIONS;

  return 0;
}

int validate_route(char **m, int h, int w, const char *station, string route,
                   char *dest, int num_lines, char curr_line, int dir_index) {

  char s_symbol = get_symbol_for_station(station);
  if (s_symbol == ' ')
    return ERROR_START_STATION_INVALID;

  int r = -1, c = -1;
  get_symbol_position(m, h, w, s_symbol, r, c);

  vector< vector<int> > past_points;

  vector<int> point;
  point.push_back(r);
  point.push_back(c);

  past_points.push_back(point);
  point.clear();

  while (route[dir_index] != '\0') {
    string dir;
    while (route[dir_index] != '\0' and route[dir_index] != ',') {
      dir += route[dir_index++];
    }
    int res = move(m, h, w, dir.c_str(), r, c);
    if (res)
      return res;

    if (m[r][c] != curr_line) {
      curr_line = m[r][c];
      num_lines++;
    }
    if (route[dir_index] != '\0')
      dir_index++;

    if (isalnum(m[r][c])) {
      validate_route(m, h, w, symbol_mapping[(m[r][c])].c_str(), route,
                     dest, num_lines, curr_line, dir_index);
    }
  }
  if (isalnum(m[r][c])) {
    strcpy(dest, symbol_mapping[(m[r][c])].c_str());
    return num_lines;
  }
  return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
}
