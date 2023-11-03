#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#define ML 512

char *pm;
char *home_dir;
int omode;
int layout;
int position;
int iconsize;
gboolean gshowicons;
gboolean gshowtext;
gboolean gpostxt;
char *sessiondo;

const gchar *clayout;
const gchar *cposition;
const gchar *ciconsize;
gboolean cgshowicons;
gboolean cgshowtext;
char config_file_path[256];

GtkWidget *window;
Display *display;
int screenWidth, screenHeight;
GtkWidget *grid;
GtkWidget *dialog;
GtkWidget *label;
GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;
GtkWidget *headerbar;
GtkWidget *button;
GtkWidget *image;
GtkWidget *wtitle;

//cfg widgets
GtkWidget *submenu;
GtkWidget *submenu_item3;
GtkWidget *poscombo;
GtkWidget *ordcombo;
GtkWidget *icocombo;
GtkWidget *wshowico;
GtkWidget *wshowtxt;
GtkWidget *wpostxt;
GtkWidget *defbtn;
GtkWidget *applybtn;

//mainwindow widgets
GtkWidget *shutdown_box;
GtkWidget *reboot_box;
GtkWidget *sleep_box;
GtkWidget *hibernate_box;
GtkWidget *lock_box;
GtkWidget *logout_box;
GtkWidget *killall_box;
	GtkWidget *shutdown_btn;
	GtkWidget *reboot_btn;
	GtkWidget *sleep_btn;
	GtkWidget *hibernate_btn;
	GtkWidget *lock_btn;
	GtkWidget *logout_btn;
	GtkWidget *killall_btn;
		GtkWidget *shutdown_ico;
		GtkWidget *shutdown_txt;
		GtkWidget *killall_ico;
		GtkWidget *killall_txt;
		GtkWidget *reboot_ico;
		GtkWidget *reboot_txt;
		GtkWidget *sleep_ico;
		GtkWidget *sleep_txt;
		GtkWidget *hibernate_ico;
		GtkWidget *hibernate_txt;
		GtkWidget *lock_ico;
		GtkWidget *lock_txt;
		GtkWidget *logout_ico;
		GtkWidget *logout_txt;


static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Escape) {
        exit(0);
    }
    return FALSE;
}
static gboolean on_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer user_data) {
    exit(0);
    return TRUE;
}


int getScreenSize(Display *display, int *width, int *height)
{
	Screen *screen = XDefaultScreenOfDisplay(display);
	if (screen)
	{
		*width = XWidthOfScreen(screen);
		*height = XHeightOfScreen(screen);
		return 1;
	}
	return 0;
}




void restart_program(GtkWidget *widget, gpointer data)
{
	printf("Program Reloaded...\n");
	char *args[] = {pm, NULL};
	execvp(args[0], args);
}

void on_submenu_item3_selected(GtkMenuItem *menuitem, gpointer userdata) 
{
	dialog = gtk_about_dialog_new();

	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "SGLogout");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright © 2023 Simple GTK Desktop Environment");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "Simple GTK Session Manager");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://itzselenux.github.io/sglogout");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), "Project WebSite");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog),"system-shutdown");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

void readconf()
{
	//READ THE CONF
	/////////////////////////////////////////
	if (home_dir == NULL) {
		fprintf(stderr, "Error: HOME environment variable is not set.\n");
		exit(1);
	}

	snprintf(config_file_path, sizeof(config_file_path), "%s/.config/sglogout.conf", home_dir);

	FILE *file = fopen(config_file_path, "r");
	if (file == NULL)
	{
		if (file == NULL)
		{
			FILE *default_conf = fopen("/etc/sglogout.conf", "r");
			if (default_conf == NULL)
			{
				fprintf(stderr, "Error: could not open default configuration file /etc/sglogout.conf, please reinstall the program or put a config file in ~/.config/sglogout.conf.\n");
				exit(1);
			}
			
			file = fopen(config_file_path, "w");
			if (file == NULL) {
				fprintf(stderr, "Error: could not create %s for writing.\n", config_file_path);
				exit(1);
			}

			int ch;
			while ((ch = fgetc(default_conf)) != EOF)
			{
				fputc(ch, file);
			}

			fclose(default_conf);
			printf("Default configuration file copied to %s.\n", config_file_path);
		}
		else
		{
			fclose(file);
			printf("%s exists and can be read.\n", config_file_path);
		}
	}

// Open the file for reading
	char line[ML];

	if (file != NULL) {
		// Read each line from the file and parse the variable assignments
		while (fgets(line, ML, file) != NULL)
		{
			char *name = strtok(line, "=");
			char *value_str = strtok(NULL, "=");

			if (file != NULL)
			{
				// Read each line from the file and parse the variable assignments
				while (fgets(line, ML, file) != NULL)
				{
					char *name = strtok(line, "=");
					char *value_str = strtok(NULL, "=");
			
					if (name != NULL && value_str != NULL)
					{
						// Set the value of the corresponding variable based on the name
						if (strcmp(name, "position") == 0) 
						{
							position = atoi(value_str);
						} 
						else if (strcmp(name, "layout") == 0)
						{
							layout = atoi(value_str);
						} 
						else if (strcmp(name, "iconsize") == 0) 
						{
							iconsize = atoi(value_str);
						} 
						else if (strcmp(name, "showicons") == 0) 
						{
							gshowicons = atoi(value_str);
						} 
						else if (strcmp(name, "showtext") == 0) 
						{
							gshowtext = atoi(value_str);
						}
						else if (strcmp(name, "textpos") == 0) 
						{
							gpostxt = atoi(value_str);
						}
					}
				}
			}
		}
		fclose(file);
	} else {
		printf("Error opening file");
	}
	printf("\nLayout: %d\nPosition: %d\nIconSize: %d\nShowIcons: %d\nShowText: %d\nTextPosition: %d\n", layout, position, iconsize, gshowicons, gshowtext, gpostxt);
}

