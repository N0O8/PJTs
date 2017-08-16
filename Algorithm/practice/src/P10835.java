import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-18.
 * https://www.acmicpc.net/problem/10835
 */
public class P10835
{
    static int[][] table;
    static int[] left_deck, right_deck;

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int n;

        n = scanner.nextInt();
        left_deck = new int[n];
        right_deck = new int[n];

        table = new int[n][n];

        for (int i = 0; i < n; i++) left_deck[i] = scanner.nextInt();
        for (int i = 0; i < n; i++) right_deck[i] = scanner.nextInt();

        System.out.println(calc(n-1, n-1));
    }

    static int calc(int left, int right)
    {
        if( (left < 0) || (right < 0) ) return 0;
        if(table[left][right] > 0) return table[left][right];

        int max = Integer.max(calc(left-1, right), calc(left-1, right-1));
        if(left_deck[left] > right_deck[right]) max = Integer.max(max, calc(left, right-1)+right_deck[right]);

        return table[left][right] = max;
    }
}
