
from UnionFind import *
from Graph import *
from Visualizer import *



class MstBoruvka:

	def mst(graph):
		mst = set()
		uf = UnionFind(graph.vertices)

		while len(mst) < graph.num_of_vertices() - 1:
			MstBoruvka.boruvka_step(graph, mst, uf)

		total_weight = 0
		for e in mst:
			total_weight += e.weight 

		return (mst, total_weight)

	def boruvka_step(graph, mst, uf):
		chosen = {}
		if Config.VERBOSE:
			print("\n*** New iteration with", len(mst), "edges in MST ***")
			print("*** UnionFind ***")
			print(uf)

		for e in graph.edges:
			x = uf.find(e.a)
			y = uf.find(e.b)

			if x == y:
				continue
			if (x not in chosen) or (e.lighter(chosen[x])):
				chosen[x] = e
			if (y not in chosen) or (e.lighter(chosen[y])):
				chosen[y] = e

		for e in chosen.values():
			x = uf.find(e.a)
			y = uf.find(e.b)

			if x != y:
				mst.add(e)
				uf.union(x, y)

		if Config.VERBOSE:
			nb = input('Press ENTER to continue...')

def main():

	print("*** Test Boruvka MST ***")

	g = Graph.fromFile("1.g")
	mst = MstBoruvka.mst(g)

	output = Visualizer.draw_graph(g)
	f = open("output", "w")
	f.write(output)
	f.close()

	print ("Total weight:", mst[1])
	Visualizer.print_edges(mst[0])
	return 

if __name__ == "__main__":
    main()