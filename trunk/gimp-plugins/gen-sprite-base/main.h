/**
 * Gera um sprite base no modo e resuluções definidas pelo usuário.
 *
 * @date segunda, 22 de novembro de 2010
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 */

#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct
{
	gint     dummy1;
	gint     dummy2;
	gint     dummy3;
	guint    seed;
	gboolean random_seed;
} PlugInVals;

typedef struct
{
	gint32 image_id;
} PlugInImageVals;

typedef struct
{
	gint32 drawable_id;
} PlugInDrawableVals;

typedef struct
{
	gboolean chain_active;
} PlugInUIVals;


/*  Default values  */

extern const PlugInVals         default_vals;
extern const PlugInImageVals    default_image_vals;
extern const PlugInDrawableVals default_drawable_vals;
extern const PlugInUIVals       default_ui_vals;


#endif /* __MAIN_H__ */
