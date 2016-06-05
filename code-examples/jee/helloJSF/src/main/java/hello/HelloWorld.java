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
	private String firstName = "Vorname";
	private String lastName = "Nachname";

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getGreeting() {
		return "Hello" + " " + firstName + " " + lastName + "!";
	}
}
