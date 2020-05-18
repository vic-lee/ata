import java.util.Scanner;

public class A {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while (t-- > 0) {
			int n = sc.nextInt();
			int arr[] = new int[n];
			for (int i = 0; i < n; i++)
				arr[i] = sc.nextInt();
			int cnt = 0, sum = 0;
			for (int i = 0; i < n; i++) {
				if (arr[i] == 0)
					cnt++;
				sum += arr[i];
			}
			if (sum == 0) {
				System.out.println(Math.max(cnt, 1));
			} else if (sum == (-cnt))
				System.out.println(cnt + 1);
			else
				System.out.println(cnt);
		}
	}

}
