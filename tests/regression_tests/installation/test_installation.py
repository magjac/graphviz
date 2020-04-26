import subprocess
import os

def test_installation():
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    result = subprocess.Popen(['bash', './check_installation.sh'])
    text = result.communicate()[0]
    print(text)
    assert result.returncode == 0
