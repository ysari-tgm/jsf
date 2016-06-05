package login;

import java.io.IOException;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;

@ManagedBean
@SessionScoped
public class LoginBean {
	public static final String AUTH_KEY = "app.user.name";

	private String convert1;
	private String convert2;

	public String getConvert1() {
		return convert1;
	}

	public void setConvert1(String convert1) {
		this.convert1 = convert1;
	}

	public String getConvert2() {
		return convert2;
	}

	public void setConvert2(String convert2) {
		this.convert2 = convert2;
	}

	public void validation() throws IOException {
		if (password.equals(superSecret) && username.equals(bestUser)) {
			setAuthenticated(true);
			FacesContext.getCurrentInstance().getExternalContext().getSessionMap().put(AUTH_KEY, username);
			FacesContext.getCurrentInstance().getExternalContext().redirect("app/welcome.xhtml");
		} else {
			setAuthenticated(false);
			FacesContext.getCurrentInstance().addMessage(null, new FacesMessage(FacesMessage.SEVERITY_WARN,
					"Wrong Credentials", "Username or Password are incorrect"));
		}
	}

	public void logout() throws IOException {
		setAuthenticated(false);
		FacesContext.getCurrentInstance().getExternalContext().getSessionMap().remove(AUTH_KEY);
		FacesContext.getCurrentInstance().getExternalContext().redirect("info.xhtml");
	}
}
