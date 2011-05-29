#!/usr/bin/env python

### Alinhar Camadas - Diogo_RBG - http://diogorbg.blogspot.com ###
# Copie para "/home/usuario/.gimp-x.x/plug-ins" nomeado como "tmwbr-alinhar-camadas.py".
# Nao deixe de dar permicao de execucao e nao use acentos !!!

from gimpfu import *

def alinharCamadas(img, layer, horz, op, op1, op2):
	img.undo_group_start()

	i = 0
	j = 0
	cont = len(img.layers)

	if op==True:
		w = img.width
		h = img.height

	elif op2==False:
		w = 0
		h = 0
		for id in range(cont):
			layer = img.layers[cont-1-id]
			if layer.width > w:
				w = layer.width
			if layer.height > h:
				h = layer.height

	if op1==True:
		for id in range(cont):
			layer = img.layers[cont-1-id]
			pdb.gimp_drawable_set_name( layer, "a#"+str(id) )

	for id in range(cont):
		layer = img.layers[cont-1-id]
		if op==True:
			pdb.gimp_layer_resize_to_image_size(layer)
		if op1==True:
			pdb.gimp_drawable_set_name( layer, str(id) )
		if op2==True:
			layer.set_offsets(0, 0)
		else:
			layer.set_offsets( i*w, j*h)
		i = i+1
		if i==horz:
			i = 0
			j = j+1

	pdb.gimp_image_resize_to_layers(img)
	img.undo_group_end()

register(
	"tmwbr-alinhar-camadas",
	"Alinhar e numerar camadas",
	"Alinhar e numerar camadas",
	"Diogo_RBG - http://diogorbg.blogspot.com",
	"Diogo_RBG",
	"23/01/2008",
	"<Image>/TMW-BR/Alinhar Camadas...",
	"*",
	[
		(PF_SPINNER, "horz", "Quadros na horizontal", 2, (1, 1000, 1)),
		(PF_BOOL, "op", "Redimencionar camada", False),
		(PF_BOOL, "op1", "Numerar camada", False),
		(PF_BOOL, "op2", "Alinhar na origem", False)
	],
	[],
	alinharCamadas)

main()
