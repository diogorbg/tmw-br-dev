package parse;

import bean.Header;
import bean.Map;
import bean.Status;

public interface ProcessMap {

	public boolean processLogin(Header header, Map map, Status status);

	public boolean processLogout(Header header, Map map, Status status);

}
