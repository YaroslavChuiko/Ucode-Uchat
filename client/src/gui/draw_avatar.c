#include "../../inc/client.h"

gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    if (widget) {}
    // (void)data;
    int size = (int)data;
    // char* a = utils->current_user->avatar_path;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(utils->current_user->avatar_path, size, size, FALSE, NULL); // get_pixbuf_with_size(a, 34, 34);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    double x = 0,
        y = 0,
        width = size,
        height = size,
        aspect = 1.0,                       /* aspect ratio */
        corner_radius = height / 2.0;       /* and corner curvature radius */
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
