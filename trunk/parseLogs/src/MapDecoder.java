import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

import bean.Char;
import bean.Header;
import bean.Status;
import parse.ParserChars;
import parse.ParserLog;
import parse.ProcessMap;

public class MapDecoder extends parse.Process implements ProcessMap {

	private SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
	private static Map<Integer,Char> mapChars = null;
	private static Set<Integer> setChars = new LinkedHashSet<Integer>();

	public static void main(String[] args) {
		ParserLog parser = new ParserLog();
		parse.Process decoder = new MapDecoder();
		try {
			mapChars = ParserChars.loadChars("../db/chars.db");
			parser.loadMap("../map.log", decoder);
			System.out.println("\n.:: Contas Envolvidas ::.");
			for(Integer obj : setChars) {
				Char chr = mapChars.get( new Integer(obj) );
				if (chr==null)
					chr = new Char(obj, 0, "<nome?>", 0, 0);
				System.out.println(chr.getName()+"["+chr.getLvl()+"]("+chr.getIdAcc()+")");
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public boolean processLogin(Header header, bean.Map map, Status status) {
		setChars.add( header.getIdChr() );
		Char chr = mapChars.get( new Integer(header.getIdChr()) );
		if (chr==null)
			chr = new Char(header.getIdChr(), 0, "<nome?>", 0, 0);
		String str = String.format("%s,%s,%d,%s[%d](%d), ip:%s, map:%s,%d,%d, lvl:%d,%d, gm:%d", header.getCmd(), fmt.format(header.getDate()), header.getIdAcc(),
				chr.getName(),chr.getLvl(),header.getIdChr(), header.getIp(), map.getMap(), map.getX(), map.getY(), status.getLvl(), status.getXp(), status.getLvlGm());
		System.out.println(str);
		return true;
	}

	public boolean processLogout(Header header, bean.Map map, Status status) {
		String str = String.format("%s,%s,%d,%d, ip:%s, map:%s,%d,%d, lvl:%d,%d, gm:%d", header.getCmd(), fmt.format(header.getDate()), header.getIdAcc(),
				header.getIdChr(), header.getIp(), map.getMap(), map.getX(), map.getY(), status.getLvl(), status.getXp(), status.getLvlGm());
		System.out.println(str);
		return true;
	}

}
