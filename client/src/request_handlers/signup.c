#include "../../inc/client.h"

t_response_code handle_signup_response(const char* response_str) {

    cJSON* json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    cJSON_Delete(json);
    return error_code;   

}


int handle_signup_request(const char* user_name, const char* user_password)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "type", REQ_USR_SIGNUP);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    int error_code = handle_signup_response(response);
            
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);

	return error_code;
}

void build_signup_menu(GtkWidget **main_area)
{
	t_auth_menu.signup_event = gtk_event_box_new();
    // gtk_widget_set_name(GTK_WIDGET(signup_event), "register");
    // gtk_event_box_set_above_child(GTK_EVENT_BOX(t_auth_menu.signup_event), TRUE); // ????
	gtk_box_pack_start(GTK_BOX(*main_area), t_auth_menu.signup_event, false, false, 0);


	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
	gtk_container_add(GTK_CONTAINER(t_auth_menu.signup_event), box); 
    add_class(box, "signup_menu");

    //username box
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *username_label = gtk_label_new("Username:");
	GtkWidget *username_field = gtk_entry_new();
	t_auth_fields.username_field = username_field;
	gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
    // gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_USERNAME);
	g_signal_connect(G_OBJECT(username_field), "focus-out-event", G_CALLBACK(focus_out_username_field), NULL); //password_notify_label
	// g_signal_connect(GTK_ENTRY(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);

    GtkWidget *username_notify_label = gtk_label_new(" ");
	t_auth_fields.username_notify_label = username_notify_label;
	gtk_widget_set_halign(username_notify_label, GTK_ALIGN_START);
	add_class(username_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(username_box), username_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(username_box), username_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(username_box), username_notify_label,FALSE,FALSE,0);
    //

    //password box
    GtkWidget *password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *password_label = gtk_label_new("Password:");
	GtkWidget *password_field = gtk_entry_new();
	t_auth_fields.password_field = password_field;
	gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password");
    // gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_USERNAME);
	gtk_entry_set_visibility(GTK_ENTRY(password_field), false);
	g_signal_connect(G_OBJECT(password_field), "focus-out-event", G_CALLBACK(focus_out_password_field), NULL);
	// g_signal_connect(GTK_ENTRY(password_field), "changed", G_CALLBACK(password_field_change_event), NULL);

    GtkWidget *password_notify_label = gtk_label_new(" ");
	t_auth_fields.password_notify_label = password_notify_label;
	gtk_widget_set_halign(password_notify_label, GTK_ALIGN_START);
	add_class(password_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(password_box), password_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_notify_label,FALSE,FALSE,0);
    //

    //repassword box
    GtkWidget *repassword_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *repassword_label = gtk_label_new("Repeat Password:");
	GtkWidget *repassword_field = gtk_entry_new();
	t_auth_fields.repassword_field = repassword_field;
	gtk_entry_set_placeholder_text(GTK_ENTRY(repassword_field), "Password");
    // gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_USERNAME);
	gtk_entry_set_visibility(GTK_ENTRY(repassword_field), false);
	g_signal_connect(G_OBJECT(repassword_field), "focus-out-event", G_CALLBACK(focus_out_repassword_field), NULL);

	GtkWidget *repassword_notify_label = gtk_label_new(" ");
	t_auth_fields.repassword_notify_label = repassword_notify_label;
	gtk_widget_set_halign(repassword_notify_label, GTK_ALIGN_START);
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
	t_auth_fields.result_notify_label = signup_notify_label;
	gtk_widget_set_halign(signup_notify_label, GTK_ALIGN_CENTER);
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

	gtk_box_pack_start(GTK_BOX(box), username_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box), password_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box), repassword_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box), signup_btn_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box), event_switch_to_login,FALSE,FALSE,0);

	gtk_widget_show_all(t_auth_menu.signup_event);
}
