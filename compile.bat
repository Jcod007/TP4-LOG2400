@echo off
echo ========================================
echo   Compilation de MiniDesign
echo ========================================
echo.

g++ -o MiniDesign.exe ^
  MiniDesign.cpp ^
  Plan.cpp ^
  GraphElement.cpp ^
  Point.cpp ^
  PointBase.cpp ^
  PointCloud.cpp ^
  PointFactory.cpp ^
  AffichageListe.cpp ^
  SupprimerCommand.cpp ^
  -std=c++17

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Compilation réussie!
    echo.
    echo Exécutable créé: MiniDesign.exe
    echo.
    echo Pour exécuter:
    echo   .\MiniDesign.exe
    echo.
) else (
    echo.
    echo ❌ Erreur de compilation
    echo.
    exit /b 1
)
