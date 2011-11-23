package parse;

import java.util.List;

import bean.Header;
import bean.Map;

public interface ProcessTrade {

	public boolean processTradePC(Header header, Map map, int zeny);

	public boolean processTrade(Header header, int chr1, List<String> trade1, int chr2, List<String> trade2);

	public boolean processTradeOk(Header header, int chr1, int chr2);

}
