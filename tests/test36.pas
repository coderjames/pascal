PROGRAM test36;
TYPE person =
    RECORD
        name : STRING;
        age  : INTEGER;
    END;

VAR
    bob : person;

BEGIN
    bob.name := 'Bob Bear';
    bob.age  := 15;
END.
