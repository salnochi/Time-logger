#include <gtk/gtk.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

GtkWidget *entry;
GtkWidget *status_label;

void flushBuffer() {
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
}

void on_capture_clicked(GtkButton *button, gpointer user_data) {
    const gchar *subject = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(subject) == 0) {
        gtk_label_set_text(GTK_LABEL(status_label), "Please enter a subject.");
        return;
    }

    time_t rawtime;
    struct tm *info;
    char MY_TIME[80];

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(MY_TIME, sizeof(MY_TIME), "%m%d%Y, %H:%M:%S", info);

    FILE *fpt = fopen("logs/time_log_gui.csv", "a");
    if (!fpt) {
        gtk_label_set_text(GTK_LABEL(status_label), "Failed to open log file.");
        return;
    }

    fprintf(fpt, "%s,%s\n", MY_TIME, subject);
    fclose(fpt);

    char status_msg[256];
    snprintf(status_msg, sizeof(status_msg), "Captured: %s, %s", subject, MY_TIME);
    gtk_label_set_text(GTK_LABEL(status_label), status_msg);

    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void on_quit_clicked(GtkButton *button, gpointer user_data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Time Log");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 150);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label = gtk_label_new("Enter the time stamp subject:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);

    GtkWidget *capture_button = gtk_button_new_with_label("Capture Time");
    g_signal_connect(capture_button, "clicked", G_CALLBACK(on_capture_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), capture_button, TRUE, TRUE, 0);

    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect(quit_button, "clicked", G_CALLBACK(on_quit_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), quit_button, TRUE, TRUE, 0);

    status_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), status_label, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
