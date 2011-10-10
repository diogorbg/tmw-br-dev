import bean.Header;
import bean.Map;
import bean.Status;
import parse.ProcessMap;

public class Teste implements ProcessMap {

	@Override
	public boolean processLogin(Header header, Map map, Status status) {
		System.out.printf("* Login do jogador %d de ip '%s' em '%d'", header.getIdChr(), header.getIp(), header.getTimer());
		return true;
	}

	@Override
	public boolean processLogout(Header header, Map map, Status status) {
		System.out.printf("* Logout do jogador %d de ip '%s' em '%d'", header.getIdChr(), header.getIp(), header.getTimer());
		return true;
	}

}
