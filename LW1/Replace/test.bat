rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
echo test1
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с пустой строкой ожидается нулевой код возврата
echo test2
%PROGRAM% test-data\empty-line.txt "%TEMP%\empty-line.txt" searchString replacementString
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty-line.txt" test-data\empty-line.txt >nul
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата
echo test3
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата
rem echo test4
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата
echo test5
%PROGRAM% test-data\fox-2-line.txt "%TEMP%\fox-2-line.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox-2-line.txt" test-data\fox-2-line-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err

rem При попытке открытия не существующего файла ожидается не нулевой код возврата
echo test6
%PROGRAM% test-data\no-file.txt "%TEMP%\no-file.txt" searchString replacementString
if NOT ERRORLEVEL 1 goto err

echo test7
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" "" cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err

echo test8
%PROGRAM% test-data\number.txt "%TEMP%\number.txt" 1231234 4
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\number.txt" test-data\number-replace.txt >nul
if ERRORLEVEL 1 goto err

echo test9
%PROGRAM% test-data\mama.txt "%TEMP%\mama.txt" ma mama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\mama.txt" test-data\ma-replace-mama.txt >nul
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1