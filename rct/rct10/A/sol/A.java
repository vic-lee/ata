import java.util.Scanner;

public class A {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt(), x1 = sc.nextInt(), y1 = sc.nextInt(), x2 = sc.nextInt(), y2 = sc.nextInt();
		sc.nextLine();
		String str = sc.nextLine();
		int h = x2 - x1, v = y2 - y1;
		for(int i = 0; i<t;i++) {
			if(h == 0 && v == 0) {
				System.out.println(i);
				return;
			}
			char c = str.charAt(i);
			if(c == 'N' && v>0) v--;
			if(c == 'S' && v<0) v++;
			if(c == 'E' && h>0) h--;
			if(c == 'W' && h<0) h++;
		}
		if(h==0 && v ==0) {
			System.out.println(t);
		}
		else System.out.println(-1);
	}

}
