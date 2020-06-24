import java.util.Arrays;
import java.util.Scanner;

public class B {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int arr[] = new int[n];
		long ans = 0;
		for (int i = 0; i < n; i++) {
			arr[i] = sc.nextInt();
		}
		Arrays.sort(arr);
		long cnt = 2;
		for (int i = 0; i < n - 1; i++) {
			ans += (arr[i] * (cnt++));
		}
		ans += arr[n - 1] * (--cnt);
		System.out.println(ans);
	}

}
