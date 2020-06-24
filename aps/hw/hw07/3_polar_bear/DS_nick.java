static class DisjointUnionSet {
    int[] rank, parent;
    int n;
    int sets;

    public String toString() {
        return Arrays.toString(parent);
    }

    public DisjointUnionSet(int x) {
        rank = new int[x];
        parent = new int[x];
        n = x;
        sets = x;
        this.makeSet();
    }

    private void makeSet() {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    public int find(int x) {
        if (parent[x] == x) {
            return x;
        }

        return parent[x] = find(parent[x]);
    }

    public void union(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        sets--;
        if (xRoot == yRoot) {
            return;
        }

        if (rank[xRoot] < rank[yRoot]) {

            parent[xRoot] = yRoot;
        }

        else if (rank[yRoot] < rank[xRoot]) {

            parent[yRoot] = xRoot;
        } else {

            parent[xRoot] = yRoot;
            rank[yRoot] = rank[yRoot] + 1;
        }
    }
}