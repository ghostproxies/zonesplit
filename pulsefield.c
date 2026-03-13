#include <stdint.h>
#include <stdio.h>

int circular_shift;
unsigned short odd_increase;

struct pulsefield_state {
  uint8_t a;
  uint8_t b;
};

void pulsefield(struct pulsefield_state *s) {
  s->a = ((s->a << circular_shift) | (s->a >> (8 - circular_shift))) ^ s->b;
  s->b += odd_increase;
}

int main(void) {
  struct pulsefield_state s;
  unsigned short i = 0;
  unsigned short j;

  while (i < 256) {
    j = 0;

    while (j < 256) {
      circular_shift = 1;

      while (circular_shift < 8) {
        odd_increase = 1;

        while (odd_increase < 256) {
          s.a = i;
          s.b = j;
          pulsefield(&s);

          while (s.b != j) {
            pulsefield(&s);
          }

          if (s.a != i) {
            printf("The state collides when a is %u and b is %u.\n", s.a, s.b);
          }

          odd_increase += 2;
        }

        circular_shift++;
      }

      j++;
    }

    i++;
  }

  return 0;
}
