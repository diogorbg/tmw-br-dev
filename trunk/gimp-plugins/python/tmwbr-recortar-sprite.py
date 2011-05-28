#!/usr/bin/env python

### Recortar Sprite - Diogo_RBG - http://diogorbg.blogspot.com ###
# Copie para "/home/usuario/.gimp-x.x/plug-ins" nomeado como "tmwbr_recortar_sprite.py".
# Nao deixe de dar permicao de execucao e nao use acentos !!!

from gimpfu import *

def recortarSprite(img, layer, horz, vert, op):
	pdb.gimp_context_push()
	img.undo_group_start()

	qw = int(img.width/horz);
	qh = int(img.height/vert);
	op = (op==True)

	for j in range(vert):
		for i in range(horz):
			pdb.gimp_rect_select(img, i*qw, j*qh, qw, qh, CHANNEL_OP_REPLACE,  0, 0.0)
			layer_float = pdb.gimp_selection_float(layer, -i*qw*op, -j*qh*op)
			pdb.gimp_drawable_set_name(layer_float, "quadro."+str( int(i+j*horz) ))

	pdb.gimp_image_remove_layer(img, layer)
	if op:
		pdb.gimp_image_resize_to_layers(img)

	img.undo_group_end()
	pdb.gimp_context_pop()

register(
	"tmwbr-recortar-sprite",
	"Recorta uma imagem em muitas camadas",
	"Recorta uma imagem em muitas camadas",
	"Diogo_RBG - http://diogorbg.blogspot.com",
	"Diogo_RBG",
	"28/05/2011",
	"<Image>/TMW-BR/Recortar Sprite...",
	"*",
	[
		(PF_SPINNER, "horz", "Quadros na horizontal", 2, (1, 1000, 1)),
		(PF_SPINNER, "vert", "Quadros na vertical", 2, (1, 1000, 1)),
		(PF_BOOL, "op", "Alinhar quadros na origem", False)
	],
	[],
	recortarSprite)

main()
