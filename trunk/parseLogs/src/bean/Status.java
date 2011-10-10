package bean;

public class Status {

	private int lvl;
	private int xp;
	private int lvlGm;

	public Status() {
	}

	public Status(int lvl, int xp, int lvlGm) {
		this.lvl = lvl;
		this.xp = xp;
		this.lvlGm = lvlGm;
	}

	public int getLvl() {
		return lvl;
	}

	public void setLvl(int lvl) {
		this.lvl = lvl;
	}

	public int getXp() {
		return xp;
	}

	public void setXp(int xp) {
		this.xp = xp;
	}

	public int getLvlGm() {
		return lvlGm;
	}

	public void setLvlGm(int lvlGm) {
		this.lvlGm = lvlGm;
	}

}
