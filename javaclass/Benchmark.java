package bench;
import lang.IO;
public class Benchmark {

  public static void foo(int N, int M) {
    IO.print("Hello foo!\n");
    Foo[] foo = new Foo[N];
    IO.print("Hello created foo!\n");
    Foo outer;

    for (int i = 1; i <= M; i++) {
      Foo o1 = new Foo(i);

      if (i % 3 == 0) {
        foo[i % N] = o1;
      }

      Bar o2 = new Bar(i);

      if (i % 5 == 0) {
        o1.setY(o2);
      }

      outer = o1;
    }

    IO.print("Hello start dump!\n");
    // dump 
    for (int i = 0; i < N; i++) {
      // Foo f = foo[i];

      if (foo[i] == null) {
        IO.print("Foo:null\n");
      } else {
        if (foo[i].getY() == null) {
          IO.print("Foo.Bar:null\n");
        } else {
          IO.print(foo[i].getY().a);
          IO.print("\n");
        }
      }
    }

    IO.print("Hello!\n");
  }

  public static void main(String[] args) {
    int N = 10;
    int M = 10;
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