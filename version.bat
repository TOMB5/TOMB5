git rev-parse HEAD > version.txt

set /p HASH = < version.txt

echo #define GIT_COMMIT_HASH %HASH% > version.h

del version.txt