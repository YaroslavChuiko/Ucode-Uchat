#include "../../inc/client.h"

void destroy_create_chat_menu(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (widget){}
    // if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    gtk_widget_destroy(GTK_WIDGET(widget));
}


void create_chat_list_item(char *group_name)
{
    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(t_chat_screen.chat_list), event_box, FALSE, FALSE, 3);

    GtkWidget *chat_list_item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(event_box), chat_list_item);
    add_class(chat_list_item, "chat_list_item");

    // GtkWidget *avatar = gtk_drawing_area_new();
    GtkWidget *avatar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    // g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)list->avatar);   // Получить avatar пользовтеля
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chat_list_item), avatar, FALSE, FALSE, 0);
    add_class(avatar, "chat_list_item_avatar");

    // GtkWidget *chat_list_item_content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // gtk_box_pack_start(GTK_BOX(chat_list_item), chat_list_item_content, false, false, 0);
    // add_class(chat_list_item_content, "chat_list_item_content");

    // text block
    GtkWidget *chat_list_item_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chat_list_item_text), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chat_list_item_text), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat_list_item), chat_list_item_text, false, false, 0);
    add_class(chat_list_item_text, "chat_list_item_text");

    GtkWidget *chat_list_item_title = gtk_label_new(group_name);
    gtk_widget_set_halign(GTK_WIDGET(chat_list_item_title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat_list_item_text), chat_list_item_title, false, false, 0);
    GtkWidget *chat_list_item_message = gtk_label_new("Last message");
    gtk_widget_set_halign(GTK_WIDGET(chat_list_item_message), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat_list_item_text), chat_list_item_message, false, false, 0);
    //

    // info block
    GtkWidget *chat_list_item_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chat_list_item_info), GTK_ALIGN_END);
    // gtk_widget_set_valign(GTK_WIDGET(chat_list_item_info), GTK_ALIGN_END);
    gtk_box_pack_end(GTK_BOX(chat_list_item), chat_list_item_info, false, false, 0);
    add_class(chat_list_item_info, "chat_list_item_info");

    GtkWidget *chat_list_item_time = gtk_label_new("15:00");
    gtk_widget_set_valign(GTK_WIDGET(chat_list_item_time), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(chat_list_item_time), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(chat_list_item_info), chat_list_item_time, false, false, 0);
    add_class(chat_list_item_time, "chat_list_item_time");
    GtkWidget *chat_list_item_notify = gtk_label_new("2");
    gtk_widget_set_size_request(GTK_WIDGET(chat_list_item_notify), 20, 20);
    gtk_widget_set_valign(GTK_WIDGET(chat_list_item_notify), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(chat_list_item_notify), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(chat_list_item_info), chat_list_item_notify, false, false, 0);
    add_class(chat_list_item_notify, "chat_list_item_notify");
    //

    gtk_widget_show_all(event_box);
}

void create_chat_btn_click(GtkWidget *widget, gpointer chat_name_field1)/////////////////////////////////////////////////////////////
{
    // if (widget){}

    // GtkWidget *parent = gtk_widget_get_parent(widget);
    
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");
    // GtkWidget *create_chat_notify_label = get_widget_by_name_r(toplevel, "create_chat_notify_label");

    if (!validate_name_field(chat_name_field, chat_name_notify_label))
    {
        // set_notify_error_style(create_chat_notify_label, "");
        return;
    }
    
    char *group_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(chat_name_field)));

    int error_code = handle_create_chat_request(group_name);
    handle_create_chat_error_code(error_code, chat_name_field, chat_name_notify_label);

    if (error_code == R_SUCCESS)
    {
        create_chat_list_item(group_name);
        gtk_widget_destroy(toplevel);
    }
}

void destroy_popup(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen)
{
    if (widget){}
    gtk_widget_destroy(widget);
}

