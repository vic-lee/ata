import java.util.*;

public class B {

	static Scanner sc = new Scanner(System.in);
	static int edges[][], dist[];
	static boolean[] visited;

	public static void main(String[] args) {
		int numVertices = sc.nextInt(), numTrainEdges = sc.nextInt();
		edges = new int[numVertices + 1][numVertices + 1];
		dist = new int[numVertices + 1];
		visited = new boolean[numVertices + 1];

		buildGraph(numVertices, numTrainEdges);
		Arrays.fill(dist, 1000000000);
		bfs(0, numVertices);

		int ans = dist[numVertices];
		Arrays.fill(dist, 1000000000);
		b = new boolean[numVertices + 1];
		bfs(1, numVertices);
		ans = Math.max(ans, dist[numVertices]);

		if (ans >= 1000000000) {
			System.out.println(-1);
			return;
		}
		System.out.println(ans);
	}

	public static void buildGraph(int n, int m) {
		for (int i = 0; i < m; i++) {
			int x = sc.nextInt(), y = sc.nextInt();
			edges[x][y] = 1;
			edges[y][x] = 1;
		}
	}

	public static void bfs(int x, int numVertices) {
		Queue<Integer> q = new LinkedList<>();
		q.add(1);
		dist[1] = 0;
		visited[1] = true;
		while (!q.isEmpty()) {
			int y = q.poll();
			for (int i = 1; i <= numVertices; i++) {
				if (edges[y][i] == x) {
					dist[i] = Math.min(dist[y] + 1, dist[i]);
					if (!visited[i]) {
						visited[i] = true;
						q.add(i);
					}
				}
			}
		}
	}
}
