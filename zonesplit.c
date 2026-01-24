// Copyright William Stafford Parsons

#include <stdint.h>
#include <stdio.h>

int rotate;
uint16_t increase;

struct zonesplit_state {
  uint8_t a;
  uint8_t b;
};

uint8_t zonesplit(struct zonesplit_state *s) {
  s->a = ((s->a << rotate) | (s->a >> (8 - rotate))) ^ s->b;
  s->b += increase;
  return s->a;
}

int main(void) {
  struct zonesplit_state s;
  unsigned short i = 0;
  unsigned short j;

  while (i < 256) {
    j = 0;

    while (j < 256) {
      rotate = 1;

      while (rotate < 8) {
        increase = 1;

        while (increase < 256) {
          s.a = i;
          s.b = j;
          zonesplit(&s);

          while (s.b != j) {
            zonesplit(&s);
          }

          if (s.a != i) {
            printf("The state overlaps when a is %u and b is %u\n", s.a, s.b);
          }

          increase += 2;
        }

        rotate++;
      }

      j++;
    }

    i++;
  }

  return 0;
}
