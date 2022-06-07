#!/bin/bash

# https://stackoverflow.com/questions/2826029/passing-additional-variables-from-command-line-to-make


BASE_DIR="my_test"

# Find all main files
SRC=$(find './mains' -name '*_*.cpp' -printf '%p ')
echo $SRC
# Split them
IFS=' '
read -ra SRC <<< "$SRC"


echo "There are ${#SRC[*]} main files to tests."
for MAIN_FILE in ${SRC[@]}; do
    SRC_NAME=$(cut -d'_' -f2 <<< $MAIN_FILE | cut -d'.' -f1)
    DIR_NAME="$BASE_DIR/res_$SRC_NAME"
    echo
    echo "--------------------------------"
    echo "| STARTING TESTS FOR : $SRC_NAME |"
    echo "--------------------------------"
    echo

    mkdir -p $DIR_NAME

    FT_RES="$DIR_NAME/ft_tests_res"
    STD_RES="$DIR_NAME/std_tests_res"

    make fclean
    make SRC=$MAIN_FILE
    ./Container > $FT_RES 2>&1
    make fclean
    make gostd SRC=$MAIN_FILE
    ./Container > $STD_RES 2>&1

    DIFF=$(diff $FT_RES $STD_RES)

    echo $DIFF > "$DIR_NAME/diff_res"

    if [ "$DIFF" != "" ]
    then
        echo "❌ : Find diff, check diff_res file to check"
    else
        echo "✅ : No diff find, nice"
    fi
done



# Clear results and all .o files with option "clean"
if [ $# -gt 0 ] && [ $1 == "clean" ]
then
    printf "\n\n! remove the folder ./$BASE_DIR"
    rm -rf "./$BASE_DIR"
    rm ./mains/*.o
fi