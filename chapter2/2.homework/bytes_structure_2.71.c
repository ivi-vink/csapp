#include <stdio.h>
#include <string.h>

typedef unsigned packed_t;

/*
  3    2    1    0
  byte byte byte byte
  1000 1100 1110 1111
  xbyte(..., 2);
  >> 8
  0000 0000 1000 1100
  & 0xFF
  0000 0000 0000 1100

  0 <= x < 7 -> id
  -8 < x <  0 -> minus
*/
int xbyte(packed_t word, int bytenume);
int xbyte(packed_t word, int bytenum) {
    int max_bytes = 3;
    int max_bits = max_bytes << 3;
    int shift_bits = (3 - bytenum) << 3;
    return (int) word << shift_bits >> max_bits;
}

/*
  Copy integer into buffer if space is available
  WARNING: The following code is buggy

  size_t is an unsigned. So one of the operands gets casted.
  Either
  int -> unsigned
  or
  unsigned -> int

  apparently the result of unsigned - int or int - unsigned -> unsigned
 */
void buggy_copy_int(int val, void *buf, int maxbytes) {
    /*
      Check if maxbytes will cause problems when converted to unsigned.
     */
    if (maxbytes < 0) {
        return;
    }
    if (maxbytes >= sizeof(val)) {
        memcpy(buf, (void *) &val, sizeof(val));
    }
}

int main() {
    int maxbytes = 4;
    char buf[maxbytes];
    int i;
    for (i=0; i<maxbytes; ++i) {
        buf[i] = 'a';
    }

    buggy_copy_int(32, buf, maxbytes);
    for (i=0; i<maxbytes; ++i) {
        printf("%x\n", buf[i]);
    }
    return 0;

    printf("%x\n", xbyte(0x0000FF00, 1));
    return 0;
}
