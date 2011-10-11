import java.io.FileNotFoundException;
import java.io.IOException;

import parse.ParserLog;

public class ParserLogs {

	public static void main(String[] args) {
		ParserLog parser = new ParserLog();
		CountUsers users = new CountUsers();
		try {
			parser.loadMap("/home/diogorbg/workspace/parseLogs/map.log", users);
			users.print();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
