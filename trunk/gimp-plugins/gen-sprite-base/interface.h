/**
 * Gera um sprite base no modo e resuluções definidas pelo usuário.
 *
 * @date segunda, 22 de novembro de 2010
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/* Public functions */

gboolean dialog (gint32 image_ID, GimpDrawable *drawable, PlugInVals *vals,
	PlugInImageVals *image_vals, PlugInDrawableVals *drawable_vals, PlugInUIVals *ui_vals);

#endif /* __INTERFACE_H__ */
