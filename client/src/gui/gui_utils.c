#include "../../inc/client.h"

void destroy(GtkWidget* widget, gpointer data)
{
	handle_logout_request(false);
    // pthread_cancel(utils->th_reader);
	client_cleanup(false);
    gtk_main_quit();
}

void add_class(GtkWidget *widget, char *class_name)
{
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, class_name);
}

void remove_class(GtkWidget *widget, char *class_name)
{
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, class_name);
}

void on_crossing(GtkWidget *widget, GdkEventCrossing *event)
{
	GdkDisplay *display = gtk_widget_get_display(widget);
	GdkCursor *cursor = NULL;	

	switch (gdk_event_get_event_type((GdkEvent*)event))
	{
		case GDK_ENTER_NOTIFY:
			gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE); // it's for trigger :hover for this widget in CSS
			cursor = gdk_cursor_new_from_name (display, "hand1");
			break;

		case GDK_LEAVE_NOTIFY:
			gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
			cursor = gdk_cursor_new_from_name (display, "default");
			break;

		default:
			break;
	}

	gdk_window_set_cursor (gtk_widget_get_window(widget), cursor);

	// Release the reference on the cursor
	g_object_unref(cursor);
}

GtkWidget* create_new_window(char *title, int width, int height, bool resizable)
{
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); //GTK_WIN_POS_CENTER GTK_WIN_POS_CENTER_ON_PARENT
	gtk_window_set_resizable(GTK_WINDOW(window), resizable);
    g_signal_connect(window, "delete_event", G_CALLBACK(destroy), NULL); //delete_event

	return window;
}

static void destroy_popup_window(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen)
{
    if (widget){}
    gtk_widget_destroy(widget);
}

GtkWidget *create_popup_window(int width, int height)
{
    GtkWidget*  popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //GTK_WINDOW_POPUP
    // t_chat_screen.popup_menu = popup_window;
    gtk_widget_set_name(GTK_WIDGET(popup_window), "popup_window");
    gtk_window_set_default_size(GTK_WINDOW(popup_window), width, height);
    gtk_window_set_transient_for(GTK_WINDOW(popup_window), GTK_WINDOW(main_window));
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popup_window), TRUE);
	gtk_window_set_position(GTK_WINDOW(popup_window), GTK_WIN_POS_CENTER_ON_PARENT); //GTK_WIN_POS_CENTER
    gtk_window_set_decorated(GTK_WINDOW(popup_window), FALSE);
    g_signal_connect(G_OBJECT(popup_window), "focus-out-event", G_CALLBACK(destroy_popup_window), NULL);

    return popup_window;
}

void set_field_error_style(GtkWidget *field)
{
    remove_class(field, "input_field--success");
    add_class(field, "input_field--error");
}

void set_field_success_style(GtkWidget *field)
{
    remove_class(field, "input_field--error");
    add_class(field, "input_field--success");
}

void set_notify_error_style( GtkWidget *notify_label, char *message)
{
    remove_class(notify_label, "notify_label--success");
    add_class(notify_label, "notify_label--error");
    gtk_label_set_text(GTK_LABEL(notify_label), message);
}

void set_notify_success_style( GtkWidget *notify_label, char *message)
{
    remove_class(notify_label, "notify_label--error");
    add_class(notify_label, "notify_label--success");
    gtk_label_set_text(GTK_LABEL(notify_label), message);
}

void clear_container(GtkWidget *container)
{
    gtk_container_foreach(GTK_CONTAINER(container), (GtkCallback)gtk_widget_destroy, NULL);
}

//return NULL if find nothing
GtkWidget *get_widget_by_name(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL; 
    GList *children = NULL;

    if (GTK_IS_CONTAINER(container))
    {
        children = gtk_container_get_children(GTK_CONTAINER(container));
    }
    else {
        return NULL;
    }

    while (children)
    {
        if (!mx_strcmp(gtk_widget_get_name(GTK_WIDGET(children->data)), name))
        {
            result = GTK_WIDGET(children->data);
            break;
        }
        
        children = children->next;   
    }
    g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); //

    return result;
}

//return NULL if find nothing
GtkWidget *get_widget_by_name_r(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL; 
    GList *children = NULL;

    if (GTK_IS_CONTAINER(container))
    {
        children = gtk_container_get_children(GTK_CONTAINER(container));
    }
    else
    {
        return NULL;
    }

    while (children)
    {
        if (!mx_strcmp(gtk_widget_get_name(GTK_WIDGET(children->data)), name))
        {
            result = GTK_WIDGET(children->data);
            break;
        }
        else if(GTK_IS_CONTAINER(children->data))
        {
            result = get_widget_by_name_r(children->data, name);
            if (result != NULL)
                break;
        }

        children = children->next;   
    }
    g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); //

    return result;
}
