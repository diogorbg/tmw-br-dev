import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.SimpleDateFormat;

import bean.Header;
import bean.Map;
import bean.Status;
import parse.ParserLog;
import parse.ProcessMap;


public class MapDecoder extends parse.Process implements ProcessMap {

	private SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");

	public static void main(String[] args) {
		ParserLog parser = new ParserLog();
		parse.Process decoder = new MapDecoder();
		try {
			parser.loadMap("/home/diogorbg/workspace2/parseLogs/map.log", decoder);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public boolean processLogin(Header header, Map map, Status status) {
		String str = String.format("%s,%s,%d,%d, ip:%s, map:%s,%d,%d, lvl:%d,%d, gm:%d", header.getCmd(), fmt.format(header.getDate()), header.getIdAcc(),
				header.getIdChr(), header.getIp(), map.getMap(), map.getX(), map.getY(), status.getLvl(), status.getXp(), status.getLvlGm());
		System.out.println(str);
		return true;
	}

	public boolean processLogout(Header header, Map map, Status status) {
		String str = String.format("%s,%s,%d,%d, ip:%s, map:%s,%d,%d, lvl:%d,%d, gm:%d", header.getCmd(), fmt.format(header.getDate()), header.getIdAcc(),
				header.getIdChr(), header.getIp(), map.getMap(), map.getX(), map.getY(), status.getLvl(), status.getXp(), status.getLvlGm());
		System.out.println(str);
		return true;
	}

}
