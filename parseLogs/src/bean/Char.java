package bean;

public class Char {

	private int id;
	private int idAcc;
	private String name;
	private int lvl;
	private int zeny;

	public Char() {
	}

	public Char(int id, int idAcc, String name, int lvl, int zeny) {
		set(id, idAcc, name, lvl, zeny);
	}

	public void set(int id, int idAcc, String name, int lvl, int zeny) {
		this.id = id;
		this.idAcc = idAcc;
		this.name = name;
		this.lvl = lvl;
		this.zeny = zeny;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getIdAcc() {
		return idAcc;
	}

	public void setIdAcc(int idAcc) {
		this.idAcc = idAcc;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getLvl() {
		return lvl;
	}

	public void setLvl(int lvl) {
		this.lvl = lvl;
	}

	public int getZeny() {
		return zeny;
	}

	public void setZeny(int zeny) {
		this.zeny = zeny;
	}

}
