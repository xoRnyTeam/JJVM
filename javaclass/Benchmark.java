package bench;
import lang.IO;
public class Benchmark {

  public static void foo(int N, int M) {
    Foo[] foo = new Foo[M];
    Foo outer;

    for (int i = 1; i <= N; i++) {
      Foo o1 = new Foo(i);

      if (i % 3 == 0) {
        foo[i % M] = o1;
      }

      Bar o2 = new Bar(i);

      if (i % 5 == 0) {
        o1.setY(o2);
      }

      outer = o1;
    }

    // dump 
    for (int i = 0; i < M; i++) {
      Foo f = foo[i];

      if (f == null) {
        IO.print("Foo:null\n");
      } else {
        if (f.getY() == null) {
          IO.print("Foo.Bar:null\n");
        } else {
          IO.print(" " + f.getY().a + "\n");
        }
      }
    }

    IO.print("Hello!\n");
  }

  public static void main(String[] args) {
    int N = 40000;
    int M = 1000;
    IO.print("Hello!\n");
    foo(N, M);
  }
}

class Bar {
  public int a;
  public Bar(int a) { this.a = a; }
}

class Foo {
  private int x;
  private Bar y;

  public Foo(int x) {
    this.x = x;
    this.y = null;
  }

  public Bar getY() { return this.y; }

  public void setY(Bar b) { this.y = b; }
}