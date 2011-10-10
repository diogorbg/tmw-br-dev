import java.text.SimpleDateFormat;

import parse.ProcessMap;
import bean.Header;
import bean.Map;
import bean.Status;

public class CountUsers extends parse.Process implements ProcessMap {

	private int count;
	private SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm");  

	public CountUsers() {
	}

	public boolean processLogin(Header header, Map map, Status status) {
		add();
		System.out.println(sdf.format(header.getDate())+ "," +getCount()+ ",add");
		//System.out.println("* Login do jogador "+header.getIdChr()+" de ip '"+header.getIp()+"' em '"+header.getTimer()+"'");
		return true;
	}

	public boolean processLogout(Header header, Map map, Status status) {
		del();
		System.out.println(sdf.format(header.getDate())+ "," +getCount()+ ",del");
		//System.out.println("* Logout do jogador "+header.getIdChr()+" de ip '"+header.getIp()+"' em '"+header.getTimer()+"'");
		return true;
	}

	public void add() {
		count+= 1;
	}

	public void del() {
		count-= 1;
	}

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}

}
