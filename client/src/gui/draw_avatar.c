#include "../../inc/client.h"

gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    if (widget) {}
    int avatar_color = (int)data;

    char *path = "client/data/img/user_avatars/avatar";
    char *tmp = mx_strjoin(path, mx_itoa(avatar_color+1));
    path = mx_strjoin(tmp, ".png");
    mx_strdel(&tmp);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 27, 27, FALSE, NULL); // get_pixbuf_with_size(a, 34, 34);
    mx_strdel(&path);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0;
    double y = 0;
    double width = 27;
    double height = 27;
    double aspect = 1.0;                       /* aspect ratio */
    double corner_radius = height / 2.0;       /* and corner curvature radius */
    double radius = corner_radius / aspect;
    double degrees = 3.14159265358979 / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_fill(cr);
    return FALSE;
}

gboolean draw_chat_avatar(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    if (widget) {}
    int avatar_color = (int)data;

    char *path = "client/data/img/chat_avatars/avatar";
    char *tmp = mx_strjoin(path, mx_itoa(avatar_color+1));
    path = mx_strjoin(tmp, ".png");
    mx_strdel(&tmp);
    
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 42, 42, FALSE, NULL);
    mx_strdel(&path);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0;
    double y = 0;
    double width = 42;
    double height = 42;
    double aspect = 1.0;
    double corner_radius = height / 2.0;
    double radius = corner_radius / aspect;
    double degrees = 3.14159265358979 / 180.0;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    cairo_fill(cr);
    return FALSE;
}
