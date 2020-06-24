import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Scanner in = new Scanner(br);

		int n = in.nextInt();
		int m = in.nextInt();

		int[] moneyList = new int[n];
		for (int i = 0; i < n; i++) {
			moneyList[i] = in.nextInt();
		}

		DisjointSet djs = new DisjointSet(n, moneyList);
		for (int i = 0; i < m; i++) {
			djs.union(in.nextInt(), in.nextInt());
		}

		boolean even = djs.redistribute();
		if (even)
			System.out.println("POSSIBLE");
		else
			System.out.println("IMPOSSIBLE");

	}

}
