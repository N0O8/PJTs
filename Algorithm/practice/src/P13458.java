import java.util.Scanner;

/**
 * Created by jikhan.woo on 2017-07-24.
 * https://www.acmicpc.net/problem/13458
 */
public class P13458
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int N, B, C;
        int[] A;
        long total = 0;

        N = scanner.nextInt();
        A = new int[N];

        for(int i = 0; i < A.length; i++) A[i] = scanner.nextInt();
        B = scanner.nextInt();
        C = scanner.nextInt();

        for(int i = 0; i < A.length; i++)
        {
            A[i] -= B;
            total += 1;

            if(A[i] <= 0) continue;
            total += (A[i]/C) + ( (A[i]%C > 0) ? 1 : 0 );
        }

        System.out.println(total);
    }
}
