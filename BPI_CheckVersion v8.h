******************************************************************
**	CheckVersion v7.h Include									**
**	Copyright © 2003-2010 by Imagine That, Inc.					**
**	All rights reserved.										**
**	Created by Anthony Nastasi									**
******************************************************************



******************************************************************
** Created 2003
**	Modified:
**	Date	Release		By			Description
**
******************************************************************


procedure CheckVersionExec()
{

	integer executiveBlockNumber;
	string execDialogItem;
	
	executiveBlockNumber = SysGlobalInt23;
	
	execDialogItem = GetDialogVariable(executiveBlockNumber, "ExtendSim_lbl", 0, 0);
	
	if(execDialogItem != "ExtendSim")
		{
		UserError("Please replace your current Executive block with the Executive found in the Item library.");
		abort;
		}

}//procedure ExecCheckVersion()