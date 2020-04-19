import subprocess
import os
import sys

def test_shapes():
    python_version = sys.version_info[0]
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    result = subprocess.Popen(['python' + str(python_version), './shapes.py'])
    text = result.communicate()[0]
    print(text)
    assert result.returncode == 0
