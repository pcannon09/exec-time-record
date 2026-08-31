#!/bin/bash

# PCANNON COMPILE.SH v1.2 - FROM PCANNON PROJECT STANDARDS
# STANDARD: 20260714
# https://github.com/pcannon09/pcannonProjectStandards

if [ ! -f ".root_dir" ]; then
	echo "Need a \`.root_dir\` file for indication"
	echo "Execute \`gen.sh\` at the repo root"

	exit 1
fi

set -e

source ./utils/inc/sh/colors.sh

export NINJA_STATUS="${BOLD}${BRIGHT_BLACK}[ ${GREEN}%p${BRIGHT_BLACK} :: ${RED}%u/%t${BRIGHT_BLACK} :: ${MAGENTA}%o/s${BRIGHT_BLACK} :: ${CYAN}%e${BRIGHT_BLACK} ] ${RESET}"

CHECKS=true

if [[ "$1" == "nochecks" ]] || [[ "$2" == "nochecks" ]] || [[ "$3" == "nochecks" ]] ; then
	CHECKS=false
fi

if [[ "$CHECKS" = true ]]; then
	if ! command -v cmake > /dev/null 2>&1; then
		echo -e "$BRIGHT_RED Please have 'cmake' installed $RESET"
		exit
	fi

	if ! command -v ninja > /dev/null 2>&1 || ! command -v make > /dev/null 2>&1; then
		echo -e "$BRIGHT_RED Please have 'ninja' or 'make' installed $RESET"
		exit
	fi

	if ! command -v jq > /dev/null 2>&1; then
		echo -e "$BRIGHT_RED Please have 'jq' installed $RESET"
		exit
	fi
fi

COMPILATION_FILE_PATH=".private/dev/compilation.json"
PROJECT_INFO_PATH=".private/project.json"

cores=$(jq '.cores' "$COMPILATION_FILE_PATH")
enableBackup=$(jq -r '.enableBackup' "$COMPILATION_FILE_PATH")

projectName=$(jq -r '.exeName' "$PROJECT_INFO_PATH")

BUILD_TYPE=Debug

if [ "$2" == "ndev" ]; then
	BUILD_TYPE=Release
fi

readarray -t compileMacros < <(jq -r '.macros // [] | .[]' "$COMPILATION_FILE_PATH")

if [ ! -d "./build" ]; then
	mkdir build
fi

function __compileSoftware() {
	cmake --build build -j"$cores" -v
}

if [ "$enableBackup" == "YES" ] || [ "$enableBackup" == "yes" ] || [ "$enableBackup" == "y" ]; then
	printf "${BOLD}${GREEN}[ INFO ] Backing up executable\n${RESET}"

	exeBakPath="./build/bin/exeBackup"

	if [ ! -d "$exeBakPath" ]; then
		mkdir -p "$exeBakPath"
	fi

	if [ -f "build/bin/$projectName" ]; then
		cp "./build/bin/$projectName" "$exeBakPath/$projectName-$(date +%s)"
	fi

	echo -e " [ Done ]"
fi

if [ "$1" == "setup" ]; then
	if [ "$2" != "ndev" ]; then
		SYSTEM_NAME="$2"

	else
		if [ ! -z "$3" ]; then
			SYSTEM_NAME="$3"
		fi
	fi

	echo $SYSTEM_NAME

	for macro in "${compileMacros[@]}"; do
		if [ -n "$macro" ]; then
			if [[ "$macro" != *=* ]]; then
				compilerFlags+=" -D$macro"
			else
				compilerFlags+=" -D$macro"
			fi
		else
			echo -e "${BRIGHT_YELLOW}${BOLD}[ WARN ] Skipping empty macro \`${macro}\`${RESET}"
		fi
	done

	cmakeCommand=(
			cmake
			-S ..
			-B .
			-G Ninja
			-DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
			-DCMAKE_POLICY_VERSION_MINIMUM=3.5
			-DCMAKE_C_FLAGS="${compilerFlags}"
	)

	pastWD=$(pwd)
	echo -e "${BRIGHT_BLUE}${BOLD}[ * ] Running CMake:${RESET}"
	printf ' %q' "${cmakeCommand[@]}"
	echo

	cd build/

	"${cmakeCommand[@]}"

	cd $pastWD

elif [ -z "$1" ] || [ "$1" == "m" ] || [[ "$1" == "nochecks" ]]; then
	__compileSoftware "$@"

elif [ "$1" == "settings" ]; then
	echo -e "[ * ] Compilation settings"

	if [ ! -d "tmp" ]; then
		echo -e "${BOLD}[ NOTE ] Creating \`tmp/\` dir${RESET}"
		mkdir -p tmp
	fi

# 	Create config if it doesn't exist
	if [[ ! -s "$COMPILATION_FILE_PATH" ]]; then
cat > "$COMPILATION_FILE_PATH" <<EOF
{
"cores": 10,
"enableBackup": "NO",
"macros": []
}
EOF
	fi

# 	CORES
	echo -e "${BOLD}[ PROMPT ] Enter the number of cores to compile the program ('same' to keep current)${RESET}"
	read -r cores

	if [[ "$cores" == "same" ]]; then
		cores=$(jq '.cores' "$COMPILATION_FILE_PATH")
		echo -e "${GREEN}$cores${RESET}"

	elif [[ "$cores" =~ ^[0-9]+$ ]]; then
		:

	else
		echo -e "${RED}Give a number for \`cores\`, not a string or boolean${RESET}"
		exit 1
	fi

# 	ENABLE BACKUP
	echo -e "${BOLD}[ PROMPT ] Enable backup? 'YES' or 'NO' ('same' to keep current)${RESET}"
	read -r enableBackup

	if [[ "$enableBackup" == "same" ]]; then
		enableBackup=$(jq -r '.enableBackup' "$COMPILATION_FILE_PATH")
		echo -e "${GREEN}$enableBackup${RESET}"
	fi

# 	MACROS
	echo -e "${BOLD}[ PROMPT ] Macros (OPTIONAL)\n(done: Stop adding)\n(clear: Clear list)\n(same: Keep current list)${RESET}"

	programMacros=()

	while IFS= read -r macroVal; do
		case "$macroVal" in
			same)
				mapfile -t programMacros < <(
					jq -r '.macros[]' "$COMPILATION_FILE_PATH"
				)

				echo "[ CURRENT MACROS ]"
				printf "${GREEN} - %s\n" "${programMacros[@]}"
				printf "${RESET}"

				break
				;;

			done)
				break
				;;

			clear)
				programMacros=()
				echo "[ CLEARED ]"
				;;

			*)
				programMacros+=("$macroVal")
				;;
		esac
	done

	echo -e "${BRIGHT_BLUE}${BOLD}[ * ] TOTAL MACROS [${programMacros[*]}]${RESET}"

# 	WRITE JSON
	macrosJson=$(printf '%s\n' "${programMacros[@]}" | jq -R . | jq -s .)

	jq \
		--argjson cores "$cores" \
		--arg enableBackup "$enableBackup" \
		--argjson macros "$macrosJson" \
		'
		.cores = $cores
		| .enableBackup = $enableBackup
		| .macros = $macros
		' \
		"$COMPILATION_FILE_PATH" > tmp/tmp_dev_compilation.json

	mv tmp/tmp_dev_compilation.json "$COMPILATION_FILE_PATH"

	echo -e "[ DONE ]"
	exit
# 	END OF SETTINGS
fi

