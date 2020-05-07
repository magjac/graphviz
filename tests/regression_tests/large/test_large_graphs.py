from unittest import TestCase

import subprocess
import os


TEST_DIR = os.path.dirname(os.path.realpath(__file__))


class TestLargeGraphs(TestCase):
	def test_long_chain(self):
		"""
		This test will fail on 32bit Windows machine if compiled with stack size < 16MB.
		long_chain input file generated using code below:		
			from graphviz import Digraph

			graph = Digraph(format='svg')

			prev = "start"
			graph.node("start", label="start")

			for i in range(33000):
				new_node = str(i)    
				graph.node(new_node, label=new_node, shape='rectangle')
				
				graph.edge(prev, new_node)
				
				prev = new_node

			graph.render("long_chain")
		"""
		subprocess.check_call([
			'dot', '-Tsvg', '-O', os.path.join(TEST_DIR, 'long_chain')
		])
