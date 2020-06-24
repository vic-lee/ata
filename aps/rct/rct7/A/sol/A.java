import java.util.*;

public class A {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while (t-- > 0) {
			int n = sc.nextInt();
			boolean isEven = false;
			int index = 0;
			for (int i = 0; i < n; i++) {
				if ((sc.nextInt() % 2) == 0) {
					isEven = true;
					index = i + 1;
				}
			}
			if (isEven) {
				System.out.println(1);
				System.out.println(index);
			} else if (n > 1) {
				System.out.println(2);
				System.out.println(1 + " " + 2);
			} else {
				System.out.println(-1);
			}
		}
	}

}