void on_default_button_clicked(GtkButton *button, gpointer user_data) {
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_OK_CANCEL, "Are you sure you want to restore SGLogout settings as default?");
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(dialog), "Confirmation");
	gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_OK) {
		char *home_dir = getenv("HOME");
		if (home_dir == NULL) {
			fprintf(stderr, "Error: HOME environment variable is not set.\n");
			exit(1);
		}
		char *source_file = "/etc/sglogout.conf";
		char *destination_file = "/.config/sglogout.conf";
		char command[100];
		sprintf(command, "cp %s %s%s", source_file, home_dir, destination_file);
		system(command);
		restart_program(NULL, pm);

	} else {
		printf("Operation cancelled.\n");
	}
	gtk_widget_destroy(dialog);
}

	void on_apply_button_clicked(GtkButton *button, gpointer user_data) 
	{
	gshowtext = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wshowtxt));
	gshowicons = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wshowico));
	gpostxt = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wpostxt));
	const gchar *active_ico = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(icocombo));
	const gchar *active_pos = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(poscombo));  
	const gchar *active_ord = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ordcombo));   

		if (active_pos != NULL) 
		{
				 if (g_strcmp0(active_pos, "Top - Left") == 0) 
			{
				cposition = "0";
			}
			else if (g_strcmp0(active_pos, "Top - Center") == 0) 
			{
				cposition = "1";
			}
			else if (g_strcmp0(active_pos, "Top - Right") == 0) 
			{
				cposition = "2";
			}
			else if (g_strcmp0(active_pos, "Middle - Left") == 0) 
			{
				cposition = "3";
			}
			else if (g_strcmp0(active_pos, "Middle - Center") == 0) 
			{
				cposition = "4";
			}
			else if (g_strcmp0(active_pos, "Middle - Right") == 0) 
			{
				cposition = "5";
			}
			else if (g_strcmp0(active_pos, "Bottom - Left") == 0) 
			{
				cposition = "6";
			}
			else if (g_strcmp0(active_pos, "Bottom - Center") == 0) 
			{
				cposition = "7";
			}
			else if (g_strcmp0(active_pos, "Bottom - Right") == 0) 
			{
				cposition = "8";
			}
		}
			if (active_ord != NULL) 
		{
			if (g_strcmp0(active_ord, "Vertical") == 0) 
			{
				clayout = "0";
			} 
			else if (g_strcmp0(active_ord, "Horizontal") == 0) 
			{
				clayout = "1";
			} 
			else if (g_strcmp0(active_ord, "Grid") == 0) 
			{
				clayout = "2";
			} 
		}
		if (active_ico != NULL) 
		{
			if (g_strcmp0(active_ico, "Tiny 8x8") == 0) 
			{
				ciconsize = "0";
			} 
			else if (g_strcmp0(active_ico, "Small 16x16") == 0) 
			{
				ciconsize = "1";
			} 
			else if (g_strcmp0(active_ico, "Medium 32x32") == 0) 
			{
				ciconsize = "2";
			} 
			else if (g_strcmp0(active_ico, "Big 64x64") == 0) 
			{
				ciconsize = "3";
			}
			else if (g_strcmp0(active_ico, "Large 128x128") == 0) 
			{
				ciconsize = "4";
			}
			else if (g_strcmp0(active_ico, "Huge 256x256") == 0) 
			{
				ciconsize = "5";
			}
			else if (g_strcmp0(active_ico, "Massive 512x512") == 0) 
			{
				ciconsize = "6";
			}
		}
 FILE *fp = fopen(config_file_path, "r+");
	if (fp == NULL) {
		perror("Failed to open config file");
		exit(EXIT_FAILURE);
	}
	int iiconsize = atoi(ciconsize); //fix weid bug when saving iconsize value
	char line[ML];
	while (fgets(line, ML, fp) != NULL) 
	{
		if (strncmp(line, "position=", 9) == 0) 
		{
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "position=%s\n", cposition);
		}
		else if (strncmp(line, "layout=", 7) == 0) 
		{
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "layout=%s\n", clayout);
		}
		else if (strncmp(line, "iconsize=", 9) == 0) 
		{
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "iconsize=%d\n", iiconsize);
		}
		else if (strncmp(line, "showicons=", 10) == 0) 
		{
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "showicons=%d\n", gshowicons);
		}
		else if (strncmp(line, "showtext=", 9) == 0) 
		{
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "showtext=%d\n", gshowtext);
		}
		else if (strncmp(line, "textpos=", 7) == 0) 
		{
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "textpos=%d\n", gpostxt);
		}
	}

	// close the file
	fclose(fp);

	// The code below will only execute if the execvp() call fails
	restart_program(NULL, pm);
	}

