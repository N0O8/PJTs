import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-14.
 */
public class P7569
{
    static int N, M, H;
    static int[][][] box;

    public static void main(String[] args)
    {
        boolean all_matured = true, all_not_matured = true;
        Scanner scanner = new Scanner(System.in);

        N = scanner.nextInt();
        M = scanner.nextInt();
        H = scanner.nextInt();

        box = new int[H][M][N];

        System.out.printf("%d %d %d, %d\n", N, M, H, box.length);
        for(int i = 0; i < H; i++)
        {
            for (int j = 0; j < M; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    box[i][j][k] = scanner.nextInt();
                    if (box[i][j][k] == 1) all_not_matured = false;
                    else if (box[i][j][k] == 0) all_matured = false;
                }
            }
        }
        System.out.println("In Processing...");
        if(all_matured) System.out.println("0");
        else if(all_not_matured) System.out.println("-1");
        else System.out.println(calc2());
    }

    static int calc()
    {
        int[][][] today_matured = new int[H][M][N];
        int[][][] mirror_box = new int[H][M][N];
        int days = 0;

        while(true)
        {
            days++;

            for (int i = 0; i < H; i++)
                for (int j = 0; j < M; j++)
                    for(int k = 0; k < N; k++)
                        mirror_box[i][j][k] = box[i][j][k];

            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        if ((today_matured[i][j][k] != 1) && (box[i][j][k] == 1))
                        {
                            if ( (i-1 >= 0) && (box[i - 1][j][k] == 0) ) box[i - 1][j][k] = today_matured[i - 1][j][k] = 1; // above
                            if ( (i+1 < H) && (box[i + 1][j][k] == 0) ) box[i + 1][j][k] = today_matured[i + 1][j][k] = 1; // below
                            if ( (j-1 >= 0) && (box[i][j - 1][k] == 0) ) box[i][j - 1][k] = today_matured[i][j - 1][k] = 1; // up
                            if ( (j+1 < M) && (box[i][j + 1][k] == 0) ) box[i][j + 1][k] = today_matured[i][j + 1][k] = 1; // down
                            if ( (k-1 >= 0) && (box[i][j][k - 1] == 0) ) box[i][j][k - 1] = today_matured[i][j][k - 1] = 1; // left
                            if ( (k+1 < N) && (box[i][j][k + 1] == 0) ) box[i][j][k + 1] = today_matured[i][j][k + 1] = 1; // right
                        }
                    }
                }
            }

            for (int i = 0; i < H; i++)
                for (int j = 0; j < M; j++)
                    for(int k = 0; k < N; k++)
                        today_matured[i][j][k] = 0;

            if(Arrays.deepEquals(mirror_box, box)) break;
        }


        for (int i = 0; i < H; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < N; k++)
                    if(box[i][j][k] == 0) return -1;

        return days-1;
    }

    static int calc2()
    {
        int max_day = 0;
        Queue q = new LinkedList();

        for (int i = 0; i < H; i++)
            for (int j = 0; j < M; j++)
                for(int k = 0; k < N; k++)
                    if(box[i][j][k] == 1) q.offer((int)(box[i][j][k]<<21 | i<<14 | j<<7 | k));  // max : 100 100 100 100

        while(!q.isEmpty())
        {
            int day = (int)q.peek() >> 21 & 0x7ff;
            int h = (int)q.peek() >> 14 & 0x7f;
            int m = (int)q.peek() >> 7 & 0x7f;
            int n = (int)q.poll() & 0x7f;

            if(day > max_day) max_day = day;
            day++;
            if ( (h-1 >= 0) && (box[h - 1][m][n] == 0) ) // above
            {
                box[h - 1][m][n] = day;
                q.offer((int)(box[h-1][m][n]<<21 | (h-1)<<14 | m<<7 | n));
            }
            if ( (h+1 < H) && (box[h + 1][m][n] == 0) ) // below
            {
                box[h + 1][m][n] = day;
                q.offer((int)(box[h+1][m][n]<<21 | (h+1)<<14 | m<<7 | n));
            }
            if ( (m-1 >= 0) && (box[h][m - 1][n] == 0) ) // up
            {
                box[h][m - 1][n] = day;
                q.offer((int)(box[h][m-1][n]<<21 | h<<14 | (m-1)<<7 | n));
            }
            if ( (m+1 < M) && (box[h][m + 1][n] == 0) ) // down
            {
                box[h][m + 1][n] = day;
                q.offer((int)(box[h][m+1][n]<<21 | h<<14 | (m+1)<<7 | n));
            }
            if ( (n-1 >= 0) && (box[h][m][n - 1] == 0) ) // left
            {
                box[h][m][n - 1] = day;
                q.offer((int)(box[h][m][n-1]<<21 | h<<14 | m<<7 | (n-1)));
            }
            if ( (n+1 < N) && (box[h][m][n + 1] == 0) ) // right
            {
                box[h][m][n + 1] = day;
                q.offer((int)(box[h][m][n+1]<<21 | h<<14 | m<<7 | (n+1)));
            }
        }

        for (int i = 0; i < H; i++)
            for (int j = 0; j < M; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    if (box[i][j][k] == 0) return -1;
                }
            }

        return max_day-1;
    }
}