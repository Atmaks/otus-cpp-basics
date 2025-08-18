# Примеры функций для сборки-запуска домашних заданий
# Не используем Makefile, потому что страшно неудобный

$executableName = "main.exe"

function Build-Cmake {
    cmake -B "$PSScriptRoot/build-cmake" -S . && cmake --build "$PSScriptRoot/build-cmake"
}

function Run-Cmake {
    & "$PSScriptRoot/build-cmake/Debug/$executableName"
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
        "$PSScriptRoot/main.cpp"
    );
    $outputFile = "$PSScriptRoot/build-manual/$executableName";

    Write-Output "cl.exe $flags $sourceFiles /Fe:$outputFile";

    & cl.exe $flags $sourceFiles "/Fe:$outputFile";
    Pop-Location;
}

function Run-Manual {
    Push-Location;
    Set-Location "$PSScriptRoot/build-manual";

    & "$PSScriptRoot/build-manual/$executableName" $args;

    Pop-Location;
}
