@ECHO OFF

pushd shapes
python shapes.py
popd

REM Larger graph testing
# FIXME: re-enable when https://gitlab.com/graphviz/graphviz/-/issues/1710 is fixed
#python -m unittest discover large
