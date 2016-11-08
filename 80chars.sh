# simple grep call to find lines over 80 characters
# within our source and header files
grep -nP "^.{81,}$" *.h *.c
