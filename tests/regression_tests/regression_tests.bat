@ECHO OFF

pushd shapes
python shapes.py
popd

REM Larger graph testing
python -m unittest discover large
