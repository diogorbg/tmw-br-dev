package bean;

public class Map {

	private String map;
	private int x = -1;
	private int y = -1;

	public Map() {
	}

	public Map(String map, int x, int y) {
		this.map = map;
		this.x = x;
		this.y = y;
	}

	public String getMap() {
		return map;
	}

	public void setMap(String map) {
		this.map = map;
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

}
