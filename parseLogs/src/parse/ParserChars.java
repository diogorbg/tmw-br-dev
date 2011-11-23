package parse;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import bean.Char;

public class ParserChars {

	private String[] vet;

	Map<Integer,Char> loadChars(String fileName) throws FileNotFoundException, IOException {
		BufferedReader buf = null;
		Map<Integer,Char> map = new HashMap<Integer,Char>();
		Char chr = null;
		String linha;

		buf = new BufferedReader(new FileReader( new File(fileName) ));
		while ((linha = buf.readLine()) != null) {
			vet = linha.split("\\t", 4);
			try {
				int lvl = Integer.parseInt( vet[3].split(",")[1] );
				int zeny = Integer.parseInt( vet[4].split(",")[2] );
				chr = new Char( getInt(0), vet[2], lvl, zeny );
				map.put( getInt(0), chr );
			} catch (NumberFormatException e) {}
		}
		return map;
	}
	
	private int getInt(int i) {
		try {
			return Integer.parseInt( vet[i] );
		} catch (NumberFormatException e) {
			System.err.println("#Erro ao converter para inteiro. '"+vet[i]+"'");
			return -1;
		}
	}

}
