import java.util.Scanner;
import java.util.Stack;

/**
 * Created by jikhan.woo on 2017-07-24.
 * https://www.acmicpc.net/problem/12100
 */
public class P12100
{
    static int N;
    static int[][][] cache;
    static int[][] board;

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        Stack stack = new Stack();
        int left = 0, right = 1, up = 2, down = 3, sum_of_element = 0, max = 0;
        N = scanner.nextInt();
        board = new int[N][N];
        cache = new int[3000][N][N];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                sum_of_element += board[i][j] = scanner.nextInt();
                max = Integer.max(max, board[i][j]);
            }
        }

        if(max == sum_of_element)
        {
            System.out.println(sum_of_element);
            return;
        }

        for(int i = down; i >= left; i--)
        {
            max = Integer.max(max, rotate(1 << 10, i));
            if(max == sum_of_element)
            {
                System.out.println(sum_of_element);
                return;
            }
            stack.push(2 << 10 | i << (1-1)*2);
        } // data : step + 5th rotate + 4th rotate + 3rd rotate + 2nd rotate + 1st rotate -- xxxx xx xx xx xx xx

        while(!stack.isEmpty())
        {
            int temp = (int)stack.pop();
            int step = temp >> 10;
            int raw_data = temp & 0x3FF;

            for(int i = down; i >= left; i--)
            {
                max = Integer.max(max, rotate(temp, i));
                if(max == sum_of_element)
                {
                    System.out.println(sum_of_element);
                    return;
                }
                if(step < 5) stack.push(step+1 << 10 | (raw_data | (i << (step-1)*2)) );
            }
        }
        System.out.println(max);
        /*
        int temp;
        rotate(1 << 10, left);
        temp = left << (1-1)*2;
        System.out.println(temp);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) System.out.printf("%d ", cache[temp][i][j]);
            System.out.println();
        }

        System.out.println();
        System.out.println(rotate(2 << 10 | temp, right));
        temp |= right << (2-1)*2;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) System.out.printf("%d ", cache[temp][i][j]);
            System.out.println();
        }
        */
    }

    public static int rotate(int data, int direction)
    {
        int max_val = 0;
        int step = data >> 10;
        int received_pos = data & 0x3FF;
        int final_pos = received_pos | direction << (step-1) * 2;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) cache[final_pos][i][j] = (step == 1) ? board[i][j] : cache[received_pos][i][j];

        switch(direction)
        {
            case 0: // left
                for(int i = 0; i < N; i++)
                {
                    int board_pos = 0;
                    for(int j = 1; j < N; j++)
                    {
                        if(cache[final_pos][i][j] > 0)
                        {
                            int temp = cache[final_pos][i][j];
                            if(cache[final_pos][i][j] == cache[final_pos][i][board_pos])
                            {
                                cache[final_pos][i][j] = 0;
                                cache[final_pos][i][board_pos] += temp;
                                max_val = Integer.max(max_val, cache[final_pos][i][board_pos]);
                                board_pos++;
                            } // merge
                            else if(cache[final_pos][i][board_pos] == 0)
                            {
                                cache[final_pos][i][j] = 0;
                                cache[final_pos][i][board_pos] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][i][board_pos]);
                            } // shift to empty
                            else
                            {
                                cache[final_pos][i][j] = 0;
                                cache[final_pos][i][++board_pos] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][i][board_pos]);
                            } // cannot merged -> shift to next position
                        }
                    }
                }
                break;
            case 1: // right
                for(int i = 0; i < N; i++)
                {
                    int board_pos = N-1;
                    for(int j = N-2; j >= 0; j--)
                    {
                        if(cache[final_pos][i][j] > 0)
                        {
                            int temp = cache[final_pos][i][j];
                            if(cache[final_pos][i][j] == cache[final_pos][i][board_pos])
                            {
                                cache[final_pos][i][j] = 0;
                                cache[final_pos][i][board_pos] += temp;
                                max_val = Integer.max(max_val, cache[final_pos][i][board_pos]);
                                board_pos--;
                            } // merge
                            else if(cache[final_pos][i][board_pos] == 0)
                            {
                                cache[final_pos][i][j] = 0;
                                cache[final_pos][i][board_pos] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][i][board_pos]);
                            } // shift to empty
                            else
                            {
                                cache[final_pos][i][j] = 0;
                                cache[final_pos][i][--board_pos] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][i][board_pos]);
                            } // cannot merged -> shift to next position
                        }
                    }
                }
                break;
            case 2: // up
                for(int i = 0; i < N; i++)
                {
                    int board_pos = 0;
                    for(int j = 1; j < N; j++)
                    {
                        if(cache[final_pos][j][i] > 0)
                        {
                            int temp = cache[final_pos][j][i];
                            if(cache[final_pos][j][i] == cache[final_pos][board_pos][i])
                            {
                                cache[final_pos][j][i] = 0;
                                cache[final_pos][board_pos][i] += temp;
                                max_val = Integer.max(max_val, cache[final_pos][board_pos][i]);
                                board_pos++;
                            } // merge
                            else if(cache[final_pos][board_pos][i] == 0)
                            {
                                cache[final_pos][j][i] = 0;
                                cache[final_pos][board_pos][i] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][board_pos][i]);
                            } // shift to empty
                            else
                            {
                                cache[final_pos][j][i] = 0;
                                cache[final_pos][++board_pos][i] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][board_pos][i]);
                            } // cannot merged -> shift to next position
                        }
                    }
                }
                break;
            case 3: // down
                for(int i = 0; i < N; i++)
                {
                    int board_pos = N-1;
                    for(int j = N-2; j >= 0; j--)
                    {
                        if(cache[final_pos][j][i] > 0)
                        {
                            int temp = cache[final_pos][j][i];
                            if(cache[final_pos][j][i] == cache[final_pos][board_pos][i])
                            {
                                cache[final_pos][j][i] = 0;
                                cache[final_pos][board_pos][i] += temp;
                                max_val = Integer.max(max_val, cache[final_pos][board_pos][i]);
                                board_pos--;
                            } // merge
                            else if(cache[final_pos][board_pos][i] == 0)
                            {
                                cache[final_pos][j][i] = 0;
                                cache[final_pos][board_pos][i] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][board_pos][i]);
                            } // shift to empty
                            else
                            {
                                cache[final_pos][j][i] = 0;
                                cache[final_pos][--board_pos][i] = temp;
                                max_val = Integer.max(max_val, cache[final_pos][board_pos][i]);
                            } // cannot merged -> shift to next position
                        }
                    }
                }
                break;
            default:
                break;
        }

/*
        System.out.printf("%d th rotate, direction : %s\n", step, (direction == 0) ? "Left" : (direction == 1) ? "Right" : (direction == 2) ? "Up" : "Down");
        System.out.print("start ");
        for (int i = 0; i < step; i++)
        {
            System.out.printf("--> %s ", ((final_pos & (0x3 << (i*2))) >> (i*2) == 0) ? "Left" : ((final_pos & (0x3 << (i*2))) >> (i*2) == 1) ? "Right" : ((final_pos & (0x3 << (i*2))) >> (i*2) == 2) ? "Up" : "Down");
        }
        System.out.println();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) System.out.printf("%d ", cache[final_pos][i][j]);
            System.out.println();
        }
        System.out.println();
*/
        return max_val;
    }
}
