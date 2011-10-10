package parse;

public interface ProcessMap extends Process {

	public boolean processLogin(bean.Header header, bean.Map map, bean.Status status);

	public boolean processLogout(bean.Header header, bean.Map map, bean.Status status);

}
