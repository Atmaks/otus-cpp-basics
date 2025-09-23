# Примеры функций для сборки-запуска домашних заданий
# Не используем Makefile, потому что страшно неудобный

function Build-Cmake {
    cmake -B "$PSScriptRoot/build-cmake" -S . && cmake --build "$PSScriptRoot/build-cmake"
}

function Run-Cmake {
    param ($fileName)
    & "$PSScriptRoot/build-cmake/Debug/physics.exe" $fileName
}

function Build-Manual {
    Push-Location;
    New-Item -Path "$PSScriptRoot/build-manual" -ItemType Directory -ErrorAction SilentlyContinue;
    Set-Location "$PSScriptRoot/build-manual";

    $flags = @(
        "/Zi", # debug info
        "/std:c++17", # c++ standard
        "/Wall", # all the warnings
        "/EHsc" # что-то про исключения
    );
    $sourceFiles = @(
        "$PSScriptRoot/hello_world.cpp",
        "$PSScriptRoot/example.cpp"
    );
    $outputFile = "$PSScriptRoot/build-manual/hello_world.exe";

    & cl.exe $flags $sourceFiles "/Fe:$outputFile";
    Pop-Location;
}

function Run-Manual {
    & "$PSScriptRoot/build-manual/hello_world.exe"
}
