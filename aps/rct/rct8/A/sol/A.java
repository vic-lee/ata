import java.util.Scanner;

public class A {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int freq[] = new int[1010];
		for (int i = 0; i < n; i++) {
			freq[sc.nextInt()]++;
		}
		int cnt = 0, ans = 0;
		for (int i = 0; i <= 1000; i++) {
			if (freq[i] > 0) {
				cnt++;
				ans = Math.max(ans, freq[i]);
			}
		}
		System.out.println(ans + " " + cnt);
	}

}
