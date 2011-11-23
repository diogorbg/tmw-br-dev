package bean;

public class Char {

	private int id;
	private String nome;
	private int lvl;
	private int zeny;

	public Char() {
	}

	public Char(int id, String nome, int lvl, int zeny) {
		set(id, nome, lvl, zeny);
	}

	public void set(int id, String nome, int lvl, int zeny) {
		this.id = id;
		this.nome = nome;
		this.lvl = lvl;
		this.zeny = zeny;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
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
