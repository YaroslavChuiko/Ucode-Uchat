#include "../../inc/client.h"

void set_current_user(t_user** user, const cJSON* user_json) {

    *user = malloc(sizeof(t_user));
    const cJSON* id_json = cJSON_GetObjectItem(user_json, "id");
    const cJSON* name_json = cJSON_GetObjectItemCaseSensitive(user_json, "username");
    const cJSON* pass_json = cJSON_GetObjectItemCaseSensitive(user_json, "password");

    (*user)->user_id = cJSON_IsNumber(id_json) ? id_json->valueint : -1;
    (*user)->name = cJSON_IsString(name_json) ? mx_strdup(name_json->valuestring) : NULL;
    (*user)->password = cJSON_IsString(pass_json) ? mx_strdup(pass_json->valuestring) : NULL;

}

t_response_code handle_login_response(const char* response_str) {

    if (response_str == NULL)
        return R_INVALID_INPUT;

    cJSON* json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    if (error_code != R_SUCCESS) {
        cJSON_Delete(json);
        return error_code;
    }

    pthread_mutex_lock(&utils->lock);
    set_current_user(&utils->current_user, json);
    pthread_mutex_unlock(&utils->lock);

    if (utils->current_user->user_id == -1 ||
        !utils->current_user->name || 
        !utils->current_user->password) {
            return R_JSON_FAILURE; 
    }

    cJSON_Delete(json);
    return R_SUCCESS;

}

t_response_code handle_login_request(const char* user_name, const char* user_password) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGIN);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    
    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_login_response(response);
    
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);

    return error_code;
}

void build_login_menu(GtkWidget **main_area)
{
	t_auth_menu.login_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	gtk_box_pack_start(GTK_BOX(*main_area), t_auth_menu.login_menu, true, false, 0);
    add_class(t_auth_menu.login_menu, "login_menu");

    //username box
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
	GtkWidget *username_label = gtk_label_new("Username:");
	GtkWidget *username_field = gtk_entry_new();
	t_auth_fields.username_field = username_field;
	gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
	// g_signal_connect(G_OBJECT(username_field), "focus-out-event", G_CALLBACK(focus_out_username_field), NULL);

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
	// g_signal_connect(G_OBJECT(password_field), "focus-out-event", G_CALLBACK(focus_out_password_field), NULL);

    GtkWidget *password_notify_label = gtk_label_new(" ");
	t_auth_fields.password_notify_label = password_notify_label;
	gtk_widget_set_halign(password_notify_label, GTK_ALIGN_START);
	add_class(password_notify_label, "notify_label");

	gtk_box_pack_start(GTK_BOX(password_box), password_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_field,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(password_box), password_notify_label,FALSE,FALSE,0);
    //

    //LOGIN_BTN BOX
    GtkWidget *login_btn_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *login_btn = gtk_button_new_with_label("Login");
	g_signal_connect(login_btn, "clicked", G_CALLBACK(login_button_click), main_area);
    GtkWidget *login_notify_label = gtk_label_new(" ");
	t_auth_fields.result_notify_label = login_notify_label;
	gtk_widget_set_halign(login_notify_label, GTK_ALIGN_CENTER);
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
	g_signal_connect(G_OBJECT(event_switch_to_signup), "button_press_event", G_CALLBACK(switch_to_signup_menu), main_area);

	GtkWidget *signup_label = gtk_label_new("Sign up");
	add_class(signup_label, "switch_auth_menu_label");
	gtk_container_add(GTK_CONTAINER(event_switch_to_signup), signup_label);
	gtk_box_pack_start(GTK_BOX(text_box), event_switch_to_signup,FALSE,FALSE,0);
    //

	gtk_box_pack_start(GTK_BOX(t_auth_menu.login_menu), username_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(t_auth_menu.login_menu), password_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(t_auth_menu.login_menu), login_btn_box,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(t_auth_menu.login_menu), text_box,FALSE,FALSE,0);
	
	gtk_widget_show_all(t_auth_menu.login_menu);
}
