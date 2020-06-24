import java.util.Arrays;
import java.util.Scanner;

public class B {

	static int dp[][];

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int arr[] = new int[n + 2];
		int left[] = new int[n + 2];
		int right[] = new int[n + 2];
		arr[n + 1] = 1000000100;
		for (int i = 1; i <= n; i++)
			arr[i] = sc.nextInt();
		for (int i = 1; i <= n; i++) {
			if (arr[i] > arr[i - 1])
				left[i] = left[i - 1] + 1;
			else
				left[i] = 1;
		}
		for (int i = n; i >= 0; i--) {
			if (arr[i] < arr[i + 1])
				right[i] = right[i + 1] + 1;
			else
				right[i] = 1;
		}
		int ans = 1;
		for (int i = 1; i <= n; i++) {
			if ((arr[i + 1] - arr[i - 1]) > 1) {
				ans = Math.max(ans, 1 + left[i - 1] + right[i + 1]);
			} else
				ans = Math.max(ans, Math.max(1 + left[i - 1], 1 + right[i + 1]));
		}
		System.out.println(ans);
	}
}
