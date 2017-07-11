import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-11.
 * https://www.acmicpc.net/problem/10610
 */

public class P10610
{
    public static void main(String[] args)
    {
        Scanner s = new Scanner(System.in);
        String input = s.nextLine();
        StringBuilder sb = new StringBuilder();

        int[] ibuffer = new int[10];
        int count = 0;

        for(int i = 0; i < input.length(); i++)
        {
            ibuffer[input.charAt(i)-'0']++;
            count += input.charAt(i)-'0';
        }

        if( (ibuffer[0] > 0) && (count%3 == 0) )
        {
            for (int i = 9; i >= 0; i--)
            {
                while(ibuffer[i]-- > 0) sb.append(i);
            }
            System.out.println(sb.toString());
        }
        else System.out.println("-1");
    }
}