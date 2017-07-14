import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-13.
 * https://www.acmicpc.net/problem/2098
 */
public class P2098
{
    static int table[][];
    static int map[][];
    static int n;

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);

        n = scanner.nextInt();
        table = new int[n][n];
        map = new int[n][1 << n];

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) table[i][j] = scanner.nextInt();

        System.out.println(calc_path(0, 1));
    }

    static int calc_path(int cur, int visited)
    {
        int min = Integer.MAX_VALUE / 2;

        if(visited == (1 << n) - 1)
        {
            if(table[cur][0] != 0) return table[cur][0]; // return if all city were visited
            else return Integer.MAX_VALUE / 2; // cannot back to home, return MAX
        }
        if(map[cur][visited] != 0) return map[cur][visited];


        for(int i = 0; i < n; ++i)
        {
            if( (visited & (1 << i)) != 0 ) continue; // already visited city
            if(table[cur][i] == 0) continue; // cannot visit

            int price = calc_path(i, visited | (1 << i));
            min = Integer.min(min, price + table[cur][i]);
        }

/*
        while(rev_visited != 0)
        {
            if(table[cur][cnt] == 0)
            {
                cnt++;
                rev_visited >>= 1;
                continue; // cannot visit
            }
            if((rev_visited & 0x1) == 1)
            {
                if( (visited | (1 << cnt)) == ((1 << n) - 1) )
                {
                    if(table[cnt][0] != 0) min = Integer.min(min, table[cnt][0] + table[cur][cnt]); // return if all city were visited
                }
                else
                {
                    int price;
                    if(map[cur][visited | (1 << cnt)] != 0) price = map[cur][visited | (1 << cnt)]; // already calculated route
                    // for reducing function call overhead, deal with if statement in loop
                    else price = calc_path(cnt, visited | (1 << cnt));

                    min = Integer.min(min, price+table[cur][cnt]);
                }
            }
            rev_visited >>= 1;
            cnt++;
        }
*/
        return map[cur][visited] = min;
    }
}