import java.util.Scanner;

public class B {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int k2 = sc.nextInt(), k3 = sc.nextInt(), k5 = sc.nextInt(), k6 = sc.nextInt();
		int x = Math.min(k2, Math.min(k5, k6));
		int y = Math.max(0, Math.min(k3, k2 - x));
		System.out.println(x * 256l + y * 32l);
	}

}
