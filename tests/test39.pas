PROGRAM test39;

VAR
    i : INTEGER;

FUNCTION monkey( cstr : ^CHAR ) : INTEGER;
BEGIN
  i := 0;
  WHILE cstr^ <> 0 DO
    BEGIN
    i := i + 1;
    cstr := cstr + 1;
    END;
    
    monkey := i;
END;

BEGIN
    filbert := monkey( PCHAR('Hello, World') );
END.
