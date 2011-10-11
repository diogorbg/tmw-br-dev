import java.text.SimpleDateFormat;
import java.util.Date;

import parse.ProcessMap;
import bean.Header;
import bean.Map;
import bean.Status;

public class CountUsers extends parse.Process implements ProcessMap {

	private static int TEMPO = 30;
	private int count=0, max=0;
	private int nLogin=0, nLogout=0;
	private Date date = null;

	private String title = "";
	private String[] tab = new String[24*60/TEMPO];

	private SimpleDateFormat fmt1 = new SimpleDateFormat("dd/MM/yyyy");
	private SimpleDateFormat fmt2 = new SimpleDateFormat("HH:mm");

	public CountUsers() {
	}

	public void print() {
		System.out.println(title);
		for (int i=0; i<tab.length; i++) {
			System.out.println(tab[i]);
		}
	}

	@SuppressWarnings("deprecation")
	public boolean processLogin(Header header, Map map, Status status) {

		//if(status.getLvlGm()>0 || status.getLvl() < 70)
		//	return true;

		add();

		Date d1 = (Date) header.getDate().clone();
		d1.setSeconds(0);
		d1.setMinutes( (d1.getMinutes()/TEMPO) * TEMPO );
		if (date==null) {
			date = (Date) d1.clone();
			date.setMinutes(0);
			date.setHours(0);
		}
		if (d1.compareTo(date)>0) {
			Date d2 = (Date) date.clone();
			while (d1.compareTo(d2)>0) {
				addTab(d2);
				d2.setTime( d2.getTime()+(TEMPO*60000) );
			}
			date = (Date) d1.clone();
			zerar();
		}

		//System.out.println(sdf.format(header.getDate())+ ", qtd " +getCount()+ ", login, lvl " +status.getLvl()+ ", lvlGM " +status.getLvlGm());
		//System.out.println("* Login do jogador "+header.getIdChr()+" de ip '"+header.getIp()+"' em '"+header.getTimer()+"'");
		return true;
	}

	@SuppressWarnings("deprecation")
	public boolean processLogout(Header header, Map map, Status status) {
		//if(status.getLvlGm()>0 || status.getLvl() < 70)
		//	return true;

		del();

		Date d1 = (Date) header.getDate().clone();
		d1.setSeconds(0);
		d1.setMinutes( (d1.getMinutes()/TEMPO) * TEMPO );
		if (date==null) {
			date = (Date) d1.clone();
			date.setMinutes(0);
			date.setHours(0);
		}
		if (d1.compareTo(date)>0) {
			Date d2 = (Date) date.clone();
			while (d1.compareTo(d2)>0) {
				addTab(d2);
				d2.setTime( d2.getTime()+(TEMPO*60000) );
			}
			date = (Date) d1.clone();
			zerar();
		}

		//System.out.println(sdf.format(header.getDate())+ ", qtd " +getCount()+ ", logout, lvl " +status.getLvl()+ ", lvlGM " +status.getLvlGm());
		//System.out.println("* Logout do jogador "+header.getIdChr()+" de ip '"+header.getIp()+"' em '"+header.getTimer()+"'");
		return true;
	}

	@SuppressWarnings("deprecation")
	private void addTab(Date d2) {
		String key = fmt2.format(d2);
		if(key.equals("00:00")) {
			if(title.length()==0)
				title = "hora";
			title += (","+fmt1.format(d2));
		}
		int i = d2.getHours()*60/TEMPO +  d2.getMinutes()/TEMPO;
		if(tab[i]==null) {
			tab[i] = ""+key;
		}
		tab[i] += ","+max();
	}

	public void add() {
		nLogin++;
		count += 1;
		if(count>max)
			max = count;
	}

	public void del() {
		if(nLogout==nLogin)
			return;
		nLogout++;
		count -= 1;
	}

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}

	public int max() {
		return max>count ? max : count;
	}

	public int zerar() {
		return max = count;
	}

}
