
#include <curses.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <termios.h>

#define MAX_FILES 256

typedef struct {
  char filename[256];
  int is_dir;
} FileInfo;

typedef enum { LEFT, RIGHT } window;

WINDOW *left_wnd, *right_wnd;

FileInfo left_data[MAX_FILES];
FileInfo right_data[MAX_FILES];

int left_file_count;
int right_file_count;

int left_selected_row;
int right_selected_row;
int left_start_row;
int right_start_row;

window curr_window;
window prev_window;

void display_table(WINDOW* win,
                   FileInfo* data,
                   int total_rows,
                   int start_row,
                   int selected_row,
                   int is_focused);

void run_file_manager();

void sig_winch();
int compare_file_info(const void* a, const void* b);
void load_directory(const char* path, FileInfo* data, int* file_count);
void navigate_directory(FileInfo* data, int selected_row, char* current_path);
void handle_keyboard_event(int ch, char* left_path, char* right_path);

void run_file_manager() {
  initscr();
  signal(SIGWINCH, sig_winch);
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  refresh();

  curr_window = LEFT;
  prev_window = RIGHT;

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  left_wnd = newwin(rows, cols / 2, 0, 0);

  right_wnd = newwin(rows, cols / 2, 0, cols / 2);

  char left_path[512] = ".";
  char right_path[512] = ".";

  load_directory(left_path, left_data, &left_file_count);
  load_directory(right_path, right_data, &right_file_count);

  display_table(left_wnd, left_data, left_file_count, left_start_row,
                left_selected_row, curr_window == LEFT);
  display_table(right_wnd, right_data, right_file_count, right_start_row,
                right_selected_row, curr_window == RIGHT);

  wrefresh(left_wnd);
  wrefresh(right_wnd);

  while (true) {
    int ch = wgetch(stdscr);
    if (ch == 'q') {
      break;
    } else if (ch == KEY_RESIZE) {
      sig_winch(1);
    } else {
      handle_keyboard_event(ch, left_path, right_path);
    }
  }

  delwin(left_wnd);
  delwin(right_wnd);
  endwin();
  exit(EXIT_SUCCESS);
}

void display_table(WINDOW* win,
                   FileInfo* data,
                   int total_rows,
                   int start_row,
                   int selected_row,
                   int is_focused) {
  int height = getmaxy(win); 
  int width = getmaxx(win);
  int name_width = width / 2;

  werase(win);
  for (int i = 0; i < height && (i + start_row) < total_rows; ++i) {
    if (is_focused && (i + start_row) == selected_row) {
      wattron(win, A_REVERSE);
    }
    mvwprintw(win, i + 2, 1, "%-*s ", name_width,
              data[i + start_row].filename);
    if (is_focused && (i + start_row) == selected_row) {
      wattroff(win, A_REVERSE);
    }
  }
  wrefresh(win);
}

void sig_winch() {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
  resizeterm(size.ws_row, size.ws_col);

  wresize(left_wnd, size.ws_row, size.ws_col / 2);
  mvwin(left_wnd, 0, 0);
  display_table(left_wnd, left_data, left_file_count, left_start_row,
                left_selected_row, curr_window == LEFT);

  wresize(right_wnd, size.ws_row, size.ws_col / 2);
  mvwin(right_wnd, 0, size.ws_col / 2);
  display_table(right_wnd, right_data, right_file_count, right_start_row,
                right_selected_row, curr_window == RIGHT);

  wrefresh(left_wnd);
  wrefresh(right_wnd);

  keypad(stdscr, TRUE);
  refresh();
}

int compare_file_info(const void* a, const void* b) {
  FileInfo* file1 = (FileInfo*)a;
  FileInfo* file2 = (FileInfo*)b;

  if (file1->is_dir != file2->is_dir) {
    return file2->is_dir - file1->is_dir;
  }
  return strcmp(file1->filename, file2->filename);
}

void load_directory(const char* path, FileInfo* data, int* file_count) {
  DIR* dir;
  struct dirent* entry;
  struct stat statbuf;

  *file_count = 0;

  if ((dir = opendir(path)) == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0) {
      continue;
    }

    FileInfo file_info;
    snprintf(file_info.filename, sizeof(file_info.filename), "%s",
             entry->d_name);

    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
    stat(fullpath, &statbuf);
    file_info.is_dir = S_ISDIR(statbuf.st_mode);
    data[*file_count] = file_info;
    (*file_count)++;
  }

  closedir(dir);
}

void navigate_directory(FileInfo* data, int selected_row, char* current_path) {
  if (data[selected_row].is_dir) {
    strcat(current_path, "/");
    strcat(current_path, data[selected_row].filename);
    load_directory(
        current_path, data,
        (curr_window == LEFT) ? &left_file_count : &right_file_count);
    if (curr_window == LEFT) {
      left_start_row = left_selected_row = 0;
    } else {
      right_start_row = right_selected_row = 0;
    }
  }
}

void handle_keyboard_event(int ch, char* left_path, char* right_path) {
  int height_left = getmaxy(left_wnd) - 5;
  int height_right = getmaxy(right_wnd) - 5;

  switch (ch) {
    case '\t':
      prev_window = curr_window;
      curr_window = (curr_window == LEFT) ? RIGHT : LEFT;
      display_table(left_wnd, left_data, left_file_count, left_start_row,
                    left_selected_row, curr_window == LEFT);
      display_table(right_wnd, right_data, right_file_count, right_start_row,
                    right_selected_row, curr_window == RIGHT);
      break;
    case KEY_UP:
      if (curr_window == LEFT) {
        if (left_selected_row > 0) {
          left_selected_row--;
          if (left_selected_row < left_start_row) {
            left_start_row--;
          }
        }
        display_table(left_wnd, left_data, left_file_count, left_start_row,
                      left_selected_row, curr_window == LEFT);
      } else {
        if (right_selected_row > 0) {
          right_selected_row--;
          if (right_selected_row < right_start_row) {
            right_start_row--;
          }
        }
        display_table(right_wnd, right_data, right_file_count, right_start_row,
                      right_selected_row, curr_window == RIGHT);
      }
      break;
    case KEY_DOWN:
      if (curr_window == LEFT) {
        if (left_selected_row < left_file_count - 1) {
          left_selected_row++;
          if (left_selected_row >= left_start_row + height_left) {
            left_start_row++;
          }
        }
        display_table(left_wnd, left_data, left_file_count, left_start_row,
                      left_selected_row, curr_window == LEFT);
      } else {
        if (right_selected_row < right_file_count - 1) {
          right_selected_row++;
          if (right_selected_row >= right_start_row + height_right) {
            right_start_row++;
          }
        }
        display_table(right_wnd, right_data, right_file_count, right_start_row,
                      right_selected_row, curr_window == RIGHT);
      }
      break;
    case '\n':
      if (curr_window == LEFT) {
        navigate_directory(left_data, left_selected_row, left_path);
        display_table(left_wnd, left_data, left_file_count, left_start_row,
                      left_selected_row, curr_window == LEFT);
      } else {
        navigate_directory(right_data, right_selected_row, right_path);
        display_table(right_wnd, right_data, right_file_count, right_start_row,
                      right_selected_row, curr_window == RIGHT);
      }
      break;
  }
}

int main() {
  run_file_manager();
}
