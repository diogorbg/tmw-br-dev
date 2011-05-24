#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#define PLUGIN_NAME "tmwbr-hello2"
#define PLUGIN_DESC "Gerar Animação"
#define PLUGIN_MENU "Gerar _Animação..."
#define PLUGIN_HELP \
	"É capaz de gerar uma sequencia animada de um sprite.\n"\
	"\n"\
	"Diogo_RBG - <a href=\"http://diogorbg.blogspot.com\">http://diogorbg.blogspot.com</a>\n"\
	"<b>The Mana World BR</b> - <a href=\"http://www.themanaworld.com.br\">www.themanaworld.com.br</a>"

static void query(void);
static void run(const gchar *name, gint nparams, const GimpParam *param,
	gint *nreturn_vals, GimpParam **return_vals);
static void executar(gint32 idImg, gint32 idDraw, int v3, int v4);

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
		PLUGIN_NAME,
		PLUGIN_DESC,
		"Mostra uma janela cheia de botões.",
		"Diogo_RBG",
		"Copyright Diogo_RBG",
		"2010",
		PLUGIN_MENU,
		"RGB*, GRAY*, INDEXED*",
		GIMP_PLUGIN,
		G_N_ELEMENTS (args), 0,
		args, NULL);

	gimp_plugin_menu_register (PLUGIN_NAME, "<Image>/TMW-BR");
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

	if (run_mode==GIMP_RUN_NONINTERACTIVE)
		return;

	GtkWidget *dlg;
	GtkWidget *main_vbox;
	GtkWidget *hbox;
	GtkWidget *imagem;
	GtkWidget *label;
	GtkWidget *frame;
	GtkWidget *table;
	GtkWidget *combo;
	GtkWidget *combo3;
	GtkWidget *combo4;
	GtkListStore *store;
	gboolean   run = FALSE;
	int row;

	// Inicializa o GTK+
	gimp_ui_init(PLUGIN_NAME, TRUE);

	// Cria uma janela dialogo.
	dlg = gimp_dialog_new(PLUGIN_DESC, PLUGIN_NAME,
		NULL, 0, NULL,NULL,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		GTK_STOCK_OK, GTK_RESPONSE_OK,
		NULL);
	gtk_window_set_resizable(GTK_WINDOW(dlg), FALSE);

	main_vbox = gtk_vbox_new(FALSE, 6);
	gtk_container_set_border_width(GTK_CONTAINER(main_vbox), 6);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dlg)->vbox), main_vbox);

	/* Cabeçalho */

	hbox = gtk_hbox_new(FALSE, 6);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox, FALSE, FALSE, 0);
	//gtk_container_add(GTK_CONTAINER(main_vbox), hbox);

	imagem = gtk_image_new_from_file("logo.png");
	gtk_box_pack_start(GTK_BOX(hbox), imagem, FALSE, FALSE, 0);
	//gtk_container_add(GTK_CONTAINER(hbox), imagem);
	gtk_widget_show(imagem);

	label = gtk_label_new(PLUGIN_HELP);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
	//gtk_container_add(GTK_CONTAINER(hbox), label);
	gtk_widget_show(label);

	gtk_widget_show(hbox);

	/* Configurações do sprite */

	//frame = gimp_frame_new("Configurações do sprite");
	//gtk_box_pack_start(GTK_BOX(main_vbox), frame, FALSE, FALSE, 0);
	//gtk_widget_show(frame);

	//table = gtk_table_new(2, 2, FALSE);
	//gtk_table_set_col_spacings(GTK_TABLE(table), 4);
	//gtk_table_set_row_spacings(GTK_TABLE(table), 2);
	//gtk_container_add(GTK_CONTAINER(frame), table);
	//gtk_widget_show(table);

	//row = 0;
	//combo = gimp_int_combo_box_new(
		//"Camada Selecionada", 1,
		////"Camadas Visíveis",   2,
		//NULL);
	//gimp_int_combo_box_set_active(GIMP_INT_COMBO_BOX(combo), 1);
	//gimp_table_attach_aligned(GTK_TABLE(table), 0, row++, "Usar:", 0.0, 0.5, combo, 1, FALSE);

	//combo = gimp_int_combo_box_new(
		//"Sprite Base Completo", 1,
		////"Sprite Base Chapéu 1", 2,
		////"Sprite Base Chapéu 2", 3,
		//NULL);
	//gimp_int_combo_box_set_active(GIMP_INT_COMBO_BOX(combo), 1);
	//gimp_table_attach_aligned(GTK_TABLE(table), 0, row++, "Tipo:", 0.0, 0.5, combo, 1, FALSE);

	/* Opções para geração da animação */

	frame = gimp_frame_new("Opções para geração da animação");
	gtk_box_pack_start(GTK_BOX(main_vbox), frame, FALSE, FALSE, 0);
	gtk_widget_show(frame);

	table = gtk_table_new(2, 2, FALSE);
	gtk_table_set_col_spacings(GTK_TABLE(table), 4);
	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
	gtk_container_add(GTK_CONTAINER(frame), table);
	gtk_widget_show(table);

	row = 0;
	combo3 = gimp_int_combo_box_new(
		"Parado",           1,
		"Andando",          2,
		"Atacando1",        3,
		"Atacando2",        4,
		"Sentado",          5,
		"Morto",            6,
		"Parado+Andando",   7,
		"Parado+Atacando1", 8,
		"Parado+Atacando2", 9,
		NULL);
	gimp_int_combo_box_set_active(GIMP_INT_COMBO_BOX(combo3), 1);
	gimp_table_attach_aligned(GTK_TABLE(table), 0, row++, "Ação:", 0.0, 0.5, combo3, 1, FALSE);

	combo4 = gimp_int_combo_box_new(
		"Todos (lado a lado)", 1,
		"Abaixo",   2,
		"Esquerda", 3,
		"Acima",    4,
		"Direita",  5,
		NULL);
	gimp_int_combo_box_set_active(GIMP_INT_COMBO_BOX(combo4), 1);
	gimp_table_attach_aligned(GTK_TABLE(table), 0, row++, "Direção:", 0.0, 0.5, combo4, 1, FALSE);

	/* Show the main containers */

	gtk_widget_show(main_vbox);
	gtk_widget_show(dlg);

	run = (gimp_dialog_run(GIMP_DIALOG(dlg)) == GTK_RESPONSE_OK);

	gint32 idImg = param[1].data.d_int32;
	gint32 idDraw = param[2].data.d_int32;
	//GimpDrawable *drawable = gimp_drawable_get(param[2].data.d_drawable);
	gint v3;
	gint v4;
	if(run==TRUE) {
		gimp_int_combo_box_get_active(GIMP_INT_COMBO_BOX(combo3), &v3);
		gimp_int_combo_box_get_active(GIMP_INT_COMBO_BOX(combo4), &v4);
		executar(idImg, idDraw, v3, v4);
	}

	gtk_widget_destroy(dlg);
}

