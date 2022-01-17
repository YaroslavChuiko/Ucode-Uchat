#include "../inc/client.h"

void destroy_create_group_menu(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (widget)
    {
    }
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

void create_group_btn_click(GtkWidget *widget, gpointer group_name_field)
{
    if (widget)
    {
    };

    char *group_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget *)group_name_field)));

    if (!mx_strcmp(group_name, ""))
    {
        remove_class((GtkWidget *)group_name_field, "field_success");
        add_class((GtkWidget *)group_name_field, "field_error");
        return;
    }

    int error_code = handle_create_chat_request(group_name);
    handle_create_chat_error_code(error_code, (GtkWidget *)group_name_field);
    if (error_code == R_SUCCESS)
    {
        create_chat_list_item(group_name);
        gtk_widget_destroy(t_chat_screen.popup_menu);
    }
}

void destroy_popup(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen)
{
    if (widget)
    {
    }
    gtk_widget_destroy(widget);
}

void build_create_group_menu(GtkWidget *main_area)
{
    GtkWidget*  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    t_chat_screen.popup_menu = window;
    gtk_widget_set_name(GTK_WIDGET(window), "main_window");
	gtk_window_set_title(GTK_WINDOW(window), "Uchat");
    // gtk_container_set_border_width(GTK_CONTAINER(window), 50);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS); //GTK_WIN_POS_CENTER
	// gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    g_signal_connect(G_OBJECT(window), "focus-out-event", G_CALLBACK(destroy_popup), NULL);



    GtkWidget *create_group_event = gtk_event_box_new();
    // t_chat_screen.popup_menu = create_group_event;
    // gtk_event_box_set_above_child(GTK_EVENT_BOX(create_group_event), false);
    // gtk_widget_set_size_request(GTK_WIDGET(create_group_event), WINDOW_WIDTH, WINDOW_HEIGHT);
    // gtk_fixed_put(GTK_FIXED(main_area), create_group_event, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), create_group_event );
    add_class(create_group_event, "create_group_event");
    // g_signal_connect(G_OBJECT(create_group_event), "button_press_event", G_CALLBACK(destroy_create_group_menu), NULL);

    GtkWidget *create_group_wrap = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(create_group_wrap), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(create_group_wrap), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(create_group_wrap), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_container_add(GTK_CONTAINER(create_group_event), create_group_wrap);

    GtkWidget *create_group_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_widget_set_name(GTK_WIDGET(create_group_menu), "Create new group");
    gtk_widget_set_size_request(GTK_WIDGET(create_group_menu), 400, 300);
    gtk_container_add(GTK_CONTAINER(create_group_wrap), create_group_menu);
    add_class(create_group_menu, "create_group_menu");

    GtkWidget *menu_title = gtk_label_new("Create new group");
    gtk_widget_set_halign(GTK_WIDGET(menu_title), GTK_ALIGN_CENTER);

    GtkWidget *group_name_label = gtk_label_new("Group name:");
    gtk_widget_set_halign(GTK_WIDGET(group_name_label), GTK_ALIGN_START);
    GtkWidget *group_name_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(group_name_field), "Group name");

    GtkWidget *signup_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(signup_notify_label, GTK_ALIGN_CENTER);
    add_class(signup_notify_label, "notify_label");

    GtkWidget *create_group_btn = gtk_button_new_with_label("Create group");
    g_signal_connect(G_OBJECT(create_group_btn), "clicked", G_CALLBACK(create_group_btn_click), group_name_field);

    gtk_box_pack_start(GTK_BOX(create_group_menu), menu_title, true, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_group_menu), group_name_label, true, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_group_menu), group_name_field, true, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_group_menu), create_group_btn, true, FALSE, 0);

    // gtk_container_add(GTK_CONTAINER(main_area), create_group_event);

    gtk_widget_show_all(window);
}

void popup_create_group_menu(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen)
{
    if (widget)
    {
    }
    // if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    build_create_group_menu((GtkWidget *)chat_screen);
}

