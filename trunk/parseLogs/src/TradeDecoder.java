import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Map;
import java.util.List;

import parse.ParserChars;
import parse.ParserItens;
import parse.ParserLog;
import parse.ProcessTrade;
import bean.Header;

public class TradeDecoder extends parse.Process implements ProcessTrade {

	private SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
	private static Map<Integer,String> mapItens = null;

	public static void main(String[] args) {
		ParserLog parser = new ParserLog();
		ParserItens parserItens = new ParserItens();
		ParserChars parserChars = new ParserChars();
		parse.Process decoder = new TradeDecoder();
		try {
			mapItens = parserItens.loadItens("../db/itens.db");
			parser.loadTrade("/home/diogorbg/workspace2/parseLogs/trade.log", decoder);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public boolean processTradePC(Header header, bean.Map map, int zeny) {
		String str = String.format("%s,%s,%d,%d, map:%s,%d,%d, zeny:%d", header.getCmd(), fmt.format(header.getDate()), header.getIdAcc(),
				header.getIdChr(), map.getMap(), map.getX(), map.getY(), zeny);
		System.out.println(str);
		return true;
	}

	public boolean processTrade(Header header, int chr1, List<String> trade1, int chr2, List<String> trade2) {
		System.out.println("Trade "+chr1+" >> "+chr2+" :");
		for(String s : trade1) {
			String[] s2 = s.split(",");
			System.out.println(" * "+s2[1]+" - " + mapItens.get( new Integer(s2[0]) ) + " ("+s2[0]+")");
		}

		System.out.println("Trade "+chr2+" >> "+chr1+" :");
		for(String s : trade2) {
			String[] s2 = s.split(",");
			System.out.println(" * "+s2[1]+" - " + mapItens.get( new Integer(s2[0]) ) + " ("+s2[0]+")");
		}
		return true;
	}

	public boolean processTradeOk(Header header, int chr1, int chr2) {
		System.out.println("---");
		return true;
	}

}
