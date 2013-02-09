PROGRAM test19;
VAR i : INTEGER;
BEGIN
  i := 0;
  BEGIN
    i := i + 1;  // i = 1
    BEGIN
      i := i * 2; // i = 2
    END
  END;
  BEGIN
    i := i * i; // i = 4
  END
END.
