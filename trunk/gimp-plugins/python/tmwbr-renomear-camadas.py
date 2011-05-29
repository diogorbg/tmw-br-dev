#!/usr/bin/env python

### Renomear Camadas - Diogo_RBG - http://diogorbg.blogspot.com ###
# Copie para "/home/usuario/.gimp-x.x/plug-ins" nomeado como "tmwbr-renomear-camadas.py".
# Nao deixe de dar permicao de execucao e nao use acentos !!!

from gimpfu import *

def renomearCamadas(img, layer, prf, num, sfx, op):
	img.undo_group_start()

	i = 0
	j = 0
	cont = len(img.layers)

	for id in range(cont):
		layer = img.layers[cont-1-id]
		pdb.gimp_drawable_set_name( layer, "a#"+str(id) )

	for id in range(cont):
		layer = img.layers[cont-1-id]
		if op==True:
			pdb.gimp_drawable_set_name( layer, prf+str( int(cont-1-id+num) )+sfx )
		else:
			pdb.gimp_drawable_set_name( layer, prf+str( int(id+num) )+sfx )

	img.undo_group_end()

register(
	"tmwbr-renomear-camadas",
	"Numerar e renomear camadas",
	"Numerar e renomear camadas",
	"Diogo_RBG - http://diogorbg.blogspot.com",
	"Diogo_RBG",
	"23/01/2008",
	"<Image>/TMW-BR/Renomear Camadas...",
	"*",
	[
		(PF_STRING, "prf", "Prefixo", "quadro."),
		(PF_SPINNER, "num", "Numero inicial", 0, (-1000, 1000, 1)),
		(PF_STRING, "sfx", "Sufixo", " (75ms) (replace)"),
		(PF_BOOL, "op", "Contagem invertida", False)
	],
	[],
	renomearCamadas)

main()
