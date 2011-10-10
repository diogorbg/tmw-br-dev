package parse;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

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

	private int getInt(int i) {
		try {
			return Integer.parseInt( info[i] );
		} catch (NumberFormatException e) {
			System.err.println("#Erro ao converter para inteiro. '"+info[i]+"'");
			return -1;
		}
	}

}
