import java.util.*;

public class B {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), m = sc.nextInt();
		while (m-- > 0) {
			int x = sc.nextInt();
			HashSet<Integer> hs = new HashSet<>();
			int cnt = 0;
			for (int j = 0; j < x; j++) {
				int k = sc.nextInt();
				if (hs.contains(-k)) {
					cnt++;
				} else {
					hs.add(k);
				}
			}
			if (cnt == 0) {
				System.out.println("YES");
				return;
			}
		}
		System.out.println("NO");
	}

}
