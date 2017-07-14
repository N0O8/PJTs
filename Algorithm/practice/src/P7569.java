import java.util.Arrays;
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
        if(all_matured) System.out.println("0");
        else if(all_not_matured) System.out.println("-1");
        else System.out.println(calc());
    }

    static int calc()
    {
        int[][][] today_matured = new int[H][M][N];
        int[][][] mirror_box = new int[H][M][N];
        int days = 0;
        boolean stop_flag = false;

        while(!stop_flag)
        {
            days++;
            stop_flag = true;

            for (int i = 0; i < H; i++)
                for (int j = 0; j < M; j++)
                    for(int k = 0; k < N; k++) mirror_box[i][j][k] = box[i][j][k];

            System.out.println(days + " th day");

            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        if ((today_matured[i][j][k] != 1) && (box[i][j][k] == 1))
                        {
                            try
                            {
                                if ( (i-1 >= 0) && (box[i - 1][j][k] == 0) ) box[i - 1][j][k] = today_matured[i - 1][j][k] = 1; // above
                                if ( (i+1 < H) && (box[i + 1][j][k] == 0) ) box[i + 1][j][k] = today_matured[i + 1][j][k] = 1; // below
                                if ( (j-1 >= 0) && (box[i][j - 1][k] == 0) ) box[i][j - 1][k] = today_matured[i][j - 1][k] = 1; // up
                                if ( (j+1 < M) && (box[i][j + 1][k] == 0) ) box[i][j + 1][k] = today_matured[i][j + 1][k] = 1; // down
                                if ( (k-1 >= 0) && (box[i][j][k - 1] == 0) ) box[i][j][k - 1] = today_matured[i][j][k - 1] = 1; // left
                                if ( (k+1 < N) && (box[i][j][k + 1] == 0) ) box[i][j][k + 1] = today_matured[i][j][k + 1] = 1; // right
                            } catch (Exception e)
                            {
                            }
                        }
                        else if (box[i][j][k] == 0) stop_flag = false;
                    }
                }
            }

            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    Arrays.fill(today_matured[i][j], 0);
                    System.out.println(Arrays.toString(mirror_box[i][j]));
                    System.out.println(Arrays.toString(box[i][j]));
                }
            }
            if(Arrays.equals(mirror_box, box)) return -1; // todo : 다차원 배열 비교 수정필요

            if(days >= 4) break;
        }

        return days;
    }
}