void safeexit(Display *display, GtkWidget *widget)  
{
gtk_window_close(GTK_WINDOW(window));
int exiting = 0; 
int al = 0;
if (widget == shutdown_btn) {
		g_print("Shutdown button called safeexit\n");
		sessiondo = "poweroff"; 
	}
	else if (widget == reboot_btn)
	{
		g_print("Reboot button called safeexit\n");
		sessiondo = "reboot";

	}
	else if (widget == sleep_btn)
	{
		g_print("Sleep button called safeexit\n");
		system("loginctl suspend");
		exit(0);

	}
	else if (widget == hibernate_btn)
	{
		g_print("Hibernate button called safeexit\n");
		system("loginctl hibernate");
		exit(0);;
	}
	else if (widget == killall_btn)
	{
		g_print("Kill All button called safeexit\n");
		sessiondo = "\0";

	}
	else if (widget == lock_btn)
	{
		g_print("Lock button called safeexit\n");
		system("xset s activate");
		exit(0);
	}
	else if (widget == logout_btn)
	{
		g_print("Logout button called safeexit\n");
	sessiondo = "terminate-user $USER";
	}
	else
	{
		g_print("Unknown widget called safeexit\n");
	}
	
		system("wmctrl -l | grep ' 0 '| cut -d ' ' -f 1 | xargs -I {} wmctrl -ic {}");

	while (!exiting)
	{
		sleep(1);
		FILE *fp = popen("wmctrl -l | grep ' 0 '", "r");
		if (fp != NULL) {
			char line[256];
			if (fgets(line, sizeof(line), fp) == NULL) {
				g_print("No more windows remaining, continuing \n");
				exiting = 1;
				char *systemd;
	FILE *fp = popen("pidof systemd", "r");
	if (fp) 
	{
		char buffer[128];
		if (fgets(buffer, sizeof(buffer), fp) != NULL) {
			printf("Systemd detected, using systemctl poweroff...\n");
			char *systemd = "systemctl";
			pclose(fp);
		}
		else
		{
			printf("Systemd not detected, using loginctl poweroff...\n");
			systemd = "loginctl";
			pclose(fp);
		}
	} else {
		perror("Error trying to get systemd");
	}
	char fcmd[1024];
	sprintf(fcmd, "%s %s", systemd, sessiondo);
	g_print(fcmd);
	system(fcmd);
			} 
			else
			{
				al +=1;
				if (al == 16)
				{
				g_print("After 16 attemps, there are still windows open, cancelling...\n");
				exit(0);
				}
				else
				{
				g_print("There are some windows open, trying again.\n");
				}
			}
			pclose(fp);
		}
	}
}



pthread_t safeexitThread;

void *safeexit_thread(void *data) {
	GtkWidget *widget = (GtkWidget *)data;
	safeexit((Display *)display, widget);
	return NULL;
}

void core_safeexit_thread(Display *display, GtkWidget *widget) {
	int result = pthread_create(&safeexitThread, NULL, safeexit_thread, (void *)widget);
	if (result != 0) {
		perror("Error creating thread");
	}
}

