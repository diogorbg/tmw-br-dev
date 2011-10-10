package bean;

import java.util.Calendar;
import java.util.Date;

/**
 * Classe com informações do cabeçalho da maioria dos arquivos de log.
 * @author diogorbg
 *
 */
public class Header {

	private String cmd;
	private Date date;
	private int idAcc;
	private int idChr;
	private String ip;

	public Header() {
	}

	public Header(String cmd, long timer, int idAcc, int idChr, String ip) {
		Calendar c = Calendar.getInstance();

		this.cmd = cmd;
		c.setTimeInMillis(timer*1000);
		this.date = c.getTime();
		this.idAcc = idAcc;
		this.idChr = idChr;
		this.ip = ip;
	}

	/**
	 * Seta todos os atributos.
	 */
	public void set(String cmd, long timer, int idAcc, int idChr, String ip) {
		Calendar c = Calendar.getInstance();

		this.cmd = cmd;
		c.setTimeInMillis(timer*1000);
		this.date = c.getTime();
		this.idAcc = idAcc;
		this.idChr = idChr;
		this.ip = ip;
	}

	/**
	 * Retorna o comando obtido no log.
	 */
	public String getCmd() {
		return cmd;
	}

	public void setCmd(String cmd) {
		this.cmd = cmd;
	}

	/**
	 * Retorna o data da ocorrência.
	 */
	public Date getDate() {
		return date;
	}

	public void setDate(Date date) {
		this.date = date;
	}

	/**
	 * Retorna o id da conta.
	 */
	public int getIdAcc() {
		return idAcc;
	}

	public void setIdAcc(int idAcc) {
		this.idAcc = idAcc;
	}

	/**
	 * Retorna o id do personagem.
	 */
	public int getIdChr() {
		return idChr;
	}

	public void setIdChr(int idChr) {
		this.idChr = idChr;
	}

	/**
	 * Retorna o ip da conexão.
	 * @return Retorna null, caso ip não fornecido no log.
	 */
	public String getIp() {
		return ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

}
