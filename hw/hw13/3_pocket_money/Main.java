import java.io.*;
import java.text.DecimalFormat;
import java.util.Arrays;

public class Main {
	// static double epsilon = 2*Math.exp(-32);
	static int MIN = Integer.MIN_VALUE;
	static long[][] memo;
	static int[] faceValue = { 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5 };

	// 100 50 20 10 5 2 1 0.5 0.2 0.1 0.05
	public static void main(String[] args) throws NumberFormatException, IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line = br.readLine();

		int money = Integer.parseInt(line.substring(0, line.length() - 3)) * 100
				+ Integer.parseInt(line.substring(line.length() - 2, line.length()));
		// initiating memo table
		// System.out.println(money);
		int intValue = money / 5;
		memo = new long[intValue + 1][intValue + 1];
		for (int i = 0; i <= intValue; i++) {
			for (int j = 0; j <= intValue; j++) {
				memo[i][j] = MIN;
			}
		}

		DecimalFormat df = new DecimalFormat("0.00");

		if (money == 0 || (money % 5 != 0)) {
			System.out.printf("%6s%17s\n", line, 0);
		} else {
			long ways = dfs(money, money);
			// String format = df.format(money);
			System.out.printf("%6s%17s\n", line, ways);
		}

		// System.out.println(0.3-0.2);
	}

	public static long dfs(int money, int largest) {
		// System.out.println("Money value is: "+money+", and the largest allowed to use
		// is: "+largest);
		// int indMon = (int)((money+epsilon)/0.05);
		// System.out.println("index is: "+indMon);

		// int indLargest = (int)(largest/0.05);

		// no money, one combination
		if (money < 0)
			return 0;
		if (money <= 5)
			return 1;
		int moneyInd = money / 5;
		int largestInd = largest / 5;
		// money==0.05, one combination
		// if(indMon==1) return 1;

		// check memo table
		if (memo[moneyInd][largestInd] != MIN) {
			// System.out.println("checking the memo, result is: "+memo[money][largest]);
			return memo[moneyInd][largestInd];
		}

		// checkLargest, ind stores the index of the largest possible bill value allowed
		// to use
		int ind = 0;
		while (ind < faceValue.length && faceValue[ind] > largest) {
			ind++;
		}

		// recursively check the possible # of combination for each subproblem
		// subproblem being dfs(money-i) where i is the currency face value less than
		// money
		long result = 0;
		// int i = 0;
		while (ind < faceValue.length) {
			result += dfs(money - faceValue[ind], faceValue[ind]);
			ind++;
		}
		memo[moneyInd][largestInd] = result;
		// System.out.println("result is: "+result);
		return result;
	}

}
