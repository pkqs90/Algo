import java.util.*;
import java.io.*;
import java.math.*;

/*
 * Thanks to Petr providing this template.
 */

public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		
		int T;
		T = in.nextInt();
		for(int kase = 1; kase <= T; kase ++){
			String A = in.next();
			String B = in.next();
			BigInteger a = new BigInteger (A, 2);
			BigInteger b = new BigInteger (B, 2);
			a = a.gcd(b);
			out.println("Case #" + kase + ": " + a.toString(2));
		}
		out.flush();
//		out.close();
	}
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

}