// while (test)
//   body
//
//  goto test;
//  loop:
//      body;
//  test:
//      t = test;
//      if (t)
//          goto loop;

short loop_while(short a, short b)
{
    short result = 0;
    while (a > b) {
        result = result + a*b;
        a = a - 1;
    }
    return result;
}

int main(void) {
    return 0;
}
