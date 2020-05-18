import java.util.Scanner;

public class B {

	static int dp[][] = new int[30001][500];
	static int offset = 250;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), d = sc.nextInt();
		for (int i = 0; i < dp.length; i++) {
			for (int j = 0; j < dp[0].length; j++)
				dp[i][j] = -1;
		}
		int freq[] = new int[30001];
		for (int i = 0; i < n; i++)
			freq[sc.nextInt()]++;
		int x = recur(freq, d, d, d);
		System.out.println(x);
	}

	public static int recur(int freq[], int p, int l, int d) {
		if (p > 30000)
			return 0;
		if (dp[p][l - d + offset] != -1)
			return dp[p][l - d + offset];
		int ans = freq[p];
		ans += Math.max(recur(freq, p + l, l, d), recur(freq, p + l + 1, l + 1, d));
		if (l > 1)
			ans = Math.max(ans, freq[p] + recur(freq, p + l - 1, l - 1, d));
		return dp[p][l - d + offset] = ans;
	}
}
