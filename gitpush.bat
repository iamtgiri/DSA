@echo off

cd /d %~dp0

git add .
git commit -m "add new problems"
git push

echo.
echo All changes pushed successfully!
pause
