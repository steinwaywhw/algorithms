from UnionFind import *
from Graph import *

class Visualizer:

	def draw_graph(graph):
		output = ""
		for v in graph.vertices:
			output += str(v) + " [shape=box]; "
		for e in graph.edges:
			output += \
				str(e.a) + \
				" -- " + \
				str(e.b) +\
				" [label=" + \
				str(e.weight) + \
				"]; "	

		return "graph { graph [ranksep=3.0; nodesep=3.0; sep=3.0; splines=curved; overlap=false]; " + output + " }"

	def print_edges(edges):
		for e in edges:
			print([str(e.a), str(e.b), str(e.weight)])

