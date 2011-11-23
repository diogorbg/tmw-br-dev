package parse;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ParserItens {

	private String[] vet;

	public Map<Integer,String> loadItens(String fileName) throws FileNotFoundException, IOException {
		BufferedReader buf = null;
		Map<Integer,String> map = new HashMap<Integer,String>();
		String linha;

		buf = new BufferedReader(new FileReader( new File(fileName) ));
		while ((linha = buf.readLine()) != null) {
			vet = linha.split(",", 2);
			try {
				map.put( Integer.parseInt(vet[0]), vet[1] );
			} catch (NumberFormatException e) {}
		}
		return map;
	}
	
}
