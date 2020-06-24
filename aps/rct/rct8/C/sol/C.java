import java.util.Scanner;

public class C {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int a = sc.nextInt(), b = sc.nextInt();
		int gcd = gcd(a, b);
		a /= gcd;
		b /= gcd;
		if (Math.abs(a - b) == 1) {
			System.out.println("Equal");
		} else if (a < b) {
			System.out.println("Dasha");
		} else
			System.out.println("Masha");
	}

	private static int gcd(int a, int b) {
		// TODO Auto-generated method stub
		if (a % b == 0)
			return b;
		return gcd(b, a % b);
	}

}
