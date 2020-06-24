import java.util.Scanner;

public class ship {
	static int pos[];

	public static void main(String args[]) {
		Scanner get = new Scanner(System.in);
		int n = get.nextInt();
		int k = get.nextInt();
		int a = get.nextInt();
		int m = get.nextInt();
		int arr[] = new int[m];
		pos = new int[n + 2];
		for (int i = 0; i < m; i++) {
			arr[i] = get.nextInt();
			pos[arr[i]] = i + 1;
		}
		pos[n + 1] = 1;
		System.out.println(bs(arr, k, a));

	}

	public static int bs(int[] arr, int k, int a) {
		int low = 1, high = arr.length, result = -1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (!check(mid, k, a)) {
				high = mid - 1;
				result = mid;
			} else {
				low = mid + 1;
			}
		}
		return result;
	}

	public static boolean check(int mid, int k, int a) {
		int ans = 0, last = 0;
		for (int i = 1; i < pos.length; i++) {

			if (pos[i] <= mid && pos[i] > 0) {
				ans += ((i - last - 1) / (a + 1));
				if ((i - last - 1) % (a + 1) == a)
					ans++;
				last = i;
			}
		}
		return ans >= k;
	}
}