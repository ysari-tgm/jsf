package hello;
import java.io.Serializable;

import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;
import javax.faces.bean.SessionScoped;

@ManagedBean(name = "helloWorld")
@ApplicationScoped
public class HelloWorld implements Serializable{
	private static final long serialVersionUID = 1L;
	private String input = "1.0";
	private String output = "1.0";

	public String getInput() {
		return input;
	}

	public void setInput(String input) {
		this.input = input;
	}

	public String getOutput() {
		return output;
	}

	public void setOutput(String output) {
		this.output = output;
	}

	
	public String ctof() {
		double temp = Double.parseDouble(input)*9/5+32; 
		output = String.valueOf(temp);
		return output;
	}
	public String ctok() {
		double temp = Double.parseDouble(input)+273.15; 
		output = String.valueOf(temp);
		return output;
	}
	public String ktoc() {
		double temp = Double.parseDouble(input)-273.15; 
		output = String.valueOf(temp);
		return output;
	}
	public String ktof() {
		double temp = Double.parseDouble(input)*9/5-459.67; 
		output = String.valueOf(temp);
		return output;
	}
	public String ftoc() {
		double temp = (Double.parseDouble(input)-32)*5/9; 
		output = String.valueOf(temp);
		return output;
	}
	public String ftok() {
		double temp = (Double.parseDouble(input)+459.67)*5/9;
		output = String.valueOf(temp);
		return output;
	}
}
