@echo off

python -m PyQt5.uic.pyuic -x app.ui -o app.py

set /p tmp=converted