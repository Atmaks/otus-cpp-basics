# Примеры функций для сборки-запуска домашних заданий
# Не используем Makefile, потому что страшно неудобный

function Build-Cmake {
    cmake -B "$PSScriptRoot/build-cmake" -S . && cmake --build "$PSScriptRoot/build-cmake"
}

function Run-Cmake {
    & "$PSScriptRoot/build-cmake/Debug/statistics.exe" "$PSScriptRoot/input.txt"
}
