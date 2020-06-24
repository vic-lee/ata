import java.util.Scanner;

public class A {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int evenLast = -1, oddLast = -1, ans = -1;
		for (int i = 1; i <= n; i++) {
			int x = sc.nextInt();
			if (x % 2 == 0) {
				if (evenLast == -1)
					evenLast = i;
				else
					ans = 0;
			} else {
				if (oddLast == -1)
					oddLast = i;
			}
		}
		if (ans == -1)
			System.out.println(evenLast);
		else
			System.out.println(oddLast);
	}

}
