struct {
    char *a;
    short b;
    double c;
    char d;
    float e;
    char f;
    long g;
    int h;
} rec;
// A.
//      |char* 8|short 2|gap 6|double 8|char 1|float 4|char 1|gap 2|long 8|int 4|gap 4|
//      |-------|-------------|--------|---------------------------|------|-----------|
//          8           8          8                  8                8        8
//
//      a 0
//      b 8
//      c 16
//      d 24
//      e 25
//      f 29
//      g 32
//      h 40
//
// B.
//      48
//
// C.
//      |char* 8|short 2|char 1|float 4|char 1|double 8|long 8|int 4|gap 4|
//      |-------|-----------------------------|--------|------|-----------|
//          8                  8                  8        8        8
//
//      a 0
//      b 8
//      c 16
//      d 10
//      e 11
//      f 15
//      g 24
//      h 32
//
//      total 40
