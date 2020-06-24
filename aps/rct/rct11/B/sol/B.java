import java.util.Arrays;
import java.util.*;

public class B {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int arr[] = new int[n];
		int freq[] = new int[200010];
		TreeMap<Integer, Integer> tm = new TreeMap<>();
		for (int i = 0; i < n; i++) {
			arr[i] = sc.nextInt();
			freq[arr[i]]++;
		}
		for (int i = 0; i <= 100000; i++) {
			if (freq[i] > 0)
				tm.put(i, freq[i]);
		}
		Arrays.sort(arr);
		int ans = n;
		for (int i = n / 2 - 1; i >= 0; i--) {
			int val = 2 * arr[i];
			Integer key = tm.ceilingKey(val);
			if (tm.containsKey(arr[i]) && key != null) {
				ans--;
				int val1 = tm.get(key);
				if (val1 > 1) {
					val1--;
					tm.replace(key, val1);
				} else
					tm.remove(key);
				int val2 = tm.get(arr[i]);
				if (val2 > 1) {
					val2--;
					tm.replace(arr[i], val2);
				} else
					tm.remove(arr[i]);
			}
		}
		System.out.println(ans);
	}

}
