#!/bin/bash

source ./utils/inc/sh/colors.sh

COMPILATION_FILE_PATH=".private/dev/compilation.json"
PROJECT_INFO_PATH=".private/project.json"

cores=$(jq '.cores' $COMPILATION_FILE_PATH)
projectName=$(jq -r '.CMakeName' $PROJECT_INFO_PATH)

if [ ! -d "build" ]; then
    mkdir build
fi

cd build/

if [[ "$1" == "--no-backup" ]] || [[ "$1" == "--no-bak" ]]; then
    echo "${BOLD}${GREEN}[ INFO ] Continuing without executable backup${RESET}"

else
    printf "${BOLD}${GREEN}[ INFO ] Backing up executable\n${RESET}"

    exeBakPath="./exeBackup" 

    if [ ! -d "$exeBakPath" ]; then
        mkdir -p "$exeBakPath"
    fi
    
    cp "$projectName" "$exeBakPath/$projectName-bak"

    echo " [ Done ]"
fi

if [ "$1" == "" ]; then
    cmake ..

elif [ "$1" == "--settings" ]; then
    cd ..

    echo "[ * ] Compilation settings"

    echo -e "${BOLD}[ PROMPT ] Enter the number of cores to compile the program ${RESET}"

    read cores
    
    if [ ! -d "tmp" ]; then
        echo -e "${BOLD}[ NOTE ] Creating \`tmp/\` dir"

        mkdir tmp
    fi

    if [[ ! -s "$COMPILATION_FILE_PATH" ]]; then
        echo "{}" > "$COMPILATION_FILE_PATH" 
    fi

    jq ".cores = $cores" "$COMPILATION_FILE_PATH" > tmp/tmp_dev_compilation.json

    mv tmp/tmp_dev_compilation.json "$COMPILATION_FILE_PATH"
    
    echo "[ DONE ]"

    exit
fi

make -j${cores}

cd ..
