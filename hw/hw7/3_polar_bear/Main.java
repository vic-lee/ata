class Main {
    public static void main(String[] args) {
        // 1 <= N, M <= 1000
        int N = 1000;
        int M = 1000;

        // Elevations are between [1, 10^9]
        int minHeight = 1;
        int maxHeight = 25;

        System.out.println(N + " " + M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                System.out.print(
                        ((int) (Math.random() * (maxHeight - minHeight) + 1) + minHeight) + ((j == M - 1) ? "" : " "));
            }
            System.out.println();
        }

        // 1 <= seaLevels <= 10^5
        int numSeaLevels = 100000;

        // 0 <= t1 <= t2 <= ... < 10^9 is the maximum water level
        int startingLevel = 0;
        System.out.println(numSeaLevels);
        for (int k = 0; k < numSeaLevels; k++) {
            System.out.print((startingLevel++) + (k == numSeaLevels - 1 ? "" : " "));
        }
    }
}