# tests that examples provided with Graphviz compile correctly

import os
import platform
import pytest
import subprocess

def c_compiler():
    '''find the system's C compiler'''
    return os.environ.get('CC', 'cc')

@pytest.mark.parametrize('src', ['demo.c', 'dot.c', 'example.c', 'neatopack.c',
  'simple.c'])
def test_compile_example(src):
    '''try to compile the example'''

    # FIXME: if you know how to call the C compiler on Windows, please implement
    # this functionality
    if platform.system() == 'Windows':
        pytest.skip('not implemented for Windows')

    # construct an absolute path to the example
    filepath = os.path.join(os.path.abspath(os.path.dirname(__file__)),
      '../dot.demo', src)

    cc = c_compiler()

    libs = ('cgraph', 'gvc')

    # ensure the C compiler can build this without error
    subprocess.check_call([cc, '-o', os.devnull, filepath]
      + ['-l{}'.format(l) for l in libs])
