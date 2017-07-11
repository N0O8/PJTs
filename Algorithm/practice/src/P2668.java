import java.util.*;

/**
 * Created by jikhan.woo on 2017-07-11.
 * https://www.acmicpc.net/problem/2668
 */
public class P2668 {
    static int n, max_len = 0;
    static int[] arr;
    static boolean[] visited, map;

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        Stack s = new Stack();
        n = scanner.nextInt();
        arr = new int[n+1];
        visited = new boolean[n+1];
        map = new boolean[n+1];

        for (int i = 1; i <= n; i++) arr[i] = scanner.nextInt();

        for (int i = 1; i <= n; i++)
        {
            //if(!visited[i])
            {
                visited[i] = true;
                s.push(i);
                is_circular(i, i, s);
            }
        }

        System.out.println(max_len);
        for (int i = 1; i <= n; i++) {
            if(map[i]) System.out.println(i);
        }
    }

    public static void is_circular(int start, int pos, Stack s)
    {
        if(arr[pos] > n) return;

        if(visited[arr[pos]])
        {
            if(arr[pos] == start)
            {
                while (!s.isEmpty())
                {
                    map[(int) s.peek()] = true;
                    max_len++;
                    if ((int) s.pop() == arr[pos]) break;
                }
            }
            else
            {
                while (!s.isEmpty()) visited[(int)s.pop()] = false;
            }
            s.clear();

            return;
        }

        visited[arr[pos]] = true;
        s.push(arr[pos]);
        is_circular(start, arr[pos], s);
    }
}
