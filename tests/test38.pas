PROGRAM test38;

PROCEDURE echo( msg : STRING; times : INTEGER );
VAR
    i : INTEGER;
BEGIN
    FOR i := 0 TO times DO
        writelin( msg );
END;

BEGIN
    echo( 'Hello, world!', 4 )
END.
