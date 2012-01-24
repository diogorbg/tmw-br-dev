--
-- admin.sqlite3
-- Arquivo de assuntos administrativos.
--

--
-- Dados de jogador --
--
CREATE TABLE "jogador" (
	"jog_id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	"jog_idConta" INTEGER NOT NULL,
	"jog_idChar" INTEGER NOT NULL,
	"jog_nomeConta" TEXT NOT NULL,
	"jog_nomeChar" TEXT NOT NULL,
	-- 0:inativo 1:ativo --
	"jog_status" INTEGER NOT NULL DEFAULT (1)
);
-- impede duplicar jogador --
CREATE UNIQUE INDEX "jog_unico" on jogador (jog_idConta ASC, jog_idChar ASC);

--
-- Cargos vinculados ao membro da cúpula --
-- É mantido um histórico de cargos exercidos --
--
CREATE TABLE "cargoHistorico" (
	"car_id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	"car_jog_id" INTEGER NOT NULL,
	-- adm, gm, dev, pub --
	"car_cargo" VARCHAR(3) NOT NULL,
	-- Data em que foi aceito no cargo --
	"car_dataInicio" INTEGER NOT NULL,
	-- Entenda como vigência até a dataVigencia. 0:sem_limite_estabelecido --
	"car_dataVigencia" INTEGER NULL DEFAULT (0),
	-- Quando deixou de exercer o cargo. --
	"car_dataFim" INTEGER NULL DEFAULT (0),
	-- Chave estrangeira parece não funcionar. Mas de qualquer forma... --
	FOREIGN KEY (car_jog_id) REFERENCES jogador(jog_id) ON DELETE RESTRICT
);
-- impede inserir cargo igual sem encerrar anterior --
CREATE UNIQUE INDEX "car_unico" on cargoHistorico (car_jog_id ASC, car_cargo ASC, car_dataFim ASC);

--
-- Comandos executados para assuntos administrativos --
--
CREATE TABLE "comandoHistorico" (
	"cmd_id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	"cmd_jog_id" INTEGER NOT NULL,
	"cmd_car_id" INTEGER NOT NULL,
	"cmd_data" INTEGER NOT NULL,
	"cmd_cmd" TEXT NOT NULL,
	-- Chave estrangeira parece não funcionar. Mas de qualquer forma... --
	FOREIGN KEY (cmd_jog_id) REFERENCES jogador(jog_id) ON DELETE RESTRICT,
	FOREIGN KEY (cmd_car_id) REFERENCES cargoHistorico(car_id) ON DELETE RESTRICT
);

--
-- Cargos ativos ocupados por jogadores ativos --
--
CREATE VIEW "view_jogadorCargo" AS SELECT jog_id, jog_idConta, jog_idChar, jog_nomeConta,
	jog_nomeChar, car_cargo, car_dataInicio, car_dataVigencia
FROM jogador
INNER JOIN cargoHistorico ON car_jog_id = jog_id
WHERE jog_status=1 AND car_dataFim=0;
