import java.io.*;
import java.util.Arrays;

public class Main {

	static int INF = Integer.MAX_VALUE;
	static int[][] memo;
	static int[] list;
	static int num;
	static int maxNum;
	static int minNum;
	static int sum;

	public static void main(String[] args) throws NumberFormatException, IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		num = Integer.parseInt(br.readLine().trim());
		maxNum = ((num % 2 == 0) ? (num / 2) : (num / 2 + 1));
		minNum = num - maxNum;
		list = new int[num];
		sum = 0;
		for (int i = 0; i < num; i++) {
			list[i] = Integer.parseInt(br.readLine().trim());
			sum += list[i];
		}
		// Arrays.sort(list);
		memo = new int[sum + 1][num + 1];
		for (int i = 0; i <= sum; i++) {
			for (int j = 0; j <= num; j++) {
				memo[i][j] = INF;
			}
		}
		int diff = DP(0, 0, 0);
		int leftHeight = (sum - diff) / 2;
		int right = sum - leftHeight;
		System.out.println(leftHeight + " " + right);

	}

	// for the i'th number, assuming it's already on the right tower,
	// we decide whether to put on the left tower
	public static int DP(int i, int leftHeight, int leftNum) {
		// System.out.println(i+" "+leftHeight+" "+leftNum+" ");

		// if: 1. number of toy on left tower is larger than maxNum
		// 2. number of toy on left + all the toy left is smaller than minNum
		// i.e. at this point, even all the remaining toys goes onto
		// the left tower, the difference in number is still bigger than one
		// then: solution is not valid, return INF
		if ((leftNum > maxNum) || (num - i + leftNum < minNum)) {
			// System.out.println("not possible");
			return INF;
		}
		if (i >= num) {
			int right = sum - leftHeight;
			return (leftHeight < right) ? (right - leftHeight) : (leftHeight - right);
		}

		if (memo[leftHeight][leftNum] != INF) {
			return memo[leftHeight][leftNum];
		}

		int diff = Math.min(DP(i + 1, leftHeight + list[i], leftNum + 1), DP(i + 1, leftHeight, leftNum));

		// memoizing:
		memo[leftHeight][leftNum] = diff;
		memo[sum - leftHeight][num - leftNum] = diff; // the result is symmetric for right or left
		return diff;

	}

}
