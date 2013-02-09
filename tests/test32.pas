PROGRAM test32;
LABEL
    1;

VAR
    index : INTEGER;

BEGIN
  index := 5;
  GOTO 1;
  index := 0;
  1: IF index > 0 THEN writeln('PASS');
  IF index = 0 THEN writeln('FAIL');
END.
