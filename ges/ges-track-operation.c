/* GStreamer Editing Services
 * Copyright (C) 2009 Edward Hervey <edward.hervey@collabora.co.uk>
 *               2009 Nokia Corporation
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

/**
 * SECTION:ges-track-operation
 * @short_description: Base Class for effects and overlays
 */

#include "ges-internal.h"
#include "ges-track-object.h"
#include "ges-track-operation.h"

G_DEFINE_ABSTRACT_TYPE (GESTrackOperation, ges_track_operation,
    GES_TYPE_TRACK_OBJECT);

struct _GESTrackOperationPrivate
{
  /* Dummy variable */
  void *nothing;
};

static gboolean
ges_track_operation_create_gnl_object (GESTrackObject * object)
{
  GESTrackOperationClass *klass = NULL;
  GESTrackOperation *self = NULL;
  GstElement *child = NULL;
  GstElement *gnlobject;

  self = GES_TRACK_OPERATION (object);
  klass = GES_TRACK_OPERATION_GET_CLASS (self);

  gnlobject = gst_element_factory_make ("gnloperation", NULL);

  if (klass->create_element) {
    child = klass->create_element (self);

    if (G_UNLIKELY (!child)) {
      GST_ERROR ("create_element returned NULL");
      return TRUE;
    }

    gst_bin_add (GST_BIN (gnlobject), child);
    self->element = child;
  }

  object->gnlobject = gnlobject;

  return TRUE;
}

static void
ges_track_operation_class_init (GESTrackOperationClass * klass)
{
  GESTrackObjectClass *track_class = GES_TRACK_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (GESTrackOperationPrivate));

  track_class->create_gnl_object = ges_track_operation_create_gnl_object;
  klass->create_element = NULL;
}

static void
ges_track_operation_init (GESTrackOperation * self)
{
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self,
      GES_TYPE_TRACK_OPERATION, GESTrackOperationPrivate);
}
