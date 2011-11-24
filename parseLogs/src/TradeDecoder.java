import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import parse.ParserChars;
import parse.ParserItens;
import parse.ParserLog;
import parse.ProcessTrade;
import bean.Char;
import bean.Header;

public class TradeDecoder extends parse.Process implements ProcessTrade {

	private SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
	private static Map<Integer,String> mapItens = null;
	private static Map<Integer,Char> mapChars = null;
	private static Set<Integer> setChars = new LinkedHashSet<Integer>();

	public static void main(String[] args) {
		ParserLog parser = new ParserLog();
		parse.Process decoder = new TradeDecoder();
		try {
			mapItens = ParserItens.loadItens("../db/itens.db");
			mapChars = ParserChars.loadChars("../db/chars.db");
			parser.loadTrade("../trade.log", decoder);
			System.out.println("\n.:: Contas Envolvidas ::.");
			for(Integer obj : setChars) {
				Char chr = mapChars.get( new Integer(obj) );
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

	public boolean processTradePC(Header header, bean.Map map, int zeny) {
		Char chr = mapChars.get( new Integer(header.getIdChr()) );
		String str = String.format("%s - %s[%d](%d), map:%s,%d,%d, zeny:%d", fmt.format(header.getDate()),
				chr.getName(), chr.getLvl(), header.getIdAcc(), map.getMap(), map.getX(), map.getY(), zeny);
		System.out.println(str);
		return true;
	}

	public boolean processTrade(Header header, int chr1, List<String> trade1, int chr2, List<String> trade2) {
		setChars.add( chr1 );
		setChars.add( chr2 );
		Char obj1 = mapChars.get( new Integer(chr1) );
		Char obj2 = mapChars.get( new Integer(chr2) );
		System.out.println("Trade "+obj1.getName()+" >> "+obj2.getName()+" :");
		for(String s : trade1) {
			String[] s2 = s.split(",");
			System.out.println(" * "+s2[1]+" - " + mapItens.get( new Integer(s2[0]) ) + " ("+s2[0]+")");
		}

		System.out.println("Trade "+obj2.getName()+" >> "+obj1.getName()+" :");
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
