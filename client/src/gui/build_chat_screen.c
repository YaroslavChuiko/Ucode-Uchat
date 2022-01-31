#include "../../inc/client.h"

void build_leftbar(GtkWidget *chat_screen)
{
    GtkWidget *left_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(left_bar), LEFT_BAR_W, WINDOW_HEIGHT);
    gtk_grid_attach(GTK_GRID(chat_screen), left_bar, 0, 0, 1, 1);
    add_class(left_bar, "leftbar");

    //header block
    GtkWidget *header_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    add_class(header_block, "leftbar_header_block");
    
    GtkWidget *header_label = gtk_label_new("Messages");
    add_class(header_label, "leftbar_header_label");

    GtkWidget *create_new_chat_btn = gtk_event_box_new();
    add_class(create_new_chat_btn, "event_switch_auth_menu");
    g_signal_connect(G_OBJECT(create_new_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_new_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_new_chat_btn), "button_press_event", G_CALLBACK(popup_create_chat_menu), chat_screen);
    GtkWidget *create_chat_label = gtk_label_new("Create new chat");
    add_class(create_chat_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(create_new_chat_btn), create_chat_label);
    
    gtk_box_pack_start(GTK_BOX(header_block), header_label, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(header_block), create_new_chat_btn, FALSE, FALSE, 0);
    //

    // search block
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
    add_class(search_block, "search_block");

    GtkWidget *search_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search");
    gtk_widget_set_name(search_field, "global_search_field");
    // g_signal_connect(G_OBJECT(search_field), "activate", G_CALLBACK(search_field_enter_pressed), NULL);
	g_signal_connect(G_OBJECT(search_field), "changed", G_CALLBACK(search_field_change_event), NULL);

    GtkWidget *clear_field_btn = gtk_button_new_with_label("X");
    gtk_widget_set_size_request(GTK_WIDGET(clear_field_btn), 40, 40);
    // gtk_widget_grab_focus(clear_field_btn);
	g_signal_connect(G_OBJECT(clear_field_btn), "clicked", G_CALLBACK(clear_search_field), search_field);

    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(search_block), clear_field_btn, false, false, 0);
    //

    // chatlist
    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrollable_wrap, "chatlist_scrollable_wrap");
    add_class(scrollable_wrap, "scrollable_wrap");

    GtkWidget *chatlist = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(chatlist, "chatlist");
    add_class(chatlist, "chatlist");
    // gtk_widget_set_tooltip_text(chatlist, "chatlist");
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chatlist);
    // gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(scrollable_wrap)));
    //

    GtkWidget *btn_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    add_class(btn_block, "btn_block");

    GtkWidget *logout_btn = gtk_event_box_new();
    add_class(logout_btn, "event_switch_auth_menu");
    gtk_widget_set_halign(GTK_WIDGET(logout_btn), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(logout_btn), GTK_ALIGN_START);
    g_signal_connect(G_OBJECT(logout_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(logout_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(logout_btn), "button_press_event", G_CALLBACK(logout_btn_click), NULL);
    GtkWidget *logout_label = gtk_label_new("Log out");
    add_class(logout_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(logout_btn), logout_label);
    gtk_box_pack_start(GTK_BOX(btn_block), logout_btn, FALSE, FALSE, 0);

    GtkWidget *change_password_btn = gtk_event_box_new();
    add_class(change_password_btn, "event_switch_auth_menu");
    gtk_widget_set_halign(GTK_WIDGET(change_password_btn), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(change_password_btn), GTK_ALIGN_START);
    g_signal_connect(G_OBJECT(change_password_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_password_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    // g_signal_connect(G_OBJECT(change_password_btn), "button_press_event", G_CALLBACK(build_change_password_window), NULL);
    GtkWidget *change_password_label = gtk_label_new("Change password");
    add_class(change_password_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(change_password_btn), change_password_label);
    gtk_box_pack_start(GTK_BOX(btn_block), change_password_btn, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(left_bar), header_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), search_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), btn_block, false, false, 0);
}

void build_start_messaging_label()
{
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");

    clear_container(chat_container);

    GtkWidget *messaging_label = gtk_label_new("Select a chat to start messaging");
    gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(messaging_label, TRUE);
    gtk_widget_set_hexpand(messaging_label, TRUE);
    add_class();

    gtk_box_pack_start(GTK_BOX(chat_container), messaging_label, FALSE, FALSE, 0);

    gtk_widget_show_all(chat_container);
}

void build_rightbar(GtkWidget *chat_screen)
{
    GtkWidget *chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(chat, TRUE);
    gtk_widget_set_vexpand(chat, TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(chat), WINDOW_WIDTH - LEFT_BAR_W, WINDOW_HEIGHT);
    gtk_grid_attach(GTK_GRID(chat_screen), chat, 1, 0, 2, 1);
    gtk_widget_set_name(chat, "chat");
    add_class(chat, "chat");

    // build_start_messaging_label();
}

void build_chat_screen()
{
	GtkWidget* main_area = get_widget_by_name_r(main_window, "main_area");
    GtkWidget *grid = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);
    gtk_container_add(GTK_CONTAINER(main_area), grid);

    build_leftbar(grid);
    build_rightbar(grid);

    update_chatlist();

    gtk_widget_show_all(grid);
}
