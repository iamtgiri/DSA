@echo off
REM --------------------------------------
REM Batch script to commit and push changes
REM --------------------------------------

cd /d %~dp0

git add .
git commit -m "add new problems"
git push

echo.
echo ✅ All changes pushed successfully!
pause
