# #!/bin/bash

# PROGRAM="./cub3D"
# TEST_MAPS_DIR="maps/"
# RED=$(tput setaf 1)
# GREEN=$(tput setaf 2)
# NC=$(tput sgr0)

# for map_file in $TEST_MAPS_DIR*.cub; do
#     echo -e "\nTesting map: $map_file\n"
#     $PROGRAM "$map_file"
    
#     exit_status=$?
#     if [ $exit_status -eq 0 ]; then
#         echo -e "${GREEN}Map is valid.${NC}\n"
#     else
#         echo -e "${RED}Map is not valid.${NC}\n"
#     fi
    
#     echo "---------------------"
# done


#!/bin/bash

PROGRAM="./cub3D"
TEST_MAPS_DIR="maps/"
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
BLA=$(tput setaf 3)
NC=$(tput sgr0)

# Check invalid maps
echo  "\n${BLA}Checking invalid maps:${NC}\n"

for map_file in $TEST_MAPS_DIR/invalid_*.cub; do
    echo  "\nTesting map: $map_file\n"
    output=$($PROGRAM "$map_file" 2>&1)

    exit_status=$?
    if [ $exit_status -eq 1 ]; then
		echo "${RED}$output"
        echo  "${GREEN}Map is invalid.${NC}\n"
    else
        echo  "${RED}Map is valid.${NC}\n"
    fi
    
    echo "---------------------"
done

# Check correct maps
echo  "${BLA}Checking correct maps:${NC}\n"

for map_file in $TEST_MAPS_DIR/correct_*.cub; do
    echo  "\nTesting map: $map_file\n"
    output=$($PROGRAM "$map_file" 2>&1)

    exit_status=$?
    if [ $exit_status -eq 0 ]; then
        echo  "${GREEN}Map is valid.${NC}\n"
    else
        echo  "${RED}Map is not valid.${NC}\n"
    fi
    
    echo "---------------------"
done
