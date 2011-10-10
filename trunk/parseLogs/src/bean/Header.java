package bean;

/**
 * Classe com informações do cabeçalho da maioria dos arquivos de log.
 * @author diogorbg
 *
 */
public class Header {

	private String cmd;
	private int timer;
	private int idAcc;
	private int idChr;
	private String ip;

	public Header() {
	}

	public Header(String cmd, int timer, int idAcc, int idChr, String ip) {
		this.cmd = cmd;
		this.timer = timer;
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
	 * Retorna o tempo da ocorrência.
	 */
	public int getTimer() {
		return timer;
	}

	public void setTimer(int timer) {
		this.timer = timer;
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
