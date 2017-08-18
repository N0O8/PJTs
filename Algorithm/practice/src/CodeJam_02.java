import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * Created by jikhan.woo on 2017-08-18.
 * https://codejam.lge.com/contest/dashboard?problem_id=13&round_id=3
 */
public class CodeJam_02
{
    public static void main(String[] args)
    {
        if(args.length == 0)
        {
            System.out.println("No args");
            System.exit(0);
        }

        Solve_CodeJam_02 t = new Solve_CodeJam_02();
        t.run(args[0]);
    }
}

class Solve_CodeJam_02
{
    public void run(String filename)
    {
        File file = new File(filename);
        try
        {
            BufferedReader br = new BufferedReader(new FileReader(file));
            FileWriter out = new FileWriter(filename.substring(0, filename.length()-3).concat(".out"));
            int T = Integer.parseInt(br.readLine());
            StringTokenizer token;

            for(int z = 0; z < T; z++)
            {
                int N = Integer.parseInt(br.readLine());
                int[][] map = new int[N][2];
                double min_val = 987654321.0;
                long min_perimeter = 987654321;

                for (int i = 0; i < N; i++)
                {
                    String temp = br.readLine();
                    token = new StringTokenizer(temp, " ");

                    for (int j = 0; token.hasMoreTokens(); j++) {
                        map[i][0] = Integer.parseInt(token.nextToken());
                        map[i][1] = Integer.parseInt(token.nextToken());
                    }
                }

                for (int i = 0; i < N; i++)
                {
                    int x1 = map[i][0];
                    int y1 = map[i][1];

                    for (int j = i + 1; j < N; j++)
                    {
                        int x2 = map[j][0];
                        int y2 = map[j][1];
                        int diff_x = Math.abs(x1 - x2);
                        int diff_y = Math.abs(y1 - y2);

                        double val = (double)Integer.min(diff_x, diff_y) / (double)Integer.max(diff_x, diff_y);

                        if (min_val > val)
                        {
                            min_val = val;
                            min_perimeter = diff_x + diff_y;
                            min_perimeter *= 2;
                        } else if (min_val == val)
                        {
                            long temp = diff_x + diff_y;
                            temp *= 2;
                            min_perimeter = Long.min(min_perimeter, temp);
                        }
                    }
                }

                out.write(Long.toUnsignedString(min_perimeter));
                out.write("\n");
            }
            br.close();
            out.close();
        } catch (Exception e) {}
    }
}


/*
public class Filtest {

 public static void main(String[] args) {

  StringTokenizer token;

  try {
   BufferedReader in  = new BufferedReader(new FileReader("rTest.txt")); //파일로부터 데이터를 읽어 버퍼에 저장
   FileWriter out = new FileWriter("wTest.txt"); //읽은 내용을 복사할 파일을 생성

   String temp;

   while ((temp = in.readLine()) != null) { //한 줄씩 읽기
    token = new StringTokenizer(temp, " ");  //공백 단위로 끊기
    for (int i = 0; token.hasMoreTokens(); i++) { //한 줄에 있는 단어 수만큼
     out.write(token.nextToken()+" "); //복사하여 쓰기
    }
    out.write("\n"); //줄바꿈 표시
   }
   in.close();  //파일 스트림 닫기
   out.close(); //파일 스트림 닫기
  } catch (Exception e){
   e.printStackTrace();
  }
 }
}
 */
