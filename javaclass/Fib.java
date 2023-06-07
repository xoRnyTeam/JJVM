package test;
import lang.IO;

public class Fib {
  static int fibonachi(int n) {
    if(n < 2) return n;
    return fibonachi(n - 1) + fibonachi(n - 2);
  }
  public static void main(String[] args) {
		int reply = fibonachi(30);
		IO.print(reply);
	}
}