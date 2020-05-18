import java.util.HashSet;
import java.util.Scanner;

public class A {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), m = sc.nextInt();
		int parent[] = new int[m + 1];
		int size[] = new int[m + 1];
		int ans = 0;
		for (int i = 0; i <= m; i++)
			parent[i] = i;
		for (int i = 0; i < n; i++) {
			int k = sc.nextInt();
			if (k == 0) {
				ans++;
				continue;
			}
			int x = getParent(parent, sc.nextInt());
			for (int j = 1; j < k; j++) {
				int y = getParent(parent, sc.nextInt());
				parent[y] = x;
			}
			size[x]++;
		}
		HashSet<Integer> hs = new HashSet<>();
		for (int i = 1; i <= m; i++)
			if (size[getParent(parent, i)] > 0)
				hs.add(getParent(parent, i));
		System.out.println(ans + Math.max(0, hs.size() - 1));

	}

	public static int getParent(int parent[], int x) {
		if (parent[x] == x)
			return x;
		return parent[x] = getParent(parent, parent[x]);
	}

}
