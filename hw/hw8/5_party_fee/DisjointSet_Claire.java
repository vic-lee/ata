

public class DisjointSet {
	
	private int size;
	private int[] set;
	private int largestSize;
	int counter;
	private int[] moneyArr;
	private Integer[] groupMoneyArr;
	
	public DisjointSet(int size, int[] moneyArr) {
		this.size = size;
		this.set = new int[size];
		this.groupMoneyArr = new Integer[size];
		for (int i=0; i<size; i++) {
			this.set[i] = -1;
			//this.groupMoneyArr[i];
		}
		this.largestSize = -1;
		this.moneyArr = moneyArr;
	}
	
	
	//private int setNum;
	
	/**
	 * determine which set an element belongs to
	 * @param x the element
	 * @return the root index
	 */
	
	// is this func less efficient than optimal?
	public int find(int x) {
		int parent = this.set[x];
		if (parent < 0) {		
			return x;
		}
		int root = this.find(parent);
		//this.setParent(x,root); // path compression
		this.set[x] = root;
		return root;
		
	}
	
	/**
	 * merge two sets of which x and y are members
	 * @param x
	 * @param y
	 */
	public void union(int x, int y) {
		
		//if(this.largestSize>-this.size) { // could delete, updating size part
			counter++;
			int root_x = this.find(x);
			int root_y = this.find(y);
			if (root_x != root_y) {
				int xSize = this.set[root_x];
				int ySize = this.set[root_y];
				int sumSize = xSize+ySize;
				Integer leftMoney = this.groupMoneyArr[root_x];
				 //System.out.println("The leftMoney is "+ leftMoney);
				Integer rightMoney = this.groupMoneyArr[root_y];
				if (leftMoney == null) {
					leftMoney = this.moneyArr[x];
					this.groupMoneyArr[root_x] = leftMoney;
				}
				
				if (rightMoney ==null) {
					rightMoney = this.moneyArr[y];
					this.groupMoneyArr[root_y] = rightMoney;
				}
				
				//System.out.println("The leftMoney is "+ leftMoney);
				//if (root_y == y) rightMoney = this.moneyArr[y];
				//else rightMoney = this.groupMoneyArr[root_y];
				//System.out.println("The rightMoney is "+ rightMoney);
				
				if (xSize<ySize) { // y is the final root
					//this.setSize(root_y,xSize+ySize);
					this.set[root_y] = sumSize;
					//this.setParent(root_x,root_y);
					this.set[root_x] = root_y;
					this.groupMoneyArr[root_y]+=leftMoney;
					this.groupMoneyArr[root_x]=Integer.MAX_VALUE;
					//return root_y;
					
				}
				else { // x is the final root
					//this.setSize(root_x,xSize+ySize);
					this.set[root_x] = sumSize;
					//this.setParent(root_y,root_x);
					this.set[root_y] = root_x;
					this.groupMoneyArr[root_x]+=rightMoney;
					this.groupMoneyArr[root_y]=Integer.MAX_VALUE;
					
					//return root_x;
				}	
				
				// updating the largest size of the set
				//if (sumSize<this.largestSize) this.largestSize = sumSize;
				 
			//} // updating size end bracket
			
		}
		//else return root_x;
		//else return false;
	}
	
	/**
	 * determine if x and y belong to the same set
	 * @param x
	 * @param y
	 * @return
	 */
	
	public boolean sameSet(int x, int y) {
		int root_x = this.find(x);
		int root_y = this.find(y);
		if(root_x == root_y) {
			return true;
		}
		else return false;
	}
	
	
	/*public void setParent(int e, int parent) {    // don't need this?
		this.set[e] = parent;
	}
	
	public int getParent(int e) {    // don't need this?
		return this.set[e];
	}
	*/
	
	/*
	public int getSize(int root) {   // PROBABLY DONT NEED THIS EVEN. GONNA TRY
		int value = this.set[root];
		if (value<0) {
			return -value;
		}
		else {
			return this.getSize(value); // not really necessary
		}
		
	}
	*/

	/*
	public void setSize(int root, int size) {  // SAME, PROB NO NEED
		int value = this.set[root];
		if (value<0) {
			//this.setParent(root,-size);
			this.set[root] = -size;
		}
		else this.setSize(value,size); // recursive step, not necessary
		
	}
	*/
	
	public int setNum() {
		int setNum = 0;
		for (int i = 0; i < this.size; i++) {
			if (this.set[i]<0) {
				setNum++;
			}
		}
		return setNum;
	}
	
	public void printSet() {
		for (int i = 0; i < this.size; i++) {
			System.out.print(this.set[i]+" ");
		}
		System.out.println();
	}
	
	
	// can get rid of this but just a problem of constant time
	public int largestSize() {
		
		// Going through every item in the arr to check largest set.
		
		/*
		int largestSize=0;
		int size;
		for (int i = 0; i < this.size; i++) {
			if ((size = this.set[i])<0) {
				if (size < largestSize) {
					largestSize = size;
				}
			}
		}
		
		return -largestSize;
		*/
		return -this.largestSize;
	}
	
	public boolean redistribute() {
		//boolean even = true;
		for (int i = 0; i<this.size; i++) {
			//System.out.println(i);
			Integer money = this.groupMoneyArr[i];
			if (money==null && this.moneyArr[i]!=0)
				return false;
			if (money!=null && money!=0 && money!=Integer.MAX_VALUE)
				return false;
		}
		
		return true;
	}
	
	
}
