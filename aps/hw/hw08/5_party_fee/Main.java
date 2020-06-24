import java.io.*;
import java.util.Arrays;

public class Main {
	public static void main(String args[]) throws NumberFormatException, IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
		String[] vals = reader.readLine().split(" ");
		int numStudents = Integer.parseInt(vals[0]);
		int M = Integer.parseInt(vals[1]);
		int[] balances = new int[numStudents];
		for (int i = 0; i < numStudents; i++) {
			balances[i] = Integer.parseInt(reader.readLine());
		}
		DSU d = new DSU(numStudents, balances);
		for (int i = 0; i < M; i++) {
			vals = reader.readLine().split(" ");
			int x = Integer.parseInt(vals[0]);
			int y = Integer.parseInt(vals[1]);
			if (d.find(x) != d.find(y)) {
				d.union(x, y);
			}
		}
		System.out.println(Arrays.toString(d.sizes));
		boolean possible = true;
		for (int i = 0; i < numStudents; i++) {
			if (d.sizes[i] != 0) {
				possible = false;
				break;
			}
		}
		if (possible) {
			writer.write("POSSIBLE\n");
		} else {
			writer.write("IMPOSSIBLE\n");
		}
		writer.flush();
	}

	public static class DSU {
		int numSets;

		int[] parents;
		int[] ranks;
		int[] sizes;

		public DSU(int N, int[] balances) {
			parents = new int[N];
			ranks = new int[N];
			sizes = new int[N];
			for (int i = 0; i < N; i++) {
				parents[i] = i;
				ranks[i] = 0;
				sizes[i] = balances[i];
			}
			numSets = N;
		}

		public int getNumberOfSets() {
			return numSets;
		}

		private int find(int x) {
			if (parents[x] == x)
				return x;
			return x = find(parents[x]);
		}

		public int getSize(int x) {
			return sizes[find(x)];
		}

		public boolean sameSet(int x, int y) {
			return find(x) == find(y);
		}

		public boolean union(int x, int y) {
			int pX = find(x);
			int pY = find(y);
			if (pX == pY)
				return false;

			if (ranks[pX] == ranks[pY]) {
				ranks[pX]++;
				parents[pY] = pX;
				sizes[pX] += sizes[pY];
				sizes[pY] = 0;
			} else if (ranks[pX] < ranks[pY]) {
				parents[pX] = pY;
				sizes[pY] += sizes[pX];
				sizes[pX] = 0;
			} else if (ranks[pX] > ranks[pY]) {
				parents[pY] = pX;
				sizes[pX] += sizes[pY];
				sizes[pY] = 0;
			}

			numSets--;
			return true;
		}

	}
}