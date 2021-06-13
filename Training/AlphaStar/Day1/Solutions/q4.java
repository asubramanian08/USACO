package Day1.Solutions;

/*USACO DEC17 Problem 'heyfeast' Analysis
by Nick Wu
Let's start by tackling a problem that we'll need to solve if we want to solve the original problem - 
given that haybale i is the rightmost haybale we'll eat, what is the rightmost leftmost haybale we need to
eat to guarantee a total flavor of M?

We can solve this problem in linear time for all choices of rightmost haybale using two pointers. If we 
maintain a rightmost pointer that starts at the leftmost haybale and only moves to the right, along with a 
leftmost pointer that also starts at the leftmost haybale, we can advance the leftmost pointer if the 
haybales between those pointers sum to a total flavor of at least M. Both pointers only advance to the 
right, and we can maintain a running total of the sum between the two pointers.

With this in place, we now need to be able to efficiently query for the minimum value in an array in these
subintervals. There are several different approaches to do this efficiently. One of the simplest approaches
is keeping all of the values between the two entries into a balanced binary search tree. We can insert,
remove, and query for the maximum value in O(logN), giving us an O(NlogN) algorithm.
*/
import java.io.*;
import java.util.*;

public class q4 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        long need = Long.parseLong(st.nextToken());
        long[] f = new long[n];
        long[] s = new long[n];
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            f[i] = Long.parseLong(st.nextToken());
            s[i] = Long.parseLong(st.nextToken());
        }
        int left = 0;
        long ret = Long.MAX_VALUE;
        TreeMap<Long, Integer> seen = new TreeMap<Long, Integer>();
        long flavor = 0;
        for (int i = 0; i < n; i++) {
            flavor += f[i];
            update(seen, s[i], 1);
            while (flavor - f[left] >= need) {
                update(seen, s[left], -1);
                flavor -= f[left++];
            }
            if (flavor >= need) {
                ret = Math.min(ret, seen.lastKey());
            }
            pw.println(ret);
        }
        pw.close();
    }

    private static void update(Map<Long, Integer> m, long k, int v) {
        if (!m.containsKey(k)) {
            m.put(k, 0);
        }
        int nv = m.get(k) + v;
        if (nv == 0) {
            m.remove(k);
        } else {
            m.put(k, nv);
        }

    }
}
