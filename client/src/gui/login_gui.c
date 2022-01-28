#include "../../inc/client.h"

void build_login_menu()
{
	GtkWidget* main_area = get_widget_by_name_r(main_window, "main_area");

	GtkWidget *login_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	gtk_box_pack_start(GTK_BOX(main_area), login_menu, true, false, 0);
    gtk_widget_set_name(login_menu, "login_menu");
    add_class(login_menu, "login_menu");

    //username box
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
	GtkWidget *username_label = gtk_label_new("Username:");
	GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(username_field, "username_field");
	gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
	// g_signal_connect(G_OBJECT(username_field), "focus-out-event", G_CALLBACK(focus_out_username_field), NULL);

    GtkWidget *username_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(username_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(username_notify_label, "username_notify_label");
	add_class(username_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(username_box), username_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(username_box), username_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(username_box), username_notify_label,FALSE,FALSE,0);
    //

    //password box
    GtkWidget *password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
	GtkWidget *password_label = gtk_label_new("Password:");
	GtkWidget *password_field = gtk_entry_new();
    gtk_widget_set_name(password_field, "password_field");
	gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password");
    // gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_USERNAME);
	gtk_entry_set_visibility(GTK_ENTRY(password_field), false);

    GtkWidget *password_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(password_notify_label, "password_notify_label");
	add_class(password_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(password_box), password_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_notify_label,FALSE,FALSE,0);
    //

    //LOGIN_BTN BOX
    GtkWidget *login_btn_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *login_btn = gtk_button_new_with_label("Login");
	g_signal_connect(login_btn, "clicked", G_CALLBACK(login_button_click), NULL);
    
    GtkWidget *login_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(login_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(login_notify_label, "login_notify_label");
	add_class(login_notify_label, "notify_label");

    gtk_box_pack_start(GTK_BOX(login_btn_box), login_btn,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(login_btn_box), login_notify_label,FALSE,FALSE,0);
    //

    //text box
    GtkWidget *text_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *label = gtk_label_new("Don't have an account yet? ");
	gtk_box_pack_start(GTK_BOX(text_box), label,FALSE,FALSE,0);

	GtkWidget *event_switch_to_signup = gtk_event_box_new();
	add_class(event_switch_to_signup, "event_switch_auth_menu");
	g_signal_connect(G_OBJECT(event_switch_to_signup), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_signup), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
	g_signal_connect(G_OBJECT(event_switch_to_signup), "button_press_event", G_CALLBACK(switch_to_signup_menu), NULL);

	GtkWidget *signup_label = gtk_label_new("Sign up");
	add_class(signup_label, "switch_auth_menu_label");
	gtk_container_add(GTK_CONTAINER(event_switch_to_signup), signup_label);
	gtk_box_pack_start(GTK_BOX(text_box), event_switch_to_signup,FALSE,FALSE,0);
    //

	gtk_box_pack_start(GTK_BOX(login_menu), username_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(login_menu), password_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(login_menu), login_btn_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(login_menu), text_box,FALSE,FALSE,0);
	
	gtk_widget_show_all(login_menu);
}
