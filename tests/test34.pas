PROGRAM test34;
VAR
    i : INTEGER;
    arr : ARRAY[5] OF INTEGER;

BEGIN
  FOR i := 5 DOWNTO 0 DO
    arr[i-1] := i;
END.
