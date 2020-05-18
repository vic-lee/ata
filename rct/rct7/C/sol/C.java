import java.util.Arrays;
import java.util.Scanner;

public class C {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		Pair p[] = new Pair[n];
		for (int i = 0; i < n; i++) {
			p[i] = new Pair(sc.nextInt(), sc.nextInt());
		}
		Arrays.sort(p);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			int a = p[i].x, b = p[i].y;
			if (b < ans) {
				ans = a;
			} else
				ans = b;
		}
		System.out.println(ans);
	}

	static class Pair implements Comparable<Pair> {
		int x, y;

		Pair(int a, int b) {
			x = a;
			y = b;
		}

		@Override
		public int compareTo(Pair p) {
			int x = Integer.compare(this.x, p.x);
			if (x == 0) {
				return Integer.compare(this.y, p.y);
			}
			return x;
		}

	}
}
