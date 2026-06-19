#!/bin/sh

file="$1"
guard="${file^^}_H"

{
    echo "#ifndef $guard"
    echo "#define $guard"
    echo

    grep '^[a-zA-Z_].*(' "$file.c" | sed 's/{.*$/;/'

    echo
    echo "#endif /* $guard */"
} > "$file.h"
