import java.util.Scanner;

public class B {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), x = sc.nextInt();
		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += sc.nextInt();
		if (sum == (x - n + 1)) {
			System.out.println("YES");
		} else
			System.out.println("NO");
	}
}
