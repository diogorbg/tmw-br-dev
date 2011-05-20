/**
 * Gera um sprite base no modo e resuluções definidas pelo usuário.
 *
 * @date segunda, 22 de novembro de 2010
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 */

#include "config.h"

#include <gtk/gtk.h>

#include <libgimp/gimp.h>

#include "main.h"
#include "render.h"

#include "plugin-intl.h"

/*  Public functions  */

void render (gint32 image_ID, GimpDrawable *drawable, PlugInVals *vals,
	PlugInImageVals *image_vals, PlugInDrawableVals *drawable_vals) {

	g_message ("Este plugin é apenas um modelo. Ele não faz absolutamente nada.");
}
