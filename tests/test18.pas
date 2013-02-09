PROGRAM test18;
VAR
    i : INTEGER;

FUNCTION increment( val : INTEGER ) : INTEGER;
BEGIN
  increment := val + 1;
END;

BEGIN
    i := increment(0);
END.
