BEGIN TRANSACTION;

INSERT INTO "jogador" VALUES(1,20020,500,'diogorbg','Diogo_RBG',1);
INSERT INTO "jogador" VALUES(2,20040,510,'mg_acc','MisterG',1);
INSERT INTO "jogador" VALUES(3,20030,505,'pix_acc','pix',1);
INSERT INTO "jogador" VALUES(4,20050,515,'a','aaa',1);
INSERT INTO "jogador" VALUES(5,20060,520,'b','bbb',1);

INSERT INTO "cargoHistorico" VALUES(1,1,'adm',1000100,0,0);
INSERT INTO "cargoHistorico" VALUES(2,1,'dev',1000101,0,0);
INSERT INTO "cargoHistorico" VALUES(3,2,'gm',1000200,0,0);
INSERT INTO "cargoHistorico" VALUES(4,3,'dev',1000300,1000500,0);
INSERT INTO "cargoHistorico" VALUES(5,4,'gm',1000400,1000500,1000500);
INSERT INTO "cargoHistorico" VALUES(6,4,'gm',1000600,1000700,0);

INSERT INTO "comandoHistorico" VALUES(1,1,1,1000100,'@cargo adm diogo_rbg');
INSERT INTO "comandoHistorico" VALUES(2,1,2,1000101,'@cargo dev diogo_rbg');
INSERT INTO "comandoHistorico" VALUES(3,1,1,1000150,'@vigencia adm diogo_rbg 0');
INSERT INTO "comandoHistorico" VALUES(4,1,2,1000151,'@vigencia dev diogo_rbg 0');
INSERT INTO "comandoHistorico" VALUES(5,1,3,1000200,'@cargo gm misterg');
INSERT INTO "comandoHistorico" VALUES(6,1,3,1000250,'@vigencia misterg 0');
INSERT INTO "comandoHistorico" VALUES(7,1,4,1000300,'@cargo dev pix');
INSERT INTO "comandoHistorico" VALUES(8,1,5,1000400,'@cargo gm aaa');
INSERT INTO "comandoHistorico" VALUES(9,1,5,1000600,'@cargo gm aaa');

COMMIT;
