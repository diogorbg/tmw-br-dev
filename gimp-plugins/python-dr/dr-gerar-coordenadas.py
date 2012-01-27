#!/usr/bin/env python

### Gerar Coordenadas - Diogo_RBG - http://diogorbg.blogspot.com ###
# Copie para "/home/usuario/.gimp-x.x/plug-ins" nomeado como "dr-gerar-coordenadas.py".
# Nao deixe de dar permicao de execucao e nao use acentos !!!

from gimpfu import *
from array import array
import os

def gerarCoordenadas(img, layer, impr, op1, op2, filename, editor): # horz, vert,
	pdb.gimp_image_undo_group_start(img)
	bg = gimp.get_background()
	gimp.set_background(255, 255, 255)

	#horz = int(horz)
	#vert = int(vert)
	impr = int(impr)
	if len(filename)<1 : filename = "_src.txt"
	filename = '%s'%pdb.gimp_image_get_filename(img)+filename
	tmp = open(filename, 'w')

	#jump = 0
	cont = len(img.layers)
	for id in range(cont):
		layer = img.layers[cont-1-id]
		if layer.visible==False : continue

		col = 0
		tmp.write("int "+layer.name+"[][4] = {")
		fuzzy = gimp.Layer(img, layer.name+"#fuzzy", layer.width, layer.height, layer.type, 50, NORMAL_MODE)
		img.add_layer(fuzzy, cont-1-id)
		for y in range(0, layer.height/impr):
			y = y*impr
			for x in range(0, layer.width/impr):
				x = x*impr
				pix = pdb.gimp_image_pick_color(img, fuzzy, x, y, False, False, 0)
				if pix[0]>0.0 : continue
				pix = pdb.gimp_image_pick_color(img, layer, x, y, False, False, 0)
				if pix[3]<1.0 : continue
				pdb.gimp_fuzzy_select(layer, x, y, 0, CHANNEL_OP_REPLACE, False, False, 0, False)
				sel, x1, y1, x2, y2 = pdb.gimp_selection_bounds(img)
				pdb.gimp_rect_select(img, x1, y1, (x2-x1), (y2-y1), CHANNEL_OP_REPLACE, False, 0)
				pdb.gimp_edit_bucket_fill(fuzzy, BG_BUCKET_FILL, NORMAL_MODE, 100, 0, False, 0, 0)
				if col==0 : tmp.write("\n\t")
				else : tmp.write(" ")
				col = col + 1
				if col>=5 : col = 0
				if op1 :
					tmp.write('{%d'%x1+',%d'%y1+",%d"%(x2-x1)+',%d'%(y2-y1)+"},")
				else :
					tmp.write('{%d'%x1+',%d'%y1+",%d"%(x2-1)+',%d'%(y2-1)+"},")
		if col==0 : tmp.write("\n\t")
		else : tmp.write(" ")
		tmp.write("{0,0,0,0}\n")
		tmp.write("};\n\n")
		if op2==False :
			pdb.gimp_image_remove_layer(img, fuzzy)

	tmp.close()
	if len(editor)>0 : os.system(editor%filename)

	pdb.gimp_selection_none(img)
	gimp.set_background(bg)
	pdb.gimp_image_undo_group_end(img)

register(
	"dr-gerar-coordenadas",
	"Localiza e gera as coordenadas de retangulos",
	"Localiza e gera as coordenadas de retangulos",
	"Diogo_RBG - http://diogorbg.blogspot.com",
	"Diogo_RBG",
	"25/01/2012",
	"<Image>/Filters/Diogo__RBG/Gerar Coordenadas...",
	"*",
	[
		#(PF_SPINNER, "horz", "Quadros na horizontal", 1, (1, 1000, 1)),
		#(PF_SPINNER, "vert", "Quadros na vertical", 1, (1, 1000, 1)),
		(PF_SPINNER, "impr", "Imprecisao de varredura", 5, (1, 99, 1)),
		(PF_BOOL, "op1", "Retornar como largura e altura", True),
		(PF_BOOL, "op2", "Exibir retangulos gerados", True),
		(PF_STRING, "filename", "Nome do arquivo", "_src.txt"),
		(PF_STRING, "editor", "Abrir com editor", "geany \"%s\"")
	],
	[],
	gerarCoordenadas)

main()
