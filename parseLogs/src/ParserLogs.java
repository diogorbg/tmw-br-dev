import java.io.FileNotFoundException;
import java.io.IOException;

import parse.ParserLog;
import parse.Process;

public class ParserLogs {

	public static void main(String[] args) {
		ParserLog parser = new ParserLog();
		Process users = new CountUsers();
		try {
			parser.loadMap("/home/diogorbg/workspace2/parseLogs/map.log", users);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
