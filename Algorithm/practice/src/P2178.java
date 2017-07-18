import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-18.
 * https://www.acmicpc.net/problem/2178
 */

public class P2178
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String[] smap;
        int[][] imap;
        int n, m, min = Integer.MAX_VALUE;
        Queue q = new LinkedList();

        n = scanner.nextInt();
        m = scanner.nextInt();

        smap = new String[n];
        imap = new int[n][m];
        scanner.nextLine();

        for (int i = 0; i < n; i++)
        {
            smap[i] = scanner.nextLine();
            for (int j = 0; j < m; j++) imap[i][j] = smap[i].charAt(j) - '0';
        }

        q.offer(1 << 16);

        while (!q.isEmpty())
        {
            int temp = (int)q.poll();
            int cur_x = ( temp & 0xff);
            int cur_y = ((temp >> 8) & 0xff);
            int cur_distance = temp>>16;

            if ((cur_x == n - 1) && (cur_y == m - 1))
            {
                min = Integer.min(cur_distance, min);
                imap[0][0] = 0;
                continue;
            }

            cur_distance++;

            if ((cur_x - 1 >= 0) && ((imap[cur_x - 1][cur_y] == 1) || (imap[cur_x - 1][cur_y] > cur_distance))) // up
            {
                imap[cur_x - 1][cur_y] = cur_distance;
                int data = (cur_x - 1) | (cur_y << 8) | (cur_distance << 16);

                q.offer(data);
            }
            if ((cur_x + 1 < n) && ((imap[cur_x + 1][cur_y] == 1) || (imap[cur_x + 1][cur_y] > cur_distance))) // down
            {
                imap[cur_x + 1][cur_y] = cur_distance;
                int data = (cur_x + 1) | (cur_y << 8) | (cur_distance << 16);

                q.offer(data);
            }
            if ((cur_y - 1 >= 0) && ((imap[cur_x][cur_y - 1] == 1) || (imap[cur_x][cur_y - 1] > cur_distance))) // left
            {
                imap[cur_x][cur_y - 1] = cur_distance;
                int data = (cur_x) | ((cur_y - 1) << 8) | (cur_distance << 16);

                q.offer(data);
            }
            if ((cur_y + 1 < m) && ((imap[cur_x][cur_y + 1] == 1) || (imap[cur_x][cur_y + 1] > cur_distance))) // right
            {
                imap[cur_x][cur_y + 1] = cur_distance;
                int data = (cur_x) | ((cur_y + 1) << 8) | (cur_distance << 16);

                q.offer(data);
            }
        }

        System.out.println(min);
    }
}