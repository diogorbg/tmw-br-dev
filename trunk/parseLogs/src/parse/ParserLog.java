package parse;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import bean.Header;
import bean.Map;
import bean.Status;

public class ParserLog {

	private String[] info;

	public void loadMap(String fileName, Process process) throws FileNotFoundException, IOException, Exception {
		BufferedReader buf = null;
		Header header = new Header();
		Map map = new Map();
		Status status = new Status();
		String linha;

		buf = new BufferedReader(new FileReader( new File(fileName) ));
		while ((linha = buf.readLine()) != null) {
			info = linha.split(",");
			header.set(info[0], getInt(1), getInt(2), getInt(3), info[7]);

			if (info[0].equals("login")) {
				if (process instanceof ProcessMap) {
					map.set(info[4], getInt(5), getInt(6));
					status.set(getInt(8), getInt(9), getInt(10));
					if( ((ProcessMap)process).processLogin(header, map, status) == false )
						return;
				} else {
					throw new Exception("Impossível processar função ProcessMap.processLogin()");
				}
			} else if (info[0].equals("logout")) {
				if (process instanceof ProcessMap) {
					map.set(info[4], getInt(5), getInt(6));
					status.set(getInt(8), getInt(9), getInt(10));
					if( ((ProcessMap)process).processLogout(header, map, status) == false )
						return;
				} else {
					throw new Exception("Impossível processar função ProcessMap.processLogout()");
				}
			}
		}
	}

	public void loadTrade(String fileName, Process process) throws FileNotFoundException, IOException, Exception {
		BufferedReader buf = null;
		Header header = new Header();
		Map map = new Map();
		List<String> trade1 = new ArrayList<String>();
		List<String> trade2 = new ArrayList<String>();
		String linha;

		buf = new BufferedReader(new FileReader( new File(fileName) ));
		while ((linha = buf.readLine()) != null) {
			info = linha.split(",");
			if(info.length>3)
				header.set(info[0], getInt(1), getInt(2), getInt(3), null);
			else
				header.set(info[0], 0, 0, 0, null);

			if (info[0].equals("tradePC1") || info[0].equals("tradePC2")) {
				if (process instanceof ProcessTrade) {
					map.set(info[4], getInt(5), getInt(6));
					if( ((ProcessTrade)process).processTradePC(header, map, getInt(7)) == false )
						return;
				} else {
					throw new Exception("Impossível processar função ProcessTrade.processTrade()");
				}
			} else if (info[0].equals("trade")) {
				if (process instanceof ProcessTrade) {
					trade1.clear();
					trade2.clear();
					for(int i=3; i<info.length-1; i++) {
						if(getInt(i+1)>0) {
							trade1.add(info[i]+","+info[i+1]);
						} else {
							trade2.add(info[i]+","+info[i+1]);
						}
						i++;
					}
					if( ((ProcessTrade)process).processTrade(header, getInt(1), trade1, getInt(2), trade2) == false )
						return;
				} else {
					throw new Exception("Impossível processar função ProcessTrade.processTrade()");
				}
			} else if (info[0].equals("tradeOk")) {
				if (process instanceof ProcessTrade) {
					if( ((ProcessTrade)process).processTradeOk(header, getInt(1), getInt(2)) == false )
						return;
				} else {
					throw new Exception("Impossível processar função ProcessTradeOk.processTradeOk()");
				}
			}
		}
	}

	private int getInt(int i) {
		try {
			return Integer.parseInt( info[i] );
		} catch (NumberFormatException e) {
			System.err.println("#Erro ao converter para inteiro. '"+info[i]+"'");
			return -1;
		}
	}

}
