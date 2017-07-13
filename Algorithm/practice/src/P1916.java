import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-12.
 * https://www.acmicpc.net/problem/1916
 */
public class P1916
{
    public static void main(String[] args)
    {
        solve sol = new solve();
        sol.init();
        System.out.println(sol.run());
    }
}

class solve
{
    int city, bus, start, end;
    int[][] map;
    int[] price_table;

    void init()
    {
        Scanner scanner = new Scanner(System.in);
        city = scanner.nextInt();
        bus = scanner.nextInt();
        map = new int[bus][3];
        price_table = new int[bus];
        for(int i = 0; i < bus; i++)
        {
            map[i][0] = scanner.nextInt();
            map[i][1] = scanner.nextInt();
            map[i][2] = scanner.nextInt();
        }
        start = scanner.nextInt();
        end = scanner.nextInt();
    }

    int run()
    {
        int min = Integer.MAX_VALUE;
        for(int i = 0; i < bus; i++)
        {
            if(map[i][0] == start) calc_price(i, map[i][2]);
        }

        for (int i = 0; i < price_table.length; i++)
        {
            if( (map[i][1] == end) && (price_table[i] > 0) )
            {
                if(price_table[i] <= min) min = price_table[i];
            }
        }

        return min;
    }

    void calc_price(int cur, int price)
    {
        if(map[cur][1] == end) return;

        for(int i = 0; i < bus; i++)
        {
            if(map[i][0] == map[cur][1])
            {
                int temp = price + map[cur][2];
                if(temp < price_table[i]) calc_price(i, temp);
            }
        }
    }
}