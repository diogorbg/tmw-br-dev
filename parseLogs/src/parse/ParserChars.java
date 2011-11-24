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

	public static Map<Integer,Char> loadChars(String fileName) throws FileNotFoundException, IOException {
		String[] vet;
		BufferedReader buf = null;
		Map<Integer,Char> map = new HashMap<Integer,Char>();
		Char chr = null;
		String linha;

		buf = new BufferedReader(new FileReader( new File(fileName) ));
		while ((linha = buf.readLine()) != null) {
			vet = linha.split("\\t", 5);
			try {
				int idAcc = Integer.parseInt( vet[1].split(",")[0] );
				int lvl = Integer.parseInt( vet[3].split(",")[1] );
				int zeny = Integer.parseInt( vet[4].split(",")[2] );
				chr = new Char( getInt(vet[0]), idAcc, vet[2], lvl, zeny );
				map.put( getInt(vet[0]), chr );
			} catch (NumberFormatException e) {}
		}
		return map;
	}
	
	private static int getInt(String str) {
		try {
			return Integer.parseInt( str );
		} catch (NumberFormatException e) {
			System.err.println("#Erro ao converter para inteiro. '"+str+"'");
			return -1;
		}
	}

}
