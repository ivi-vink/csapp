// A.
struct P1 {
    int i;
    char c;
    int j;
    char d;
};
//      Largest primitive is 4, so the local alignment value must be 4
//      |int 4| char 1|gap 3 |int 4 |char 1|gap 3|
//      |-----|--------------|------|------------|
//         4          4          4         4
//      i   0
//      c   4
//      j   8
//      d   12
//
//      total 16
//
// B.
struct P2 {
    int i;
    char c;
    char d;
    long j;
};
//      Largest primitive is 8, so the local alignment value must be 8
//      |int 4|char 1| char 1|gap 2|long 8|
//      |--------------------------|------|
//                   8                8
//      i 0
//      c 4
//      d 5
//      j 8
//
//      total 16
//
// C.
struct P3 {
    short w[3];
    char c[3];
};
//      Largest primitive is 2, so the local alignment value must be 2
//      |short 2|short 2|short 2|char 1|char 1|char 1|gap 1|
//      |-------|-------|-------|-------------|------------|
//           2      2       2          2             2
//
//      w[0] 0
//      w[1] 2
//      w[2] 4
//      c[0] 6
//      c[1] 7
//      c[2] 8
//
//      total 10
//
// D.
struct P4 {
    short w[5];
    char *c[3];
};
//      Largest primitive is 8, so the local alignment value must be 8
//      |short 2|short 2|short 2|short 2|short 2|gap 6|char* 8|char* 8|char* 8|
//      |-------------------------------|-------------|-------|-------|-------|
//                      8                       8         8        8      8
//
//      w[0] 0
//      w[1] 2
//      w[2] 4
//      w[3] 6
//      w[4] 8
//      c[0] 16
//      c[1] 24
//      c[2] 32
//
//      total 40
// E.
struct P5 {
    struct P3 a[2];
    struct P2 t;
};
//      Largest primitive is 8, so the local alignment value must be 8
//      |P3 10|P3 10|gap 4|P2 16|
//
//      a[0] 0
//      a[1] 10
//      t    24
