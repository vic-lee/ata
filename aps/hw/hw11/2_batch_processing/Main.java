import java.io.*;
import java.util.Arrays;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line1 = br.readLine().trim().split(" ");
		StringBuilder sb = new StringBuilder("");
		int N = Integer.parseInt(line1[0]);
		int M = Integer.parseInt(line1[1]);
		int[] arr = new int[N];
		String[] line2 = br.readLine().trim().split(" ");
		for (int i = 0; i < N; i++) {
			arr[i] = Integer.parseInt(line2[i]);
		}

		long start = Integer.MAX_VALUE;
		long end = 0;
		// CALCULATE START AND END!
		for (int i = 0; i < N; i++) {
			end += arr[i];
			if (arr[i] < start) {
				start = arr[i];
			}
		}

		int[] result = binary(arr, start, end, M);
		printList(result);
		boolean flag = false;
		for (int i = M - 2; i >= 0; i--) {
			if (result[i] == 0 || flag) {
				flag = true;
				result[i] = Math.max(result[i + 1] + 1, result[i]);
			}
		}
		printList(result);
		int ind = M - 2;
		for (int i = 0; i < N; i++) {
			sb.append(arr[i] + " ");
			if ((ind >= 0) && (i + 1 == result[ind])) {
				sb.append("/ ");
				ind--;
			}
		}
		System.out.println(sb.deleteCharAt(sb.length() - 1).toString());

	}

	public static int[] checkValid(long target, int[] arr, int n) {
		int[] cuts = new int[n];
		long subCount = 0;
		long sum = 0;
		int ind = 0;
		for (int i = arr.length - 1; i >= 0; i--) {
			if (arr[i] > target)
				return null;
			sum += arr[i];
			if (sum > target) {
				subCount++;
				if (subCount <= n) {
					cuts[ind] = i + 1;
					ind++;
				}
				sum = arr[i];
			}
		}
		subCount++;
		System.out.println("checking valid: target: " + target + "; subcount: " + subCount);
		if (subCount > n) {
			System.out.println("list is null");
			return null;
		} else {
			printList(cuts);
			return cuts;
		}
	}

	public static int[] binary(int[] arr, long start, long end, int n) {
		long mid = (start + end) / 2;

		System.out.println("start: " + start + " ; end: " + end + "; mid: " + mid);

		if (start >= end) {
			return checkValid(end, arr, n);
		}
		if (checkValid(mid, arr, n) != null) {
			return binary(arr, start, mid, n);
		} else {
			return binary(arr, mid + 1, end, n);
		}
	}

	public static void printList(int[] arr) {
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
	}
}
