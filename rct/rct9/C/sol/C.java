import java.util.*;

public class C {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int arr[] = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = sc.nextInt();
		int freq[] = new int[100010];
		for (int i : arr)
			freq[i]++;
		long dp[] = new long[100010];
		dp[1] = freq[1];
		for (int i = 2; i <= 100000; i++) {
			dp[i] = Math.max(dp[i - 1], dp[i - 2] + 1l * i * freq[i]);
		}
		System.out.println(dp[100000]);
	}

}
