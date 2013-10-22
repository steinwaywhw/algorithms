

class UnionFindNode:
    def __init__(self, obj, rank = 0):
        self.object = obj
        self.parent = self
        self.rank = rank

    def __str__(self):
        return str(self.object) + ", p=" + str(self.parent.object)


class UnionFind:

    def __init__(self, objs):
        self.nodes = []
        self.map = {}

        for o in objs:
            self.make_node(o)

    def make_node(self, obj):
        node = UnionFindNode(obj)
        self.nodes.append(node)
        self.map[obj] = node

    def find(self, obj):
        node = self.map[obj]
        if node.parent != node:
            node.parent = self.map[self.find(node.parent.object)]
        return node.parent.object

    def union(self, a, b):
        parent_a = self.map[self.find(a)]
        parent_b = self.map[self.find(b)]

        if parent_a == parent_b:
            return
        elif parent_a.rank > parent_b.rank:
            parent_b.parent = parent_a
        elif parent_a.rank < parent_b.rank:
            parent_a.parent = parent_b
        else:
            parent_b.parent = parent_a
            parent_a.rank = parent_a.rank + 1

    def __str__(self):
        sets = {}
        for n in self.nodes:
            p = self.find(n.object)
            if p not in sets:
                sets[p] = set() 

            sets[p].add(n.object)

        output = ""
        for s in sets:
            output += str({str(s):{str(n) for n in sets[s]}}) + "\n"
        return output

         

