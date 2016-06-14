package servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class MyServlet
 */

public class MyServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, 
                HttpServletResponse response)
     */
    protected void doGet(HttpServletRequest request, 
                HttpServletResponse response)
        throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        String output=
        "<html><body><h1>Welcome!</h1>";

       Date c = new Date();
       SimpleDateFormat fmt = new SimpleDateFormat("dd.MM.yyyy");
       SimpleDateFormat t = new SimpleDateFormat("HH:mm");
       String dateFormatted = fmt.format(c);
       String timeFormatted = t.format(c);
       output+="<h3>Today is the "+dateFormatted+ "</h3>";
       output+="Now it's "+timeFormatted+"<br/>";

       int hour=Integer.parseInt(timeFormatted.substring(0, 2));
       if(hour<11)
    	   output+="Good morning!";
       else if(hour<13)
    	   output+="Happy lunch!";
       else if(hour<18)
    	   output+="Nice afternoon!";
       else
    	   output+="Good Night!";
       output+="</body></html>";
       out.println(output);
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, 
                HttpServletResponse response)
     */
    protected void doPost(HttpServletRequest request, 
                HttpServletResponse response)
        throws ServletException, IOException {
        // TODO Auto-generated method stub
    }

}
