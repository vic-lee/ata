import java.util.*;

public class A {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		StringBuilder ans = new StringBuilder();
		int val = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j += 2) {
				ans.append(val + " " + (n * n - val + 1) + " ");
				val++;
			}
			ans.append("\n");
		}
		System.out.println(ans);
	}

}
