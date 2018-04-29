#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <ctype.h>

#include <gtk/gtk.h>
#include <glib.h>

#define RESET "\033[0m"
#define GREEN "\033[1;32m"

GtkWidget   *window_main, *scrolled_window, *scrolled_window2, *text_entry,  
            *button_print, *button_analize, *button_clear,*text_view, *text_view2;
GtkBuilder  *builder;   

static GtkWidget* window_maingtk();
void widget_build();
void on_window_main_destroy();

void button_clear_clicked();
void button_analize_clicked();
void button_print_clicked();

void append_textview(GtkWidget *text_view, const gchar *text);
void analize_func(FILE *analize,FILE *data);

int main(int argc, char *argv[]) { //GOOD
    gtk_init(&argc, &argv);
    window_main = window_maingtk();
    gtk_widget_show(window_main);
    gtk_main();
    return 0;
}

static GtkWidget* window_maingtk() { //GOOD
    GError* error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "./style/style.glade", &error)) {
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }
    GFile *file = g_file_new_for_path("./style/style.css");
    GtkCssProvider *provider = gtk_css_provider_new();
    if(!gtk_css_provider_load_from_file(provider, file, &error)) {
        g_warning("%s", error->message);
        g_error_free(error);
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_builder_connect_signals(builder, NULL);

    widget_build();

    g_object_unref(builder);

    return window_main;
}

void widget_build() { //GOOD
    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    if (!window_main) {
        g_critical("Ошибка при получении виджета window_main");
    }   
    scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled_window"));
    if (!scrolled_window) {
        g_critical("Ошибка при получении виджета scrolled_window");
    }
    scrolled_window2 = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled_window2"));
    if (!scrolled_window2) {
        g_critical("Ошибка при получении виджета scrolled_window2");
    }
    text_entry = GTK_WIDGET(gtk_builder_get_object(builder, "text_entry"));
    if (!text_entry) {
        g_critical("Ошибка при получении виджета text_entry");
    }
    button_print = GTK_WIDGET(gtk_builder_get_object(builder, "button_print"));
    if (!button_print) {
        g_critical("Ошибка при получении виджета button_print");
    }
    button_analize = GTK_WIDGET(gtk_builder_get_object(builder, "button_analize"));
    if (!button_analize) {
        g_critical("Ошибка при получении виджета button_analize");
    }
    button_clear = GTK_WIDGET(gtk_builder_get_object(builder, "button_clear"));
    if (!button_clear) {
        g_critical("Ошибка при получении виджета button_clear");
    }
    text_view = GTK_WIDGET(gtk_builder_get_object(builder, "text_view"));
    if (!text_view) {
        g_critical("Ошибка при получении виджета text_view");
    }
    text_view2 = GTK_WIDGET(gtk_builder_get_object(builder, "text_view2"));
    if (!text_view2) {
        g_critical("Ошибка при получении виджета text_view2");
    }

}

void on_window_main_destroy() { //GOOD
    gtk_main_quit();
    printf("%sGoodbye ^^%s\n", GREEN, RESET);
}

void button_clear_clicked() { //GOOD
    FILE *analize, *data;
    analize = fopen("./src/analize_text.txt", "r");
    data = fopen("./src/data_text.txt", "r");

    if (data != NULL || analize != NULL) {
        GtkTextBuffer *buffer;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_set_text(buffer,"", 0);
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view2));
        gtk_text_buffer_set_text(buffer,"", 0);

        remove("./src/data_text.txt");
        remove("./src/analize_text.txt");
    }
}

void button_analize_clicked() {
    FILE *analize, *data;
    data = fopen("./src/data_text.txt", "r");

    if (data != NULL) {
        analize = fopen("./src/analize_text.txt", "w");
        analize_func(analize, data);
    }
}

void button_print_clicked() { //GOOD
    char *text = (char*)gtk_entry_get_text(GTK_ENTRY(text_entry));
    if (strcmp(text, "") != 0) {
        FILE *data;
        data = fopen("./src/data_text.txt", "w");
        append_textview(text_view, gtk_entry_get_text(GTK_ENTRY(text_entry)));
        append_textview(text_view2, gtk_entry_get_text(GTK_ENTRY(text_entry)));
        fprintf (data, "%s", text);
        fclose(data);
        gtk_entry_set_text(GTK_ENTRY(text_entry), "");
    }
}

void append_textview(GtkWidget *text_view, const gchar *text) { //GOOD
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    GtkTextMark *mark = gtk_text_buffer_get_insert (buffer);
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    gtk_text_buffer_insert (buffer, &iter, text, -1);
}

void analize_func(FILE *analize,FILE *data) {
    // в процессе :)
}