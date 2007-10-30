/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __PK_ENGINE_H
#define __PK_ENGINE_H

#include <glib-object.h>
#include <dbus/dbus-glib.h>

#define	PK_DBUS_SERVICE			"org.freedesktop.PackageKit"
#define	PK_DBUS_PATH			"/org/freedesktop/PackageKit"
#define	PK_DBUS_INTERFACE		"org.freedesktop.PackageKit"

G_BEGIN_DECLS

#define PK_TYPE_ENGINE		(pk_engine_get_type ())
#define PK_ENGINE(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), PK_TYPE_ENGINE, PkEngine))
#define PK_ENGINE_CLASS(k)	(G_TYPE_CHECK_CLASS_CAST((k), PK_TYPE_ENGINE, PkEngineClass))
#define PK_IS_ENGINE(o)	 	(G_TYPE_CHECK_INSTANCE_TYPE ((o), PK_TYPE_ENGINE))
#define PK_IS_ENGINE_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k), PK_TYPE_ENGINE))
#define PK_ENGINE_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o), PK_TYPE_ENGINE, PkEngineClass))
#define PK_ENGINE_ERROR		(pk_engine_error_quark ())
#define PK_ENGINE_TYPE_ERROR	(pk_engine_error_get_type ())

typedef struct PkEnginePrivate PkEnginePrivate;

typedef struct
{
	 GObject		 parent;
	 PkEnginePrivate	*priv;
} PkEngine;

typedef struct
{
	GObjectClass	parent_class;
} PkEngineClass;

typedef enum
{
	PK_ENGINE_ERROR_DENIED,
	PK_ENGINE_ERROR_NOT_SUPPORTED,
	PK_ENGINE_ERROR_NO_SUCH_TRANSACTION,
	PK_ENGINE_ERROR_NO_SUCH_FILE,
	PK_ENGINE_ERROR_TRANSACTION_EXISTS_WITH_ROLE,
	PK_ENGINE_ERROR_REFUSED_BY_POLICY,
	PK_ENGINE_ERROR_PACKAGE_ID_INVALID,
	PK_ENGINE_ERROR_SEARCH_INVALID,
	PK_ENGINE_ERROR_FILTER_INVALID,
	PK_ENGINE_ERROR_INPUT_INVALID,
	PK_ENGINE_ERROR_INVALID_STATE,
	PK_ENGINE_ERROR_INITIALIZE_FAILED,
	PK_ENGINE_ERROR_LAST
} PkEngineError;

GQuark		 pk_engine_error_quark			(void);
GType		 pk_engine_error_get_type		(void);
GType		 pk_engine_get_type		  	(void);
PkEngine	*pk_engine_new				(void);
gboolean	 pk_engine_use_backend			(PkEngine	*engine,
							 const gchar	*backend);

gboolean	 pk_engine_get_tid			(PkEngine	*engine,
							 gchar		**tid,
							 GError		**error);
gboolean	 pk_engine_get_updates			(PkEngine	*engine,
							 const gchar	*tid,
							 GError		**error);
gboolean	 pk_engine_search_name			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*filter,
							 const gchar	*search,
							 GError		**error);
gboolean	 pk_engine_search_details		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*filter,
							 const gchar	*search,
							 GError		**error);
gboolean	 pk_engine_search_group			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*filter,
							 const gchar	*search,
							 GError		**error);
gboolean	 pk_engine_search_file			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*filter,
							 const gchar	*search,
							 GError		**error);
gboolean	 pk_engine_get_depends			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 GError		**error);
gboolean	 pk_engine_get_update_detail		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 GError		**error);
gboolean	 pk_engine_get_requires			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 GError		**error);
gboolean	 pk_engine_get_description		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 GError		**error);
gboolean	 pk_engine_get_files			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 GError		**error);
gboolean	 pk_engine_resolve			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*filter,
							 const gchar	*package,
							 GError		**error);
void		 pk_engine_rollback			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*transaction_id,
							 DBusGMethodInvocation *context,
							 GError		**error);
void		 pk_engine_refresh_cache		(PkEngine	*engine,
							 const gchar	*tid,
							 gboolean	 force,
							 DBusGMethodInvocation *context,
							 GError		**error);
gboolean	 pk_engine_get_old_transactions		(PkEngine	*engine,
							 const gchar	*tid,
							 guint		 number,
							 GError		**error);
void		 pk_engine_update_system		(PkEngine	*engine,
							 const gchar	*tid,
							 DBusGMethodInvocation *context,
							 GError		**error);
void		 pk_engine_remove_package		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 gboolean	 allow_deps,
							 DBusGMethodInvocation *context,
							 GError		**error);
void		 pk_engine_install_package		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 DBusGMethodInvocation *context,
							 GError		**error);
void		 pk_engine_install_file			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*full_path,
							 DBusGMethodInvocation *context,
							 GError		**error);
void		 pk_engine_update_package		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*package_id,
							 DBusGMethodInvocation *context,
							 GError		**error);

gboolean	 pk_engine_get_transaction_list		(PkEngine	*engine,
							 gchar		***transaction_list,
							 GError		**error);
gboolean	 pk_engine_get_status			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	**status,
							 GError		**error);
gboolean	 pk_engine_get_role			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	**status,
							 const gchar	**package_id,
							 GError		**error);
gboolean	 pk_engine_cancel			(PkEngine	*engine,
							 const gchar	*tid,
							 GError		**error);
gboolean	 pk_engine_get_backend_detail		(PkEngine	*engine,
							 gchar		**name,
							 gchar		**author,
							 GError		**error);
gboolean	 pk_engine_get_actions			(PkEngine	*engine,
							 gchar		**actions,
							 GError		**error);
gboolean	 pk_engine_get_groups			(PkEngine	*engine,
							 gchar		**groups,
							 GError		**error);
gboolean	 pk_engine_get_filters			(PkEngine	*engine,
							 gchar		**filters,
							 GError		**error);
guint		 pk_engine_get_seconds_idle		(PkEngine	*engine);

gboolean	 pk_engine_get_progress			(PkEngine	*engine,
							 const gchar	*tid,
							 guint		*percentage,
							 guint		*subpercentage,
							 guint		*elapsed,
							 guint		*remaining,
							 GError		**error);
gboolean	 pk_engine_get_package			(PkEngine	*engine,
							 const gchar	*tid,
							 gchar		**package,
							 GError		**error);

/* repo stuff */
gboolean	 pk_engine_get_repo_list		(PkEngine	*engine,
							 const gchar	*tid,
							 GError		**error);
void		 pk_engine_repo_enable			(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*repo_id,
							 gboolean	 enabled,
							 DBusGMethodInvocation *context,
							 GError		**error);
void		 pk_engine_repo_set_data		(PkEngine	*engine,
							 const gchar	*tid,
							 const gchar	*repo_id,
							 const gchar	*parameter,
							 const gchar	*value,
							 DBusGMethodInvocation *context,
							 GError		**error);

G_END_DECLS

#endif /* __PK_ENGINE_H */
