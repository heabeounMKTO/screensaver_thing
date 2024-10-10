#define TB_IMPL
#include "termbox2.h"
#include <stdio.h>
#include "vec.h"
#include <stdbool.h>
#include <time.h>

#define FPS 24
#define TIME_PER_FRAME 1000 / FPS


typedef struct  {
  Vec3 pos, dir, color;
} BitchAssLogo;

bool terminal2small_queen() {
    if (tb_height() < 10 || tb_width() < 10) {
        fprintf(stderr, "terminal 2 small comeon now\n");
        return true;
    }
    return false;
}

void move_bitchass_logo(BitchAssLogo *logo) {
  logo->pos.x += logo->dir.x;
  logo->pos.y += logo->dir.y;
  if(logo->pos.x == 0 || logo->pos.x == tb_width() - 3) {
    logo->dir.x *= -1;
    logo->color = vec3_add(logo->color, vec3_new(1.0f, 1.0f, 1.0f));
  }
  if(logo->pos.y == 0 || logo->pos.y == tb_height() - 3) {
    logo->dir.y *= -1;
    logo->color = vec3_add(logo->color, vec3_new(1.0f, 1.0f, 1.0f));
  }

}
uintattr_t get_color(Vec3 col) {
    const uintattr_t colors[] = {
        TB_RED,
        TB_GREEN,
        TB_YELLOW,
        TB_BLUE,
        TB_MAGENTA,
        TB_CYAN,
        TB_WHITE
    };
  int color_idx = (int) (vec3_dot(col, col) / 7);
  return colors[color_idx];
}

bool did_bro_quit() {
    struct tb_event event = { 0 };
    tb_peek_event(&event, TIME_PER_FRAME);
    if (event.ch == 'q')
        return true;
    return false;
}

void draw_shit(BitchAssLogo *logo){
    const uintattr_t fg = TB_BLACK | TB_BOLD | TB_ITALIC;
    const uintattr_t bg = get_color(logo->color);
    tb_set_clear_attrs(fg, fg);
    tb_clear();
    tb_set_cell(logo->pos.x, logo->pos.y, 'A', fg, bg);
    tb_set_cell(logo->pos.x + 1, logo->pos.y, 'Y', fg, bg);
    tb_set_cell(logo->pos.x + 2, logo->pos.y, 'Y', fg, bg);
    tb_present();
}

int main(int argc, char **argv) {

  srand(time(NULL));
  tb_init();
   printf("terminal w %d terminal h %d", tb_width(), tb_height()); 
  if (terminal2small_queen()) {
      return 1;
  }
  // having z = 0 might cause some bullshit dot prods maybe comeon now
  BitchAssLogo _alogo = {
    .pos = {.x = rand() % tb_width(), .y= rand() % tb_height(), .z=0.0},
    .dir = vec3_from_int(1),
    .color = vec3_from_int(1)
  };
  while(true) {
    move_bitchass_logo(&_alogo);
    // vec3_print(_alogo.pos);
    draw_shit(&_alogo);
    if(did_bro_quit()) {
      return 0;
    }
  }
}
