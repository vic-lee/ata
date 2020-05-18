import java.util.Scanner;

/* if you want to submit this on VJudge, change name of class from B -> Main*/

public class B {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		int n = 0, m = 0;
		int arr[][] = null;
		Loop1: while (true) {
			n = sc.nextInt();
			m = sc.nextInt();
			if (n == 0 && m == 0)
				break;
			arr = new int[n + m][3];
			for (int i = 0; i < n; i++) {
				arr[i][0] = sc.nextInt();
				arr[i][1] = sc.nextInt();
			}
			for (int i = n; i < n + m; i++) {
				arr[i][0] = sc.nextInt();
				arr[i][1] = sc.nextInt();
				arr[i][2] = sc.nextInt();
			}

			boolean array[] = new boolean[1000000 + 1];
			for (int i = 0; i < n; i++) {
				int x = arr[i][0], y = arr[i][1];
				for (int j = x; j < y; j++) {
					if (array[j]) {
						System.out.println("CONFLICT");
						continue Loop1;
					}
					array[j] = true;
				}
			}
			for (int i = n; i < n + m; i++) {
				int x = arr[i][0], y = arr[i][1], z = arr[i][2];
				while (y < 1000001) {
					for (int j = x; j < y; j++) {
						if (array[j]) {
							System.out.println("CONFLICT");
							continue Loop1;
						}
						array[j] = true;
					}
					x += z;
					y += z;
				}
			}
			System.out.println("NO CONFLICT");
		}
	}

}
