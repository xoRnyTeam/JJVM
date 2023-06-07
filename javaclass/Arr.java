package bench;
import lang.IO;
public class Arr {
  public static void main(String[] args) {
    int N = 2;
    Foo[] foo = new Foo[N];

    foo[0] = new Foo(1);
    foo[1] = new Foo(2);
    IO.print("foo:\n");
    IO.print(foo[1].x);
  }
}

class Foo {
  public int x;
  private Bar y;

  public Foo(int x) {
    this.x = x;
    this.y = null;
  }

  public Bar getY() { return this.y; }

  public void setY(Bar b) { this.y = b; }
}