import java.text.SimpleDateFormat;
import java.util.Date;

import parse.ProcessMap;
import bean.Header;
import bean.Map;
import bean.Status;

public class CountUsers extends parse.Process implements ProcessMap {

	private int count = 0;
	private Date date = null;

	private SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm");

	public CountUsers() {
	}

	public boolean processLogin(Header header, Map map, Status status) {

		//if(status.getLvlGm()>0 || status.getLvl() < 70)
		//	return true;
		//if (header.getIdAcc()!=2005693) return true;

		Date d1 = (Date) header.getDate().clone();
		d1.setSeconds(0);
		d1.setMinutes( (d1.getMinutes()/10) * 10 );
		if (date==null) {
			date = (Date) d1.clone();
		} else if (d1.compareTo(date)>0) {
			Date d2 = (Date) date.clone();
			while (d1.compareTo(d2)>0) {
				System.out.println(sdf.format(d2)+ ",qtd " +getCount()+ ",login");
				d2.setTime( d2.getTime()+600000 );
			}
			date = (Date) d1.clone();
		}

		add();

		//System.out.println(sdf.format(header.getDate())+ ", qtd " +getCount()+ ", login, lvl " +status.getLvl()+ ", lvlGM " +status.getLvlGm());
		//System.out.println("* Login do jogador "+header.getIdChr()+" de ip '"+header.getIp()+"' em '"+header.getTimer()+"'");
		return true;
	}

	public boolean processLogout(Header header, Map map, Status status) {
		//if(status.getLvlGm()>0 || status.getLvl() < 70)
		//	return true;
		//if (header.getIdAcc()!=2005693) return true;

		Date d1 = (Date) header.getDate().clone();
		d1.setSeconds(0);
		d1.setMinutes( (d1.getMinutes()/10) * 10 );
		if (date==null) {
			date = (Date) d1.clone();
		} else if (d1.compareTo(date)>0) {
			Date d2 = (Date) date.clone();
			while (d1.compareTo(d2)>0) {
				System.out.println(sdf.format(d2)+ ",qtd " +getCount()+ ",logout");
				d2.setTime( d2.getTime()+600000 );
			}
			date = (Date) d1.clone();
		}

		del();

		//System.out.println(sdf.format(header.getDate())+ ", qtd " +getCount()+ ", logout, lvl " +status.getLvl()+ ", lvlGM " +status.getLvlGm());
		//System.out.println("* Logout do jogador "+header.getIdChr()+" de ip '"+header.getIp()+"' em '"+header.getTimer()+"'");
		return true;
	}

	public void add() {
		count+= 1;
	}

	public void del() {
		if(count>0)
			count-= 1;
	}

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}

}
