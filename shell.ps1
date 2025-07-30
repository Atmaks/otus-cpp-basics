# Здесь мы "включаем" консоль разработчика, но в PowerShell. 2025 на дворе всё-таки!
## USAGE: . .\shell.ps1
## Точка обязательна! если просто выполнить скрипт, функции не подключатся

cmd.exe /c "call `"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat`" && set > $PSScriptRoot\vcvars.txt";

Get-Content "$PSScriptRoot\vcvars.txt" | Foreach-Object {
    if ($_ -match "^(.*?)=(.*)$") {
        Set-Content "env:\$($matches[1])" $matches[2]
    }
}

Remove-Item "$PSScriptRoot\vcvars.txt";

. "$PSScriptRoot/helpers.ps1";
