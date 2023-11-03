#include "sglogout.h"
int main(int argc, char *argv[]) 
{

home_dir = getenv("HOME");

readconf();
int ea;
	gtk_init(&argc, &argv);

	display = XOpenDisplay(NULL);
	if (!display) {
		g_print("No se pudo abrir una conexión X11.\n");
		return 1;
	}

if (getScreenSize(display, &screenWidth, &screenHeight)) {

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "SGLogout");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);

	//g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //is commented to prevent destroying process when destroying window

	theme = gtk_icon_theme_get_default();
	info = gtk_icon_theme_lookup_icon(theme, "system-shutdown", 48, 0);
	if (info != NULL) 
	{
		GdkPixbuf *icon = gtk_icon_info_load_icon(info, NULL);
		gtk_window_set_icon(GTK_WINDOW(window), icon);
		g_object_unref(icon);
		g_object_unref(info);
	}

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	if (gpostxt == 0)
	{
		omode = GTK_ORIENTATION_HORIZONTAL;
	}
	else if (gpostxt == 1)
	{
		omode = GTK_ORIENTATION_VERTICAL;
	}

		shutdown_box = gtk_box_new(omode, 5);
		reboot_box = gtk_box_new(omode, 5);
		sleep_box = gtk_box_new(omode, 5);
		hibernate_box = gtk_box_new(omode, 5);
		killall_box = gtk_box_new(omode, 5);
		lock_box = gtk_box_new(omode, 5);
		logout_box = gtk_box_new(omode, 5);
		int siconsize;
		
			switch (iconsize)
			{
		case 0:
			siconsize = 8;
			break;
		case 1:
			siconsize = 16;
			break;
		case 2:
			siconsize = 32;
			break;
		case 3:
			siconsize = 64;
			break;
		case 4:
			siconsize = 128;
			break;
		case 5:
			siconsize = 256;
			break;
		case 6:
			siconsize = 512;
			break;
		default:
			siconsize = 32;
			break;
	}

		
		shutdown_btn = gtk_button_new();
			shutdown_ico = gtk_image_new_from_icon_name("system-shutdown", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(shutdown_ico), siconsize);
			shutdown_txt = gtk_label_new("Shut down");
		reboot_btn = gtk_button_new();
			reboot_ico = gtk_image_new_from_icon_name("system-reboot", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(reboot_ico), siconsize);
			reboot_txt =gtk_label_new("Reboot");
		sleep_btn = gtk_button_new();
			sleep_ico = gtk_image_new_from_icon_name("system-suspend", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(sleep_ico), siconsize);
			sleep_txt = gtk_label_new("Suspend");
		hibernate_btn = gtk_button_new();
			hibernate_ico = gtk_image_new_from_icon_name("system-hibernate", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(hibernate_ico), siconsize);
			hibernate_txt = gtk_label_new("Hibernate");
		killall_btn = gtk_button_new();
			killall_ico = gtk_image_new_from_icon_name("window-close", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(killall_ico), siconsize);
			killall_txt = gtk_label_new("Close all windows");
		lock_btn = gtk_button_new();
			lock_ico = gtk_image_new_from_icon_name("lock", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(lock_ico), siconsize);
			lock_txt = gtk_label_new("Lock screen");
		logout_btn = gtk_button_new();
			logout_ico = gtk_image_new_from_icon_name("system-log-out", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(logout_ico), siconsize);
			logout_txt = gtk_label_new("Logout");

		//Add icon to box
		if (gshowicons == 1)
		{
			gtk_container_add(GTK_CONTAINER(shutdown_box), shutdown_ico);
			gtk_container_add(GTK_CONTAINER(reboot_box), reboot_ico);
			gtk_container_add(GTK_CONTAINER(sleep_box), sleep_ico);
			gtk_container_add(GTK_CONTAINER(hibernate_box), hibernate_ico);
			gtk_container_add(GTK_CONTAINER(killall_box), killall_ico);
			gtk_container_add(GTK_CONTAINER(lock_box), lock_ico);
			gtk_container_add(GTK_CONTAINER(logout_box), logout_ico);
		}

		//add text next to icon, into the box
		if (gshowtext == 1)
		{
			gtk_container_add(GTK_CONTAINER(shutdown_box), shutdown_txt);
			gtk_container_add(GTK_CONTAINER(reboot_box), reboot_txt);
			gtk_container_add(GTK_CONTAINER(sleep_box), sleep_txt);
			gtk_container_add(GTK_CONTAINER(hibernate_box), hibernate_txt);
			gtk_container_add(GTK_CONTAINER(killall_box), killall_txt);
			gtk_container_add(GTK_CONTAINER(lock_box), lock_txt);
			gtk_container_add(GTK_CONTAINER(logout_box), logout_txt);
		}
		//add the full box into the button
			gtk_container_add(GTK_CONTAINER(shutdown_btn), shutdown_box);
			gtk_container_add(GTK_CONTAINER(reboot_btn), reboot_box);
			gtk_container_add(GTK_CONTAINER(sleep_btn), sleep_box);
			gtk_container_add(GTK_CONTAINER(hibernate_btn), hibernate_box);
			gtk_container_add(GTK_CONTAINER(killall_btn), killall_box);
			gtk_container_add(GTK_CONTAINER(lock_btn), lock_box);
			gtk_container_add(GTK_CONTAINER(logout_btn), logout_box);
		
		if (gshowicons == 0 && gshowtext == 0)
		{
			ea = 1;
		}

