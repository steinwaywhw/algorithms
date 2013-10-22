from UnionFind import *

import Config



class Edge:
	def __init__(self, a = None, b = None, weight = 0):
		self.a = a
		self.b = b
		self.weight = weight

	def lighter(self, other):
		return self.weight < other.weight

	def __str__(self):
		return str([str(self.a), str(self.b), self.weight])

class Graph:
	def __init__(self, edges = set(), vertices = set()):
		self.edges = edges
		self.vertices = vertices

	def add_edge(self, edge):
		self.edges.add(edge)

	def add_vertex(self, vertex):
		self.vertices.add(vertex)

	def num_of_edges(self):
		return len(self.edges)

	def num_of_vertices(self):
		return len(self.vertices)

	def debug(self):
		for v in self.vertices:
			print(v.__repr__())
		for e in self.edges:
			print(e.__repr__())

	def fromFile(file):
		if Config.VERBOSE:
			print("Reading from ", file)

		g = Graph()
		with open(file, 'r') as f:
			for line in f:
				content = [x for x in line.split()]

				if Config.VERBOSE:
					print(content)

				a = str(content[0])
				b = str(content[1])
				e = Edge(a, b, float(content[2]))
				g.add_vertex(a)
				g.add_vertex(b)
				g.add_edge(e)

		if Config.VERBOSE:
			print ("Graph created with", g.num_of_vertices(), "vertices and", g.num_of_edges(), "edges")
		return g

