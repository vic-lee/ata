import java.util.Scanner;

public class A {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), k = sc.nextInt(), l = sc.nextInt(), c = sc.nextInt(), d = sc.nextInt(), p = sc.nextInt(),
				nl = sc.nextInt(), np = sc.nextInt();
		int totalVolume = k * l, totalSlices = c * d;
		System.out.println(Math.min(totalVolume / (n * nl), Math.min(totalSlices / n, p / (n * np))));
	}
}
