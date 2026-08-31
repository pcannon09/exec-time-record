PROJECT_INFO_PATH=".private/project.json"

projectName=$(jq -r '.CMakeName' $PROJECT_INFO_PATH)

./build/$projectName "$@"
