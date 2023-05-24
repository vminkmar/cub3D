#!/bin/bash

PROGRAM="./cub3D"
TEST_MAPS_DIR="test_maps"
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLA=$(tput setaf 4)
NC=$(tput sgr0)
invalid_counter=0
valid_counter=0
valid_map_counter=0
invalid_map_counter=0



echo -e  "\n${YELLOW}Checking invalid maps:${NC}\n"

for map_file in $TEST_MAPS_DIR/invalid_maps/*.cub; do
    echo -e  "\nTesting invalid map: $map_file\n"
    output=$($PROGRAM "$map_file" 2>&1)

    exit_status=$?
    if [ $exit_status -eq 1 ]; then
		echo -e "${RED}$output"
        echo -e  "${GREEN}Map is invalid.${NC}\n"
		((invalid_counter ++))
    else
        echo -e  "${RED}Map is valid.${NC}\n"
    fi
    ((invalid_map_counter++))
    echo -e "---------------------"
done


Check correct maps
echo -e  "${BLA}Checking correct maps:${NC}\n"

for map_file in $TEST_MAPS_DIR/valid_maps/*.cub; do
    echo -e  "\nTesting valid map: $map_file\n"
    output=$($PROGRAM "$map_file" 2>&1)

    exit_status=$?
    if [ $exit_status -eq 0 ]; then
        echo -e  "${GREEN}Map is valid.${NC}\n"
		((valid_counter ++))
    else
		echo -e "$output"
        echo -e  "${RED}Map is not valid.${NC}\n"

    fi
    ((valid_map_counter++))
    echo -e "---------------------"
done


echo -e "\n${BLA}Invalid Maps $invalid_counter / $invalid_map_counter\n"
echo -e "Valid Maps $valid_counter / $valid_map_counter\n"


# echo -e  "\n${YELLOW}Checking invalid maps:${NC}\n"

# for map_file in $TEST_MAPS_DIR/maps/*.cub; do
#     echo -e  "\nTesting invalid map: $map_file\n"
#     output=$($PROGRAM "$map_file" 2>&1)

#     exit_status=$?
#     if [ $exit_status -eq 1 ]; then
# 		echo -e "${RED}$output"
#         echo -e  "${GREEN}Map is invalid.${NC}\n"
# 		((invalid_counter ++))
#     else
#         echo -e  "${RED}Map is valid.${NC}\n"
#     fi
#     ((invalid_map_counter++))
#     echo -e "---------------------"
# done