if (ea == 1)
{
	gtk_grid_attach(GTK_GRID(grid), gtk_label_new("You have hidden the icons and the text, what did you expect to happen?"), 0, 0, 6, 6); 
}
else
{
	if (layout == 0)
	{
		gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
		gtk_grid_attach(GTK_GRID(grid), shutdown_btn,  0, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), reboot_btn,    0, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), sleep_btn,     0, 2, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), hibernate_btn, 0, 3, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), killall_btn,   0, 4, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), lock_btn,      0, 5, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), logout_btn,    0, 6, 1, 1);
	}
	else if (layout == 1)
	{
		gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
		gtk_grid_attach(GTK_GRID(grid), shutdown_btn,  0, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), reboot_btn,    1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), sleep_btn,     2, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), hibernate_btn, 3, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), killall_btn,   4, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), lock_btn,      5, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), logout_btn,    6, 0, 1, 1);
	}
	else if (layout == 2)
	{
		gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
		gtk_grid_attach(GTK_GRID(grid), shutdown_btn,  0, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), reboot_btn,    1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), sleep_btn,     2, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), hibernate_btn, 0, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), killall_btn,   1, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), lock_btn,      2, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(grid), logout_btn,    1, 2, 1, 1);
	}
}



gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_widget_show_all(window);

int windowWidth, windowHeight;
		gtk_window_get_size(GTK_WINDOW(window), &windowWidth, &windowHeight);

			switch (position)
			{
		case 0:
			gtk_window_move(GTK_WINDOW(window), 0, 0);
			break;
		case 1:
			gtk_window_move(GTK_WINDOW(window), screenWidth/2-windowWidth/2, 0);
			break;
		case 2:
			gtk_window_move(GTK_WINDOW(window), screenWidth, 0);
			break;
		case 3:
			gtk_window_move(GTK_WINDOW(window), 0, screenHeight/2-windowHeight/2);
			break;
		case 4:
			gtk_window_move(GTK_WINDOW(window), screenWidth/2-windowWidth/2, screenHeight/2-windowHeight/2);
			break;
		case 5:
			gtk_window_move(GTK_WINDOW(window), screenWidth, screenHeight/2-windowHeight/2);
			break;
		case 6:
			gtk_window_move(GTK_WINDOW(window), 0, screenHeight);
			break;
		case 7:
			gtk_window_move(GTK_WINDOW(window), screenWidth/2-windowWidth/2, screenHeight);
			break;
		case 8:
			gtk_window_move(GTK_WINDOW(window), screenWidth, screenHeight);
			break;
	}

g_signal_connect(shutdown_btn, "clicked", G_CALLBACK(core_safeexit_thread), shutdown_btn);
g_signal_connect(reboot_btn, "clicked", G_CALLBACK(core_safeexit_thread), reboot_btn);
g_signal_connect(sleep_btn, "clicked", G_CALLBACK(core_safeexit_thread), sleep_btn);
g_signal_connect(hibernate_btn, "clicked", G_CALLBACK(core_safeexit_thread), hibernate_btn);
g_signal_connect(killall_btn, "clicked", G_CALLBACK(core_safeexit_thread), killall_btn);
g_signal_connect(lock_btn, "clicked", G_CALLBACK(core_safeexit_thread), lock_btn);
g_signal_connect(logout_btn, "clicked", G_CALLBACK(core_safeexit_thread), logout_btn);
g_signal_connect(window, "key-release-event", G_CALLBACK(on_key_press), 0);
g_signal_connect(window, "focus-out-event", G_CALLBACK(exit), 0);

gtk_main();
return 0;
}}

