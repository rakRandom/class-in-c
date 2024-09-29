@echo off

if not exist .\class.exe (
    cd build
    make release
    move class.exe ..
    cd ..
    echo:
)

.\class
