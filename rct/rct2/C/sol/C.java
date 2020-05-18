import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		double sum = 0;
		int ans = 0;
		// we sum up the values of a[i]s for the players.
		for (int i = 0; i < n; i++) {
			int g = sc.nextInt();
			ans = Math.max(ans, g);
			sum += g;
		}
		// at this point, ans variable contains the most number of games a player would
		// play.
		// now the min number of rounds required will be the max of (ans,
		// ceil(sum/(n-1))) (Why?)
		ans = Math.max(ans, (int) ((sum + n - 2) / (n - 1))); // ceil(sum/(n-1)) = (sum+n-2)/(n-1)
		System.out.println(ans);
	}
}

// BONUS: Can you solve this problem using Binary Search?