import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int numsCount = input.nextInt();
        BigInteger[] nums = new BigInteger[numsCount];

        for (int i = 0; i < numsCount; i++) {
            int tmp = input.nextInt();
            nums[i] = BigInteger.valueOf(tmp);
        }

        input.close();

        BigInteger maxProduct = nums[0];
        BigInteger currentMin = nums[0];
        BigInteger currentMax = nums[0];

        for (int i = 1; i < nums.length; i++) {
            BigInteger num = nums[i];

            if (num.compareTo(BigInteger.ZERO) < 0) {
                BigInteger tmp = currentMax;
                currentMax = currentMin;
                currentMin = tmp;
            }

            currentMin = currentMin.multiply(num);
            if (num.compareTo(currentMin) < 0) {
                currentMin = num;
            }

            currentMax = currentMax.multiply(num);
            if (num.compareTo(currentMax) > 0) {
                currentMax = num;
            }

            // System.out.println(currentMin + " " + currentMax);

            maxProduct = currentMax.compareTo(maxProduct) > 0 ? currentMax : maxProduct;
        }

        System.out.println(maxProduct);
    }
}