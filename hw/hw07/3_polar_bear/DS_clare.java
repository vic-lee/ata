public class DisjointSet {

    private int size;
    private int[] set;

    public DisjointSet(int size) {
        this.size = size;
        set = new int[size];
        for (int i = 0; i < size; i++) {
            this.set[i] = size + 1; //
        }
    }

    // private int setNum;

    /**
     * determine which set an element belongs to
     * 
     * @param x the element
     * @return the root index
     */
    public int find(int x) {
        int parent = this.getParent(x);
        if (parent > this.size) { // the part is below water, i.e., not any island/set
            return x;
        } else {
            if (parent < 0) { // parent is the root

                return x;
            }
            int root = this.find(parent);
            this.setParent(x, root); // path compression
            return root;
        }

    }

    public void setAboveSea(int x) {
        int parent = this.getParent(x);
        this.setParent(x, -1);
    }

    /**
     * merge two sets of which x and y are members
     * 
     * @param x
     * @param y
     */
    public void union(int x, int y) { // would make sure only union two lands above the sea,
        // meaning the root of x and y would be negative
        int root_x = this.find(x);
        int root_y = this.find(y);
        if (root_x != root_y) {
            if (this.getSize(root_x) < this.getSize(root_y)) {
                this.setSize(root_y, this.getSize(root_x) + this.getSize(root_y));
                this.setParent(root_x, root_y);

            } else {
                this.setSize(root_x, this.getSize(root_x) + this.getSize(root_y));
                this.setParent(root_y, root_x);
            }

        }
    }

    /**
     * determine if x and y belong to the same set
     * 
     * @param x
     * @param y
     * @return
     */
    public boolean sameSet(int x, int y) {
        int root_x = this.find(x);
        int root_y = this.find(y);
        if (root_x == root_y && root_x < this.size) {
            return true;
        } else
            return false;
    }

    public void setParent(int e, int parent) {
        this.set[e] = parent;
    }

    public int getParent(int e) {
        return this.set[e];
    }

    public int getSize(int root) {
        int value = this.getParent(root);
        if (value < 0) {
            return -value;
        } else {
            return this.getSize(value); // not really necessary
        }

    }

    public void setSize(int root, int size) {
        int value = this.getParent(root);
        if (value < 0) {
            this.setParent(root, -size);
        } else
            this.setSize(value, -size); // recursive step, not necessary

    }

    public int setNum() {
        int setNum = 0;
        for (int i = 0; i < this.size; i++) {
            if (this.getParent(i) < 0) {
                setNum++;
            }
        }
        return setNum;
    }

    public void printSet() {
        for (int i = 0; i < this.size; i++) {
            System.out.print(this.getParent(i) + " ");
        }
        System.out.println();
    }
}
