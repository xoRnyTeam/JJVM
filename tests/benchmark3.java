public class Benchmark {
  public static void dump(Foo[] foo, int M) {
    for (int i = 0; i < M; i++) {
      Foo f = foo[i];

      if (f == null) {
        System.out.println("Foo:null");
      } else {
        Bar b = f.getY();
        if (b == null) {
          System.out.println("Foo.Bar:null");
        } else {
          System.out.println(b.a);
        }
      }
    }
  }

  public static void foo(int N, int M) {
    Foo[] foo = new Foo[M];
    Foo outer = null;

    for (int i = 1; i <= N; i++) {
      Foo o1 = new Foo(i);

      if (i % 3 == 0) {
        foo[(i - 1) % M] = o1;
      }

      Bar o2 = new Bar(i);

      if (i % 5 == 0) {
        o1.setY(o2);
      }

      outer = o1;
    }

    dump(foo, M);
  }

  public static void main(String[] args) {
    int N = 4000000;
    int M = 1000;
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