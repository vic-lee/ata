import java.util.Scanner;

public class C {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), d = sc.nextInt();
		int arr[] = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = sc.nextInt();
		int l = 0;
		long ans = 0;
		for (int i = 0; i < n; i++) {
			while (l < i && (arr[i] - arr[l]) > d)
				l++;
			ans += (1l * (i - l) * 1l * (i - l - 1)) / 2;
		}
		System.out.println(ans);
	}
}
