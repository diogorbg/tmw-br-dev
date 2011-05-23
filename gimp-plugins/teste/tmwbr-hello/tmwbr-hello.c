#include <libgimp/gimp.h>

static void query(void);
static void run(const gchar *name, gint nparams, const GimpParam *param,
	gint *nreturn_vals, GimpParam **return_vals);

GimpPlugInInfo PLUG_IN_INFO =
{
	NULL,
	NULL,
	query,
	run
};

MAIN()

static void query(void) {
	static GimpParamDef args[] =
	{
		{ GIMP_PDB_INT32,    "run-mode", "Rum Mode"       },
		{ GIMP_PDB_IMAGE,    "image",    "Input image"    },
		{ GIMP_PDB_DRAWABLE, "drawable", "Input drawable" }
	};

	gimp_install_procedure(
		"tmwbr-hello",
		"Olá, TMW-BR!",
		"Mostra \"olá, TMW-BR!\" em uma janela",
		"Diogo_RBG",
		"Copyright Diogo_RBG",
		"2010",
		"_Olá TMW-BR...",
		"",//"RGB*, GRAY*",
		GIMP_PLUGIN,
		G_N_ELEMENTS (args), 0,
		args, NULL);

	gimp_plugin_menu_register ("tmwbr-hello", "<Image>/TMW-BR");
}

static void run(const gchar *name, gint nparams, const GimpParam *param,
	gint *nreturn_vals, GimpParam **return_vals){

	static GimpParam  values[1];
	GimpPDBStatusType status = GIMP_PDB_SUCCESS;
	GimpRunMode       run_mode;

	/* Setting mandatory output values */
	*nreturn_vals = 1;
	*return_vals  = values;

	values[0].type = GIMP_PDB_STATUS;
	values[0].data.d_status = status;

	/* Getting run_mode - we won't display a dialog if
	* we are in NONINTERACTIVE mode */
	run_mode = param[0].data.d_int32;

	if (run_mode!=GIMP_RUN_NONINTERACTIVE)
		g_message("Olá, TMW-BR!\n");
}

