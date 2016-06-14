package configuration;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Properties;

public class Information {

	public static void main(String args[]) {
		Properties defaultProps = new Properties();
		try {
			FileInputStream in = new FileInputStream("defaultProperties");
			defaultProps.load(in);
			in.close();

			// create application properties with default
			Properties applicationProps = new Properties(defaultProps);

			for (String s : applicationProps.stringPropertyNames()) {
				System.out.println("Key: " + s + ", Value: " + applicationProps.getProperty(s));
			}

			// now save properties from last invocation
			FileOutputStream out = new FileOutputStream("appProperties");
			defaultProps.store(out, "---Very important Comments---");
			out.close();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
