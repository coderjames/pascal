PROGRAM test30;
VAR
    i : INTEGER;

PROCEDURE increment( val : ^INTEGER );
BEGIN
  val^ := val^ + 1;
END;

BEGIN
    i := 0;
    increment(@i);
END.
