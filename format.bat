@echo off

for /r %%f in (*.cpp *.h) do (
    clang-format -i "%%f"
)

echo Formatting complete.
pause