/* GStreamer
 *
 * Copyright (C) 2011 Stefan Sauer <ensonic@users.sf.net>
 *
 * gstcontrolbinding.h: Attachment for control sources
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_CONTROL_BINDING_H__
#define __GST_CONTROL_BINDING_H__

#include <gst/gstconfig.h>

#include <glib-object.h>

#include <gst/gstcontrolsource.h>

G_BEGIN_DECLS

#define GST_TYPE_CONTROL_BINDING \
  (gst_control_binding_get_type())
#define GST_CONTROL_BINDING(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_CONTROL_BINDING,GstControlBinding))
#define GST_CONTROL_BINDING_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_CONTROL_BINDING,GstControlBindingClass))
#define GST_IS_CONTROL_BINDING(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_CONTROL_BINDING))
#define GST_IS_CONTROL_BINDING_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_CONTROL_BINDING))
#define GST_CONTROL_BINDING_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_CONTOL_SOURCE, GstControlBindingClass))

typedef struct _GstControlBinding GstControlBinding;
typedef struct _GstControlBindingClass GstControlBindingClass;

/**
 * GstControlBinding:
 *
 * The instance structure of #GstControlBinding.
 */
struct _GstControlBinding {
  GObject parent;

  /*< public >*/
  GParamSpec *pspec;            /* GParamSpec for this property */
  const gchar *name;            /* name of the property */
  GstControlSource *csource;    /* GstControlSource for this property */
  gboolean disabled;
  GValue cur_value, last_value;

  /*< private >*/
  gpointer _gst_reserved[GST_PADDING];
};

/**
 * GstControlBindingClass:
 * @parent_class: Parent class
 *
 * The class structure of #GstControlBinding.
 */

struct _GstControlBindingClass
{
  GObjectClass parent_class;

  /*< private >*/
  gpointer _gst_reserved[GST_PADDING];
};

GType gst_control_binding_get_type (void);

/* Functions */

GstControlBinding * gst_control_binding_new                (GstObject * object, const gchar * property_name,
                                                            GstControlSource * csource);

gboolean            gst_control_binding_sync_values        (GstControlBinding * self, GstObject *object, 
                                                            GstClockTime timestamp, GstClockTime last_sync);
GstControlSource *  gst_control_binding_get_control_source (GstControlBinding * self);
void                gst_control_binding_set_disabled       (GstControlBinding * self, gboolean disabled);
gboolean            gst_control_binding_is_disabled        (GstControlBinding * self);
G_END_DECLS

#endif /* __GST_CONTROL_BINDING_H__ */