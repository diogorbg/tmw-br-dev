package parse;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class ParserItens {

	private String[] info;

	void loadItens(String fileName) throws FileNotFoundException, IOException {
		BufferedReader buf = null;
		String linha;

		buf = new BufferedReader(new FileReader( new File(fileName) ));
		while ((linha = buf.readLine()) != null) {
			info = linha.split(",");

			if (info[0].equals("login")) {
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
