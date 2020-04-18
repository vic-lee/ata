import java.io.*;
import java.text.DecimalFormat;

public class Main {

	static double PI = Math.PI;
	static double epsilon = 2 * Math.exp(-28);

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().trim().split(" ");
		double L = Double.parseDouble(line[0]);
		double T = Double.parseDouble(line[1]);
		double C = Double.parseDouble(line[2]);

		double arcLength = L * (1 + T * C);
		// System.out.println(arcLength);
		double halfArc = arcLength / 2.0;
		double halfLength = L / 2.0;

		if (arcLength == L || L == 0) {
			System.out.println("0.000");
		} else {
			double lowerTheta = 0;
			double upperTheta = PI;
			double theta = binarySearch(lowerTheta, upperTheta, halfArc, halfLength);
			// System.out.println(theta);
			double result = (halfArc / theta) - (halfLength / Math.tan(theta));
			DecimalFormat df = new DecimalFormat("0.000");
			System.out.println(df.format(result));
		}
	}

	// MONO DESCREASING
	public static double binarySearch(double lowerTheta, double upperTheta, double halfArc, double halfLength) {
		System.out.println(epsilon);
		double mid = (lowerTheta + upperTheta) / 2.0;
		double result;
		int i = 0;
		while (upperTheta >= lowerTheta) {
			mid = (lowerTheta + upperTheta) / 2.0;
			result = Math.sin(mid) / mid - (halfLength / halfArc);
			System.out.println("mid is " + mid + " and the result is " + result);
			if (result > epsilon) {
				lowerTheta = mid;
			} else if (result < -epsilon) {
				upperTheta = mid;
			} else {
				return mid;
			}
			i++;
		}
		return mid;
	}

}
