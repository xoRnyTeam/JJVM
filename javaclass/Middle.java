package test;
import lang.IO;

public class Middle {
	public static void main(String[] args) {
        IO.print("Create arr\n");
		int[] numbers = new int[(int)1000L];
        IO.print("Start init\n");
        for(int k = 0; k < numbers.length; k++) {
            numbers[k] = k;
        }
        IO.print("End init\n");

        if (numbers.length > 0) {
            int sum = 0;
            IO.print("If is true\n");
            for (int j = 0; j < numbers.length; j++) {
                IO.print(j);
                IO.print(": ");
                IO.print(numbers[j]);
                IO.print("\n");
                int tmp = numbers[j];
                sum = sum + tmp;
            }
            IO.print("Aver: \n");
            IO.print(sum / numbers.length);
            IO.print("\n");
        }
	}
}