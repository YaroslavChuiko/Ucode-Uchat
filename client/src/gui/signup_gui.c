#include "../../inc/client.h"

void build_signup_menu(GtkWidget **main_area)
{
	GtkWidget *signup_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
	gtk_box_pack_start(GTK_BOX(*main_area), signup_menu, false, false, 0);
    gtk_widget_set_name(signup_menu, "signup_menu");
    add_class(signup_menu, "signup_menu");

    //username box
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *username_label = gtk_label_new("Username:");
	GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(username_field, "username_field");
	gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
    // gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_USERNAME);
	g_signal_connect(G_OBJECT(username_field), "focus-out-event", G_CALLBACK(focus_out_username_field), NULL); //password_notify_label
	// g_signal_connect(GTK_ENTRY(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);

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
	g_signal_connect(G_OBJECT(password_field), "focus-out-event", G_CALLBACK(focus_out_password_field), NULL);
	// g_signal_connect(GTK_ENTRY(password_field), "changed", G_CALLBACK(password_field_change_event), NULL);

    GtkWidget *password_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(password_notify_label, "password_notify_label");
	add_class(password_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(password_box), password_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_notify_label,FALSE,FALSE,0);
    //

    //repassword box
    GtkWidget *repassword_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *repassword_label = gtk_label_new("Repeat Password:");
	GtkWidget *repassword_field = gtk_entry_new();
    gtk_widget_set_name(repassword_field, "repassword_field");
	gtk_entry_set_placeholder_text(GTK_ENTRY(repassword_field), "Password");
    // gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_USERNAME);
	gtk_entry_set_visibility(GTK_ENTRY(repassword_field), false);
	g_signal_connect(G_OBJECT(repassword_field), "focus-out-event", G_CALLBACK(focus_out_repassword_field), NULL);

	GtkWidget *repassword_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(repassword_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(repassword_notify_label, "repassword_notify_label");
	add_class(repassword_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(repassword_box), repassword_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(repassword_box), repassword_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(repassword_box), repassword_notify_label,FALSE,FALSE,0);
    //

    //SIGNUP_BTN BOX
    GtkWidget *signup_btn_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *signup_btn = gtk_button_new_with_label("Sign up");
	// GTK_WIDGET_UNSET_FLAGS(signup_btn, GTK_CAN_FOCUS); //This code line disables the focus.
	g_signal_connect(signup_btn, "clicked", G_CALLBACK(signup_button_click), main_area);

    GtkWidget *signup_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(signup_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(signup_notify_label, "signup_notify_label");
	add_class(signup_notify_label, "notify_label");

    gtk_box_pack_start(GTK_BOX(signup_btn_box), signup_btn,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(signup_btn_box), signup_notify_label,FALSE,FALSE,0);
    //

	GtkWidget *event_switch_to_login = gtk_event_box_new();
	add_class(event_switch_to_login, "event_switch_auth_menu");
	g_signal_connect(G_OBJECT(event_switch_to_login), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
	g_signal_connect(G_OBJECT(event_switch_to_login), "button_press_event", G_CALLBACK(switch_to_login_menu), main_area);

	GtkWidget *signup_label = gtk_label_new("Login");
	add_class(signup_label, "switch_auth_menu_label");
	gtk_container_add(GTK_CONTAINER(event_switch_to_login), signup_label);

	gtk_box_pack_start(GTK_BOX(signup_menu), username_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(signup_menu), password_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(signup_menu), repassword_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(signup_menu), signup_btn_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(signup_menu), event_switch_to_login,FALSE,FALSE,0);

	gtk_widget_show_all(signup_menu);
}
