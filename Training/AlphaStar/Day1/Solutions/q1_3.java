package Day1.Solutions;
/* Using a disjoint-set data structure for merging, the last approach can be improved to be as good as 
O(M + N alpha(N)), where alpha is a very slow-growing function.

Here is Jonathan Paulson's solution in Java, implementing a disjoint-set data structure with an 
O(M + N log N) guarantee:  */

import java.io.*;

public class q1_3 {
    // union-find with path-compression
    // amortized O(log N) per operation
    static int[] uf;

    static void union(int x, int y) {
        uf[find(x)] = find(y);
    }

    static int find(int x) {
        if (x == uf[x]) {
            return x;
        }
        return uf[x] = find(uf[x]);
    }

    public static int i(String s) {
        return Integer.parseInt(s);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("truth.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("truth.out")));
        String[] arr = in.readLine().split(" ");
        int n = i(arr[0]);
        int m = i(arr[1]);
        uf = new int[n];
        for (int i = 0; i < n; i++)
            uf[i] = i;
        int[] C = new int[n];
        for (int i = 0; i < n; i++)
            C[i] = i + 1;
        for (int t = 0; t < m; t++) {
            arr = in.readLine().split(" ");
            int x = i(arr[0]) - 1;
            int y = i(arr[1]) - 1;
            union(x, y);
            boolean T = arr[2].charAt(0) == 'T';
            if ((C[x] == C[y] && !T) || (C[x] == -C[y] && T)) {
                out.println(t);
                out.flush();
                return;
            }
            int cy = C[y];
            int cx = T ? C[x] : -C[x];
            for (int i = 0; i < n; i++) {
                if (C[i] == cy)
                    C[i] = cx;
                else if (C[i] == -cy)
                    C[i] = -cx;
            }
        }
        in.close();
        out.println(m);
        out.close();
        out.close();
    }
}
