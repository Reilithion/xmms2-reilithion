/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003	Peter Alm, Tobias Rundstr�m, Anders Gustafsson
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




#ifndef __XMMS_DECODER_INT_H__
#define __XMMS_DECODER_INT_H__

#include "xmms/transport.h"
#include "xmms/output.h"
#include "xmms/effect.h"
#include "xmms/error.h"

/*
 * Private function prototypes -- do NOT use in plugins.
 */

xmms_decoder_t * xmms_decoder_new (xmms_core_t *core);
gboolean xmms_decoder_open (xmms_decoder_t *decoder,
			    xmms_playlist_entry_t *entry);
xmms_core_t * xmms_decoder_core_get (xmms_decoder_t *decoder);
void xmms_decoder_start (xmms_decoder_t *decoder, 
			xmms_transport_t *transport, 
			xmms_effect_t *effect, 
			xmms_output_t *output);
gboolean xmms_decoder_seek_ms (xmms_decoder_t *decoder, guint milliseconds, xmms_error_t *err);
gboolean xmms_decoder_seek_samples (xmms_decoder_t *decoder, guint samples, xmms_error_t *err);
void xmms_decoder_wait (xmms_decoder_t *decoder);

#endif /* __XMMS_DECODER_INT_H__ */
