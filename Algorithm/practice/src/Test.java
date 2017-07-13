/**
 * Created by jikhan.woo on 2017-07-12.
 */

class t1
{
    int a;
    int b;
    void setA(int a) {this.a = a; System.out.println("setA");}
    void setB(int b) {this.b = b; System.out.println("setB");}
};

class t2
{
    t1 t;
    t2()
    {
        this.t = null;
        System.out.println("null t2 called");
    }
    t2(t1 t)
    {
        this.t = t;
        System.out.println("t1 t2 called");
    }
}
public class Test
{
    public static void main(String[] args)
    {
        t1 test1 = new t1();
        t2 test2 = new t2();
        test2.t = new t1();
        test2.t.setA(1);
        test2.t.setB(2);
        t2 test3 = new t2(test1);
        test3.t.setA(1);
        test3.t.setB(2);
    }
}
