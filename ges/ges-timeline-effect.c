/* GStreamer Editing Services
 * Copyright (C) 2011 Thibault Saunier <thibault.saunier@collabora.co.uk>
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
 * SECTION: ges-timeline-effect
 * @short_description: An effect in a #GESTimelineLayer
 *
 * The effect will be applied on the sources that have lower priorities 
 * (higher number) between the inpoint and the end of it.
 *
 * In a #GESSimpleTimelineLayer, the priorities will be set for you but if
 * you use another type of #GESTimelineLayer, you will have to handle it
 * yourself.
 */

#include <ges/ges.h>
#include "ges-internal.h"
#include "ges-types.h"

G_DEFINE_TYPE (GESTimelineEffect, ges_timeline_effect,
    GES_TYPE_TIMELINE_OPERATION);

struct _GESTimelineEffectPrivate
{
  gchar *bin_description;
};

enum
{
  PROP_0,
  PROP_BIN_DESCRIPTION,
};

static GESTrackObject *ges_tl_effect_create_track_object (GESTimelineObject
    * self, GESTrack * track);

static void
ges_timeline_effect_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec)
{
  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void
ges_timeline_effect_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec)
{
  GESTimelineEffect *self = GES_TIMELINE_EFFECT (object);

  switch (property_id) {
    case PROP_BIN_DESCRIPTION:
      self->priv->bin_description = g_value_dup_string (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void
ges_timeline_effect_class_init (GESTimelineEffectClass * klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GESTimelineObjectClass *timobj_class = GES_TIMELINE_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (GESTimelineEffectPrivate));

  object_class->get_property = ges_timeline_effect_get_property;
  object_class->set_property = ges_timeline_effect_set_property;

  /**
   * GESTrackEffect:bin_description:
   *
   * The description of the effect bin with a gst-launch-style
   * pipeline description.
   * exemple: videobalance saturation=1.5 hue=+0.5
   */
  g_object_class_install_property (object_class, PROP_BIN_DESCRIPTION,
      g_param_spec_string ("bin-description",
          "bin description",
          "Bin description of the effect",
          NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

  timobj_class->create_track_object = ges_tl_effect_create_track_object;
  timobj_class->need_fill_track = FALSE;
}

static void
ges_timeline_effect_init (GESTimelineEffect * self)
{
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self,
      GES_TYPE_TIMELINE_EFFECT, GESTimelineEffectPrivate);

}

static GESTrackObject *
ges_tl_effect_create_track_object (GESTimelineObject * self, GESTrack * track)
{
  return NULL;
}

/**
* ges_timeline_effect_new_from_bin_desc:
* @bin_description: The gst-launch like bin description of the effect
*
* Creates a new #GESTimelineEffect from the description of the bin. This is
* a convenience method for testing puposes.
*
* Returns: a newly created #GESTimelineEffect, or %NULL if something went
* wrong.
*/
GESTimelineEffect *
ges_timeline_effect_new_from_bin_desc (const gchar * bin_description)
{
  return g_object_new (GES_TYPE_TIMELINE_EFFECT, "bin-description",
      bin_description, NULL);
}
