
import java.io.*;
import java.util.*;

public class Main {

    public static void main(final String[] args) throws NumberFormatException, IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        final int daysCount = Integer.valueOf(br.readLine());

        final Queue<Integer> maxQueue = new PriorityQueue<Integer>(Collections.reverseOrder());
        final Queue<Integer> minQueue = new PriorityQueue<Integer>();

        long ans = 0;
        Integer min, max, val;

        for (int i = 0; i < daysCount; i++) {
            final String[] line = br.readLine().trim().split(" ");
            final int dailyReceiptCount = Integer.valueOf(line[0]);

            for (int k = 1; k <= dailyReceiptCount; k++) {
                val = Integer.valueOf(line[k]);
                maxQueue.add(val);
                minQueue.add(val);
            }
            max = maxQueue.poll();
            min = minQueue.poll();
            ans += max - min;
            // remove duplicates from the other queue.
            maxQueue.remove(min);
            minQueue.remove(max);
        }

        System.out.println(ans);
    }
}
