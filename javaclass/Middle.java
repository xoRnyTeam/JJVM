public class Middle {
	public static void main(String[] args) {
		double[] numbers = new double[(int)1000L];
        for(int k = 0; k < numbers.length; k++) {
            numbers[k] = k;
        }

		double average = 0;
        if (numbers.length > 0) {
            double sum = 0;
            for (int j = 0; j < numbers.length; j++) {
                sum += numbers[j];
            }
            average = sum / numbers.length;
            System.out.println(average);
        }
	}
}