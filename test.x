//
//  Test.x
//
//  This is a comment
//

AA = 3;
BB = 5;
CC = 7;

Print(AA);
Print(BB);
Print(CC);

AA = 53;
BB = 47;
CC = AA + BB;

Print(2 * CC);

Print(1*2 + 4*3);

Print((1 + 2) * (4 + 5));


Print(5 ? 7 : 9);
Print(0 ? 7 : 9);

Assert((5 ? 7 : 9) == 7);
Assert((0 ? 7 : 9) == 9);

Assert((1*2 + 4*3) == 14);

Assert(((1 + 2) * (4 + 5)) == 27);

Assert(0xff == 255);

Print(0xff);

Assert((0x0f & 1) == 1);

Assert((0xff & ~0x55) == 0xaa);

// Assert((2*5 - 10 ? 7 : 23) == 23);

Assert(~0 == -1);

