******************************************************************
**	Utilities v9.h												**
**	Copyright © 2008-2014 by Imagine That, Inc.					**
**	All rights reserved.										**
**	Created by Anthony Nastasi									**
******************************************************************
// this is a test by Chiu


******************************************************************
** Created 2008
**	Modified:
**	Date	Release		By			Descripton
**
******************************************************************


//  Contains general purpose functions and message handlers used by several blocks
//
//	Modified:
//		10/14/10 	8.0.1 		PHT 	Replaced spaces with underscores in block help file names to support a workaround of a Microsoft bug when oipening multiple help windows concurrently
//		1/14/11		8.0.2		AJN		had a conflict in the "on HelpButton" message handler.  If a block has this Utilities v8.h file include and if
//										and if a chm file has not been attached to this block, then the user gets an error message when they click
//										on the help button instead of getting the block's help window.
//		4/6/11		8.0.2		AJN		had to shorten the name of the CHM help files because the Mac has a limitation of 31 characters
//		4/7/11		8.0.2		AJN		if ExtendSim fails to open the CHM help file, resort to regular old block help- it's better than nothing.


//	Warning messages
constant	HLP_CHM_MAC_WARNING_MESSAGE is "This block's help uses a compiled html file. To view this file, 1) Download xCHM from <http://sourceforge.net/projects/xchm/>, 2) Run it, select command in File menu to make it the app for .CHM files.";
constant	HLP_CHP_WIN_WARNING_MESSAGE is "This block's help uses a compiled html file. To view this file, download and install HTML Help Workshop from the Microsoft Download Center.";
constant	HLP_CHM_SUCCESS_RESULT is 0;






integer BlockNumberGet(string blkName)
{
	
	integer		i;
	integer		me;
	integer LocationInfo[4];	
	me = MyBlockNumber();
	
	for (i=0;i<NumBlocks();i++)
		if (GetBlockTypePosition(me, 
								 LocationInfo) == BT_EXECUTABLE)
			if (blockname(i) == blkName)
				return(i);
	
	return(-1);	

}//integer BlockNumberGet(string blkName)


on HelpButton
{

	integer me;
	integer result;
	integer	pos, len;		**	10/14/10		8.0.1		PHT
	string myBlockName;
	string helpFolderPath;
	string helpFilePathName;
	
	me = MyBlockNumber();
	
	if(platformwindows)
		{
		helpFolderPath = GetAppPath() + "help\";
		}
	else
		{
		helpFolderPath = GetAppPath() + "help:";
		}
//
**	10/14/10		8.0.1		PHT
**
**	Replace spaces with underscores
//
	myBlockName = BlockName(me);
	pos = 0;
	len = StrLen(myBlockName);
	do
	{
		if (strPart(myBlockName, pos, 1) == " ")
			myBlockName = StrReplace(myBlockName, pos, 1, "_");
		pos++;
	} while (pos < len);

//	helpFilePathName = helpFolderPath + myBlockName + " block help.chm";
//	helpFilePathName = helpFolderPath + myBlockName + "_block_help.chm";	**	10/14/10		8.0.1		PHT
	helpFilePathName = helpFolderPath + myBlockName + "_b_help.chm";		//	4/6/11

	result = CallHelp (helpFilePathName, 1, 1, 1);		//open the .chm help file

	//1/14/11
	/*
	if(result != HLP_CHM_SUCCESS_RESULT)
		{
		if (platformwindows)
			{
			userError(HLP_CHP_WIN_WARNING_MESSAGE);
			}
		else
			{
			userError(HLP_CHM_MAC_WARNING_MESSAGE);
			}
		}
	*/

	if(result == HLP_CHM_SUCCESS_RESULT)				//4/7/11
		{
		abort;		//stop extendSim from opening the block's help dialog
		}
	else //if(result != HLP_CHM_SUCCESS_RESULT)
		{
		//do nothing because if there's a problem showing the CHM file, show the block's help window instead.
		}
	
		
}//on HelpButton


