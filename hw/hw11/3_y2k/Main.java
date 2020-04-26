import java.io.*;

public class Main {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine().trim());
		boolean[][] years = new boolean[n][10000];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 10000; j++) {
				years[i][j] = false;
			}
		}
		int yi, ai, bi, diff;
		String[] line;
		for (int i = 0; i < n; i++) {
			line = br.readLine().trim().split(" ");
			yi = Integer.parseInt(line[0]);
			ai = Integer.parseInt(line[1]);
			bi = Integer.parseInt(line[2]);
			diff = bi - ai;

			for (int j = yi; j < 10000; j += diff) {
				years[i][j] = true;
			}

		}
		boolean temp;
		int i = 0;
		while (i < 10000) {
			/*
			 * if(i==2141) System.out.println(i);
			 */
			temp = true;
			for (int j = 0; j < n; j++) {

				if (!years[j][i]) {
					temp = false;
					// System.out.println(years[j][i]);
					// System.out.println(temp);
					break;
				}
			}
			if (temp)
				break;
			i++;
		}
		// System.out.println(years[0][1913]);
		// System.out.println((1913-1240)%11);
		if (i < 10000)
			System.out.println(i);
		else
			System.out.println(-1);
	}

}
