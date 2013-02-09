PROGRAM test35;
TYPE person =
    RECORD
        name : STRING;
        age  : INTEGER;
    END;

VAR
    i : INTEGER;
    family : ARRAY[5] OF person;

BEGIN
  FOR i := 0 TO 5 DO
    BEGIN
    family[i].name := 'Person';
    family[i].age  := i * 10;
    END;
END.
