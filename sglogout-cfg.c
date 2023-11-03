#include "sglogout.h"

int main(int argc, char *argv[])
{
if (argc > 0) 
{
	pm = argv[0];
}
else
{
	pm = "sglauncher";
}

home_dir = getenv("HOME");
readconf();

gtk_init(&argc, &argv);

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Settings - SGLogout");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request(window, 400, 300);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	headerbar = gtk_header_bar_new();
		gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
		button = gtk_menu_button_new();
		image = gtk_image_new_from_icon_name("menulibre", GTK_ICON_SIZE_BUTTON);
		gtk_container_add(GTK_CONTAINER(button), image);

		gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), button);
		wtitle = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(wtitle), "<b>Settings - SGLogout</b>");
		gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), wtitle);

		submenu = gtk_menu_new();
			submenu_item3 = gtk_menu_item_new_with_label("About");
			gtk_menu_shell_append(GTK_MENU_SHELL(submenu), submenu_item3);
			gtk_widget_show_all(submenu);
			gtk_menu_button_set_popup(GTK_MENU_BUTTON(button), submenu);

	gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
	gtk_container_add(GTK_CONTAINER(window), grid);

ordcombo = gtk_combo_box_text_new(); 

	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ordcombo), "Vertical");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ordcombo), "Horizontal");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ordcombo), "Grid");

poscombo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Top - Left");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Top - Center");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Top - Right");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Middle - Left");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Middle - Center");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Middle - Right");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Bottom - Left");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Bottom - Center");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(poscombo), "Bottom - Right");

icocombo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Tiny 8x8");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Small 16x16");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Medium 32x32");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Big 64x64");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Large 128x128");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Huge 256x256");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(icocombo), "Massive 512x512");

wshowico = gtk_check_button_new(); 
wshowtxt =  gtk_check_button_new();
wpostxt =  gtk_check_button_new();

defbtn    = gtk_button_new_with_label("Default");
applybtn  = gtk_button_new_with_label("Apply");

gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Window Position:"), 0, 1, 1, 1); 
gtk_grid_attach(GTK_GRID(grid), poscombo, 1, 1, 1, 1);

gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Item Order:"), 0, 2, 1, 1);    
gtk_grid_attach(GTK_GRID(grid), ordcombo, 1, 2, 1, 1);

gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Icon Size:"), 0, 3, 1, 1);    
gtk_grid_attach(GTK_GRID(grid), icocombo, 1, 3, 1, 1);

gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Show icons"), 0, 4, 1, 1); 
gtk_grid_attach(GTK_GRID(grid), wshowico, 1, 4, 1, 1);

gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Show text"), 0, 5, 1, 1); 
gtk_grid_attach(GTK_GRID(grid), wshowtxt,   1, 5, 1, 1);

gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Text under icon"), 0, 6, 1, 1); 
gtk_grid_attach(GTK_GRID(grid), wpostxt,   1, 6, 1, 1);

gtk_grid_attach(GTK_GRID(grid), defbtn,   0, 7, 1, 1);
gtk_grid_attach(GTK_GRID(grid), applybtn, 1, 7, 1, 1);


//SET Options STATUS
if (gshowtext == 1)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wshowtxt), TRUE );
}
if (gshowicons == 1)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wshowico), TRUE);  
}
if (gpostxt == 1)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wpostxt), TRUE);
}
gtk_combo_box_set_active(GTK_COMBO_BOX(poscombo), position);
gtk_combo_box_set_active(GTK_COMBO_BOX(ordcombo), layout);
gtk_combo_box_set_active(GTK_COMBO_BOX(icocombo), iconsize);

g_signal_connect(submenu_item3, "activate", G_CALLBACK(on_submenu_item3_selected), NULL);
g_signal_connect(applybtn, "clicked", G_CALLBACK(on_apply_button_clicked), NULL);
g_signal_connect(defbtn, "clicked", G_CALLBACK(on_default_button_clicked), NULL);

gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_widget_show_all(window);

gtk_main();
return 0;
}
