/**
 * Gera um sprite base no modo e resuluções definidas pelo usuário.
 *
 * @date segunda, 22 de novembro de 2010
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 */

#ifndef __RENDER_H__
#define __RENDER_H__

/*  Public functions  */

void render (gint32 image_ID, GimpDrawable *drawable, PlugInVals *vals,
	PlugInImageVals *image_vals, PlugInDrawableVals *drawable_vals);

#endif /* __RENDER_H__ */
