/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003-2007 XMMS2 Team
 *
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */




#include "xmms/xmms_defs.h"
#include "xmms/xmms_xformplugin.h"
#include "xmmsc/xmmsc_util.h"
#include "xmms/xmms_util.h"
#include "xmms/xmms_log.h"

#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Type definitions
 */

/*
 * Function prototypes
 */

/*static gboolean xmms_m3u_read_playlist (xmms_transport_t *transport, guint playlist_id);*/
static gboolean xmms_m3u_plugin_setup (xmms_xform_plugin_t *xform_plugin);
static gboolean xmms_m3u_init (xmms_xform_t *xform);
static gboolean xmms_m3u_browse (xmms_xform_t *xform, const gchar *url, xmms_error_t *error);
static void xmms_m3u_destroy (xmms_xform_t *xform);

/*
 * Plugin header
 */
XMMS_XFORM_PLUGIN ("m3u",
                   "M3U reader",
                   XMMS_VERSION,
                   "Playlist parser for m3u's",
                   xmms_m3u_plugin_setup);

static gboolean
xmms_m3u_plugin_setup (xmms_xform_plugin_t *xform_plugin)
{
	xmms_xform_methods_t methods;

	XMMS_XFORM_METHODS_INIT (methods);
	methods.init = xmms_m3u_init;
	methods.destroy = xmms_m3u_destroy;
	methods.browse = xmms_m3u_browse;

	xmms_xform_plugin_methods_set (xform_plugin, &methods);

	xmms_xform_plugin_indata_add (xform_plugin,
	                              XMMS_STREAM_TYPE_MIMETYPE,
	                              "audio/x-mpegurl",
	                              NULL);

	xmms_magic_extension_add ("audio/x-mpegurl", "*.m3u");

	return TRUE;
}

static gboolean
xmms_m3u_init (xmms_xform_t *xform)
{
	xmms_xform_outdata_type_add (xform,
	                             XMMS_STREAM_TYPE_MIMETYPE,
	                             "application/x-xmms2-playlist-entries",
	                             XMMS_STREAM_TYPE_END);
	return TRUE;
}

/*
 * Member functions
 */

static gboolean
xmms_m3u_browse (xmms_xform_t *xform,
                 const gchar *url,
                 xmms_error_t *error)
{
	gchar line[XMMS_XFORM_MAX_LINE_SIZE];
	xmms_error_t err;
	gboolean extm3u = FALSE;
	gchar *tmp;
	const gchar *d;

	g_return_val_if_fail (xform, FALSE);

	xmms_error_reset (&err);

	if (!xmms_xform_read_line (xform, line, &err)) {
		XMMS_DBG ("Error reading m3u-file");
		return FALSE;
	}

	if (strcmp (line, "#EXTM3U") == 0) {
		extm3u = TRUE;
		if (!xmms_xform_read_line (xform, line, &err)) {
			return FALSE;
		}
	}

	d = xmms_xform_get_url (xform);

	do {
		if (line[0] == '#') {
			if (!xmms_xform_read_line (xform, line, &err)) {
				return FALSE;
			}
		}

		tmp = xmms_build_playlist_url (d, line);
		xmms_xform_browse_add_symlink (xform, NULL, tmp);

		g_free (tmp);

	} while (xmms_xform_read_line (xform, line, &err));

	return TRUE;
}

static void
xmms_m3u_destroy (xmms_xform_t *xform)
{
}