#define DEBUG(l) //printf("linha: %d\n", l);

/**
 * Aqui o código deixa de ser complicado e passa a utilizar suas
 * habilidades de GIMP.
 */
static void executar(gint32 idImg, gint32 idDraw, int v3, int v4){
	gint32 layer;

	gimp_progress_init("Gerar Animação...");
	gimp_image_undo_group_start(idImg);

	int W = gimp_drawable_width(idDraw);
	int H = gimp_drawable_height(idDraw);
	int w = W/9;
	int h = H/8;
	if(W%9!=0) gimp_message("Quadros não tem divisão exata na largura. Devem existir 9 quadros de larguras iguais.");
	if(H%8!=0) gimp_message("Quadros não tem divisão exata na altura. Devem existir 8 quadros de alturas iguais.");

	int *tiles;
	int i, j;
	int offx, offy;
	char buf[32];

	if(v3==1){
		tiles = (int[]){ 0,0 ,-1};
	} else if(v3==2) {
		tiles = (int[]){ 1,75, 2,75, 3,75, 4,75, 5,75, 6,75 ,-1};
	} else if(v3==3) {
		tiles = (int[]){ 9,75, 10,75, 11,75, 12,75 ,-1};
	} else if(v3==4) {
		tiles = (int[]){ 13,75, 14,75, 15,75, 16,75, 17,75 ,-1};
	} else if(v3==5) {
		tiles = (int[]){ 7,0 ,-1};
	} else if(v3==6) {
		tiles = (int[]){ 8,0 ,-1};
	} else if(v3==7) {
		tiles = (int[]){ 0,500, 1,75, 2,75, 3,75, 4,75, 5,75, 6,75 ,-1};
	} else if(v3==8) {
		tiles = (int[]){ 0,500, 9,75, 10,75, 11,75, 12,75 ,-1};
	} else if(v3==9) {
		tiles = (int[]){ 0,500, 13,75, 14,75, 15,75, 16,75, 17,75 ,-1};
	}

	v4-=2;
	for(i=0; tiles[i]>=0; i+=2) {
		if(v4>=0) {
			offx = ((tiles[i]+v4*18)%9)*w;
			offy = ((tiles[i]+v4*18)/9)*h;
			gimp_rect_select(idImg, offx, offy, w, h, GIMP_CHANNEL_OP_REPLACE, FALSE, 0.0);
			layer = gimp_selection_float(idImg, idDraw, -offx, -offy);
			if( tiles[i+1] )
				sprintf(buf, "Quadro%02d (%dms) (replace)", (i/2)+1, tiles[i+1]);
			else
				sprintf(buf, "Quadro%02d", (i/2)+1);
			gimp_drawable_set_name(layer, buf);
		} else {
			for(j=0; j<4; j++) {
				offx = ((tiles[i]+j*18)%9)*w;
				offy = ((tiles[i]+j*18)/9)*h;
				gimp_rect_select(idImg, offx, offy, w, h, GIMP_CHANNEL_OP_REPLACE, FALSE, 0.0);
				layer = gimp_selection_float(idImg, idDraw, -offx+j*w, -offy);
				if(j==0) {
					if( tiles[i+1] )
						sprintf(buf, "Quadro%02d (%dms) (replace)", (i/2)+1, tiles[i+1]);
					else
						sprintf(buf, "Quadro%02d", (i/2)+1);
					gimp_drawable_set_name(layer, buf);
				} else {
					gimp_image_merge_down(idImg, layer, 0); //EXPAND_AS_NECESSARY
				}
			}
		}
	}
	gimp_selection_none(idImg);

	gimp_image_remove_layer(idImg, idDraw);
	gimp_image_resize_to_layers(idImg);

	gimp_image_undo_group_end(idImg);
	gimp_progress_end();
	gimp_displays_flush();
}













