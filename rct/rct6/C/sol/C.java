import java.util.*;

public class C {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int arr[] = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = sc.nextInt();
		System.out.println(recur(0, n - 1, arr, 0));

	}

	public static int recur(int l, int r, int[] arr, int h) {
		if (l > r)
			return 0;
		int min = arr[l], temp = l;
		for (int i = l; i <= r; i++) {
			if (arr[i] < min) {
				min = arr[i];
				temp = i;
			}
		}
		return Math.min((r - l + 1), recur(l, temp - 1, arr, min) + min + recur(temp + 1, r, arr, min) - h);
	}
}
