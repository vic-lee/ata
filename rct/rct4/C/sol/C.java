import java.util.Scanner;

public class C {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int arr[] = new int[n];
		int leftCount = 0, rightCount = 0;
		for (int i = 0; i < n; i++) {
			arr[i] = sc.nextInt();
			if (arr[i] == 0)
				leftCount++;
			if (arr[i] == 1)
				rightCount++;
		}
		int left = n - 1, right = 0;
		long ans = 0;
		while (left > right) {
			if (arr[left] == 0) {
				ans += rightCount;
				leftCount--;
			} else {
				rightCount--;
			}
			if (arr[right] == 1) {
				ans += leftCount;
				rightCount--;
			} else {
				leftCount--;
			}
			left--;
			right++;
		}
		System.out.println(ans);
	}
}
