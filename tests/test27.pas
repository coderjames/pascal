PROGRAM test27;
VAR
    i : INTEGER;
    arr : ARRAY[5] OF INTEGER;

BEGIN
  i := 0;
  WHILE i < 5 DO
    BEGIN
    arr[i] := i;
    i := i + 1;
    END
END.
