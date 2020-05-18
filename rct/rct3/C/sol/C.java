import java.util.*;

public class C {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int array[] = new int[n + 1];
		int ans = 0;
		for (int i = 2; i <= n; i++) {
			if (array[i] == 0) {
				for (int j = i; j <= n; j += i) {
					array[j]++;
				}
			}
			if (array[i] == 2)
				ans++;
		}
		System.out.println(ans);
	}
}