void build_create_chat_menu(GtkWidget *main_area)
{
    GtkWidget*  popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //GTK_WINDOW_POPUP
    t_chat_screen.popup_menu = popup_window;
    gtk_widget_set_name(GTK_WIDGET(popup_window), "popup");
	// gtk_window_set_title(GTK_WINDOW(popup_window), "Uchat");
    // gtk_container_set_border_width(GTK_CONTAINER(popup_window), 50);
	gtk_window_set_default_size(GTK_WINDOW(popup_window), 400, 300);
    gtk_window_set_transient_for(GTK_WINDOW(popup_window), GTK_WINDOW(main_window));
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popup_window), TRUE);
	gtk_window_set_position(GTK_WINDOW(popup_window), GTK_WIN_POS_CENTER_ON_PARENT); //GTK_WIN_POS_CENTER
	// gtk_window_set_resizable(GTK_WINDOW(popup_window), FALSE);
	gtk_window_set_decorated(GTK_WINDOW(popup_window), FALSE);
    g_signal_connect(G_OBJECT(popup_window), "focus-out-event", G_CALLBACK(destroy_popup), NULL);

    // GtkWidget *dialog = gtk_dialog_new_with_buttons("Create new chat",
    //                                                 main_window,
    //                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
    //                                                 GTK_STOCK_OK,
    //                                                 GTK_RESPONSE_NONE,
    //                                                 NULL);
    // GtkWidget *create_chat_event = gtk_dialog_get_content_area (GTK_DIALOG (dialog));


    GtkWidget *create_chat_event = gtk_event_box_new();
    // t_chat_screen.popup_menu = create_chat_event;
    // gtk_event_box_set_above_child(GTK_EVENT_BOX(create_chat_event), false);
    // gtk_widget_set_size_request(GTK_WIDGET(create_chat_event), WINDOW_WIDTH, WINDOW_HEIGHT);
    // gtk_fixed_put(GTK_FIXED(main_area), create_chat_event, 0, 0);
	gtk_container_add(GTK_CONTAINER(popup_window), create_chat_event );
    add_class(create_chat_event, "create_chat_event");
    // g_signal_connect(G_OBJECT(create_chat_event), "button_press_event", G_CALLBACK(destroy_create_chat_menu), NULL);

    GtkWidget *create_chat_wrap = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(create_chat_wrap), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(create_chat_wrap), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(create_chat_wrap), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_container_add(GTK_CONTAINER(create_chat_event), create_chat_wrap);

    GtkWidget *create_chat_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_widget_set_name(GTK_WIDGET(create_chat_menu), "Create new group");
    gtk_widget_set_size_request(GTK_WIDGET(create_chat_menu), 400, 300);
    gtk_container_add(GTK_CONTAINER(create_chat_wrap), create_chat_menu);
    add_class(create_chat_menu, "create_chat_menu");

    GtkWidget *menu_title = gtk_label_new("Create new group");
    gtk_widget_set_halign(GTK_WIDGET(menu_title), GTK_ALIGN_CENTER);

    GtkWidget *chat_name_label = gtk_label_new("Group name:");
    gtk_widget_set_halign(GTK_WIDGET(chat_name_label), GTK_ALIGN_START);
    GtkWidget *chat_name_field = gtk_entry_new();
    gtk_widget_set_name(chat_name_field, "chat_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat_name_field), "Group name");

    GtkWidget *chat_name_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(chat_name_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(chat_name_notify_label, "chat_name_notify_label");
    add_class(chat_name_notify_label, "notify_label");

    GtkWidget *create_chat_btn = gtk_button_new_with_label("Create group");
    g_signal_connect(G_OBJECT(create_chat_btn), "clicked", G_CALLBACK(create_chat_btn_click), chat_name_field);
    GtkWidget *create_chat_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(create_chat_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(create_chat_notify_label, "create_chat_notify_label");
	add_class(create_chat_notify_label, "notify_label");

    gtk_box_pack_start(GTK_BOX(create_chat_menu), menu_title, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), create_chat_btn, FALSE, FALSE, 30);

    // gtk_container_add(GTK_CONTAINER(main_area), create_chat_event);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus (popup_window);
}

void popup_create_chat_menu(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen)
{
    if (widget){}
    // if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    build_create_chat_menu((GtkWidget *)chat_screen);
}