void build_leftbar(GtkWidget *chat_screen)
{
    GtkWidget *left_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_widget_set_hexpand(left_bar, TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(left_bar), LEFT_BAR_W, LEFT_BAR_H);
    // gtk_fixed_put(GTK_FIXED(chat_screen), left_bar, 0, 0);
    gtk_grid_attach(GTK_GRID(chat_screen), left_bar, 0, 0, 1, 1);
    // gtk_box_pack_start(GTK_BOX(chat_screen), left_bar, FALSE, FALSE, 0);
    add_class(left_bar, "left_bar");

    // search block
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    // gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
    add_class(left_bar, "search_block");

    GtkWidget *search_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search");
    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    //

    // chat list
    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    add_class(scrollable_wrap, "scrollable_wrap");
    // gtk_widget_set_size_request(scrollable_wrap, LEFT_BAR_W, LEFT_BAR_H - 104);
    GtkWidget *chat_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    t_chat_screen.chat_list = chat_list;
    add_class(chat_list, "chat_list");
    // gtk_widget_set_size_request(chat_list, LEFT_BAR_W, LEFT_BAR_H - 104);
    gtk_widget_set_tooltip_text(chat_list, "chat_list");
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chat_list);
    // gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(scrollable_wrap)));
    //

    GtkWidget *event_switch_to_login = gtk_event_box_new();
    add_class(event_switch_to_login, "event_switch_auth_menu");
    g_signal_connect(G_OBJECT(event_switch_to_login), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "button_press_event", G_CALLBACK(popup_create_group_menu), chat_screen);
    GtkWidget *signup_label = gtk_label_new("Create new group");
    add_class(signup_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(event_switch_to_login), signup_label);

    gtk_box_pack_start(GTK_BOX(left_bar), search_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), event_switch_to_login, FALSE, FALSE, 0);
}

void build_rightbar(GtkWidget *chat_screen)
{
    GtkWidget *chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(chat, TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(chat), 920, 720); // 75%
    // gtk_fixed_put(GTK_FIXED(chat_screen), chat, 360, 0);
    gtk_grid_attach(GTK_GRID(chat_screen), chat, 1, 0, 2, 1);
    // gtk_box_pack_start(GTK_BOX(chat_screen), chat, FALSE, FALSE, 0);
    add_class(chat, "chat");

    // GtkWidget *grid = gtk_grid_new();
    // gtk_container_add(GTK_CONTAINER(chat), grid);

    // GtkWidget *messaging_label = gtk_label_new("Select a chat to start messaging");
    // gtk_grid_attach(GTK_GRID(grid), messaging_label, 0, 0, 1, 1);


    GtkWidget *messaging_label = gtk_label_new("Select a chat to start messaging");
    gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chat), messaging_label, FALSE, FALSE, 0);
    gtk_widget_set_vexpand(messaging_label, TRUE);
    gtk_widget_set_hexpand(messaging_label, TRUE);
}

void build_chat_screen(GtkWidget **main_area)
{
    // GtkWidget *chat_screen = gtk_fixed_new();
    // gtk_container_add(GTK_CONTAINER(*main_area), chat_screen);
    // gtk_widget_set_size_request(chat_screen, WINDOW_WIDTH, WINDOW_HEIGHT);

    // GtkWidget* chat_screen = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // gtk_container_add(GTK_CONTAINER(*main_area), chat_screen);
    // gtk_widget_set_size_request(chat_screen, WINDOW_WIDTH, WINDOW_HEIGHT);

    GtkWidget *grid = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);
    // gtk_fixed_put(GTK_FIXED(chat_screen), grid, 0, 0);
    gtk_container_add(GTK_CONTAINER(*main_area), grid);


    build_leftbar(grid);
    build_rightbar(grid);

    // gtk_grid_attach(GTK_GRID(grid), left_bar, 0, 0, 1, 1);
    // gtk_grid_attach(GTK_GRID(grid), chat, 1, 0, 1, 1);

    gtk_widget_show_all(grid);
}
