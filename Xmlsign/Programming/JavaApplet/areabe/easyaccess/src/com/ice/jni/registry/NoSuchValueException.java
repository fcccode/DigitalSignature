/*
** Java native interface to the Windows Registry API.
** Copyright (c) 1997 by Timothy Gerard Endres
** 
** This program is free software.
** 
** You may redistribute it and/or modify it under the terms of the GNU
** General Public License as published by the Free Software Foundation.
** Version 2 of the license should be included with this distribution in
** the file LICENSE, as well as License.html. If the license is not
** included	with this distribution, you may find a copy at the FSF web
** site at 'www.gnu.org' or 'www.fsf.org', or you may write to the
** Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139 USA.
**
** THIS SOFTWARE IS PROVIDED AS-IS WITHOUT WARRANTY OF ANY KIND,
** NOT EVEN THE IMPLIED WARRANTY OF MERCHANTABILITY. THE AUTHOR
** OF THIS SOFTWARE, ASSUMES _NO_ RESPONSIBILITY FOR ANY
** CONSEQUENCE RESULTING FROM THE USE, MODIFICATION, OR
** REDISTRIBUTION OF THIS SOFTWARE. 
** 
*/

package com.ice.jni.registry;

/**
 * This exception is used to indicate that no such key exists in the registry.
 *
 * @version $Revision: 1.1.2.1 $
 * @author Timothy Gerard Endres,
 *    <a href="mailto:time@ice.com">time@ice.com</a>.
 */

public class
NoSuchValueException extends RegistryException
	{
	static public final String	RCS_ID = "$Id: NoSuchValueException.java,v 1.1.2.1 2003/12/04 19:59:26 avdron Exp $";
	static public final String	RCS_REV = "$Revision: 1.1.2.1 $";
	static public final String	RCS_NAME = "$Name:  $";

	public
	NoSuchValueException()
		{
		super();
		}

	public
	NoSuchValueException( String msg )
		{
		super( msg, Registry.ERROR_FILE_NOT_FOUND );
		}

	public
	NoSuchValueException( String msg, int regErr )
		{
		super( msg, regErr );
		}

	}


