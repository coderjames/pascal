PROGRAM test15;
TYPE
    INTPTR = ^INTEGER;

VAR
    index : INTEGER;
    ptr   : ^INTEGER;
    ptrptr : ^INTPTR;

BEGIN
  index := 0;
  ptr := @index;
  ptrptr := @ptr;

END.
