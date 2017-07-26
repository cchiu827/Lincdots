******************************************************************
**	Link Info v7.h Include										**
**	Copyright © 2003-2010 by Imagine That, Inc.					**
**	All rights reserved.										**
**	Created by Anthony Nastasi									**
******************************************************************



******************************************************************
** Created 2003
**	Modified:
**	Date	Release		By			Description
**
**	1/17/11	8.0.2		PHT			Added new cWHAT_HAPPENED constant for table properties modified
**
******************************************************************
**	1/12/11	8.0.2		DJK			Added DBFieldGetProperties() input parameters

//DILinkInfo() and DILinkUpdateInfo()
constant cWHICH_LINK_TYPE	is 0;
constant cWHICH_DB_INDEX	is 1;
constant cWHICH_TABLE_INDEX	is 2;
constant cWHICH_COLUMN		is 3;
constant cWHICH_ROW			is 4;
constant cWHAT_HAPPENED		is 5;
constant cHOW_MANY_ROWS_CHANGED	is 6;
constant cDIALOG_ITEM_ID 		is 7;			// ID of dialog item that is linked
constant cWHICH_BLOCK_ORIGIN_OF_CHANGE 	is 8;			// Block number at the origin of the change only in DILinkUpdateInfo function
constant cWHICH_READ_ONLY	is 10;
	

//DILinkInfo() and DILinkUpdateInfo():  return values for cWHICH_LINK_TYPE 
constant cWHICH_ISNO_LINK	is 0;
constant cWHICH_IS_GA		is 1;
constant cWHICH_IS_DB		is 2;
constant cWHICH_IS_DA		is 3;


//DILinkUpdateInfo():  return values for cWHAT_HAPPENED
constant cDATA_CHANGED					is 1;
constant cFIELD_INSERTED				is 2;
constant cFIELD_DELETED					is 3;
constant cFIELD_RENAMED					is 4;
constant cRECORD_INSERTED				is 5;
constant cRECORD_DELETED				is 6;
constant cTABLE_DELETED					is 7;		//works of db tables, ga's and dynamic arrays
constant cTABLE_RENAMED					is 8;		//works of db tables, ga's and dynamic arrays
constant cDB_DELETED					is 9;
constant cDB_RENAMED					is 10;
constant cLINK_CREATED					is 11;
constant cLINK_FLAGS_MODIFIED			is 12;
constant cLINK_CLEARED					is 13;
constant cDB_REPLACED					is 14;		//DBDatabaseImport() can replace a database
constant cTABLE_RESIZED					is 15;		//for global arrays and dynamic arrays only
constant cTABLE_INSERTED				is 16;		//only when a database table gets inserted
//constant cDB_INSERTED			is 17;		//only when a database gets inserted
	//ajn- commented out after discussion with steve and bob as the application currently doesn't support this and actually may never support it.constant cFIELD_PROPERTIES_MODIFIED		is 17;		
constant cFIELD_MOVED					is 18;		//if user used mouse to move a field in the db viewer
constant cFIELD_PROPERTIES_RECORD_ID_MODIFIED		is 21;
constant cTABLE_PROPERTIES_MODIFIED		is 20;		
	

//DILinkUpdateString() input parameters
constant cWHICH_NAME_DIALOG_ITEM is 0;
constant cWHICH_NAME_SOURCE is 1;



//DILinkModify() input parameters
constant READ_ONLY is 0;
constant INTIT_MSGS is 1;
constant SIM_MSGS is 2;
constant FINAL_MSGS is 3;
constant ANY_MSGS is 4;
constant SHOW_FIELD_NAMES is 11;

**	1/12/11	8.0.2		DJK			Added DBFieldGetProperties() input parameters
//DBFieldGetProperties() input parameters
constant cFIELD_TYPE is 1;
constant cFIELD_DECIMALS is 2;
constant cFIELD_UNIQUE is 3;
constant cFIELD_READONLY is 4;
constant cFIELD_INVISIBLE is 5;
constant cFIELD_ID is 6;
















