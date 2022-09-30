@echo off

astyle ./src/slot_machine.cpp

rem alternate:

clang-format ./src/slot_machine.cpp > ./src/slot_machine.formatted.cpp
