******************************************************************
**	Equation v7.h Include										**
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
//	2/13/08		7.0.2		DJK			Added error message if Send GlobalProofStr to Proof is checked an there is no Proof Control block
//	9/12/08		7.0.4		AJN			added the function oVars_InitVals()
//	10/13/08	7.0.4		AJN			added auto check for executive's attrib settings.
//	10/21/08	7.0.5		AJN			added update of the DB Index iVars to CheckData
//	10/24/08	7.0.5		AJN			in places where it's possible, switch from iVars_Types_str[] to iVars_Types_Int[] because it's faster
//	10/24/08	7.0.5		AJN			in places where it's possible, switch from oVars_Types_str[] to oVars_Types_Int[] because it's faster
//	10/28/08	7.0.5		AJN			found a typo in EQ_OnDialogClick
//	10/29/08	7.0.5		AJN			added expandRecords_chk
//	10/30/08	7.0.5		AJN			added EQ_OpenDeveloperReference_btn
//	11/04/08	7.0.5		AJN			altered how records are getting registered
//	11/14/08	7.0.5		AJN			for db index vars- added updates to iVars_IndexesForDBIndexVars[] in on LinkStructure
//	12/16/08	7.0.5		AJN			added calls to iVarsIn_ConIsWhichVarUpdate()
//	2/5/09		7.0.5		AJN			added more intelligent condition for when to update connector labels at beginning of sim
//	3/31/09		7.0.6		AJN			added another arg to EQ_Calc() specifying whether static variables should be restored.  in certain cases
//										like when Equation (I) is controlling a downstream blocker, EQ_Calc can get called via "on oVarsOut" more than 
//										once per item because the downstream blocker can send more than one message per item out its select connector.
//										consequently, static variables can incorrectly be changed more than once.  this is why we restore in this case.
//	4/21/09		7.0.6		AJN			change was made to make iVarsIn_GetConInfo() and oVarsOut_GetConInfo() more robust
//	4/22/09		7.0.6		AJN			was calling ConnectorLabelsSet() with the third arg incorrectly. was using "numRow" instear of "numCons"
//	4/23/08		7.0.6		AJN			fixed bug with using "open developer reference" on max
//	6/19/09		8.0.0		AJN			replaced use of iVars_AttribColumnIndexes[] and oVars_AttribColumnIndexes[] with iVars_Types_Int[] and oVars_Types_Int[]
//	6/25/09		8.0.0		AJN			broke the "db index" input var type out into 4 variables
//	8/21/09		7.0.6		AJN			Added code to support calculation of next event in a bunch of different places.
//	8/25/09		4.0.6		AJN			fixed bug with test equation button
//	9/30/09		7.0.6		AJN			fixed problem name tracking. old models originally had string31's instead of string63's
//	1/14/10		8.0.0		AJN			in checkdata changed iVarsIn_IsConnected to iVarsIn_NumBlocksConnected and oVarsOut_IsConnected 
//										to oVarsOut_NumBlocksConnected. needed more than just TRUE/FALSE if connected
//	1/15/10		8.0.0		AJN			fixed a bug in how the next event time was being calculated
//	1/21/10		8.0.0		AJN			fixed bug in queue equation. if initiating msg came in on an iVarsIn connector, we were unecessarily sending a msg back to that initiating block
//	3/25/10		8.0.0		AJN			added iVarsIn_WhichConGotMsg
//	4/8/10		8.0.0		AJN			added support for include files being located in same folder as model
//	6/7/10		8.0.0		AJN			moved call to iVars_DBNT_GarbageCollection and oVars_DBNT_GarbageCollection in EQ_OnDataTableResize.  was getting an array out of bounds when 
//										user deleted a row from either the iVars or oVars table if the deleted row contained a variable of a type that warranted DBNT.
//	6/14/10		8.0.0		AJN			moved a bunch of stuf from CheckData and InitSim to PreCheckData because in v8 we added ability to calc the equation as early as CheckData
//	6/22/10		8.0.0		AJN			only need to show updated static variable values if iVars_ttbl is showing
//	6/24/10		8.0.0		AJN			added addtional checking before replacing an input or output variable with the array name.
//	7/19/10		8.0.1		AJN			tried to make iVarsIn_ConLabelsSet() and oVarsOut_ConLabelsSet() more efficient
//	7/27/10		8.0.1		PHT			Changed Advanced Resource DB writes to use new RESERVED API functions
//	8/4/10		8.0.1		AJN			in "on CreateBlock", the calc when for input cons was getting set to "after zero time event" which is wrong.
//	8/5/10		8.0.1		AJN			in BlockReceive0, we were not conditionally posting the next future event.  why is this a bug?  well notice
//										in "on iVarsIn" and "on oVarsOut" a future event is posted if the user chose to "calc immidiately".  however,
//										if the user chose to calc after a current event, then we need to post the current event in BlockReceive0.
//	8/16/10		8.0.1		AJN			the DBNT list were not being updated when user copied or deleted the rows in the iVars or oVars tables.
//	8/17/10		8.0.1		AJN			make sure calling "DB" functions with correct indexes because 8.0.1 app will throw an error msg and stop sim on some DB functions if indexes are out of range
//	10/12/10	8.0.1		AJN			Name tracking issue: using wrong counter index to cycle through iVars_DBCoords[i] and oVars_DBCoords[i].
//	10/28/10	8.0.1		AJN			had to make a fix to mimicking message emulation
//	11/17/10	8.0.2		AJN			added a new input variable called "QEQ static item value".
//	11/29/10	8.0.2		AJN			in "LinkContent" there was a nested for loop using the same counter variable ("i") as the superior loop
//	1/19/11		8.0.2		AJN			added call to EquationCompileSetSaticArray() in EQ_Compile() so that users can declare variables in include files.
//	3/30/11		8.0.2		AJN			moved call to iVars_DBNT_UpdateDBCoordsArray() and oVars_DBNT_UpdateDBCoordsArray() to earlier in CheckData because it was too late if equation was getting calculate in CheckData
//	3/31/11		8.0.2		AJN			moved the code to update iVars_IndexesForDBIndexVars[] from iVars_GetVals() to iVars_DBNT_UpdateDBCoordsArray() so that any time we
//										update iVars_DBCoords[] we also update iVars_IndexesForDBIndexVars[].  we had a situation where the two arrays were getting out of sync
//	4/16/11		8.0.2		AJN			added new input variable called "next calc event time"
//	4/18/11		8.0.2		AJN			fixed a bug with the check for duplicate variable names
//	4/19/11		8.0.2		AJN			had to write some exception handling code because of legacy issues. the problem stems from how we determine what type of output variable the 
//										user chose.  it's done using StrFind() because after v7 was released, the variable names were changed.  anyway, this works fine except for
//										the case where two different variable types share the same root name like "attribute" and "DBQS attribute".
//	4/20/11		8.0.2		AJN			added convertDateTimeData_chk
//	4/26/11		8.0.2		AJN			modified EQ_OnLinkStructure() to handle the care where a field gets moved
//	5/10/11		8.0.2		AJN			make sure a static input variable's name is also not used as an output variable name
//	5/20/11		8.0.2		AJN			added call to oVars_TableSetup() in Final Calc so that we're guaranteed updated results being posted.  Scenario Manager needs this.
//	5/24/11		8.0.2		AJN			fixed problem with test equation button-  if have a string attrib input var, must convert the string value into an index
//	6/7/11		8.0.2		AJN			created EQ_DBIndexCheck() and added call to it in CheckData
//	6/15/11		8.0.2		AJN			fixed bug with deleting rows in iVars and oVars tables.
//	7/5/11		8.0.2		AJN			fixed bug with animating the input and output connectors-  animation objects allocated to iVarsIn cons were sometimes inadvertantly getting deleted
//										when CW_IVarsIn_Animate() and CW_OVarsOut_Animate() were getting called in succession-  both functions deleted existing animation objects at the top
//										of their functions and then re-added new anim objects. could get into a situation where a newly added animation object for iVarsIn had the same object
//										ID number as an oVarsOut animation object.
//	7/6/11		8.0.2		AJN			same as the bug fix on 7/5/11 except it was done for CMC_IVarsIn_Animate() and CMC_OVarsOut_Animate()
//	7/21/11		8.0.2		AJN			added new function called EQ_CheckSeeds() to resolve problems with equations calculating a random value before InitSim
//	7/29/11		8.0.2		AJN			connectors were not being animated properly when icon was in reverse view



//*****************************************************
//*****************************************************
//Start EQE (Equation Editor) functions
//***************************************************


procedure EQE_CreateEditorFile()
{

	integer me;
	integer i;
	integer fileNumber;
	integer fileDoesExist;
	integer numRowsInEquation;
	string arrayText;
	integer arrayTextLength;
	string nextRowArrayText;
	string lineString;
	integer lineLength;
	string CR;						//Carriage Return
	string LF;						//Line Feed
	string HT;						//Horizontal Tab
	integer crPosi;
	integer lfPosi;
	integer numChars;
	integer tabStart;

	me = MyBlockNumber();
	
	if(EQE_EditorIsOpen == FALSE)
		{
	
		//create editorName
		MakeArray(EQE_Name, 1);
		EQE_Name[0] = "Equation Editor [" + me + "].h";
		
		//create a pathName for the editor file
		MakeArray(EQE_PathName, 1);
		if(PlatformWindows)
			EQE_PathName[0] = GetUserPath() + "Extensions\" + EQE_Name[0];
		else
			EQE_PathName[0] = GetUserPath() + "Extensions:" + EQE_Name[0];
		
		//if file already exists, delete it so that we can create a blank one from scratch
		fileDoesExist = FileExists(EQE_PathName[0]);
		if(fileDoesExist == TRUE)
			{
			FileDelete(EQE_PathName[0]);
			}
		
		//create the equation editor file
		fileNumber = FileNew(EQE_PathName[0], FALSE);
		
		numRowsInEquation = GetDimension(EQ_EquationText);

		//remove all occurrences of line feed characters from the equation
		LF = StrPutAscii(10);		//line feed
		for(i=0; i<numRowsInEquation; i++)
			{
			do
				{
				lfPosi = StrFind(EQ_EquationText[i], LF, FALSE, FALSE);
				if(lfPosi >= 0)
					{
					EQ_EquationText[i] = StrReplace(EQ_EquationText[i], lfPosi, 1, "");
					}
				}while (lfPosi >= 0);
			}
		
		//map text from the equation array into equation editor
		CR = StrPutAscii(13);		//carriage return
		HT = StrPutAscii(9);		//horizontal tab
		for(i=0; i<numRowsInEquation; i++)
			{
			
			arrayText = EQ_EquationText[i];								//the next chunk of text from the equation array
			arrayTextLength = StrLen(arrayText);
			while(arrayTextLength > 0)
				{
				
				crPosi = StrFind(arrayText, CR, FALSE, FALSE);
				if(crPosi >= 0)
					{
					numChars = crPosi;									//leave off the CR
					lineString = StrPart(arrayText, 0, numChars);		//the next line of text to add to the equation editor

					//set up for next pass through while
					arrayText = StrPart(arrayText, numChars+1, 255);	//remove lineString + CR from arrayText.  note: 255 used to ensure we get everything
					arrayTextLength = StrLen(arrayText);
					}
					
				else //if no CR,...
					{
					//...,then grab remaning text from current row
					lineString = arrayText;
					
					//force exit out of while loop
					arrayTextLength = 0;													

					//if there is another row in equation array,...
					if(i < numRowsInEquation - 1)
						{
						//...then define how many chars we want to remove from the next row of equation array...
						crPosi = StrFind(EQ_EquationText[i+1], CR, FALSE, FALSE);
						if(crPosi >= 0)
							numChars = crPosi;							//leave off the CR
						else
							numChars = StrLen(EQ_EquationText[i+1]);
						
						//...and add text from next row of equation array to lineString
						lineString += StrPart(EQ_EquationText[i+1], 0, numChars);

						//remove the chunk of text that we're using from next row in equation array
						EQ_EquationText[i+1] = StrPart(EQ_EquationText[i+1], numChars+1, 255);		//"numChars+1":  leave out the CR if one exists.
						}
					}
					
				//replace every instance of "5 spaces" with a tab character
				do
					{
					tabStart = StrFind(lineString, "     ", FALSE, FALSE);
					if(tabStart >= 0)
						{
						lineString = StrReplace(lineString, tabStart, 5, HT);
						}
					}
				while(tabStart >= 0);
				
				//write lineString to the equation editor file	
				FileWrite(fileNumber, lineString, "@", TRUE);		//"@" to write CR at the end of the text we're writing
									
				}//while(arrayTextLength > 0)
			
			}//for(i=0; i<numRowsInEquation; i++)
		
		//close the file after having created it.
		FileClose(fileNumber);
		
		}//if(EQE_EditorIsOpen == FALSE)

}//procedure EQE_CreateEditorFile()


procedure EQE_CloseEditor()
{
	
	integer me;
	integer fileNumber;
	integer endOfFile;
	string lineString;
	integer lineLength;
	integer currPosi;
	string HT;				//Horizontal Return
	integer htPosi;
	
	me = MyBlockNumber();
	
	//save and close the equation editor
	SaveTopDocAs(EQE_PathName[0], FALSE);	//FALSE = close synchronously
	ExecuteMenuCommand(4);
	
	//************************************************************************
	//START: open the editor file and copy contents over into the equation
	
		HT = StrPutAscii(9);			//get the Horizontal Tab symbol;

		//blank out the dynamic text dialog
		MakeArray(EQ_EquationText, 1);
		StrReplaceDynamic(EQ_EquationText, 0, 255, "");
		
		//open the equation editor file
		fileNumber = FileOpen(EQE_PathName[0], FALSE);
		
		//copy text from the equation editor file to the equation dynamic text
		endOfFile = FileEndOfFile(fileNumber);
		currPosi = 0;
		while(endOfFile == FALSE)
			{
			lineString = FileRead(fileNumber, "@") + StrPutAscii(13);		//"@" unused character to force grab to end of line character
			
			//replace every instance of a tab character with 5 spaces
			do
				{
				htPosi = StrFind(lineString, HT, FALSE, FALSE);
				if(htPosi >= 0)
					{
					lineString = StrReplace(lineString, htPosi, 1, "     ");
					}
				}
			while(htPosi >= 0);
			
			lineLength = StrLen(lineString);
			StrReplaceDynamic(EQ_EquationText, currPosi, lineLength, lineString);
			currPosi = currPosi + lineLength;
			endOfFile = FileEndOfFile(fileNumber);
			}//while(endOfFile == FALSE)
			
		//close the equation editor file
		FileClose(fileNumber);
		
	//END:  open the equation editor and copy contents over into the equation
	//************************************************************************
	
	//update settings
	EQE_EditorIsOpen = FALSE;
	DITitleSet(me, "EQE_btn", "Open / Close Equation Editor");
	DisableDialogItem("equation_dtxt", FALSE);

	EQE_DeleteEditorFile();

}//procedure EQE_CloseEditor()


procedure EQE_DeleteEditorFile()
{

	FileDelete(EQE_PathName[0]);
	
	DisposeArray(EQE_Name);
	DisposeArray(EQE_PathName);
	
}//procedure EQE_DeleteEditorFile()


on EQE_btn
{
	
	integer me;
	integer openSuccess;
	
	me = MyBlockNumber();
	
	if(EQE_EditorIsOpen == FALSE)
		{
		//create the editor file
		EQE_CreateEditorFile();
		
		//open the editor file
		openSuccess = OpenExtendFile(EQE_PathName[0]);
		if(openSuccess == 0)
			{
			EQE_EditorIsOpen = TRUE;
			//DITitleSet(me, "EQE_btn", "Close equation editor");
			}
		else
			{
			EQE_EditorIsOpen = FALSE;
			//DITitleSet(me, "EQE_btn", "Open Equation Editor");
			}
			
		//tell ExtendSim that we want to receive an "IncludeFileClose" message when user closes this window
		IncludeFileEditor(EQE_Name[0], me);
		DisposeArray(EQE_Name);
		
		DisableDialogItem("equation_dtxt", TRUE);
		}
		
	else if(EQE_EditorIsOpen == TRUE)
		{
		OpenExtendFile(EQE_PathName[0]);	//bring the editor to the front
		EQE_CloseEditor();
		}

}//on EQE_btn


// This message occurs when the user closes the equation editor window
on IncludeFileClose
{
	
	EQE_CloseEditor();
	
}//on IncludeFileClose


//*****************************************************
//End EQE (Equation Editor) functions
//*****************************************************
//*****************************************************





//*****************************************************
//*****************************************************
//Start Include file  functions
//*****************************************************


on Incl_chk
{

	integer me;
	
	me = MyBlockNumber();
	
	EQ_DialogItemsShow();
	
	Incl_TableResize(0);
		
	Incl_TableSetup();
	
	if(Incl_chk)
		{
		incl_PrototypesDisplay_dtxt = DynamicTextArrayNumber(incl_PrototypesDisplay_DA); //points "incl_PrototypesDisplay_dtxt" to "incl_PrototypesDisplay_DA".
		}
	else
		{
		//cleanup
		DisposeArray(incl_FileNames_DA);
		DisposeArray(incl_PathNames);
		DisposeArray(incl_Prototypes_DA);
		DisposeArray(incl_ModifiedFileDates);
		
		//blank out the dynamic text dialog
		MakeArray(incl_PrototypesDisplay_DA, 1);
		StrReplaceDynamic(incl_PrototypesDisplay_DA, 0, 255, "");
		MakeArray(incl_PrototypesDisplay_DA, 0);
		}
		
}//on Incl_chk


on Incl_FileNames_ttbl
{

	integer i;
	integer numRows;
	integer numCols;
	string pathName;
	integer userResponse;
	integer setVal;
	integer returnCode;
	string includeFileName;
	string modelName;
	string modelPath;
	string modelPathFileName;
	integer includeWithModel;
	string extensionsPath;
	string extensionsPathFileName;
	integer includeInExtensions;
	
	
	StopDataTableEditing();
	SetDataTableSelection("Incl_FileNames_ttbl", -2, -2, -2, -2, FALSE);

	numRows = GetDimension(Incl_FileNames_ttbl);
	numCols = GetDimension(Incl_FileNames_ttbl);
	
	if(colClicked == INCL_OPEN_BTN_COL)
		{
		if(rowClicked >= 0  && rowClicked < numRows)
			{
			//4/8/10
			//**************************************
			
			includeFileName = Incl_FileNames_ttbl[rowClicked][INCL_NAME_COL];
			
			//get model path info
			modelName = GetModelName();
			modelPath = GetModelPath(modelName);
			if(modelPath != "")			//if model has been saved
				{
				if(PlatformWindows)
					{
					modelPath = modelPath + "\";
					}
				else
					{
					modelPath = modelPath + ":";
					}
				
				modelPathFileName = modelPath + includeFileName;
				includeWithModel = FileExists(modelPathFileName);
				}
			else
				{
				modelPath = "";
				modelPathFileName = "";
				includeWithModel = FALSE;
				}
			
			//get extensions path info
			if(PlatformWindows)
				extensionsPath = GetUserPath() + "Extensions\";
			else
				extensionsPath = GetUserPath() + "Extensions:";
			extensionsPathFileName = extensionsPath + includeFileName;
			includeInExtensions = FileExists(extensionsPathFileName);
			
			//if include in both places then we have a problem
			if(includeWithModel == TRUE  &&  includeInExtensions)
				{
				UserError("The include file named ' " + includeFileName + "' exists both in the Extensions folder and in the model folder.  This is not allowed.  Please remove one of them.");
				}
			else if(includeWithModel == TRUE)
				{
				returnCode = OpenExtendFile(modelPathFileName);
				if(returnCode >= 0)
					{
					incl_PathNames[rowClicked] = modelPathFileName;
					}
				else
					{
					UserError("The include file named ' " + includeFileName + "' could not be opened");
					}
				}
			else if(includeInExtensions == TRUE)
				{
				returnCode = OpenExtendFile(extensionsPathFileName);
				if(returnCode >= 0)
					{
					incl_PathNames[rowClicked] = extensionsPathFileName;
					}
				else
					{
					UserError("The include file named ' " + includeFileName + "' could not be opened");
					}
				}
			else
				{
				UserError("The include file named ' " + includeFileName + "' could not be found.  It is is required to be located either in the Extensions folder or in the same folder as the model.");
				}
				
			//****************************************
			}
		}
	else if(colClicked == INCL_SELECT_COL  &&  rowClicked <= -1)
		{
		userResponse = CreatePopupMenu("Select all;Select none;Toggle", "", 1);
		
		if(userResponse == 3)	//if toggle
			{
			for(i=0; i<numRows; i++)
				{
				if(Incl_FileNames_ttbl[i][INCL_SELECT_COL] == TRUE)
					Incl_FileNames_ttbl[i][INCL_SELECT_COL] = FALSE;
				else 
					Incl_FileNames_ttbl[i][INCL_SELECT_COL] = TRUE;
				}
			}
		else
			{
			if(userResponse == 1)
				setVal = 1;
			else
				setVal = 0;
			for(i=0; i<numRows; i++)
				Incl_FileNames_ttbl[i][INCL_SELECT_COL] = setVal;
			}
		}
		
}//on Incl_FileNames_ttbl


on Incl_Create_btn
{
	
	integer success;
	integer nameLength;
	integer fileDoesExist;
	integer numRows;
	string extensionsPath;
	string fileName;
	string pathName;
	string lastTwoChars;
	integer fileNumber;
	
	fileName = UserParameter("Please enter the name of the new include file", "");
	
	if(fileName != "")			//if user did not click cancel
		{
		//make sure file name has a ".h" extension
		nameLength = StrLen(fileName);
		lastTwoChars = StrPart(fileName, nameLength-2, 2);
		if(lastTwoChars != ".h")
			{
			fileName = fileName + ".h";
			}
		
		//set the path
		if(PlatformWindows)
			pathName = GetUserPath() + "Extensions\" + fileName;
		else
			pathName = GetUserPath() + "Extensions:" + fileName;
		
		//does the file already exist?
		fileDoesExist = FileExists(pathname);
		if(fileDoesExist == FALSE)
			{
			
			//create the include file, add the header and then close it
			fileNumber = FileNew(pathname, FALSE);
			
			//if include file was successfully created, then...
			if(fileNumber > 0)
				{
				//...add the prototypes header to the new include
				FileWrite(fileNumber, "//**********************************", "@", TRUE);
				FileWrite(fileNumber, "//START: Equation Include Prototypes", "@", TRUE);
				FileWrite(fileNumber, "", "@", TRUE);
				FileWrite(fileNumber, "", "@", TRUE);
				FileWrite(fileNumber, "", "@", TRUE);
				FileWrite(fileNumber, "", "@", TRUE);
				FileWrite(fileNumber, "//END: Equation Include Prototypes", "@", TRUE);
				FileWrite(fileNumber, "//**********************************", "@", TRUE);
				
				//...close file
				FileClose(fileNumber);

				//...then put new include file into the list of includes for this equation
				numRows = GetDimension(Incl_FileNames_ttbl) + 1;
				Incl_TableResize(numRows);
				incl_PathNames[numRows-1] = pathName;
				Incl_FileNames_ttbl[numRows-1][INCL_NAME_COL] = fileName;
				
				//...open the new include file
				OpenExtendFile(pathName);
				}
			else
				{
				UserError("Include file was not created.  Please check that the intended name is valid.");
				}
			
			}
		
		else //if file exists
			{
			UserError("This include file already exists.  File not created.");
			}
		}
	
}//Incl_Create_btn


on Incl_Add_btn
{

	integer fileNumber;
	string pathName;
	integer numRows;
	
	if(PLATFORMWINDOWS)
		{
		fileNumber = FileOpen("*.h", "Please select an include file");
		}
	else
		{
		fileNumber = FileOpen("", "Please select an include file");
		}
	
	if(fileNumber > 0)	//if user chose a legit file
		{
		//setup the table by adding a new row to the bottom for the newly added include file
		numRows = GetDimension(Incl_FileNames_ttbl) + 1;
		Incl_TableResize(numRows);
	
		//store newly added include
		pathName = FileGetPathName(fileNumber);
		incl_PathNames[numRows-1] = pathName;
		Incl_FileNames_ttbl[numRows-1][INCL_NAME_COL] = FileNameFromPathName(pathName);
		FileClose(fileNumber);
		}
		
}//on Incl_Add_btn


on Incl_Remove_btn
{

	integer i, j;
	integer numRows;
	integer numDeletes;
	
	numRows = GetDimension(Incl_FileNames_ttbl);
	numDeletes = 0;
	
	//first, blank out all the rows that need to be deleted
	for(i=0; i<numRows; i++)
		{
		if(Incl_FileNames_ttbl[i][INCL_SELECT_COL] == TRUE)
			{
			Incl_FileNames_ttbl[i][INCL_SELECT_COL] = "";
			Incl_FileNames_ttbl[i][INCL_NAME_COL] = "";
			incl_PathNames[i] = "";
			numDeletes++;
			}
		}
		
	//second, delete the blanked out rows
	for(i=0; i<numRows; i++)
		{
		if(Incl_FileNames_ttbl[i][INCL_NAME_COL] == "")
			{
			for(j=i; j<numRows-1; j++)
				{
				Incl_FileNames_ttbl[j][INCL_SELECT_COL] = Incl_FileNames_ttbl[j+1][INCL_SELECT_COL];
				Incl_FileNames_ttbl[j][INCL_NAME_COL] = Incl_FileNames_ttbl[j+1][INCL_NAME_COL];
				incl_PathNames[j] = incl_PathNames[j+1];
				}
			}
		}
		
	//resize Incl_FileNames_ttbl
	Incl_TableResize(numRows-numDeletes);

}//on Incl_Remove_btn


procedure Incl_BuildPrototypesArray()
{

	integer i;
	integer numIncludes;
	real fileIsSelected;
	integer fileNumber;
	integer currLine;
	integer endOfFile;
	integer stopWhile;
	string lineString;
	integer lineLength;
	integer foundSemiColon;
	integer foundProcedure;
	integer foundReal;
	integer foundInteger;
	integer numPrototypes;

	numIncludes = GetDimension(Incl_FileNames_ttbl);
	DisposeArray(incl_Prototypes_DA);
	
	//cycle through each row in Incl_FileNames_ttbl
	for(i=0; i<numIncludes; i++)
		{
		//is the ith include file selected?
		fileIsSelected = StrToReal(Incl_FileNames_ttbl[i][INCL_SELECT_COL]);
		if(fileIsSelected > 0)
			{
			//open the ith selected include file
			fileNumber = FileOpen(incl_PathNames[i], FALSE);
			if(fileNumber != FALSE)								//if include file was successfully opened
				{
				//cycle through the prototypes section of the ith include
				currLine = -1;
				stopWhile = FALSE;
				while(stopWhile != TRUE)
					{
					lineString = FileRead(fileNumber, "@");
					currLine++;
					
					if(currLine == 0  &&  lineString != "//**********************************")
						{
						stopWhile = TRUE;
						}
					else if(currLine == 1  &&  lineString != "//START: Equation Include Prototypes")
						{
						stopWhile = TRUE;
						}
					else if(lineString == "//END: Equation Include Prototypes")
						{
						stopWhile = TRUE;
						}
					else
						{
						//check to see if currLine contains a prototype definition
						lineLength = StrLen(lineString);
						foundSemiColon = StrFind(lineString, ";", FALSE, FALSE);
						if(foundSemiColon > -1)
							{
							foundProcedure = StrFind(lineString, "procedure", FALSE, FALSE);
							foundReal = StrFind(lineString, "real", FALSE, FALSE);
							foundInteger = StrFind(lineString, "integer", FALSE, FALSE);
							
							if(foundProcedure > -1  ||  foundReal > -1  ||  foundInteger > -1)
								{
								numPrototypes = GetDimension(incl_Prototypes_DA) + 1;
								MakeArray(incl_Prototypes_DA, numPrototypes);
								incl_Prototypes_DA[numPrototypes-1] = lineString;
								}
							
							}
						}
					
					//if at the end of the file break loop
					if( FileEndOfFile(fileNumber) == TRUE )
						{
						stopWhile = TRUE;
						}
					}
				}

			FileClose(fileNumber);
			
			}//if(fileIsSelected > 0)
		
		}//for(i=0; i<numIncludes; i++)
		
}//procedure Incl_BuildPrototypesArray()


on incl_Prototypes_pop
{

	integer i;
	integer numPrototypes;
	integer whichFunction;
	string chosenFunction;
	integer length;
	
	numPrototypes = GetDimension(incl_Prototypes_DA);
	if(numPrototypes > 0)
		{
		//blank out the dynamic text dialog
		MakeArray(incl_PrototypesDisplay_DA, 0);
		MakeArray(incl_PrototypesDisplay_DA, 1);
		StrReplaceDynamic(incl_PrototypesDisplay_DA, 0, 255, "");
		
		//put the chosen function into the display area which is a dynamic text dialog item
		chosenFunction = incl_Prototypes_DA[incl_Prototypes_pop-1];
		length = StrLen(chosenFunction);
		StrReplaceDynamic(incl_PrototypesDisplay_DA, 0, 0, chosenFunction);
		}
	
}//on incl_Prototypes_pop


procedure Incl_TableSetup()
{

	integer me;
	integer i;
	integer numCols;
	integer positionArray[4];
	string columnHeading;
	
	me = MyBlockNumber();

	DTGrowButton(me, "Incl_FileNames_ttbl", FALSE);
	DTHideLinkButton(me, "Incl_FileNames_ttbl", TRUE);
	SetDTRowStart(me, "Incl_FileNames_ttbl", 1);
	
	//make sure the frame for Incl_FileNames_ttbl is wide enough
	DIPositionGet(me, "Incl_FileNames_ttbl", positionArray);
	DIPositionSet(me, "Incl_FileNames_ttbl", positionArray[0], positionArray[1], positionArray[2], positionArray[3]+500);	//set max width of Incl_FileNames_ttbl frame
	
	//set column widths
	SetDTColumnWidth(me, "Incl_FileNames_ttbl", INCL_OPEN_BTN_COL+1, 35, TRUE);
	SetDTColumnWidth(me, "Incl_FileNames_ttbl", INCL_SELECT_COL+1, 42, TRUE);
	SetDTColumnWidth(me, "Incl_FileNames_ttbl", INCL_NAME_COL+1, 200, TRUE);

	//set column tags
	DTColumnTagSet(MyBlockNumber(), "Incl_FileNames_ttbl", INCL_OPEN_BTN_COL, TAG_BUTTON, 0, "", "");
	DTColumnTagSet(MyBlockNumber(), "Incl_FileNames_ttbl", INCL_SELECT_COL, TAG_HEAD_TAG_POPUP, 0, "", "");
	DTColumnTagSet(MyBlockNumber(), "Incl_FileNames_ttbl", INCL_SELECT_COL, TAG_CHECKBOX, 0, "", "");

}//procedure Incl_TableSetup()
	

procedure Incl_TableResize(integer numRows)
{
	
	integer i;
	integer me;
	integer lastNumRows;
	
	me = MyBlockNumber();
	lastNumRows = GetDimension(Incl_FileNames_ttbl);

	DILinkMsgs(FALSE);
	MakeArray(incl_FileNames_DA, numRows);
	MakeArray(incl_PathNames, numRows);
	MakeArray(incl_ModifiedFileDates, numRows);
	DynamicDataTable(me, "Incl_FileNames_ttbl", incl_FileNames_DA);
	DILinkMsgs(TRUE);

	//if more rows were added to the table
	if(lastNumRows < numRows)
		{
		for(i=lastNumRows; i<numRows; i++)
			{
			Incl_FileNames_ttbl[i][0] = "";
			incl_PathNames[i] = "";
			incl_ModifiedFileDates[i] = blank;
			}
		}
	
}//procedure Incl_TableResize()


procedure Incl_Hover()
{
		
	integer numRows;
	integer hoverRow;
	integer hoverCol;
	string hoverCaption;
	
	hoverRow = WhichDTCell(0);		//0 for the row
	hoverCol = WhichDTCell(1);		//1 for the row
	
	if(hoverCol == INCL_NAME_COL)
		{
		numRows = GetDimension(Incl_FileNames_ttbl);
		if(hoverRow >= 0  &&  hoverRow < numRows)
			{
			//create caption
			hoverCaption = incl_PathNames[hoverRow];
		  	DTToolTipSet(hoverCaption);
			}
		}
			
}//procedure Incl_Hover()


//*****************************************************
//End Include file  functions
//*****************************************************
//*****************************************************




//*****************************************************
//*****************************************************
//Start "on AttribInfo"  functions
//*****************************************************


#ifdef EQ_IsItemBlock

procedure EQ_BuildAttribNamesChosen()
{
	
	integer i, j;
	
	DisposeArray(attribNamesChosen);
	
	i=0;
	
	//add attribs from iVars to attribNamesChosen
	for(j=0; j<iVars_NumTableRows; j++)
		{
		if(StrFind(iVars_Types_str[j], "attrib", FALSE, FALSE) >= 0)
			{
			MakeArray(attribNamesChosen, i+1);
			attribNamesChosen[i] = iVars_Names[j];
			i++;
			}
		}
	
	//add attribs from oVars to attribNamesChosen
	for(j=0; j<oVars_NumTableRows; j++)
		{
		if(StrFind(oVars_Types_str[j], "attrib", FALSE, FALSE) >= 0)
			{
			MakeArray(attribNamesChosen, i+1);
			attribNamesChosen[i] = oVars_Names[j];
			i++;
			}
		}
				
}//procedure EQ_BuildAttribNamesChosen()

/*
procedure EQ_OnAttribInfo()
{
	
	integer i, j;
	integer remoteArraySize;
	integer numAttribs;
	integer myNumber;
	string15 oldName;
	string15 newName;
	string15 nextName;
	string31 nextArray;
	integer numRows;
	integer changeWasMade;
	integer nextPlaceFound;
	integer lastPlaceFound;
	integer stringLength;
	string15 stringToFind;

	if(sysGlobalInt24 == ATTRIB_INFO_GET_NUM_NAMES_ARRAYS)
		{
		#ifDef EQ_IsQueryEquationItemBlock
			sysGlobalInt25 = 6;
		#else
			sysGlobalInt25 = 1;
		#endIf
		}
		
	else if(sysGlobalInt24 == ATTRIB_INFO_GET_ATTRIB_NAMES_ARRAY_NAMES)
		{
		EQ_BuildAttribNamesChosen();
		GetPassedArray(sysGlobal16, attribNameArraysRemote);
		attribNameArraysRemote[0] = "attribNamesChosen";
		
		#ifDef EQ_IsQueryEquationItemBlock
			attribNameArraysRemote[1] = "BTB_AttribNamesChosen";
			attribNameArraysRemote[2] = "DBQ_AttribNamesChosen";
			attribNameArraysRemote[3] = "DBQF_AttribNamesChosen";
			attribNameArraysRemote[4] = "DBQFP_AttribNamesChosen";
			attribNameArraysRemote[5] = "DBQSR_AttribNamesChosen";
			attribNameArraysRemote[6] = "DBQS_AttribNamesChosen";
		#endIf
		}
		
	else if(sysGlobalInt24 == ATTRIB_INFO_RENAME_ATTRIB)
		{
		//get the old and new attrib name
		GetPassedArray(sysGlobal16, attribNameOldNew);
		oldName = attribNameOldNew[0];
		newName = attribNameOldNew[1];
	
		//in EQ_EquationText replace every instance of oldName with newName
		stringToFind = oldName;
		stringLength = strLen(stringToFind);
		lastPlaceFound = -1;
		do
			{
			nextPlaceFound = StrFindDynamic(EQ_EquationText, stringToFind, 0, 0, 1);  //returns the place where the string was found or -1 if not found.
			if(nextPlaceFound > -1  &&  nextPlaceFound != lastPlaceFound)
				{
				StrReplaceDynamic(EQ_EquationText, nextPlaceFound, stringLength, newName);
				}
			else if(nextPlaceFound == lastPlaceFound)
				{
				break;
				}
			lastPlaceFound = nextPlaceFound;
			}while(nextPlaceFound > -1);  //keep replacing occurrences of the current variable until none are left.

		//search each iVars array for oldName
		changeWasMade = FALSE;
		for(i=0; i<iVars_NumTableRows; i++)
			{
			//is next iVar of type attrib?
			if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)
				{
				nextName = iVars_Names[i];
				if(nextName == oldName)
					{
					iVars_Names[i] = newName;
					changeWasMade = TRUE;
					}
				}
			}
		if(changeWasMade)
			iVars_TableSetup();	//to ensure the change takes.  ran into problem if the equation dialog was open at the time "rename" was pressed in the executive

		//search each oVars array for oldName
		for(i=0; i<oVars_NumTableRows; i++)
			{
			//is next iVar of type attrib?
			if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)
				{
				nextName = oVars_Names[i];
				if(nextName == oldName)
					{
					oVars_Names[i] = newName;
					changeWasMade = TRUE;
					}
				}
			}
		if(changeWasMade)
			oVars_TableSetup();	//to ensure the change takes.  ran into problem if the equation dialog was open at the time "rename" was pressed in the executive
		
		//search query attribs
		#ifDef EQ_IsQueryEquationItemBlock
		
			if(oldName == DBQ_AttribNamesChosen[DBQ_DATABASE_ATTRIB])
				DBQ_AttribNamesChosen[DBQ_DATABASE_ATTRIB] = newName;
			
			if(oldName == DBQ_AttribNamesChosen[DBQ_TABLE_ATTRIB])
				DBQ_AttribNamesChosen[DBQ_TABLE_ATTRIB] = newName;
			
			if(oldName == DBQ_AttribNamesChosen[DBQPT_BEST_RANK_AS_ATTRIB])
				DBQ_AttribNamesChosen[DBQPT_BEST_RANK_AS_ATTRIB] = newName;
			
			if(oldName == DBQS_AttribNamesChosen[DBQS_NUM_SPAWNS_AS_ATTRIB])
				DBQS_AttribNamesChosen[DBQS_NUM_SPAWNS_AS_ATTRIB] = newName;

			if(oldName == DBQS_AttribNamesChosen[DBQS_SPAWN_IS_WHICH_RECORD_INDEX_ATTRIB])
				DBQS_AttribNamesChosen[DBQS_SPAWN_IS_WHICH_RECORD_INDEX_ATTRIB] = newName;

			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(oldName == DBQF_AttribNamesChosen[i])
					DBQF_AttribNamesChosen[i] = newName;
				
				if(oldName == DBQFP_AttribNamesChosen[i])
					DBQFP_AttribNamesChosen[i] = newName;
				
				if(oldName == DBQSR_AttribNamesChosen[i])
					DBQSR_AttribNamesChosen[i] = newName;
				}
	
		#endif
		
		}

}//procedure EQ_OnAttribInfo()
*/
#endif //EQ_IsItemBlock
	


//*****************************************************
//End "on AttribInfo"  functions
//*****************************************************
//*****************************************************




//*****************************************************
//*****************************************************
//Start "dbg_"  Functions
//*****************************************************


on dbg_chk
{

	if(dbg_chk == TRUE)
		{
		if(EQE_EditorIsOpen == TRUE)
			{
			UserError("Please close the equation editor window first.");
			dbg_chk = FALSE;
			abort;
			}
	
		EQ_Compile(TRUE);
		}
	else
		{
		EquationDebugDispose(dbg_HiddenBlock);
		dbg_HiddenBlock = -1;
			//NOTE:  any time the hidden debug block is destroyed, must set dbg_HiddenBlock = -1 
			//so that when EquationDebugCompile() is called, a new hidden debug block is created.
		}
	
	//show breakpoint dialog items
	if(dbg_chk == TRUE)
		DisableDialogItem("dbg_OpenBreakpointsWindow_btn", FALSE);
	else
		DisableDialogItem("dbg_OpenBreakpointsWindow_btn", TRUE);
	
}//on dbg_chk


on dbg_OpenBreakpointsWindow_btn
{

	integer successfullCompile;
	
	if(EQE_EditorIsOpen == TRUE)
		{
		UserError("Please close the equation editor window first.");
		abort;
		}

	successfullCompile = EQ_Compile(FALSE);

	if(successfullCompile == TRUE)
		EquationDebugSetBreakpoints(dbg_HiddenBlock);
	
}//on dbg_OpenBreakpointsWindow_btn


//*****************************************************
//End "dbg_"  Functions
//*****************************************************
//*****************************************************



//*****************************************************
//*****************************************************
//Start "Eqn_"  Message Handlers
//*****************************************************


on EQ_TestEquation_btn
{

	integer i, j;
	integer me;
	integer numChars;
	string15 attribName;
	integer found;
	integer fieldType;
	integer legitField;
	integer parentInfo[3];
	integer currRecord;
	integer numRecords;
	integer PT_CurrBestRecordRank;
	integer S_CurrBestRecordRank;
	integer PT_NumNonBlankRankedRecords;
	integer S_NumNonBlankRankedRecords;
	integer parentArray[3];
	integer parentRecordIndex;
	integer parentParentRecordIndex;
	
	me = MyBlockNumber();
		
	EQ_Compile(FALSE);
	
//	oVarsOut_VarIsWhichConUpdate();	//make sure we know which output variables are connector variables before we calc
//	oVarsOut_ConIsWhichVarUpdate();
	
	//get the column IDs for the input varibles
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  iVars_Types_Int[i] == EQ_DB_READ_VAL_USING_ATTRIB  ||  iVars_Types_Int[i] == EQ_DB_READ_PRI_USING_ATTRIB)
			{
			#ifdef EQ_IsItemBlock
				{
				iVars_AttribColumnIndexes[i] = Attrib_GetColumnIndex(iVars_Names[i]);
				}
			#endif
			}
		else
			iVars_AttribColumnIndexes[i] = PROPERTY_TYPE_NO_PROPERTY;
		}
	
	//get the column IDs for the output varibles
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
		if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  oVars_Types_Int[i] == EQ_DB_WRITE_VAL_USING_ATTRIB  ||  oVars_Types_Int[i] == EQ_DB_WRITE_PRI_USING_ATTRIB)
			{
			#ifdef EQ_IsItemBlock
				{
				oVars_AttribColumnIndexes[i] = Attrib_GetColumnIndex(oVars_Names[i]);
				}
			#endif
			}
		else
			//oVars_AttribColumnIndexes[i] = EQ_VarTypeGet(oVars_Types_str[i]);	//6/19/09
			oVars_AttribColumnIndexes[i] = PROPERTY_TYPE_NO_PROPERTY;
		}

	//update the input variable values
	for(i=0; i<iVars_NumTableRows; i++)
		{
		
		if(iVars_Types_Int[i] == EQ_DB_READ_VAL)
			{
			if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
				if(!legitField)
					AbortAllSims();
				
				iVars_Values[i] = DBDataGetAsNumberUsingAddress(iVars_DBCoords[i]);
				
				//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
				//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
				fieldType = DBFieldGetPropertiesUsingAddress(iVars_DBCoords[i], 1) ;	//where 1 = fieldType
				if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
					{
					iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
					}
	
				iVars_ValueWasFound[i] = TRUE;
				}
			else	
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
						  "'DB read value', but the specified location does not exist.");
				AbortAllSims();
				}
			}
		
		else if(iVars_Types_Int[i] == EQ_DB_READ_PRI)
			{
			if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
				if(!legitField)
					AbortAllSims();
				
				DBDataGetParentUsingAddress(iVars_DBCoords[i], parentInfo);
				iVars_Values[i] = parentInfo[PARENT_RECORD];
	
				iVars_ValueWasFound[i] = TRUE;
				}
			else	
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
						  "'DB read PRI', but the specified location does not exist.");
				AbortAllSims();
				}
			}
		
		else if(iVars_Types_Int[i] == EQ_DB_ADDRESS)
			{
			iVars_Values[i] = iVars_DBCoords[i];
			iVars_ValueWasFound[i] = TRUE;
			}

		#ifdef EQ_IsQueryEquationTypeBlock
			
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE)
				{
				//if a direct query field has been specified
				if(DBQF_OptionsChosen[i] != DBQ_NOT_DEFINED)
					{
					if(DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))		//8/17/10
						{
						if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
							{
							fieldType = DBFieldGetProperties(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], 1) ;	//where 1 = fieldType
							
							//if query field is a string field, we know we have a problem
							if(fieldType == DB_FIELDTYPE_STRING_VALUE)
								{
								parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
								
								//if direct query field is a string field that is also child field
								if(parentRecordIndex >= 0)	
									{
									//NOTE:  if parentRecordIndex = 0, then field is a child field, but no PRI has been selected yet.
									
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read value', but the query field is a string child field. Either change the query field or change " +
											  "the variable type to 'DBQ read PRI'.");
									AbortAllSims();
									}
								
								//if direct query field is a string field
								else	
									{
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read value', but the query field is a string field.");
									AbortAllSims();
									}
								}
							
							//if query field not a string field
							else
								{
								iVars_Values[i] = DBDataGetAsNumber(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle);

								//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
								//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
								if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
									{
									iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
									}
								}
									
							iVars_ValueWasFound[i] = TRUE;
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read value', but the current record, " + DBQ_CurrRecordInQueryCycle + " is out of bounds.");
							AbortAllSims();
							}
						}
					else
						{
						if(!DBDatabaseExists(DBQ_DatabaseIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen database with index = " + DBQ_DatabaseIndex_prm + " does not exist.");
							AbortAllSims();
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query table with index = " + DBQ_TableIndex_prm + " does not exist.");
							AbortAllSims();
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query field for input variable " + (i+1) + " does not exist.");
							AbortAllSims();
							}
						}
					}
				}
	
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI)
				{
				//if an indirect parent query field has been specified
				if(DBQFP_OptionsChosen[i] != DBQ_NOT_DEFINED)
					{
					if(	
						DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i])  &&  
						DBFieldExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i])
					  )
						{
						if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
							{
							parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
							
							//if the direct query field is a child field and a PRI has been specified in the direct field's db cell
							if(parentRecordIndex >= 1)
								{
								if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex) )		//8/17/10
									{
									parentParentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex, parentInfo);
								
									//if the indirect query field is a child AND a PRI has been specified in the indirect field's db cell,...
									if(parentParentRecordIndex >= 1)
										{
										//...then by default grab the PRI found in the parent table- the "parentParent"
										iVars_Values[i] = parentParentRecordIndex;
										}
					
									//if the indirect query field is a child BUT a PRI has not been specified in the indirect field's db cell
									else if(parentParentRecordIndex == 0)	
										{
										iVars_Values[i] = blank;
										}
									
									//if indirect query field is NOT a child
									else
										{
										iVars_Values[i] = DBDataGetAsNumber(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex);
										
										//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
										//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
										fieldType = DBFieldGetProperties(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], 1) ;	//where 1 = fieldType
										if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
											{
											iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
											}
										}
									}
								else
									{
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read PRI', but parent record " + parentRecordIndex  + " does not exist.");
									AbortAllSims();
									}
								}
							
							//if the direct query field is a child field and a PRI has not been specified in the direct field's db cell
							else if(parentRecordIndex == 0)	
								{
								iVars_Values[i] = blank;
								}
							
							//if the direct query field not a child field
							else 
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', but the query field is not a child field. Either change the query field or change " +
										  "the variable type to 'DBQ read value'.");
								AbortAllSims();
								}
								
							iVars_ValueWasFound[i] = TRUE;
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read PRI', and the current record " + DBQ_CurrRecordInQueryCycle  + " does not exist.");
							AbortAllSims();
							}
						}
					else
						{
						if(!DBDatabaseExists(DBQ_DatabaseIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen database with index = " + DBQ_DatabaseIndex_prm + " does not exist.");
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query table with index = " + DBQ_TableIndex_prm + " does not exist.");
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query field for input variable " + (i+1) + " does not exist.");
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The parent table with index = " + DBQFP_TableIndex[i] + " for input variable " + (i+1) + "does not exist.");
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQFP_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The parent table with index = " + DBQFP_FieldIndex[i] + " for input variable " + (i+1) + "does not exist.");
							}
						AbortAllSims();
						}
					}
					
				//else if a direct query field has been specified
				else if(DBQF_OptionsChosen[i] != DBQ_NOT_DEFINED)
					{
					if(DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))		//8/17/10
						{
						if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
							{
							parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
							
							//if direct query field is a child AND a PRI has been specified in the direct field's db cell
							if(parentRecordIndex >= 1)
								{
								iVars_Values[i] = parentRecordIndex;	//note if parentRecordIndex = 0, then child cell has nothing selected yet
								}
				
							//if direct query field is a child BUT a PRI has not yet been specified in the direct field's db cell
							else if(parentRecordIndex == 0)	
								{
								iVars_Values[i] = blank;
								}
							
							//else if direct query field is NOT a child field
							else if(parentRecordIndex < 0)
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', but the query field is not a child field. Either change the query field or change " +
										  "the variable type to 'DBQ read value'.");
								AbortAllSims();
								}
							
							iVars_ValueWasFound[i] = TRUE;
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read PRI', and current record " + DBQ_CurrRecordInQueryCycle  + " does not exist.");
							AbortAllSims();
							}
						}
					else
						{
						if(!DBDatabaseExists(DBQ_DatabaseIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen database with index = " + DBQ_DatabaseIndex_prm + " does not exist.");
							}
						if(!DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query table with index = " + DBQ_TableIndex_prm + " does not exist.");
							}
						if(!DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]))
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The chosen query field for input variable " + (i+1) + " does not exist.");
							}
						AbortAllSims();
						}
					}
				}
			
			else if(iVars_Types_Int[i] == EQ_DBQ_CURRENT_RECORD)
				{
				//iVars_Values[i] = DBQ_CurrRecordInQueryCycle;
				currRecord = NumericParameter("Enter the current record.", 1);
				iVars_Values[i] = currRecord;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQ_NUM_RECORDS)
				{
				if(DBQ_DatabaseIndex_prm >=1  &&  DBQ_TableIndex_prm >= 1)
					numRecords = DBRecordsGetNum(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm);
				else
					numRecords = 1;
				iVars_Values[i] = numRecords;
				iVars_ValueWasFound[i] = TRUE;
				}
				
			else if(iVars_Types_Int[i] == EQ_DBQ_CURR_BEST_RANK_RESULT)
				{
				//iVars_Values[i] = DBQPT_CurrBestRankResult;
				PT_CurrBestRecordRank = NumericParameter("Enter the current best pass-through record rank.", 1);
				iVars_Values[i] = PT_CurrBestRecordRank;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQS_CURR_BEST_RANK_RESULT)
				{
				//iVars_Values[i] = DBQS_CurrBestRankResult;
				S_CurrBestRecordRank = NumericParameter("Enter the current best spawn record rank.", 1);
				iVars_Values[i] = S_CurrBestRecordRank;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS)
				{
				PT_NumNonBlankRankedRecords = NumericParameter("Enter the number of non-blank pass-through record ranks.", 1);
				iVars_Values[i] = PT_NumNonBlankRankedRecords;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS)
				{
				S_NumNonBlankRankedRecords = NumericParameter("Enter the number of non-blank spawn record ranks.", 1);
				iVars_Values[i] = S_NumNonBlankRankedRecords;
				iVars_ValueWasFound[i] = TRUE;
				}
		
			else if(iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT)
				{
				//do nothing- static query vars were initialized at the start of the query in DBQ_DoQuery() and updated during EquationCalculateDynamicVariables()
				iVars_ValueWasFound[i] = TRUE;
				}
				
		#endif //EQ_IsQueryEquationTypeBlock
	
		else if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI  ||  iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
			{
			//do nothing to preserve the static
			}

		//5/24/11
		else if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  &&  iVars_AttribTypes[i] == ATTRIB_TYPE_STRING)
			{
			//if the ivar is pointing to a string attrib, we need to convert the string val into a string index
			iVars_Values[i] = SLStringGetIndex(iVars_Names[i], iVars_ttbl[i][I_VAR_VALUE_COL]);
			
			if(iVars_Values[i] < 0)
				{
				UserError("There is a problem with the value of input variable number " + (i+1) + ". " + 
						  "The string value """ + iVars_ttbl[i][I_VAR_VALUE_COL] + """ for the attribute """ + iVars_Names[i] + """ does not exist.");
				AbortAllSims();
				}
			}
		
		else if(iVars_Types_Int[i] == EQ_STRING ) // Carollo
		{
			iVars_ValuesStr[i] = iVars_ttbl[i][I_VAR_VALUE_COL];
		}
		else
			{
			iVars_Values[i] = StrToReal(iVars_ttbl[i][I_VAR_VALUE_COL]);
			}
		
		}//for(i=0; i<iVars_NumTableRows; i++)

	//get initial values for output variables
	oVars_InitVals();

	if(dbg_chk == TRUE)
		EquationDebugCalculate(dbg_HiddenBlock, iVars_Values, oVars_Values);
	else
		EquationCalculateDynamicVariables(iVars_Values, oVars_Values, EQ_CompiledEquation);

	//update the database
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL  ||  oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
			{
			legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
			if(!legitField)
				AbortAllSims();

			//if targeted field is of type "Date Time", then convert the number being written to Julian format.
			//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
			fieldType = DBFieldGetPropertiesUsingAddress(oVars_DBCoords[i], 1) ;	//where 1 = fieldType
			if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
				{
				oVars_Values[i] = EDSimTimeToDate(oVars_Values[i], 0);
				}

			//	8/25/09
			//DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);

			if(EQ_DBAddressLocationExists(oVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL)
					DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
				
				else //if(oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
					//with this option user wants to set a parent index in a child
					DBDataSetAsParentIndexUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
				}
			else
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". Output variable " + (i+1) + " is of type " +
						  "'DB write value', but the specified location does not exist.");
				AbortAllSims();
				}
			}
		}

	//update output connectors
	#ifdef oVarsOut
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(oVars_VarIsWhichCon[i] != -1)
				ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);
			}
	#endif

	//if have static variables, update the input table
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI  ||  iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
			iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i] + " : " + iVars_Values[i];
		}

	//if the output variable is an attrib variable, get result from iVars_Values
	#ifdef EQ_IsItemBlock
			
		for(i=0; i<oVars_NumTableRows; i++)
			{
				
			if(oVars_Types_Int[i] >= EQ_ITEM_ATTRIBUTE)		//ie, it's an attribute variable
				{
				
				for(j=0; j<iVars_NumTableRows; j++)
					{
					if(oVars_Names[i] == iVars_Names[j])
						{	
						oVars_Values[i] = iVars_Values[j];
						break;
						}
					}

				}
					
			}//for(i=0; i<oVars_NumTableRows; i++)
				
	#endif

	//update the output table
	for(i=0; i<oVars_NumTableRows; i++)
	{
		// Carollo
		if (oVars_Types_Int[i] == EQ_Integer)
		{
			oVars_Values[i] = Int(oVars_Values[i]);
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_Values[i];
		}
		else if (oVars_Types_Int[i] == EQ_String)
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_ValuesStr[i];
		else
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_Values[i];
	}
	
}//on EQ_TestEquation_btn


on EQ_OpenDeveloperReference_btn	//10/30/08, 7.0.5, AJN
{

	string fileLocation;
	
	//4/23/08
	if(PlatformWindows)
		{
		fileLocation = GetAppPath() + "\Documentation\Developer Reference.pdf";
		IPCOpenFile(fileLocation);
		}
	else
		{
		fileLocation = GetAppPath() + "Documentation:Developer Reference.pdf";
		IPCOpenFile(fileLocation);
		}

}//on EQ_OpenDeveloperReference_btn


procedure EQ_OnCellAccept()
{

	string dName;		// name of the dialog item clicked
	integer caRow;
	integer caCol;
	integer SA_ValIndex;

	caRow = WhichDTCellClicked(0);		//which row did the user just exit
	caCol = WhichDTCellClicked(1);		//which col did the user just exit
	dName = WhichDialogItemClicked();
	
	if(dName == "iVars_ttbl"  &&  caRow >= 0  &&  caRow < iVars_NumTableRows  )
		{
	
		//store user's inputs in the individual arrays
		//!!NOTE:  need this here.  if not, when user types in test values, they disappear
		if(caCol == I_VAR_VALUE_COL)
			{
			if(
				iVars_Types_str[caRow] != "Static first run init"  &&  
				iVars_Types_str[caRow] != "Static multi run init"  &&  
				iVars_Types_str[caRow] != "Static open model init"  &&  
				iVars_Types_str[caRow] != "DBQ static query init"
			  )
				{
				if(iVars_Types_str[caRow] == "Attribute"  &&  iVars_AttribTypes[caRow] == ATTRIB_TYPE_STRING) 
					{
					SA_ValIndex = SLStringGetIndex(iVars_Names[caRow], iVars_ttbl[caRow][I_VAR_VALUE_COL]);
					iVars_Values[caRow] = SA_ValIndex;
					}
				else
					{
					iVars_Values[caRow] = StrToReal(iVars_ttbl[caRow][I_VAR_VALUE_COL]);
					}
				}
			
			StopDataTableEditing();
			}
		
		else if(caCol == I_VAR_NAME_COL)
			{
			iVars_Names[caRow] = iVars_ttbl[caRow][I_VAR_NAME_COL];
			}
			
		}//if(dName == "iVars_ttbl")
		
	if(dName == "oVars_ttbl"  &&  caRow >= 0  &&  caRow < oVars_NumTableRows)
		{

		//store user's inputs in the individual arrays
		if(caCol == O_VAR_NAME_COL)
			oVars_Names[caRow] = oVars_ttbl[caRow][O_VAR_NAME_COL];

		}//if(dName == "oVars_ttbl")

}//procedure EQ_OnCellAccept()

/*
procedure EQ_OnDataTableResize(integer calledFrom)
{

	string whichTable;
	integer oldNumRows;
	real newNumRows;
	integer numRowsAttribTable;
	integer popupChoice;

	whichTable = WhichDialogItemClicked();
	
	if(whichTable == "iVars_ttbl")
		{
		MakeArray(dataTableResizePop, 3);
		dataTableResizePop[0] = "Resize";
		dataTableResizePop[1] = "Copy selected row";
		dataTableResizePop[2] = "Delete selected rows";
		popupChoice = PopupMenuArray (dataTableResizePop, 0);
		DisposeArray(dataTableResizePop);
	
		if(popupChoice == 1)	//"Change the number of rows";
			{
			iVars_OldNumTableRows = iVars_NumTableRows;
			newNumRows = NumericParameter("Please enter the desired number of rows.", iVars_OldNumTableRows);
			
			if(NoValue(newNumRows))
				iVars_NumTableRows = iVars_OldNumTableRows;
			else
				{
				if(newNumRows >=0)
					iVars_NumTableRows = newNumRows;
				else
					{
					UserError("The number of rows must be greater than or equal to 0.");
					iVars_NumTableRows = iVars_OldNumTableRows;				
					}
				}
			
			//iVars_DBNT_GarbageCollection();	//6/7/10:  moved this line of code below so that we do garbage collection for all cases	0.
			iVars_ResizeDynamicArrays(RESIZE_ADD_SUBTRACT_FROM_END);
			iVarsIn_ConnectorsSetup();
			}
		
		else if(popupChoice == 2)	//"Insert rows below selected row";
			{
			iVars_CopyRow();
			}
		
		else if(popupChoice == 3)	//"Delete selected rows";
			{
			iVars_DeleteRows();
			}
			
		iVars_DBNT_GarbageCollection();		//6/7/10
		iVars_TableSetup();
		iVarsIn_ConLabelsSet();
		
		#ifdef CMC_chk
			//CMC_IVarsIn_Animate();			//7/6/11
			CMC_ConnectorAnimate();
		#endif

		#ifdef CW_IVarsIn_CalcControl_chk
			//CW_IVarsIn_Animate();			//7/5/11
			CW_ConnectorAnimate();
		#endif
		}

	else if(whichTable == "oVars_ttbl")
		{
		MakeArray(dataTableResizePop, 3);
		dataTableResizePop[0] = "Resize";
		dataTableResizePop[1] = "Copy selected row";
		dataTableResizePop[2] = "Delete selected rows";
		popupChoice = PopupMenuArray (dataTableResizePop, 0);
		DisposeArray(dataTableResizePop);
	
		if(popupChoice == 1)	//"Change the number of rows";
			{
			oVars_OldNumTableRows = oVars_NumTableRows;
			newNumRows = NumericParameter("Please enter the desired number of rows.", oVars_OldNumTableRows);
	
			if(NoValue(newNumRows))
				oVars_NumTableRows = oVars_OldNumTableRows;
			else
				{
				if(newNumRows >=0)
					oVars_NumTableRows = newNumRows;
				else
					{
					UserError("The number of rows must be greater than or equal to 0.");
					oVars_NumTableRows = oVars_OldNumTableRows;				
					}
				}
			
			//oVars_DBNT_GarbageCollection();	//6/7/10:  moved this line of code below so that we do garbage collection for all cases	0.
			oVars_ResizeDynamicArrays(calledFrom, RESIZE_ADD_SUBTRACT_FROM_END);
			oVarsOut_ConnectorsSetup();
			}
		
		else if(popupChoice == 2)	//"Insert rows below selected row";
			{
			oVars_CopyRow(calledFrom);
			}
		
		else if(popupChoice == 3)	//"Delete selected rows";
			{
			oVars_DeleteRows(calledFrom);
			}
			
		oVars_DBNT_GarbageCollection();			//6/7/10
		oVars_TableSetup();
		oVarsOut_ConLabelsSet();
		
		#ifdef CMC_chk
			//CMC_OVarsOut_Animate();			//7/6/11
			CMC_ConnectorAnimate();
		#endif
		
		#ifdef CW_OVarsOut_CalcControl_chk
			//CW_OVarsOut_Animate();			//7/5/11
			CW_ConnectorAnimate();
		#endif		
		}

	else if(whichTable == "Incl_FileNames_ttbl")
		{
		oldNumRows = GetDimension(Incl_FileNames_ttbl);
		newNumRows = NumericParameter("Please enter the desired number of rows.", oldNumRows);

		if(!NoValue(newNumRows))	//if user did not click cancel
			{
			if(newNumRows >=0  &&  newNumRows <= 20)
				{
				Incl_TableResize(newNumRows);
				}
			else if(newNumRows < 0)
				{
				UserError("The number of included files cannot be negative.");
				}
			else if(newNumRows > 20)
				{
				UserError("The number of included files may not exceed 20.");
				}
			}
		}

}//procedure EQ_OnDataTableResize(integer calledFrom)
*/

integer EQ_DBAddressLocationExists(real dbAddress, integer addressType)		//8/17/10
{

	integer addressExists;
	integer indexArray[4];
	
	addressExists = FALSE;
	
	DBAddressGetAllIndexes(dbAddress, indexArray);

	if(addressType == DB_ADDRESS_TYPE_DATABASE)
		{
		if( DBDatabaseExists(indexArray[0]) )
			addressExists = TRUE;
		}

	else if(addressType == DB_ADDRESS_TYPE_TABLE)
		{
		if( DBTableExists(indexArray[0], indexArray[1]) )
			addressExists = TRUE;
		}

	else if(addressType == DB_ADDRESS_TYPE_FIELD)
		{
		if( DBFieldExists(indexArray[0], indexArray[1], indexArray[2]) )
			addressExists = TRUE;
		}

	else if(addressType == DB_ADDRESS_TYPE_RECORD)
		{
		if( DBRecordExists(indexArray[0], indexArray[1], indexArray[2], indexArray[3]) )
			addressExists = TRUE;
		}

	return(addressExists);

}//integer EQ_DBAddressLocationExists(real dbAddress, integer addressType)


procedure EQ_OnDataTableHover()
{

	integer me;
	integer hoverRow;
	integer hoverCol;
	integer whichElement;
	integer displayCaption;
	string whichDialogItem_str;
	string hoverCaption;
	string63 dbDatabaseName;
	string63 dbTableName;
	string63 dbFieldName;
	string dbRecordName;
	integer recordIndex;
	integer iVars_DBNameTrackingListIndex;
	integer oVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();
	
	displayCaption = FALSE;
	hoverCaption = "";
	
	whichDialogItem_str = WhichDialogItem();
	
	if(whichDialogItem_str == "iVars_ttbl")
		{
		hoverRow = WhichDTCell(0);		//0 for the row
		hoverCol = WhichDTCell(1);		//1 for the row
		
		if(hoverCol == I_VAR_VALUE_COL)
			{
			if(hoverRow >= 0  &&  hoverRow < iVars_NumTableRows)
				{
				if(
					iVars_Types_Int[hoverRow] == EQ_DB_READ_VAL  ||  
					iVars_Types_Int[hoverRow] == EQ_DB_READ_PRI  ||  
					iVars_Types_Int[hoverRow] == EQ_DB_ADDRESS   ||  
					iVars_Types_Int[hoverRow] == EQ_DB_DATABASE_INDEX  ||  
					iVars_Types_Int[hoverRow] == EQ_DB_TABLE_INDEX  ||  
					iVars_Types_Int[hoverRow] == EQ_DB_FIELD_INDEX  ||  
					iVars_Types_Int[hoverRow] == EQ_DB_RECORD_INDEX
				  )
					{
					displayCaption = TRUE;
					iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
					whichElement = ListSearch(me, iVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, hoverRow, 0, "", 0);
						//2 = searchType is integer
						//DBNT_WHICH_ROW_IN_TABLE_FIELD = searchIndex
					
					//get db names
				  	dbDatabaseName = ListGetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_DB_NAME_FIELD);
				  	dbTableName = ListGetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_TABLE_NAME_FIELD);
				  	dbFieldName = ListGetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_FIELD_NAME_FIELD);
				  	dbRecordName = ListGetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_RECORD_NAME_FIELD);

					if(
						iVars_Types_Int[hoverRow] == EQ_DB_READ_VAL  ||  
						iVars_Types_Int[hoverRow] == EQ_DB_READ_PRI  ||  
						iVars_Types_Int[hoverRow] == EQ_DB_ADDRESS   ||
						iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_VALUE  ||
						iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_PRI
 					  )
					  	{
						hoverCaption = dbDatabaseName + " : " + dbTableName + " : " + dbFieldName;
					  	if(dbRecordName != "")
							hoverCaption += " : " + dbRecordName;
					  	}
					else if(iVars_Types_Int[hoverRow] == EQ_DB_DATABASE_INDEX)
						{
						hoverCaption = dbDatabaseName;
						}
					else if(iVars_Types_Int[hoverRow] == EQ_DB_TABLE_INDEX)
						{
						hoverCaption = dbDatabaseName + ":" + dbTableName;
						}
					else if(iVars_Types_Int[hoverRow] == EQ_DB_FIELD_INDEX)
						{
						hoverCaption = dbDatabaseName + ":" + dbTableName + ":" + dbFieldName;
						}
					else if(iVars_Types_Int[hoverRow] == EQ_DB_RECORD_INDEX)
						{
						hoverCaption = dbDatabaseName + ":" + dbTableName + ":" + dbFieldName;
						
						if(dbRecordName != "")
							hoverCaption += ":" + dbRecordName;
						else
							hoverCaption += ":Record " + DBRecordGetIndexFromAddress(iVars_DBCoords[hoverRow]);
						}
					else if(iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_VALUE  ||  iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_PRI)
						{
						if(dbRecordName != "")
							hoverCaption = dbRecordName;
						}
					}
				#ifdef EQ_IsQueryEquationTypeBlock
				else if(iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_VALUE  ||  iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_PRI)
					{
					displayCaption = TRUE;
					hoverCaption = DBQ_DatabaseName + " : " + DBQ_TableName + " : " + DBQF_FieldName[hoverRow];
					}
				#endif //EQ_IsQueryEquationTypeBlock
				}
			}
		if(hoverCol == I_VAR_PARENT_FIELD_COL)
			{
			#ifdef EQ_IsQueryEquationTypeBlock
			if(hoverRow >= 0  &&  hoverRow < iVars_NumTableRows)
				{
				if(iVars_Types_Int[hoverRow] == EQ_DBQ_QUERY_FIELD_PRI)
					{
					displayCaption = TRUE;
					hoverCaption = DBQ_DatabaseName + " : " + DBQ_TableName + " : " + DBQFP_FieldName[hoverRow];
					}
				}
			#endif //EQ_IsQueryEquationTypeBlock
			}
		}
		
	else if(whichDialogItem_str == "oVars_ttbl")
		{
		hoverRow = WhichDTCell(0);		//0 for the row
		hoverCol = WhichDTCell(1);		//1 for the row
		
		if(hoverCol == O_VAR_VALUE_COL)
			{
			if(hoverRow >= 0  &&  hoverRow < oVars_NumTableRows)
				{
				if(
					oVars_Types_Int[hoverRow] == EQ_DB_WRITE_VAL  ||  
					oVars_Types_Int[hoverRow] == EQ_DB_WRITE_PRI  ||  
					oVars_Types_Int[hoverRow] == EQ_DB_ADDRESS
				  )
					{
					displayCaption = TRUE;
					oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
					whichElement = ListSearch(me, oVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, hoverRow, 0, "", 0);
						//2 = searchType is integer
						//DBNT_WHICH_ROW_IN_TABLE_FIELD = searchIndex
					
					
					//get db names
				  	dbDatabaseName = ListGetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_DB_NAME_FIELD);
				  	dbTableName = ListGetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_TABLE_NAME_FIELD);
				  	dbFieldName = ListGetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_FIELD_NAME_FIELD);
				  	dbRecordName = ListGetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_RECORD_NAME_FIELD);
					
					//create caption
					hoverCaption = dbDatabaseName + " : " + dbTableName + " : " + dbFieldName;
				  	if(dbRecordName != "")
						hoverCaption += " : " + dbRecordName;
					else
						hoverCaption += ":Record " + DBRecordGetIndexFromAddress(oVars_DBCoords[hoverRow]);
					}
				}
			}
		}
		
	else if(whichDialogItem_str == "Incl_FileNames_ttbl")
		{
		
		Incl_Hover();
		
		}
		
	if(displayCaption == TRUE)
		{
		DTToolTipSet(hoverCaption);
		}

}//procedure EQ_OnDataTableHover()

/*
procedure EQ_OnLinkContent()
{

	integer i, j;
	integer me;
	integer iVars_DBNameTrackingListIndex;
	integer whatHappened;
	integer simPhase;
	integer respondToLinkAlert;
	integer changeDB;
	integer changeTable;
	integer changeField;
	integer changeRecord;
	real changeAddress;
	integer whichDBChanged;
	integer whichTableChanged;
	integer whichFieldChanged;
	integer whichRecordChanged;
	integer dbIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	integer recordIDFieldIndex;
	integer numElements;
	integer whichVarRow;
	string recordName;

	if(inLinkContent == TRUE)
		return;
	else
		inLinkContent = TRUE;

	me = MyBlockNumber();
	
	whatHappened = DILinkUpdateInfo(cWHAT_HAPPENED);
	simPhase = GetSimulationPhase();

	if(
		simPhase != PHASE_PRECHECKDATA  &&
		simPhase != PHASE_CHECKDATA  &&
		simPhase != PHASE_STEPSIZE  &&
		simPhase != PHASE_INITSIM
	  )
	  	{
	
		if(whatHappened == cDATA_CHANGED )
			{
	
			whichDBChanged = DILinkUpdateInfo(cWHICH_DB_INDEX);
			whichTableChanged = DILinkUpdateInfo(cWHICH_TABLE_INDEX);
			whichFieldChanged = DILinkUpdateInfo(cWHICH_COLUMN);
			whichRecordChanged = DILinkUpdateInfo(cWHICH_ROW);
	
			//do record name tracking for "db read" type iVars
			iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
			if(iVars_DBNameTrackingListIndex >= 0)
				{
				numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
				
				//if this block has a "db read" type input variable and if it's reading from a 
				//table that has a record ID field and if a value in that record ID field changed,... 
				for(i=0; i<iVars_NumTableRows; i++)
					{
					//...then name tracking requires us to ensure the "db read" type iVars are pointing to the correct record indexes
					if(iVars_Types_Int[i] == EQ_DB_READ_VAL  ||  iVars_Types_Int[i] == EQ_DB_READ_PRI)
						{
						dbIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
						tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
						tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
						fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
						recordIDFieldIndex = DBRecordIDFieldGetIndex(dbIndex, tableIndex);
						
						//if iVar is pointing at the table that changed and if this table has a record ID field
						if(dbIndex == whichDBChanged  &&  tableIndex == whichTableChanged  &&  whichFieldChanged == recordIDFieldIndex)
							{
							//for(i=0; i<numElements; i++)		11/29/10:  "i" is already being used in the superior for loop
							for(j=0; j<numElements; j++)
								{
								whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, j, DBNT_WHICH_ROW_IN_TABLE_FIELD);
								if(i == whichVarRow)
									{
									recordName = ListGetString(me, iVars_DBNameTrackingListIndex, j, 6, DBNT_RECORD_NAME_FIELD);	//6 for string63
									if(recordName == "")
										recordName = ListGetString(me, iVars_DBNameTrackingListIndex, j, 5, DBNT_RECORD_NAME_FIELD);	//5 for string31	//9/30/09
									if(recordName != "")
										{
										recordIndex = DBRecordFind(dbIndex, 			//database to search
																   tableIndex, 			//table to search
																   0, 					//use the record ID field as the search field
																   1, 					//the start record index
																   TRUE, 				//exact record match
																   recordName);			//the search string
										if(recordIndex == 0)
											recordIndex = -1;
										}
									else
										recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
	
									iVars_DBCoords[whichVarRow] = DBAddressCreate(dbIndex, tableIndex, fieldindex, recordIndex);
									break;
									}
								}
							}
						}
					}
				}
	
			#ifdef EQ_IsValueBlock
			
				if(CW_LAM_CalcControl_chk == TRUE)
					{
					if(modelType == DISCRETE_EVENT)
						{
						if(simPhase == PHASE_SIMULATE  ||  simPhase == PHASE_POST_INITSIM)
							{
							if(CW_LAM_RespondWhen_pop == WHEN_CALC_IMMEDIATE)
								{
								iVarsIn_SendMsgs(MSG_RECEIVED_FROM_LINK_CONTENT);
									
								#ifdef EQ_IsEquationValue
									EQ_Calc(FALSE, FALSE);			//FALSE- no iVar msgs, FALSE- no oVar msgs
								#endif
								
								#ifdef EQ_IsQueryEquationValueBlock
									DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
								#endif
								
								oVarsOut_SendMsgs(MSG_RECEIVED_FROM_LINK_CONTENT);
	
								//post this block's next future event
								if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
									{
									nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
									timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
									lastCalculatedEventTime = nextCalcEventTime;		//	5/15/09
									}
								}
							else //if(CW_LAM_RespondWhen_pop == WHEN_CALC_CURRENT_EVENT)
								{
							  	//post current event
							  	if(!rescheduled)
							  		{
									rescheduled = TRUE;
									SysGlobalInt8 = MyBlockNumber();
									SendMsgToBlock(exec,BLOCKRECEIVE3MSG);
									}
								}
							}
						
						else //if simphase is at a starting point where we can't send messages
							{
							#ifdef EQ_IsEquationValue
								EQ_Calc(FALSE, FALSE);
							#endif
							
							#ifdef EQ_IsQueryEquationValueBlock
								DBQ_DoQuery(FALSE, FALSE);
							#endif
							}
							
						}
	
					else //if(modelType == CONTINUOUS)
						{
						#ifdef EQ_IsEquationValue
							EQ_Calc(FALSE, FALSE);
						#endif
						
						#ifdef EQ_IsQueryEquationValueBlock
							DBQ_DoQuery(FALSE, FALSE);
						#endif
						}
					}
				
				else //if(CW_LAM_CalcControl_chk == FALSE)
					{
					//do nothing
					}
					
			#endif //EQ_IsValueBlock
			
			}//if(whatHappened == cDATA_CHANGED )
			
		}
		
	inLinkContent = FALSE;

}//procedure EQ_OnLinkContent()
*/


#ifdef EQ_IsValueBlock

procedure GoInShow()
{

	integer me;
	integer iconView;
	integer goInIndex;
	string15 conLabelArray[1];
	
	me = MyBlockNumber();
	iconView = IconGetView(MyBlockNumber());
	goInIndex = GetConNumber(me, "goIn");
	
	if(CW_GoIn_chk == TRUE)
		{
		SetConVisibility(me, goInIndex, TRUE);
		
		conLabelArray[0] = "Go";
		
		if(iconView == 0)
			ConnectorLabelsSet(me, goInIndex, 1, conLabelArray, RIGHT_SIDE, 0, 0, 0);
		else
			ConnectorLabelsSet(me, goInIndex, 1, conLabelArray, LEFT_SIDE, 0, 0, 0);
		}
	else
		{
		SetConVisibility(me, goInIndex, FALSE);
		}

}//procedure GoInShow()

#endif //EQ_IsValueBlock



#ifdef EQ_IsValueBlock
/*
//for current events only
procedure EQ_OnBlockReceive0()
{

	integer i;
	integer me;
	
	inBlockReceive0 = TRUE;
	me = MyBlockNumber(); 
	rescheduled = FALSE;
	
	//send input messages
	iVarsIn_SendMsgs(MSG_RECEIVED_FROM_BR0);

	#ifdef EQ_IsEquationValue
		EQ_Calc(FALSE, FALSE);			//FALSE- no iVar msgs, FALSE- no oVar msgs
	#endif
	
	#ifdef EQ_IsQueryEquationValueBlock
		DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
	#endif

	//send output messages
	oVarsOut_SendMsgs(MSG_RECEIVED_FROM_BR0);

	//8/5/10:  conditionally post this block's next event
	if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
		{
		nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
		timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
		lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
		}

	inBlockReceive0 = FALSE;

}//procedure EQ_OnBlockReceive0()
*/
#endif //EQ_IsValueBlock



#ifdef EQ_IsValueBlock
/*
//for future events only
procedure EQ_OnBlockReceive1()
{

	integer i;
	integer me;
	
	inBlockReceive1 = TRUE;
	me = MyBlockNumber(); 
	
	//4/14/09, 	
	//caluculate the equation
	if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
		{
		//send input messages
		iVarsIn_SendMsgs(MSG_RECEIVED_FROM_BR1);

		#ifdef EQ_IsEquationValue
			EQ_Calc(FALSE, FALSE);			//FALSE- no iVar msgs, FALSE- no oVar msgs
		#endif
		
		#ifdef EQ_IsQueryEquationValueBlock
			DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
		#endif

		//send output messages
		oVarsOut_SendMsgs(MSG_RECEIVED_FROM_BR1);

		//post this block's next event
		nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
		timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
		lastCalculatedEventTime = nextCalcEventTime;	//5/15/09
		}
		
	else
		{
		UserError("There is a problem with Equation block " + me + ". Please contact Imagine That.");
		AbortAllSims();
		}
  
	inBlockReceive1 = FALSE;

}//procedure EQ_OnBlockReceive1()
*/
#endif //EQ_IsValueBlock



#ifdef EQ_IsValueBlock
/*
procedure EQ_OnGoIn()
{

	integer i;
	
	if(inIVarsIn == TRUE  ||  inOVarsOut == TRUE  ||  inGoIn == TRUE  ||  inLinkContent == TRUE  ||  inBlockReceive1 == TRUE  ||  inPostInitSim == TRUE    ||  inFinalCalc == TRUE)
		{
		return;
		}
	else
		{
		inGoIn = TRUE;
		}
	
	if(CW_GoIn_chk)
		{
		//iVarsIn msgs
		iVarsIn_SendMsgs(MSG_RECEIVED_FROM_GO_IN);

		#ifdef EQ_IsEquationValue
			EQ_Calc(FALSE, FALSE);			//FALSE- no iVar msgs, FALSE- no oVar msgs
		#endif
		
		#ifdef EQ_IsQueryEquationValueBlock
			DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
		#endif

		//oVarsOut msgs
		oVarsOut_SendMsgs(MSG_RECEIVED_FROM_GO_IN);

		//post this block's next event
		if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
			{
			nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
			timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
			lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
			}
		}
		
	inGoIn = FALSE;

}//procedure EQ_OnGoIn()
*/
#endif //EQ_IsValueBlock

/*
procedure EQ_OnLinkStructure()
{

	integer me;
	integer i;
	integer simPhase;
	integer linkType;
	integer whatHappened;
	integer badDeleteOccurred;
	integer iVars_BadDeleteOccurred;
	integer oVars_BadDeleteOccurred;
	integer iVars_UpdateTable;
	integer oVars_UpdateTable;
	integer doAbort;
	integer numRecords;
	integer numElements;
	integer whichVarRow;
	integer iVars_DBNameTrackingListIndex;
	integer oVars_DBNameTrackingListIndex;
	integer usedRecordIDFieldIndex;
	
	integer changeDBIndex;
	integer changeTableIndex;
	integer changeFieldIndex;
	integer changeRecordIndex;
	
	integer deletedDBIndex;
	integer deletedTableIndex;
	integer deletedFieldIndex;
	integer deletedRecordIndex;
	
	integer usedDBIndex;
	integer usedTableIndex;
	integer usedFieldIndex;
	integer usedRecordIndex;
	
	integer newDBIndex;
	integer newTableIndex;
	integer newFieldIndex;
	integer newRecordIndex;
	
	string63 changeDBName;
	string63 changeTableName;
	string63 changeFieldName;
	string63 changeRecordName;
	
	string63 deletedDBName;
	string63 deletedTableName;
	string63 deletedFieldName;
	string63 deletedRecordName;
	
	string63 usedDBName;
	string63 usedTableName;
	string63 usedFieldName;
	string63 usedRecordName;
	
	string63 newDBName;
	string63 newTableName;
	string63 newFieldName;
	string63 newRecordName;
	
	if(inLinkStructure == TRUE)
		return;
	
	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
	inLinkStructure = TRUE;
	simPhase = GetSimulationPhase();
	whatHappened = DILinkUpdateInfo(cWHAT_HAPPENED);
	badDeleteOccurred = FALSE;
	iVars_BadDeleteOccurred = FALSE;
	oVars_BadDeleteOccurred = FALSE;
	iVars_UpdateTable = FALSE;
	oVars_UpdateTable = FALSE;
	doAbort = FALSE;

	if(whatHappened == cDB_RENAMED)
		{
		changeDBName = DILinkUpdateString(cWHICH_NAME_SOURCE);
						
		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			usedDBName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
			if(usedDBName == changeDBName)
				{
				whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
				usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
				newDBName = DBDatabaseGetName(usedDBIndex);
				ListSetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD, newDBName);	//6 for string63
				}
			}
		
		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			usedDBName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
			if(usedDBName == changeDBName)
				{
				whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
				usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
				newDBName = DBDatabaseGetName(usedDBIndex);
				ListSetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD, newDBName);	//6 for string63
				}
			}
		
		#ifdef EQ_IsQueryEquationTypeBlock
			
			if(DBQ_DatabaseOptionChosen == DBQ_USE_LIST  &&  changeDBName == DBQ_DatabaseName)
				{
				DBQ_DatabaseName = DBDatabaseGetName(DBQ_DatabaseIndex_prm);
				DBQ_DialogItemsUpdate();
				}
		
		#endif //EQ_IsQueryEquationTypeBlock
		}
	
	else if(whatHappened == cDB_DELETED)
		{
		deletedDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		deletedDBName = DILinkUpdateString(cWHICH_NAME_SOURCE);
		
		//search iVars for problem
		for(i=0; i<iVars_NumTableRows; i++)
			{
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
			if(usedDBIndex == deletedDBIndex)
				{
				UserError("The database named, " + deletedDBName + ", has been deleted, but Equation block number " + me + " was referencing a table in that database.");
				iVars_BadDeleteOccurred = TRUE;
				iVars_UpdateTable = TRUE;
				doAbort = TRUE;
				break;
				}
			}
		
		//search oVars for problem
		for(i=0; i<oVars_NumTableRows; i++)
			{
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[i]);
			if(usedDBIndex == deletedDBIndex)
				{
				UserError("The database named, " + deletedDBName + ", has been deleted, but Equation block number " + me + " was referencing a table in that database.");
				oVars_BadDeleteOccurred = TRUE;
				oVars_UpdateTable = TRUE;
				doAbort = TRUE;
				break;
				}
			}
		
		#ifdef EQ_IsQueryEquationTypeBlock
		
			if(DBQ_DatabaseOptionChosen == DBQ_USE_LIST  &&  deletedDBName == DBQ_DatabaseName)
				{
				UserError("The database named, " + DBQ_DatabaseName + ", has been deleted, but Equation block number " + me + " was referencing a table in that database.");
				badDeleteOccurred = TRUE;
				doAbort = TRUE;
				}
		
		#endif //EQ_IsQueryEquationTypeBlock
		}
		
	else if(whatHappened == cTABLE_RENAMED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		changeTableName = DILinkUpdateString(cWHICH_NAME_SOURCE);
		
		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			
			whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);		//10/12/10
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);							//10/12/10
			usedTableName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
			if(usedDBIndex == changeDBIndex  &&  usedTableName == changeTableName)
				{
				usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
				newTableName = DBTableGetName(usedDBIndex, usedTableIndex);
				ListSetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD, newTableName);	//6 for string63
				}
			}

		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);		//10/12/10
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);							//10/12/10
			usedTableName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
			if(usedDBIndex == changeDBIndex  &&  usedTableName == changeTableName)
				{
				usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
				newTableName = DBTableGetName(usedDBIndex, usedTableIndex);
				ListSetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD, newTableName);	//6 for string63
				}
			}
		
		#ifdef EQ_IsQueryEquationTypeBlock
		
			if(DBQ_TableOptionChosen == DBQ_USE_LIST)
				{
				if(changeDBIndex == DBQ_DatabaseIndex_prm  &&  changeTableName == DBQ_TableName)
					{
					DBQ_TableName = DBTableGetName(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm);
					DBQ_DialogItemsUpdate();
					}
				}
				
		#endif //EQ_IsQueryEquationTypeBlock
		}
		
	else if(whatHappened == cTABLE_DELETED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		deletedTableIndex = DILinkUpdateInfo(cWHICH_TABLE_INDEX);
		deletedTableName = DILinkUpdateString(cWHICH_NAME_SOURCE);
		
		//search iVars for problem
		for(i=0; i<iVars_NumTableRows; i++)
			{
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
			usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == deletedTableIndex)
				{
				UserError("The table named, " + deletedTableName + ", has been deleted, but Equation block number " + me + " was referencing it.");
				iVars_BadDeleteOccurred = TRUE;
				iVars_UpdateTable = TRUE;
				doAbort = TRUE;
				break;
				}
			}

		//search oVars for problem
		for(i=0; i<oVars_NumTableRows; i++)
			{
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[i]);
			usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[i]);
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == deletedTableIndex)
				{
				UserError("The table named, " + deletedTableName + ", has been deleted, but Equation block number " + me + " was referencing it.");
				oVars_BadDeleteOccurred = TRUE;
				oVars_UpdateTable = TRUE;
				doAbort = TRUE;
				break;
				}
			}

		#ifdef EQ_IsQueryEquationTypeBlock
		
			if(DBQ_TableOptionChosen == DBQ_USE_LIST)
				{
				if(changeDBIndex == DBQ_DatabaseIndex_prm  &&  deletedTableName == DBQ_TableName)
					{
					UserError("The DB table named, " + DBQ_TableName + ", has been deleted, but Equation block number " + me + " was referencing a table in that database.");
					badDeleteOccurred = TRUE;
					doAbort = TRUE;
					}
				}
		
		#endif //EQ_IsQueryEquationTypeBlock
		}
		
	else if(whatHappened == cFIELD_RENAMED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		changeTableIndex = DILinkUpdateInfo(cWHICH_TABLE_INDEX);
		changeFieldName = DILinkUpdateString(cWHICH_NAME_SOURCE);

		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedFieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedFieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex  &&  usedFieldName == changeFieldName)
				{
				newFieldName = DBFieldGetName(usedDBIndex, usedTableIndex, usedFieldIndex);
				ListSetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD, newFieldName);	//6 for string63
				}
			}
		
		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedFieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedFieldName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex  &&  usedFieldName == changeFieldName)
				{
				newFieldName = DBFieldGetName(usedDBIndex, usedTableIndex, usedFieldIndex);
				ListSetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD, newFieldName);	//6 for string63
				}
			}
			
		#ifdef EQ_IsQueryEquationTypeBlock
		
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(DBQF_OptionsChosen[i] == DBQ_USE_LIST)
					{
					usedDBIndex = DBQ_DatabaseIndex_prm;
					usedTableIndex = DBQ_TableIndex_prm;
					usedFieldName = DBQF_FieldName[i];
					if(changeDBIndex == usedDBIndex  &&  changeTableIndex == usedTableIndex  &&  usedFieldName == changeFieldName)
						{
						usedFieldIndex = DBQF_FieldIndex[i];
						newFieldName = DBFieldGetName(usedDBIndex, usedTableIndex, usedFieldIndex);
						DBQF_FieldName[i] = newFieldName;
						}
					}
				}
		
		#endif //EQ_IsQueryEquationTypeBlock
		}

	else if(whatHappened == cFIELD_DELETED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		changeTableIndex = DILinkUpdateInfo(cWHICH_TABLE_INDEX);
		deletedFieldIndex = DILinkUpdateInfo(cWHICH_COLUMN);
		deletedFieldName = DILinkUpdateString(cWHICH_NAME_SOURCE);

		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedFieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedFieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				if(usedFieldName == deletedFieldName)
					{
					UserError("The field named, " + deletedFieldName + ", has been deleted, but Equation block number " + me + " was referencing it.");
					EQ_BlockUnRegisterStructure();
					iVars_BadDeleteOccurred = TRUE;
					iVars_UpdateTable = TRUE;
					doAbort = TRUE;
					break;
					}
				else //location of the field might have changed
					{
					newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
					if(newFieldIndex != usedFieldIndex)
						{
						iVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(iVars_DBCoords[whichVarRow], 3, newFieldIndex);		//3 for the field element
						iVars_UpdateTable = TRUE;
						
						//11/14/08	7.0.5		AJN
						//if(iVars_Types_Int[whichVarRow] == EQ_DB_INDEX)	//	6/25/09
						if(iVars_Types_Int[whichVarRow] == EQ_DB_FIELD_INDEX)
							{
							if(DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]) >= 1)	//if db index var is pointing towards a field
								{
								iVars_IndexesForDBIndexVars[whichVarRow] = DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
								}
							}
						}
					}
				}
			}
		
		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedFieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedFieldName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				if(usedFieldName == deletedFieldName)
					{
					UserError("The field named, " + deletedFieldName + ", has been deleted, but Equation block number " + me + " was referencing it.");
					EQ_BlockUnRegisterStructure();
					oVars_BadDeleteOccurred = TRUE;
					oVars_UpdateTable = TRUE;
					doAbort = TRUE;
					break;
					}
				else //location of the field might have changed
					{
					newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
					if(newFieldIndex != usedFieldIndex)
						{
						oVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(oVars_DBCoords[whichVarRow], 3, newFieldIndex);		//3 for the field element
						oVars_UpdateTable = TRUE;
						}
					}
				}
			}

		#ifdef EQ_IsQueryEquationTypeBlock
		
			usedDBIndex = DBQ_DatabaseIndex_prm;
			usedTableIndex = DBQ_TableIndex_prm;
			if(changeDBIndex == usedDBIndex  &&  changeTableIndex == usedTableIndex)
				{
				//search for DBQF iVars that might be affected
				for(i=0; i<iVars_NumTableRows; i++)
					{
					if(DBQF_OptionsChosen[i] == DBQ_USE_LIST)
						{
						usedFieldIndex = DBQF_FieldIndex[i];
						usedFieldName = DBQF_FieldName[i];
						
						//if the field this var was pointing to got deleted
						if(deletedFieldName == usedFieldName)
							{
							UserError("The field named, " + deletedFieldName + ", has been deleted, but Equation block number " + me + " was referencing it.");
							EQ_BlockUnRegisterStructure();
							iVars_BadDeleteOccurred = TRUE;
							iVars_UpdateTable = TRUE;
							doAbort = TRUE;
							break;
							}
						
						//else if the field index changed
						else if(deletedFieldIndex < usedFieldIndex)
							{
							newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
							DBQF_FieldIndex[i] = newFieldIndex;
							iVars_UpdateTable = TRUE;
							}
						}
					}
				
				//search for DBQFP iVars that might be affected
				for(i=0; i<iVars_NumTableRows; i++)
					{
					if(DBQFP_OptionsChosen[i] == DBQ_USE_LIST)
						{
						usedFieldIndex = DBQFP_FieldIndex[i];
						usedFieldName = DBQFP_FieldName[i];
						
						//if the field this var was pointing to got deleted
						if(deletedFieldName == usedFieldName)
							{
							UserError("The field named, " + deletedFieldName + ", has been deleted, but Equation block number " + me + " was referencing it.");
							EQ_BlockUnRegisterStructure();
							iVars_BadDeleteOccurred = TRUE;
							iVars_UpdateTable = TRUE;
							doAbort = TRUE;
							break;
							}
						
						//else if the field index changed
						else if(deletedFieldIndex < usedFieldIndex)
							{
							newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
							DBQFP_FieldIndex[i] = newFieldIndex;
							iVars_UpdateTable = TRUE;
							}
						}
					}
				}//if(changeDBIndex == usedDBIndex  &&  changeTableIndex == usedTableIndex)
		
		#endif //EQ_IsQueryEquationTypeBlock
		}

	//4/26/11
	//else if(whatHappened == cFIELD_INSERTED)
	else if(whatHappened == cFIELD_INSERTED  ||  whatHappened == cFIELD_MOVED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		changeTableIndex = DILinkUpdateInfo(cWHICH_TABLE_INDEX);
*/
		//4/26/11
		/*
		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedFieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedFieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
				if(newFieldIndex != usedFieldIndex)	//if location of the field changed
					{
					iVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(iVars_DBCoords[whichVarRow], 3, newFieldIndex);		//3 for the field element
					iVars_UpdateTable = TRUE;

					//11/14/08	7.0.5		AJN
					//if(iVars_Types_Int[whichVarRow] == EQ_DB_INDEX)		//	6/25/09
					if(iVars_Types_Int[whichVarRow] == EQ_DB_FIELD_INDEX)		
						{
						if(DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]) >= 1)	//if db index var is pointing towards a field
							{
							iVars_IndexesForDBIndexVars[whichVarRow] = DBFieldGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
							}
						}
					}
				}
			}

		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedFieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedFieldName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
				if(newFieldIndex != usedFieldIndex)
					{
					oVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(oVars_DBCoords[whichVarRow], 3, newFieldIndex);		//3 for the field element
					oVars_UpdateTable = TRUE;
					}
				}
			}
			
		*/
/*
		//4/26/11:  use names stored in DBNT linked lists to ensure we have up to date DB indexes
		iVars_DBNT_UpdateDBCoordsArray();
		oVars_DBNT_UpdateDBCoordsArray();
		iVars_UpdateTable = TRUE;
		oVars_UpdateTable = TRUE;

		#ifdef EQ_IsQueryEquationTypeBlock
		
			usedDBIndex = DBQ_DatabaseIndex_prm;
			usedTableIndex = DBQ_TableIndex_prm;
			if(changeDBIndex == usedDBIndex  &&  changeTableIndex == usedTableIndex)
				{
				//search for DBQF iVars that might be affected
				for(i=0; i<iVars_NumTableRows; i++)
					{
					if(DBQF_OptionsChosen[i] == DBQ_USE_LIST)
						{
						usedFieldIndex = DBQF_FieldIndex[i];
						usedFieldName = DBQF_FieldName[i];
						newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
						
						//if the field index changed
						if(newFieldIndex < usedFieldIndex)
							{
							DBQF_FieldIndex[i] = newFieldIndex;
							iVars_UpdateTable = TRUE;
							}
						}
					}
				
				//search for DBQFP iVars that might be affected
				for(i=0; i<iVars_NumTableRows; i++)
					{
					if(DBQFP_OptionsChosen[i] == DBQ_USE_LIST)
						{
						usedFieldIndex = DBQFP_FieldIndex[i];
						usedFieldName = DBQFP_FieldName[i];
						newFieldIndex = DBFieldGetIndex(usedDBIndex, usedTableIndex, usedFieldName);
						
						//if the field index changed
						if(newFieldIndex < usedFieldIndex)
							{
							DBQFP_FieldIndex[i] = newFieldIndex;
							iVars_UpdateTable = TRUE;
							}
						}
					}
				}//if(changeDBIndex == usedDBIndex  &&  changeTableIndex == usedTableIndex)
		
		#endif //EQ_IsQueryEquationTypeBlock
		}

	else if(whatHappened == cRECORD_INSERTED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		changeTableIndex = DILinkUpdateInfo(cWHICH_TABLE_INDEX);

		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				//if chosen table has a record ID field, the location of the chosen record ID may have changed
				usedRecordIDFieldIndex = DBRecordIDFieldGetIndex(usedDBIndex, usedTableIndex);
				if(usedRecordIDFieldIndex >= 1)
					{
					usedRecordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
					usedRecordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
					if(usedRecordName != "")
						{
						newRecordIndex = DBRecordFind(usedDBIndex, 		//database to search
													 usedTableIndex, 	//table to search
													 0, 				//use the record ID field as the search field
													 1, 				//the start record index
													 TRUE, 				//exact record match
													 usedRecordName);	//the search string
													 
						//if location of chosen record ID changed
						if(usedRecordIndex != newRecordIndex)
							{
							iVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(iVars_DBCoords[whichVarRow], 4, newRecordIndex);		//4 for the field element
							iVars_UpdateTable = TRUE;

							//11/14/08	7.0.5		AJN
							//if(iVars_Types_Int[whichVarRow] == EQ_DB_INDEX)		//	6/25/09
							if(iVars_Types_Int[whichVarRow] == EQ_DB_RECORD_INDEX)
								{
								if(DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]) >= 1)	//if db index var is pointing towards a record
									{
									iVars_IndexesForDBIndexVars[whichVarRow] = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
									}
								}
							}
						}
					}
				}
			}

		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				//if chosen table has a record ID field, the location of the chosen record ID may have changed
				usedRecordIDFieldIndex = DBRecordIDFieldGetIndex(usedDBIndex, usedTableIndex);
				if(usedRecordIDFieldIndex >= 1)
					{
					usedRecordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
					usedRecordName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
					if(usedRecordName != "")
						{
						newRecordIndex = DBRecordFind(usedDBIndex, 		//database to search
													 usedTableIndex, 	//table to search
													 0, 				//use the record ID field as the search field
													 1, 				//the start record index
													 TRUE, 				//exact record match
													 usedRecordName);	//the search string
													 
						//if location of chosen record ID changed
						if(usedRecordIndex != newRecordIndex)
							{
							oVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(oVars_DBCoords[whichVarRow], 4, newRecordIndex);		//4 for the field element
							oVars_UpdateTable = TRUE;
							}
						}
					}
				}
			}
		}
		
	else if(whatHappened == cRECORD_DELETED)
		{
		changeDBIndex = DILinkUpdateInfo(cWHICH_DB_INDEX);
		changeTableIndex = DILinkUpdateInfo(cWHICH_TABLE_INDEX);
		deletedRecordIndex = DILinkUpdateInfo(cWHICH_ROW);
			
		//search iVars_DBNameTrackingList
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				//if chosen table has a record ID field, the location of the chosen record ID may have changed
				usedRecordIDFieldIndex = DBRecordIDFieldGetIndex(usedDBIndex, usedTableIndex);
				if(usedRecordIDFieldIndex >= 1)
					{
					usedRecordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
					usedRecordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
					
					//if doing name tracking
					if(usedRecordName != "")
						{
						newRecordIndex = DBRecordFind(usedDBIndex, 		//database to search
													  usedTableIndex, 	//table to search
													  0, 				//use the record ID field as the search field
													  1, 				//the start record index
													  TRUE, 			//exact record match
													  usedRecordName);	//the search string
						
						//if record ID no longer exists					 
						if(newRecordIndex < 1)
							{
							UserError("Record named """ + usedRecordName + """, has been deleted, but Equation block number " + me + " was referencing it.");
							iVars_BadDeleteOccurred = TRUE;
							iVars_UpdateTable = TRUE;
							doAbort = TRUE;
							break;
							}
						
						//else if location of chosen record ID changed
						else if(usedRecordIndex != newRecordIndex)
							{
							iVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(iVars_DBCoords[whichVarRow], 4, newRecordIndex);		//4 for the field element
							iVars_UpdateTable = TRUE;

							//11/14/08	7.0.5		AJN
							//if(iVars_Types_Int[whichVarRow] == EQ_DB_INDEX)		//	6/25/09
							if(iVars_Types_Int[whichVarRow] == EQ_DB_RECORD_INDEX)
								{
								if(DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]) >= 1)	//if db index var is pointing towards a record
									{
									iVars_IndexesForDBIndexVars[whichVarRow] = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
									}
								}
							}
						}
					}
				
				//if chosen table does not have a record ID field
				else
					{
					//only if model is running do we police record deletions based on location
					if(simPhase == PHASE_SIMULATE || simPhase == PHASE_FINALCALC)
						{
						usedRecordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
						if(usedRecordIndex == deletedRecordIndex)
							{
							UserError("Record " + deletedRecordIndex + ", has been deleted, but Equation block number " + me + " was referencing it.");
							iVars_BadDeleteOccurred = TRUE;
							iVars_UpdateTable = TRUE;
							doAbort = TRUE;
							break;
							}
						}
					}
				}
			}
		
		//search oVars_DBNameTrackingList
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			usedDBIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			usedTableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			
			if(usedDBIndex == changeDBIndex  &&  usedTableIndex == changeTableIndex)
				{
				//if chosen table has a record ID field, the location of the chosen record ID may have changed
				usedRecordIDFieldIndex = DBRecordIDFieldGetIndex(usedDBIndex, usedTableIndex);
				if(usedRecordIDFieldIndex >= 1)
					{
					usedRecordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
					usedRecordName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
					
					//if doing name tracking
					if(usedRecordName != "")
						{
						newRecordIndex = DBRecordFind(usedDBIndex, 		//database to search
													  usedTableIndex, 	//table to search
													  0, 				//use the record ID field as the search field
													  1, 				//the start record index
													  TRUE, 			//exact record match
													  usedRecordName);	//the search string
						
						//if record ID no longer exists					 
						if(newRecordIndex < 1)
							{
							UserError("Record named """ + usedRecordName + """, has been deleted, but Equation block number " + me + " was referencing it.");
							oVars_BadDeleteOccurred = TRUE;
							oVars_UpdateTable = TRUE;
							doAbort = TRUE;
							break;
							}
						
						//if location of chosen record ID changed
						else if(usedRecordIndex != newRecordIndex)
							{
							oVars_DBCoords[whichVarRow] = DBAddressReplaceIndex(oVars_DBCoords[whichVarRow], 4, newRecordIndex);		//4 for the field element
							oVars_UpdateTable = TRUE;
							}
						}
					}
				
				//if chosen table does not have a record ID field
				else
					{
					//only if model is running do we police record deletions based on location
					if(simPhase == PHASE_SIMULATE || simPhase == PHASE_FINALCALC)
						{
						usedRecordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
						if(usedRecordIndex == deletedRecordIndex)
							{
							UserError("Record " + deletedRecordIndex + ", has been deleted, but Equation block number " + me + " was referencing it.");
							oVars_BadDeleteOccurred = TRUE;
							oVars_UpdateTable = TRUE;
							doAbort = TRUE;
							break;
							}
						}
					}
				}
			}
		}
			
	if( iVars_UpdateTable == TRUE  &&  (dialogIsOpen || iVars_TableIsCloned) )
		iVars_TableSetup();
		
	if( oVars_UpdateTable == TRUE  &&  (dialogIsOpen || oVars_TableIsCloned) )
		oVars_TableSetup();
		
	if( iVars_BadDeleteOccurred == TRUE  ||  oVars_BadDeleteOccurred == TRUE  ||  badDeleteOccurred == TRUE)
		{
		OpenBlockDialogBox(MyBlockNumber());
		}
	
	inLinkStructure = FALSE;

	if(doAbort == TRUE)
		AbortAllSims();

}//procedure EQ_OnLinkStructure
*/

//procedure EQ_OnConnectorToolTip()
//{
//
//	integer whichConNum;
//	integer nthCon;
//	string whichConName;
//	string tipText;
//	string CR;				//Carriage Return
//
////	EQ_ConIsWhichRowUpdate();
//	iVarsIn_ConIsWhichVarUpdate();
//	oVarsOut_ConIsWhichVarUpdate();
//	
//	whichConNum = ConnectorToolTipWhich();
//	nthCon = ConArrayGetNthCon(whichConNum);
//	whichConName = GetConName(MyBlockNumber(), whichConNum);
//
//	if( StrFind(whichConName, "iVarsIn", TRUE, FALSE) != -1 )
//		{
//		tipText = iVars_Names[iVars_ConIsWhichVar[nthCon]] + " = " + ConArrayGetValue(iVarsIn, nthCon);
//		
//		#ifdef CMC_chk
//			if(CMC_chk)
//				{
//				if(CMC_IVarsIn_Settings[nthCon] == CMC_IVAR_MSG_EMULATION)
//					tipText += "   Use message emulation [ME] (default)";
//				if(CMC_IVarsIn_Settings[nthCon] == CMC_IVAR_ALWAYS)
//					tipText += "   Always propagate message [A]";
//				if(CMC_IVarsIn_Settings[nthCon] == CMC_IVAR_NEVER)
//					tipText += "   Never propagate message [N]";
//				}
//		#endif
//		
//		ConnectorToolTipSet(tipText, TRUE);
//		}
//
//	if( StrFind(whichConName, "oVarsOut", TRUE, FALSE) != -1 )
//		{
//		tipText = oVars_Names[oVars_ConIsWhichVar[nthCon]] + " = " + ConArrayGetValue(oVarsOut, nthCon);
//		
//		#ifdef CMC_chk
//			if(CMC_chk)
//				{
//				if(CMC_OVarsOut_Settings[nthCon] == CMC_OVAR_MSG_EMULATION)
//					tipText += "   Use message emulation [ME] (default)";
//				if(CMC_OVarsOut_Settings[nthCon] == CMC_OVAR_VAL_CHANGE_ONLY)
//					tipText += "   Propagate message when con value changes [CVC]";
//				if(CMC_OVarsOut_Settings[nthCon] == CMC_OVAR_ALWAYS)
//					tipText += "   Always propagate message [A]";
//				if(CMC_OVarsOut_Settings[nthCon] == CMC_OVAR_NEVER)
//					tipText += "   Never progagate message [N]";
//				}
//		#endif
//
//		ConnectorToolTipSet(tipText, TRUE);
//		}
//
//}//EQ_OnConnectorToolTip()


procedure EQ_OnCancel()
{


}//procedure EQ_OnCancel()


procedure EQ_OnOK()
{

	integer i;
	integer numIncludes;
	integer foundRankVar;
	integer numSelectVars;
	
	
	
	if(EQE_EditorIsOpen == TRUE)
		{
		OpenExtendFile(EQE_PathName[0]);	//bring the editor to the front
		EQE_CloseEditor();
		}
	
	if(GetSimulationPhase() == PHASE_NOT_CURRENTLY_RUNNING)
		{
		EQ_CheckVariables();
		EQ_CheckForSpaces(TRUE);
		EQ_Compile(FALSE);
		
//		iVarsIn_ConLabelsSet();
//		oVarsOut_ConLabelsSet();

		if(Incl_chk)
			{
			//blank out the dynamic text dialog
			MakeArray(incl_PrototypesDisplay_DA, 1);
			StrReplaceDynamic(incl_PrototypesDisplay_DA, 0, 255, "");
			MakeArray(incl_PrototypesDisplay_DA, 0);
			
			//get dates of include files
			numIncludes = GetDimension(Incl_FileNames_ttbl);
			for(i=0; i<numIncludes; i++)
				{
				incl_ModifiedFileDates[i] = FileInfo(incl_PathNames[i], 2);		//2 for modified date
				}
			}
			
		#ifdef EQ_IsQueryEquationTypeBlock
			
			//check to make sure that the DBQ read value and DBQ read PRI variables have been assigned a field
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE)
					{
					if(DBQF_OptionsChosen[i] == DBQ_NOT_DEFINED)
						{
						UserError("A field must be chosen for the 'DBQ read value' input variable from row " + (i+1) + ".");
						abort;
						}
					}

				if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI)
					{
					if(DBQF_OptionsChosen[i] == DBQ_NOT_DEFINED)
						{
						UserError("A field must be chosen for the 'DBQ read PRI' input variable from row " + (i+1) + ".");
						abort;
						}
					}
				}

			//check oVars to make sure have at least one oRank variable
			foundRankVar = FALSE;
			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(StrFind(oVars_Types_str[i], "Record rank", FALSE, FALSE) != -1)
					{
					foundRankVar = TRUE;
					break;
					}
				}
			if(!foundRankVar)
				{
				UserError("At least one 'Record Rank' variable needs to be specified for this block.");
				AbortAllSims();
				}
			
		#endif //EQ_IsQueryEquationTypeBlock
		}

}//procedure Eqn_OnOk()


procedure EQ_OnDialogClose()
{

	EQ_Calcing = FALSE;
	EQ_Calcing2 = FALSE;
	
	#ifdef EQ_IsQueryEquationTypeBlock
	
		if(!iVars_TableIsCloned  &&  !dialogIsOpen)
			{
			DisposeArray(iVars_ColTagArray_DBQ_READ);
			DisposeArray(iVars_ColTagArray_ParentIndirectionField);
			}
	
	#endif //EQ_IsQueryEquationTypeBlock

}//procedure Eqn_OnOk()



procedure EQ_OnConnectionMake()
{

//	iVarsIn_ConnectorsSetup();
//	oVarsOut_ConnectorsSetup();

}//procedure EQ_OnConnectionMake()


procedure EQ_OnConnectionBreak()
{

//	iVarsIn_ConnectorsSetup();
//	oVarsOut_ConnectorsSetup();

}//procedure EQ_OnConnectionBreak()


procedure EQ_OnPreCheckData()
{

	integer i;
	integer me;
	string31 execDialogLabel;
	
	me = MyBlockNumber();
	
	//fill out iVars_Types_Int[]
	for(i=0; i<iVars_NumTableRows; i++)
		iVars_Types_Int[i] = EQ_VarTypeGet(iVars_Types_str[i]);

	
	//fill out oVars_Types_Int[]
	for(i=0; i<oVars_NumTableRows; i++)
		oVars_Types_Int[i] = EQ_VarTypeGet(oVars_Types_str[i]);

	#ifdef EQ_IsValueBlock
	
		//set reentrance flags
		inIVarsIn = FALSE;								//11/6/08
		inOVarsOut = FALSE;								//11/6/08
		inGoIn = FALSE;
		inBlockReceive0 = FALSE;
		inBlockReceive1 = FALSE;
		inPostInitSim = FALSE;
		inFinalCalc = FALSE;
		inLinkContent = FALSE;
		EQ_Calcing = FALSE;
		EQ_Calcing2 = FALSE;
	
		rescheduled = FALSE;
	
		nextCalcEventTime = startTime - 1;
			//in the case where user calculates an event time in CheckData or StepSize,
			//we need to hold off until InitSim.  set nextCalcEventTime = -1 here so that
			//we know if we need to post an event in InitSim.
	
		//4/14/09
		//initialize oVars_CalcNextEventIndex.  code below must be executed AFTER EQ_VarTypeGet() has been called
		#ifdef EQ_IsEquationValue
		if(currentSim == 0  &&  oVars_PreserveV7CalcNextEvent == FALSE)
		#else
		if(currentSim == 0)
		#endif
			{
			oVars_CalcNextEventIndex = -1;
			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(oVars_Types_Int[i] == EQ_CALC_NEXT_EVENT)
					{
					oVars_CalcNextEventIndex = i;
					break;
					}
				}
			}

	#endif //EQ_IsValueBlock
	
	EQ_CheckVariables();
	
	EQ_InitDataStructures();		//6/14/10

}//procedure EQ_OnPreCheckData()

/*
procedure EQ_OnCheckData()
{

	integer i, j;
	string31 execDialogLabel;
	real conVal;
	integer me;
	integer count;
	integer numConBlocks;
	integer totalConBlocks;
	
	me = MyBlockNumber();
	
	//3/30/11:  use names stored in DBNT linked lists to ensure we have up to date DB indexes
	iVars_DBNT_UpdateDBCoordsArray();
	oVars_DBNT_UpdateDBCoordsArray();
	
	EQ_DBIndexCheck();							//6/7/11
	
	#ifdef EQ_IsValueBlock
	
		exec 	= sysGlobalint1;

		if(GetRunParameterLong(7))			// check for duplicate random number seeds
			SeedListClear();

		CW_IVarsIn_GetWhichCon();	//get CW_IVarsIn_WhichConnector.
		CW_OVarsOut_GetWhichCon();	//get CW_OVarsOut_WhichConnector
		CW_LAM_GetWhichDBReadVar();		//get CW_LAM_WhichDBReadIVar

		if(calcBeforeStart_chk  &&  calcBeforeStart_pop == CALC_BEFORE_START_CHECKDATA)
			{
			#ifdef EQ_IsEquationValue
				EQ_Calc(FALSE, FALSE);	//FALSE- no iVar msgs, FALSE- no oVar msgs
			#else
				DBQ_DoQuery(FALSE, FALSE);
			#endif
	
			if(modelType == DISCRETE_EVENT)
				{
				if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
					{
					nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
					
					//5/15/09: events cannot be posted in StepSize.  wait until initsim to post it.
					}
				}
			}

	#endif //EQ_IsValueBlock
	
	//3/30/11
	//use names stored in DBNT linked lists to ensure we have up to date DB indexes
	//iVars_DBNT_UpdateDBCoordsArray();
	//oVars_DBNT_UpdateDBCoordsArray();

	if(currentSim == 0)
		{
		
		//get modelType.  sysGlobalInt23 is the executive's block number if it exists.
		execDialogLabel = GetDialogVariable(sysGlobalInt23, "executive_lbl", 0, 0);
		if(execDialogLabel == "executive")
			modelType = DISCRETE_EVENT;
		else
			modelType = CONTINUOUS;
		
		iVarsIn_ConnectorsSetup();		
		oVarsOut_ConnectorsSetup();		

		//check input cons
		iVarsIn_NumCons = ConArrayGetNumCons(MyBlockNumber(), "iVarsIn");
		iVarsIn_NumConsOld = iVarsIn_NumCons;
		for(i=0; i<iVarsIn_NumCons; i++)									
			iVarsIn_NumBlocksConnected[i] = GetConBlocks(MyBlockNumber(), iVarsIn_ConNums[i], connected);
		DisposeArray(connected);
		
		//1/14/10:  commented below out in favor of above line of code.  needed more than just TRUE/FALSE if connected		/*
		//for(i=0; i<iVarsIn_NumCons; i++)
		// 	{
			                                                                                                                                                //use the conditional "if" here because some blocks are setting con vals to 10,000 in 
			//checkdata for plotter blocks to know it's a continuously updated output variable
		//	conVal = ConArrayGetValue(iVarsIn, i);
		//	if(conVal != 0)
		//		iVarsIn_NumBlocksConnected[i] = TRUE;
		//	else
		//		iVarsIn_NumBlocksConnected[i] = FALSE;
		//	}
		
		iVarsIn_CheckConInputs();
		
		//check output cons
		#ifdef oVarsOut
			oVarsOut_NumCons = ConArrayGetNumCons(MyBlockNumber(), "oVarsOut");
			oVarsOut_NumConsOld = oVarsOut_NumCons;
			for(i=0; i<oVarsOut_NumCons; i++)									
				oVarsOut_NumBlocksConnected[i] = GetConBlocks(MyBlockNumber(), oVarsOut_ConNums[i], connected);
			DisposeArray(connected);
			
			//1/14/10:  commented below out in favor of above line of code.  needed more than just TRUE/FALSE if connected
			//for(i=0; i<oVarsOut_NumCons; i++)
			//	{
				//use the conditional "if" here because some blocks are setting con vals to 10,000 in 
				//checkdata for plotter blocks to know it's a continuously updated output variable
			//	conVal = ConArrayGetValue(oVarsOut, i);
			//	if(conVal != 0)
			//		oVarsOut_NumBlocksConnected[i] = TRUE;
			//	else
			//		oVarsOut_NumBlocksConnected[i] = FALSE;
			//     	}
			
			//commented out because it's not uncommon that a user will have an out conn not connected
			//oVarsOut_CheckConOutputs();
			
			//conditionally fill out CMC_OVarsOut_ConBlocks[][2]
			#ifdef EQ_IsEquationValue
			
				if(CMC_chk)
					{
					if(CurrentSim == 0)
						{
						DisposeArray(CMC_OVarsOut_ConBlocks);
						count = 0;
						totalConBlocks = 0;
						for(i=0; i<oVarsOut_NumCons; i++)
							{
							numConBlocks = GetConBlocks(me, oVarsOut_ConNums[i], connected);
							totalConBlocks += numConBlocks;
							MakeArray(CMC_OVarsOut_ConBlocks, totalConBlocks);
							for(j=0; j<numConBlocks; j++)
								{
								CMC_OVarsOut_ConBlocks[count][0] = connected[j][0];
								CMC_OVarsOut_ConBlocks[count][1] = connected[j][1];
								count++;
								}
							}
						DisposeArray(connected);
						}
					}
			
			#endif //EQ_IsEquationValue
		
		#endif //oVarsOut
*/
		//3/31/11
		/*
		//6/25/09:  see code below for what changes were made
		//AJN, 10/21/08: update iVars_IndexesForDBIndexVars[].
		//for(i=0; i<iVars_NumTableRows; i++)
		//	{
		//	if(iVars_Types_Int[i] == EQ_DB_INDEX)
		//		{
		//		if(DBTableGetIndexFromAddress(iVars_DBCoords[i]) < 1)
		//			iVars_IndexesForDBIndexVars[i] = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
		//		
		//		else if(DBFieldGetIndexFromAddress(iVars_DBCoords[i]) < 1)
		//			iVars_IndexesForDBIndexVars[i] = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
		//		
		//		else if(DBRecordGetIndexFromAddress(iVars_DBCoords[i]) < 1)
		//			iVars_IndexesForDBIndexVars[i] = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
		//		
		//		else
		//			iVars_IndexesForDBIndexVars[i] = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
		//		}
		//	}
		//NOTE!!:  must call iVars_DBNT_UpdateDBCoordsArray() first to update iVars_DBCoords[].
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX)
				{
				iVars_IndexesForDBIndexVars[i] = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
				}
			else if(iVars_Types_Int[i] == EQ_DB_TABLE_INDEX)
				{
				iVars_IndexesForDBIndexVars[i] = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
				}
			else if(iVars_Types_Int[i] == EQ_DB_FIELD_INDEX)
				{
				iVars_IndexesForDBIndexVars[i] = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
				}
			else if(iVars_Types_Int[i] == EQ_DB_RECORD_INDEX)
				{
				iVars_IndexesForDBIndexVars[i] = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
				}
			}
		*/
/*
		EQ_BlockRegisterContent();
		EQ_BlockRegisterStructure();
		
		}//if(currentSim == 0)

	//get my index for the timeBlocks array.  only do this for Equation(V) b/ other equation blocks do not access timeBlocks array
	if(modelType == DISCRETE_EVENT)
		{
		#ifdef EQ_IsValueBlock
			if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
				{
				myIndex_FutureEvent = sysGlobalint0;
				sysGlobalint0 += 1.0;
				}
		#endif
			
		#ifdef EQ_IsQueueEquation
			if(CW_CalcEventTime_chk)
				{
				myIndex_FutureEvent = sysGlobalint0;
				sysGlobalint0 += 1.0;
				}
		#endif
		}

	iVars_TableIsCloned = CloneFind(MyBlockNumber(), "iVars_ttbl", 1);
	oVars_TableIsCloned = CloneFind(MyBlockNumber(), "oVars_ttbl", 1);

	#ifdef EQ_IsQueryEquationTypeBlock
	
		if(!iVars_TableIsCloned  &&  !dialogIsOpen)
			{
			DisposeArray(iVars_ColTagArray_DBQ_READ);
			DisposeArray(iVars_ColTagArray_ParentIndirectionField);
			}
	
	#endif //EQ_IsQueryEquationTypeBlock
}//procedure EQ_OnCheckData()
*/
/*
procedure EQ_OnStepSize()
{

	integer i;
	
	#ifdef EQ_IsValueBlock
	
		if(calcBeforeStart_chk  &&  calcBeforeStart_pop == CALC_BEFORE_START_STEP_SIZE)
			{
			#ifdef EQ_IsEquationValue
				EQ_Calc(FALSE, FALSE);	//FALSE- no iVar msgs, FALSE- no oVar msgs
			#else
				DBQ_DoQuery(FALSE, FALSE);
			#endif
	
			if(modelType == DISCRETE_EVENT)
				{
				if(oVars_CalcNextEventIndex >= 0  ||  CW_Intervals_chk)
					{
					nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
					
					//5/15/09: events cannot be posted in StepSize.  wait until initsim to post it.
					}
				}
			}

	#endif //EQ_IsValueBlock


	#ifdef EQ_IsItemBlock
	
		for(i=0; i<iVars_NumTableRows; i++)
			{
			//if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
			if(
			   iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  iVars_Types_Int[i] == EQ_QEQ_LAST_ITEM_TO_EXIT  ||  
			   iVars_Types_Int[i] == EQ_DB_READ_VAL_USING_ATTRIB  ||  iVars_Types_Int[i] ==  EQ_DB_READ_PRI_USING_ATTRIB  
			  )
				Attrib_OnStepSize(iVars_Names[i], iVars_AttribTypes[i]);		//because openModel is called when add an H-Block to a model
			}

		for(i=0; i<oVars_NumTableRows; i++)
			{
			//if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
			if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  oVars_Types_Int[i] == EQ_DB_WRITE_VAL_USING_ATTRIB  ||  oVars_Types_Int[i] ==  EQ_DB_WRITE_PRI_USING_ATTRIB)
				Attrib_OnStepSize(oVars_Names[i], oVars_AttribTypes[i]);		//because openModel is called when add an H-Block to a model
			}
			
	#endif

}//procedure EQ_OnStepSize()

/*
procedure EQ_OnInitSim()
{

	integer i, j;
	integer randomVal;
	string15 attribName;
	integer me;
	integer itemInConNum;
	integer numInBlocks;
	integer numIncludes;
	real latestModDate;
	integer recompile;
	
	me = MyBlockNumber();

	EQ_InitDataStructures();		//6/14/10
	EQ_CheckSeeds();				//7/21/11:  this function needs to be called immediately AFTER EQ_InitDataStructures() in InitSim (but not when it gets called in CheckData)
			
*/		
	//6/14/10
	/*
	EQ_Calcing = FALSE;
	EQ_Calcing2 = FALSE;
	inLinkStructure = FALSE;

	InitSeeds();															// initialize seeds for random number generator

	dialogIsOpen = BlockDialogIsOpen(MyBlockNumber());
	
	//get iVarsIn con nums
	for(i=0; i<iVarsIn_NumCons; i++)
		iVarsIn_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "IVarsIn", i);

	//conditionally initialize the iVars_Values
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] != EQ_STATIC_FRI  &&  iVars_Types_Int[i] != EQ_STATIC_MRI  &&  iVars_Types_Int[i] != EQ_STATIC_OPEN_MODEL)
			iVars_Values[i] = blank;
		}
	*/
/*	
	if(modelType == DISCRETE_EVENT)
		{
		GetSimulateMsgs(FALSE);							//if discrete event model, we don't want simulate messages

		if( GetPassedArray(sysGlobal0, timeArray) )
			{
			CheckVersionExec();			//make sure the executive in the model is from the Item library
			exec = sysGlobalInt23;
			}
		else
			{
			UserError("The Executive block must be present and to the left of all blocks on the worksheet.");
			AbortAllSims();
			}

		#ifdef EQ_IsValueBlock
			if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
				{
				GetPassedarray(sysGlobal7,timeBlocks);		//get the pointer to timeBlocks
				timeblocks[myIndex_FutureEvent] = MyBlockNumber();		//put this block's number in the reserved position in TimeBlocks
				}
		#endif
		
		#ifdef EQ_IsQueueEquation
			if(CW_CalcEventTime_chk)
				{
				GetPassedarray(sysGlobal7,timeBlocks);		//get the pointer to timeBlocks
				timeblocks[myIndex_FutureEvent] = MyBlockNumber();		//put this block's number in the reserved position in TimeBlocks
				}
		#endif
		}
*/
	//6/14/10
	/*
	//recompile if include file is out of date
	if(currentSim == 0)
		{
		if(Incl_chk)
			{
			recompile = FALSE;
			numIncludes = GetDimension(Incl_FileNames_ttbl);
			for(i=0; i<numIncludes; i++)
				{
				latestModDate = FileInfo(incl_PathNames[i], 2);
				if(incl_ModifiedFileDates[i] != latestModDate)	//2 for modified date
					{
					incl_ModifiedFileDates[i] = latestModDate;
					recompile = TRUE;
					}
				}
			if(recompile == TRUE)
				{
				EQ_Compile(FALSE);
				}
			}
		}
	*/
/*	
	#ifdef EQ_IsValueBlock		//if is the Equation(I) or Query Equation(I)
*/
/*		
		//6/14/10
		/*
		//time units conversion stuff
		if(CW_Intervals_TimeUnits_pop == DEFAULT_MODEL_TIME_UNITS)	//if true, then default model time units selected
			blockTimeUnits = GetTimeUnits();	
		else
			blockTimeUnits = CW_Intervals_TimeUnits_pop;
		
		if(EDCalendarDates()  &&  blockTimeUnits == TU_MILLISECONDS)
			{
			UserError("There is a problem in "+BlockName(me)+" block number, " + me + ".  Since model time is in Julian dates, this block's time units must be in seconds or greater.");
			abort;
			}
	
		if(EDCalendarDates())
			timeUnitConversionFactor = 1.;	//used to convert block time units to global time units
		else
			timeUnitConversionFactor = ConvertTimeUnits(1,blockTimeUnits, GetTimeUnits());	//used to convert block time units to global time units
		*/
/*		
		//1/8/10: get pointer to timeEventMsgType array in executive and tell 
		//Excecutive to send a BlockReceive1 message when a future event occurs
		if(modelType == DISCRETE_EVENT)
			{
			if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
				{
				GetPassedarray(sysGlobal13,timeEventMsgType);
				timeEventMsgType[myIndex_FutureEvent] = BlockReceive1Msg;
				}
			}
	
		//NOTE!  must initialize CW_LAM_WhichDBReadIVar in CheckData

		if(currentSim == 0)
			{
			if(CW_Intervals_chk)
				{
				if(modelType == CONTINUOUS)
					{			
					UserError("There is a problem with "+BlockName(me)+" block number " + me + ".  The option to calculate at even time intervals may only be used in discrete event models.");
					AbortAllSims();
					}
				}
		
			}//if(currentSim == 0)

		if(calcBeforeStart_chk)
			{
			if(calcBeforeStart_pop == CALC_BEFORE_START_INITSIM)
				{
				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);	//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
					
				#ifdef EQ_IsQueryEquationValueBlock
					DBQ_DoQuery(FALSE, FALSE);	//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif

				//post this block's next event
				if(modelType == DISCRETE_EVENT)
					{
					if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
						{
						nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
						timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
						lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
						}
					}
				}
			else
				{
				if(calcBeforeStart_pop == CALC_BEFORE_START_CHECKDATA  ||  calcBeforeStart_pop == CALC_BEFORE_START_STEP_SIZE)
					{
					if(modelType == DISCRETE_EVENT)
						{
						if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
							{
							if(nextCalcEventTime >= startTime)	//if this condition true, then we know an event got calculated in either checkdata or stepsize
								{
								timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
								lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
								}
							}
						}
					}
				}
			}
		else if(CW_Intervals_chk)
			{
			if(modelType == DISCRETE_EVENT)
				{
				nextCalcEventTime = EQ_GetNextCalcEventTime();
				timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
				lastCalculatedEventTime = nextCalcEventTime;
				}
			}
	
		//resize and initialize iVarsIn_MsgEverReceived[]
		if(CurrentSim == 0)
			{
			MakeArray(iVarsIn_MsgEverReceived, iVarsIn_NumCons);
			}
		for(i=0; i<iVarsIn_NumCons; i++)
			iVarsIn_MsgEverReceived[i] = FALSE;

	#endif //EQ_IsValueBlock
	
	
	#ifdef EQ_IsItemBlock
	
		//determine the block number of the connected block
		inBlock = 0;
		itemInConNum = GetConNumber(MyBlockNumber(), "itemIn");	//btb animation- used in animation
		numInBlocks = GetConBlocks(MyBlockNumber(), itemInConNum, connected);
		if (numInBlocks > 0)
			{
			inBlock		= connected[0][0];
			inConn		= connected[0][1];
			}
		DisposeArray(connected);
			//  if we are only connected to one block.  This is used to speed up 
			//  the sending of messages.  if there's more then one connected block,
			//  inBlock and out block still == 0.
			//  getConBlocks() always returns the block that is upstream as the 
			//  first element in the array when called from an input connector.  
			//  Therefore message optimization can be used with parrallel processing
		
		//get GA index
		if(CurrentSim == 0)
			{
			attribValuesIndex = GaGetIndex("_AttribValues");
			}

	#endif //EQ_IsItemBlock

	
	//get the column IDs for iVars
	if(CurrentSim == 0)
		{
		//fill out iVars_AttribColumnIndexes
		for(i=0; i<iVars_NumTableRows; i++)
			{
			//ajn- this condition does not work because we handle the "QEQ attrib last item to exit" input variable in EQ_VarTypeGet()
			//if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)
			
			//if(iVars_Types_str[i] == "Attribute"  ||  iVars_Types_str[i] == "DB read value using attrib"  ||  iVars_Types_str[i] == "DB read PRI using attrib")	//ajn, 7.0.5, 10/24/08:
			if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  iVars_Types_Int[i] == EQ_DB_READ_VAL_USING_ATTRIB  ||  iVars_Types_Int[i] == EQ_DB_READ_PRI_USING_ATTRIB)
				{
				#ifdef EQ_IsItemBlock
					iVars_AttribColumnIndexes[i] = Attrib_GetColumnIndex(iVars_Names[i]);
				#endif
				}
			else 
				//iVars_AttribColumnIndexes[i] = EQ_VarTypeGet(iVars_Types_str[i]);	//6/19/09
				iVars_AttribColumnIndexes[i] = PROPERTY_TYPE_NO_PROPERTY;
			}
		}
		
	//6/14/10
	/*
	//set up iVarsIn connector arrays
	if(CurrentSim == 0)
		{
		#ifdef iVarsIn
			iVarsIn_VarIsWhichConUpdate();
			iVarsIn_ConIsWhichVarUpdate();	//12/16/08	7.0.5	AJN
		#endif
		}
	*/

	
	//6/14/10
	/*
	//conditionally initialize the oVars_Values
	#ifdef oVars_Initialize_prm
		for(i=0; i<oVars_NumTableRows; i++)
			oVars_Values[i] = oVars_Initialize_prm;
	#else
		for(i=0; i<oVars_NumTableRows; i++)
			oVars_Values[i] = 0.0;
			//oVars_Values[i] = blank;	
				//"blank" was causing problems in continuous models, eg, a model where simulation order is such that the equation 
				//needs to provide a result before it has received it's first "on simulate" message.  (reference Inventory Mgt.mox)
	#endif
	*/
/*
	
	#ifdef oVarsOut
*/
		//6/14/10
		/*
		//set oVarsOut
		if(CurrentSim == 0)
			{
			oVarsOut_VarIsWhichConUpdate();	//Note!  must get oVarsOut_VarIsWhichCon first
			oVarsOut_ConIsWhichVarUpdate();
			}
		*/
/*
		//6/14/10:  need to leave this here becvause the app changes the values of the connectors in CheckData
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(oVars_VarIsWhichCon[i] != -1)
				ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);	//	6/25/08	7.0.3		AJN	
			}
*/	
		//6/14/10
		/*
		//get oVarsOut con nums
		for(i=0; i<oVarsOut_NumCons; i++)
			oVarsOut_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "oVarsOut", i);
		*/
/*
	#endif //oVarsOut

	//get the column IDs for oVars
	if(CurrentSim == 0)
		{
		//fill out oVars_AttribColumnIndexes
		for(i=0; i<oVars_NumTableRows; i++)
			{
			//ajn, 7.0.5, 10/24/08: this condition works, but switching to oVars_Types_Int[] because it's faster
			//if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)
			if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  oVars_Types_Int[i] == EQ_DBQS_ATTRIB  ||  
			   oVars_Types_Int[i] == EQ_DB_WRITE_VAL_USING_ATTRIB  ||  oVars_Types_Int[i] == EQ_DB_WRITE_PRI_USING_ATTRIB)
				{
				#ifdef EQ_IsItemBlock
					oVars_AttribColumnIndexes[i] = Attrib_GetColumnIndex(oVars_Names[i]);
				#endif
				}
			else
				//oVars_AttribColumnIndexes[i] = EQ_VarTypeGet(oVars_Types_str[i]);	//6/19/09
				oVars_AttribColumnIndexes[i] = PROPERTY_TYPE_NO_PROPERTY;
			}
		}
*/		
	//6/14/10
	/*
	//fill out oVars_GetValFromIVars
	if(CurrentSim == 0)
		{
		for(i=0; i<oVars_NumTableRows; i++)
			oVars_GetValFromIVars[i] = -1;
	
		for(i=0; i<oVars_NumTableRows; i++)
			{
			for(j=0; j<iVars_NumTableRows; j++)
				{
				if(oVars_Names[i] == iVars_Names[j])
					oVars_GetValFromIVars[i] = j;
					//if the same variable name is used to declare both an iVar and and oVar 
					//EquationCalculateDynamicVariables() will actually store the value of the 
					//oVar in the iVar.  oVars_GetValFromIVars[i] is used to go grab the value 
					//from the iVars array, stuff it in the oVars array, and then restore the 
					//original value of iVar.
				}
			}
		}
	
	//initialize the equation's static variables
	if(CurrentSim == 0)
		{
		for(i=0;i<iVars_NumTableRows;i++)
			{
			if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI)
				{
				iVars_Values[i] = iVars_StaticInitValues[i];
				iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i];
				}
			}
		}
	else
		{
		for(i=0;i<iVars_NumTableRows;i++)
			{
			if(iVars_Types_Int[i] == EQ_STATIC_MRI)
				{
				iVars_Values[i] = iVars_StaticInitValues[i];
				iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i];
				}
			}
		}
	*/
/*
	#ifdef SendProof_chk
		
		//get event array pointers
		if(CurrentSim == 0)
			{
			if(SendProof_chk)											// if the proof checkbox is selected
				{
				GAProof = GAGetIndex("_proof");							// get the index of the proof global array
				**  2/13/08	7.0.2		DJK			Added error message if Send GlobalProofStr to Proof is checked an there is no Proof Control block
				if(GAProof < 0)
					{
					UserError("Send GlobalProofStr to Proof is checked in the animation tab, but no Proof Control block is in the model. Add a Proof Control block and configure the Proof Animation parameters. Error found in "+BlockName(me)+" number "+me);
					AbortAllSims();
					}
				ProofBlock = GaGetInteger(GAProof,PRF_CONTROL_ROW,0);	// block number of the proof control block
				GetPassedArray(SysGlobal19,PassStringToProof);			// get the passed string which will be sent to the proof conrol block
				}
			}
	
	#endif //SendProof_chk

}//procedure EQ_OnInitSim()
*/
/*
procedure EQ_OnPostInitSim()
{

	#ifdef EQ_IsValueBlock
		
		inPostInitSim = TRUE;
		
		if(calcBeforeStart_chk  &&  calcBeforeStart_pop == CALC_BEFORE_START_POSTINITSIM)
			{
			if(modelType == DISCRETE_EVENT)
				{
				//send iVarsIn messages
				iVarsIn_SendMsgs(MSG_RECEIVED_FROM_POST_INITSIM);
				
				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
		
				#ifdef EQ_IsQueryEquationValueBlock
					DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
		
				//send oVarsOut messages
				oVarsOut_SendMsgs(MSG_RECEIVED_FROM_POST_INITSIM);
	
				//post this block's next event
				if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
					{
					nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
					timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
					lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
					}
				}
			else //if(modelType == CONTINUOUS)
				{
				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
		
				#ifdef EQ_IsQueryEquationValueBlock
					DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
				}
			}
			
		inPostInitSim = FALSE;
		
	#endif //EQ_IsValueBlock

}//procedure EQ_OnPostInitSim()


procedure EQ_OnCloneInit()
{

	iVarsIn_ConnectorsSetup();
	oVarsOut_ConnectorsSetup();

	iVars_TableSetup();
	oVars_TableSetup();

}//procedure EQ_OnCloneInit()


procedure EQ_OnOpenModel(integer calledFrom)
{

	integer i, j;
	integer numRows;
	integer numCols;
	integer me;
	real applicationVersion;
	real modelVersion;
	integer numIncludes;
	string includeName;
	integer doCompile;

	me = MyBlockNumber();
	
	applicationVersion = GetExtendVersion(0);
	modelVersion = GetExtendVersion(1);

	MySeed = randomGetSeed() + me + 1;

	EQ_Calcing = FALSE;
	EQ_Calcing2 = FALSE;
	
	inLinkStructure = FALSE;
	
	EQE_EditorIsOpen = FALSE;

	EQE_EditorIsOpen = FALSE;
	
	#ifdef iVars_TypesOldUnused2
		DisposeArray(iVars_TypesOldUnused2);
	#endif
	
	#ifdef oVars_TypesOldUnused2
		DisposeArray(oVars_TypesOldUnused2);
	#endif
	
	#ifdef EQ_IsQueryEquationTypeBlock
		
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(iVars_Types_str[i] == "_QEQ Curr Best Item Rank")
				{
				iVars_Types_str[i] = "QEQ current best item rank";
				}
			}
	
	#endif
	
	#ifdef EQ_IsQueryEquationTypeBlock
		
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(iVars_Types_str[i] == "_DBQP CurrBestRecordRankResult")
				{
				iVars_Types_str[i] = "DBQ current best record rank";
				}
			if(iVars_Types_str[i] == "_DBQS CurrBestRecordRankResult")
				{
				iVars_Types_str[i] = "DBQS current best rank result";
				}
			if(iVars_Types_str[i] == "_DBQP NumNonBlankRankedRecords")
				{
				iVars_Types_str[i] = "DBQ num non-blank ranks";
				}
			if(iVars_Types_str[i] == "_DBQS NumNonBlankRankedRecords")
				{
				iVars_Types_str[i] = "DBQS num non-blank ranks";
				}
			}
	
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(oVars_Types_str[i] == "_DBQP record rank")
				{
				oVars_Types_str[i] = "DBQ record rank";
				}
			}
	
	#endif
	
	#ifdef iVars_DAUnused
		//changed the iVars_DA array from String15 to String31.  port the data from the old array to the new array
		numRows = GetDimension(iVars_DAUnused);
		numCols = GetDimensionColumns(iVars_DA);
		if(numRows > 0)
			{
			MakeArray(iVars_DA, numRows);
			
			for(i=0; i<numRows; i++)
				for(j=0; j<numCols; j++)
					iVars_DA[i][j] = iVars_DAUnused[i][j];
	
			DisposeArray(iVars_DAUnused);
			}
	#endif
	
	#ifdef oVars_DAUnused
		//changed the oVars_DA array from String15 to String31.  port the data from the old array to the new array
		numRows = GetDimension(oVars_DAUnused);
		numCols = GetDimensionColumns(oVars_DA);
		if(numRows > 0)
			{
			MakeArray(oVars_DA, numRows);
			
			for(i=0; i<numRows; i++)
				for(j=0; j<numCols; j++)
					oVars_DA[i][j] = oVars_DAUnused[i][j];
			
			DisposeArray(oVars_DAUnused);
			}
	#endif
	
	#ifdef iVars_TypesUnused
		//changed the iVars_Types_str array from String15 to String31.  port the data from the old array to the new array
		numRows = GetDimension(iVars_TypesUnused);
		if(numRows > 0)
			{
			MakeArray(iVars_Types_str, numRows);
			for(i=0; i<numRows; i++)
				{
				iVars_Types_str[i] = iVars_TypesUnused[i];
				}
			DisposeArray(iVars_TypesUnused);
			}
	#endif

	#ifdef oVars_TypesUnused
		//changed the oVars_Types_str array from String15 to String31.  port the data from the old array to the new array
		numRows = GetDimension(oVars_TypesUnused);
		if(numRows > 0)
			{
			MakeArray(oVars_Types_str, numRows);
			for(i=0; i<numRows; i++)
				{
				oVars_Types_str[i] = oVars_TypesUnused[i];
				}
			DisposeArray(oVars_TypesUnused);
			}
	#endif
	
	//changed the names of some iVar types.  consequently, need change iVars_Types_str so pre-existing models work
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_str[i] == "_DB Value"  ||  iVars_Types_str[i] == "_DB read"  ||  iVars_Types_str[i] == "_DB read value")
			iVars_Types_str[i] = "DB read value";

		else if(iVars_Types_str[i] == "_DB read index")
			iVars_Types_str[i] = "DB read PRI";
		
		else if(iVars_Types_str[i] == "_Attrib db val"  ||  iVars_Types_str[i] == "_AttribDB read"  ||  iVars_Types_str[i] == "_Attrib DB Read Value")
			iVars_Types_str[i] = "DB read value using attrib";
		
		else if(iVars_Types_str[i] == "_Attrib DB read index"  ||  iVars_Types_str[i] == "_Attrib DB Read PRI")
			iVars_Types_str[i] = "DB read PRI using attrib";
		
		else if(iVars_Types_str[i] == "_Static FR init")
			iVars_Types_str[i] = "Static first run init";
		
		else if(iVars_Types_str[i] == "_Static MR init")
			iVars_Types_str[i] = "Static multi run init";

		else if(iVars_Types_str[i] == "_Static OM init")
			iVars_Types_str[i] = "Static open model init";

		else if(iVars_Types_str[i] == "_Last item"  ||  iVars_Types_str[i] == "_Attrib last item to exit")
			iVars_Types_str[i] = "QEQ attrib last item to exit";
		}
	
	//changed the names of some oVar types.  consequently, need change oVars_Types_str so pre-existing models work
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_Types_str[i] == "_DB Value"  ||  oVars_Types_str[i] == "_DB write"  ||  oVars_Types_str[i] == "_DB write value")
			oVars_Types_str[i] = "DB write value";

		else if(oVars_Types_str[i] == "_DB write index")
			oVars_Types_str[i] = "DB write PRI";
		
		else if(oVars_Types_str[i] == "_Attrib db val"  ||  oVars_Types_str[i] == "_AttribDB write"  ||  oVars_Types_str[i] == "_Attrib DB write value")
			oVars_Types_str[i] = "DB write value using attrib";

		else if(oVars_Types_str[i] == "_Attrib DB write index"  ||  oVars_Types_str[i] == "_Attrib DB Write PRI")
			oVars_Types_str[i] = "DB write PRI using attrib";
		}
	
	//make sure iVars_IndexesForDBIndexVars was dimensioned properly
	numRows = GetDimension(iVars_IndexesForDBIndexVars);
	if(numRows != iVars_NumTableRows)
		{
		MakeArray(iVars_IndexesForDBIndexVars, iVars_NumTableRows);
		}

	//make sure iVars_Types_Int was dimensioned properly
	numRows = GetDimension(iVars_Types_Int);
	if(numRows != iVars_NumTableRows)
		{
		MakeArray(iVars_Types_Int, iVars_NumTableRows);
		}

	//make sure oVars_Types_Int was dimensioned properly
	numRows = GetDimension(oVars_Types_Int);
	if(numRows != oVars_NumTableRows)
		{
		MakeArray(oVars_Types_Int, oVars_NumTableRows);
		}

	//transition model from v7 to v8
	if(applicationVersion >= 800  &&  modelVersion < 800)
		{
		dbg_HiddenBlock = -1;

		//6/25/09:  convert the "db index" iVars into one of four different iVars
		//NOTE:  must execute this code before call to EQ_VarTypeGet() below!!
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(iVars_Types_str[i] == "_DB index")
				{
				if(DBTableGetIndexFromAddress(iVars_DBCoords[i]) < 1)
					iVars_Types_str[i] = "DB database index";

				else if(DBFieldGetIndexFromAddress(iVars_DBCoords[i]) < 1)
					iVars_Types_str[i] = "DB table index";
				
				else if(DBRecordGetIndexFromAddress(iVars_DBCoords[i]) < 1)
					iVars_Types_str[i] = "DB field index";
				
				else
					iVars_Types_str[i] = "DB record index";
				}
			}
		}
	
	//transition v7 varTypes to v8: do a blanket removal of the "_" the varType name.
	//NOTE: do not check version because don't want to ruin models built in the beta
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(StrFind(iVars_Types_str[i], "_", FALSE, FALSE) >= 0)
			{
			iVars_Types_str[i] = StrPart(iVars_Types_str[i], 1, StrLen(iVars_Types_str[i]));
			}		
		}
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(StrFind(oVars_Types_str[i], "_", FALSE, FALSE) >= 0)
			{
			oVars_Types_str[i] = StrPart(oVars_Types_str[i], 1, StrLen(oVars_Types_str[i]));
			}		
		}

	//fill out iVars_Types_Int[] before call iVarsIn_ConnectorsSetup(), or iVars_DBNT_BuildList(), or iVars_DBNT_GarbageCollection()
	for(i=0; i<iVars_NumTableRows; i++)
		iVars_Types_Int[i] = EQ_VarTypeGet(iVars_Types_str[i]);

	//fill out oVars_Types_Int[] before call oVarsIn_ConnectorsSetup(), or oVars_DBNT_BuildList(), or oVars_DBNT_GarbageCollection()
	for(i=0; i<oVars_NumTableRows; i++)
		oVars_Types_Int[i] = EQ_VarTypeGet(oVars_Types_str[i]);

	//intialize static open model init vars
	for(i=0;i<iVars_NumTableRows;i++)
		{
		if(iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
			{
			iVars_Values[i] = iVars_StaticInitValues[i];
			iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i];
			}
		}

	//linked list name tracking stuff
	iVars_DBNT_BuildList();					//make sure iVars_DBNameTrackingList exists 
	oVars_DBNT_BuildList();					//make sure oVars_DBNameTrackingList exists 
	iVars_DBNT_GarbageCollection();
	oVars_DBNT_GarbageCollection();

	#ifdef EQ_IsItemBlock
	
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(
			   iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  iVars_Types_Int[i] == EQ_QEQ_LAST_ITEM_TO_EXIT  ||  
			   iVars_Types_Int[i] == EQ_DB_READ_VAL_USING_ATTRIB  ||  iVars_Types_Int[i] ==  EQ_DB_READ_PRI_USING_ATTRIB  
			  )
				Attrib_AddName(iVars_Names[i], iVars_AttribTypes[i]);		//because openModel is called when add an H-Block to a model
			}

		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  ||  oVars_Types_Int[i] == EQ_DB_WRITE_VAL_USING_ATTRIB  ||  oVars_Types_Int[i] ==  EQ_DB_WRITE_PRI_USING_ATTRIB)
				Attrib_AddName(oVars_Names[i], oVars_AttribTypes[i]);		//because openModel is called when add an H-Block to a model
			}
		
	#endif

	equation_dtxt = DynamicTextArrayNumber(EQ_EquationText); //points "equation_dtxt" to "EQ_EquationText".

	//force compile in OpenModel if:
	//	1. if includes are used, since the includes may have changed.
	//	2. if equation debugger on, then we need to create the remote, hidden block
	doCompile = FALSE;
	if(Incl_chk)			
		{
		numIncludes = GetDimension(Incl_FileNames_ttbl);
		for(i=0; i<numIncludes; i++)
			{
			includeName = incl_FileNames_DA[i][INCL_NAME_COL];
			if(includeName != "")
				{
				doCompile = TRUE;
				break;
				}
			}
		}
	if(dbg_chk == TRUE)
		{
		doCompile = TRUE;
		}
	if(doCompile == TRUE)
		EQ_Compile(FALSE);		
	
	iVars_ResizeDynamicArrays(RESIZE_ADD_SUBTRACT_FROM_END);
	oVars_ResizeDynamicArrays(calledFrom, RESIZE_ADD_SUBTRACT_FROM_END);
	
	//needed to make sure connector labeling is done properly
	iVarsIn_ConnectorsSetup();
	oVarsOut_ConnectorsSetup();

	iVars_TableSetup();
	oVars_TableSetup();
	
	EQ_BlockRegisterStructure();
	EQ_BlockRegisterContent();
	
	#ifdef CW_IVarsIn_CalcControl_chk
		//CW_IVarsIn_Animate();			//7/5/11
		CW_ConnectorAnimate();
	#endif
	
	#ifdef CW_OVarsOut_CalcControl_chk
		//CW_OVarsOut_Animate();			//7/5/11
		CW_ConnectorAnimate();
	#endif
	
	//4/20/11
	if(applicationVersion >= 802  &&  modelVersion < 802  && modelIs_802_OrOlder != TRUE)
		{
		modelIs_802_OrOlder = TRUE;
		convertDateTimeData_chk = TRUE;
			//NOTE:	this is needed to ensure older models run the same in 8.0.2 or later.  in older versions
			//		convertDateTimeData_chk did not exist.  consequently, the equation blocks always did the 
			//		date/time conversion implicitly.  in 8.0.2 we added convertDateTimeData_chk and defaulted 
			//		it to off so that default behavior was to not do the date time conversion.
		}

}//procedure EQ_OnOpenModel(integer calledFrom)


procedure EQ_OnEndSim()
{

	#ifdef EQ_IsItemBlock
	
		DisposeArray(attribPopContents);
		TCE_OnEndsim();								// dispose of the tracing arrays

	#endif //EQ_IsItemBlock
	
}//procedure EQ_OnEndSim()
/*
procedure EQ_OnAbortSim()
{

	integer i;
	
	//make sure EQ_Calcing is reset to false in the event abort was called in the user's equation
	EQ_Calcing = FALSE;
	
	#ifdef EQ_IsItemBlock
	
		DisposeArray(attribPopContents);

	#endif //EQ_IsItemBlock
	
	#ifdef EQ_IsEquationValue
	
		//executed only if the user has chosen the option to calc at end of sim
		if(calcAtEnd_chk  &&  calcAtEnd_pop == CALC_AT_END_ABORTSIM)
			{
			if(modelType == DISCRETE_EVENT)
				{
				//send input messages
				iVarsIn_SendMsgs(MSG_RECEIVED_FROM_ABORTSIM);

				EQ_Calc(FALSE, FALSE);	//FALSE- no iVar msgs, FALSE- no oVar msgs
				
				//send output messages
				oVarsOut_SendMsgs(MSG_RECEIVED_FROM_ABORTSIM);
				}
			else
				{
				EQ_Calc(FALSE, FALSE);
				}
			}
	
	#endif //EQ_IsEquationValue

	#ifdef EQ_IsQueryEquationValueBlock
	
		//executed only if the user has chosen the option to calc at end of sim
		if(calcAtEnd_chk  &&  calcAtEnd_pop == CALC_AT_END_ABORTSIM)
			{
			if(modelType == DISCRETE_EVENT)
				{
				//send messages out the iVarsIn input connectors
				for(i=0; i<iVarsIn_NumCons; i++)
					{
					SendMsgToOutputs(iVarsIn_ConNums[i]);
					}
				
				//DBQ_DoQuery(FALSE, FALSE);	//FALSE- no iVar msgs, FALSE- no oVar msgs
				//send messages out oVarsOut output connectors
				//for(i=0; i<oVarsOut_NumCons; i++)
				//	{
				//	SendMsgToOutputs(oVarsOut_ConNums[i]);
				//	}
				
				DBQ_DoQuery(FALSE, TRUE);	//FALSE- no iVar msgs, TRUE- oVar msgs
				}
			else
				{
				DBQ_DoQuery(FALSE, FALSE);
				}
			}
	
	#endif //EQ_IsQueryEquationValueBlock

}//procedure EQ_OnAbortSim()
*/
/*
procedure EQ_OnDialogClick()
{

	string dName;		// name of the dialog item clicked
	string dNum;		// number of the dialog popup clicked
	real returnedDBCoordinate;
	integer legitField;
	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	real oldInitVal;
	real newInitVal;
	integer numRecords;
	real dbaddress;
	integer numRows;

	rowClicked = WhichDTCellClicked(0);
	colClicked = WhichDTCellClicked(1);
	dName = WhichDialogItemClicked();
	
	if(dName == "iVars_ttbl"  &&  rowClicked >= 0  &&  rowClicked < iVars_NumTableRows)
		{
		
		if(colClicked == I_VAR_TYPE_COL)
			{
			iVars_ShowTypesPopup();

			//if db type variable, need to init the variable's value
			//if(iVars_Types_str[rowClicked] == "DB read value"  ||  iVars_Types_str[rowClicked] == "DB read PRI"  ||  iVars_Types_str[rowClicked] == "DB address"  ||  iVars_Types_str[rowClicked] == "_DB index")	//6/25/09
			if(
				iVars_Types_str[rowClicked] == "DB read value"  ||  
				iVars_Types_str[rowClicked] == "DB read PRI"  ||  
				iVars_Types_str[rowClicked] == "DB address"  ||  
				iVars_Types_str[rowClicked] == "DB database index"  ||  
				iVars_Types_str[rowClicked] == "DB table index"  ||  
				iVars_Types_str[rowClicked] == "DB field index"  ||  
				iVars_Types_str[rowClicked] == "DB record index"
			  )
				{
				iVars_DBCoords[rowClicked] = blank;
				
				//if this row already exists in the iVars name tracking linked list, blank out the names
				iVars_DBNT_AddElement(iVars_DBCoords[rowClicked], rowClicked);
				}
			
			//if the variable type is "num records", store the current number of records if possible
			#ifdef EQ_IsQueryEquationTypeBlock
				if(iVars_Types_str[rowClicked] == "DBQ num records")
					{
					if(DBQ_TableOptionChosen == DBQ_USE_LIST  &&  DBQ_DatabaseOptionChosen == DBQ_USE_LIST)
						{
						databaseIndex = DBDatabaseGetIndex(DBQ_DatabaseName);
						tableIndex = DBTableGetIndex(databaseIndex, DBQ_TableName);
						numRecords = DBRecordsGetNum(databaseIndex, tableIndex);
						iVars_Values[rowClicked] = numRecords;
						}
					}
			#endif
			}
			
		else if(colClicked == I_VAR_NAME_COL)
			{
			#ifdef EQ_IsItemBlock
				if(iVars_Types_str[rowClicked] == "Attribute"  ||  iVars_Types_str[rowClicked] == "QEQ attrib last item to exit")
					{
					iVars_OnDialogClickAttribName(ATTRIB_OPTIONS_1);
					
					
					if(iVars_Types_str[rowClicked] == "QEQ attrib last item to exit")
						{
						if(iVars_Names[rowClicked] != "None")
							{
							iVars_Names[rowClicked] = "L_" + iVars_Names[rowClicked];
							}
						}
					}

				else if(iVars_Types_str[rowClicked] == "DB read value using attrib"  ||  iVars_Types_str[rowClicked] == "DB read PRI using attrib")
					iVars_OnDialogClickAttribName(ATTRIB_OPTIONS_2);
			#endif
			}
		else if(colClicked == I_VAR_VALUE_COL)
		{	// Carollo 05/27/15
			if(iVars_Types_str[rowClicked] == "Integer" )
			{
				 iVars_Values[rowClicked] = Int(StrToReal(iVars_ttbl[rowClicked][I_VAR_VALUE_COL]));
			}
			if(iVars_Types_str[rowClicked] == "String" )
			{
				iVars_ValuesStr[rowClicked] = iVars_ttbl[rowClicked][I_VAR_VALUE_COL];
			}
			if(iVars_Types_str[rowClicked] == "Real" )
			{
				iVars_Values[rowClicked] = StrToReal(iVars_ttbl[rowClicked][I_VAR_VALUE_COL]);
			}
			else if(iVars_Types_str[rowClicked] == "DB read value"  ||  iVars_Types_str[rowClicked] == "DB read PRI")
				{
				returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				
				if( !NoValue(returnedDBCoordinate) )	//if user did not click cancel
					{
					if(returnedDBCoordinate > 0)
						{
						//make sure user specified all four elements of a db address
						databaseIndex = DBDatabaseGetIndexFromAddress(returnedDBCoordinate);
						tableIndex = DBTableGetIndexFromAddress(returnedDBCoordinate);
						fieldIndex = DBFieldGetIndexFromAddress(returnedDBCoordinate);
						recordIndex = DBRecordGetIndexFromAddress(returnedDBCoordinate);
						if(databaseIndex <= 0  ||  tableIndex <= 0  ||  fieldIndex <= 0  ||  recordIndex <= 0)
							{
							UserError("'DB read' type variables require valid indexes for the database, table, field and record.");
							iVars_DBCoords[rowClicked] = blank;
							}
						else
							{
							legitField = iVars_CheckChosenField(rowClicked, returnedDBCoordinate);							
							if(NoValue(returnedDBCoordinate)  ||  !legitField)
								iVars_DBCoords[rowClicked] = blank;
							else 
								{
								iVars_DBCoords[rowClicked] = returnedDBCoordinate;
								iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
								}
							}
						}
					else
						{
						//blank out the names in the name tracking linked list for this row
						iVars_DBNT_AddElement(blank, rowClicked);
						}
					}
				else //if user clicked cancel
					{
					//do nothing
					}
				}
			else if(iVars_Types_str[rowClicked] == "DB address")	
				{
				returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				
				if( !NoValue(returnedDBCoordinate) )
					{
					iVars_DBCoords[rowClicked] = returnedDBCoordinate;
					iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
					}
				}

			//6/25/09
			else if(iVars_Types_str[rowClicked] == "DB database index")
				{
				//returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				returnedDBCoordinate = DBAddressGetDlg2(databaseIndex, -3, -3, -3);
				
				if( !NoValue(returnedDBCoordinate) )	//if user didn't click cancel
					{
					databaseIndex = DBDatabaseGetIndexFromAddress(returnedDBCoordinate);
					if(databaseIndex >= 1)
						{
						iVars_DBCoords[rowClicked] = returnedDBCoordinate;
						iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
						}
					else
						{
						UserError("The selected database is invalid. Please select a valid database.");
						AbortAllSims();
						}
					}
				}
			
			//6/25/09
			else if(iVars_Types_str[rowClicked] == "DB table index")
				{
				//returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				returnedDBCoordinate = DBAddressGetDlg2(databaseIndex, tableIndex, -3, -3);
				
				if( !NoValue(returnedDBCoordinate) )	//if user didn't click cancel
					{
					databaseIndex = DBDatabaseGetIndexFromAddress(returnedDBCoordinate);
					if(databaseIndex >= 1)
						{
						tableIndex = DBTableGetIndexFromAddress(returnedDBCoordinate);
						if(tableIndex >= 1)
							{
							iVars_DBCoords[rowClicked] = returnedDBCoordinate;
							iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
							}
						else
							{
							UserError("The selected table is invalid. Please select a valid database and table.");
							AbortAllSims();
							}
						}
					else
						{
						UserError("The selected database is invalid. Please select a valid database and table.");
						AbortAllSims();
						}
					}
				}
			
			//6/25/09
			else if(iVars_Types_str[rowClicked] == "DB field index")
				{
				//returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				returnedDBCoordinate = DBAddressGetDlg2(databaseIndex, tableIndex, fieldIndex, -3);
				
				if( !NoValue(returnedDBCoordinate) )	//if user didn't click cancel
					{
					databaseIndex = DBDatabaseGetIndexFromAddress(returnedDBCoordinate);
					if(databaseIndex >= 1)
						{
						tableIndex = DBTableGetIndexFromAddress(returnedDBCoordinate);
						if(tableIndex >= 1)
							{
							fieldIndex = DBFieldGetIndexFromAddress(returnedDBCoordinate);
							if(fieldIndex >= 1)
								{
								iVars_DBCoords[rowClicked] = returnedDBCoordinate;
								iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
								}
							else
								{
								UserError("The selected field is invalid. Please select a valid database, table and field.");
								AbortAllSims();
								}
							}
						else
							{
							UserError("The selected table is invalid. Please select a valid database, table and field.");
							AbortAllSims();
							}
						}
					else
						{
						UserError("The selected database is invalid. Please select a valid database, table and field.");
						AbortAllSims();
						}
					}
				}
			
			//6/25/09
			else if(iVars_Types_str[rowClicked] == "DB record index")
				{
//				returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[rowClicked]);
				returnedDBCoordinate = DBAddressGetDlg2(databaseIndex, tableIndex, fieldIndex, recordIndex);
				
				if( !NoValue(returnedDBCoordinate) )	//if user didn't click cancel
					{
					databaseIndex = DBDatabaseGetIndexFromAddress(returnedDBCoordinate);
					if(databaseIndex >= 1)
						{
						tableIndex = DBTableGetIndexFromAddress(returnedDBCoordinate);
						if(tableIndex >= 1)
							{
							fieldIndex = DBFieldGetIndexFromAddress(returnedDBCoordinate);
							if(fieldIndex >= 1)
								{
								recordIndex = DBRecordGetIndexFromAddress(returnedDBCoordinate);
								if(recordIndex >= 1)
									{
									iVars_DBCoords[rowClicked] = returnedDBCoordinate;
									iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
									}
								else
									{
									UserError("The selected record is invalid. Please select a valid database, table, field and record.");
									AbortAllSims();
									}
								}
							else
								{
								UserError("The selected field is invalid. Please select a valid database, table, field and record.");
								AbortAllSims();
								}
							}
						else
							{
							UserError("The selected table is invalid. Please select a valid database, table, field and record.");
							AbortAllSims();
							}
						}
					else
						{
						UserError("The selected database is invalid. Please select a valid database, table, field and record.");
						AbortAllSims();
						}
					}
				}
			
			//6/25/09
			else if(
					iVars_Types_str[rowClicked] == "DB database index"  ||  
					iVars_Types_str[rowClicked] == "DB table index"  ||  
					iVars_Types_str[rowClicked] == "DB field index"  ||  
					iVars_Types_str[rowClicked] == "DB record index"
				   )
				{
				returnedDBCoordinate = DBAddressGetDlg(iVars_DBCoords[rowClicked]);
				
				if( !NoValue(returnedDBCoordinate) )	//if user didn't click cancel
					{
					iVars_DBCoords[rowClicked] = returnedDBCoordinate;
					iVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
					}
				}
			
			else if(
					iVars_Types_str[rowClicked] == "Static first run init"  ||  
					iVars_Types_str[rowClicked] == "Static multi run init"  ||  
					iVars_Types_str[rowClicked] == "Static open model init"  ||  
					iVars_Types_str[rowClicked] == "QEQ static calc cycle init"  ||
					iVars_Types_str[rowClicked] == "QEQ static item value"					//11/17/10
				   )
				{
				//ajn-  had to move this code to "on iVars_ttbl"
				}

			#ifdef EQ_IsQueryEquationTypeBlock
				else if(iVars_Types_str[rowClicked] == "DBQ read value"  ||  iVars_Types_str[rowClicked] == "DBQ read PRI")
					{
					DBQF_OnDialogClickQueryField(rowClicked);
					}
				else if(iVars_Types_str[rowClicked] == "DBQ start record")
					{
					DBQSR_OnDialogClickStartRecord(rowClicked);
					}
			#endif
			}

		#ifdef EQ_IsQueryEquationTypeBlock
			else if(colClicked == I_VAR_PARENT_FIELD_COL)
				{
				if(iVars_Types_str[rowClicked] == "DBQ read PRI")
					{
					DBQFP_OnDialogClickQueryField(rowClicked);
					}
				}
		#endif

		}//if(dName == "iVars_ttbl"  &&  rowClicked >= 0  &&  rowClicked < iVars_NumTableRows)

	else if(dName == "oVars_ttbl"  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows)
		{

		if(colClicked == O_VAR_TYPE_COL)
			{
			oVars_ShowTypesPopup();

			//if db type variable, need to init the variable's value
			if(
				oVars_Types_str[rowClicked] == "DB write value"  ||  
				oVars_Types_str[rowClicked] == "DB write PRI"
			  )
				{
				oVars_DBCoords[rowClicked] = blank;

				//if this row already exists in the iVars name tracking linked list, blank out the names
				//oVars_DBNT_AddElement(iVars_DBCoords[rowClicked], rowClicked);	//10/28/08, 7.0.5, AJN
				oVars_DBNT_AddElement(oVars_DBCoords[rowClicked], rowClicked);
				}
			}
	
		else if(colClicked == O_VAR_NAME_COL)
			{
			#ifdef EQ_IsItemBlock
				if(oVars_Types_str[rowClicked] == "Attribute"  ||  oVars_Types_str[rowClicked] == "DBQS attribute")
					oVars_OnDialogClickAttribName(ATTRIB_OPTIONS_1);

				else if(oVars_Types_str[rowClicked] == "DB write value using attrib"  ||  oVars_Types_str[rowClicked] == "DB write PRI using attrib")
					oVars_OnDialogClickAttribName(ATTRIB_OPTIONS_2);
			#endif
			}

		else if(colClicked == O_VAR_VALUE_COL)
			{
			if(oVars_Types_str[rowClicked] == "DB write value"  ||  oVars_Types_str[rowClicked] == "DB write PRI")
				{
				returnedDBCoordinate = DBAddressGetDlg(oVars_DBCoords[rowClicked]);
				
				if( !NoValue(returnedDBCoordinate) )	//if user did not click cancel
					{
					if(returnedDBCoordinate > 0)
						{
						//make sure user specified all four elements of a db address
						databaseIndex = DBDatabaseGetIndexFromAddress(returnedDBCoordinate);
						tableIndex = DBTableGetIndexFromAddress(returnedDBCoordinate);
						fieldIndex = DBFieldGetIndexFromAddress(returnedDBCoordinate);
						recordIndex = DBRecordGetIndexFromAddress(returnedDBCoordinate);
						if(databaseIndex <= 0  ||  tableIndex <= 0  ||  fieldIndex <= 0  ||  recordIndex <= 0)
							{
							UserError("'DB write' type variables require valid indexes for the database, table, field and record.");
							oVars_DBCoords[rowClicked] = blank;
							}
						else
							{
							legitField = oVars_CheckChosenField(rowClicked, returnedDBCoordinate);	//if it's a "db value" variable, the field cannot be a string field or a child
							
							if(NoValue(returnedDBCoordinate)  ||  !legitField)
								oVars_DBCoords[rowClicked] = blank;
							else 
								{
								oVars_DBCoords[rowClicked] = returnedDBCoordinate;
								oVars_DBNT_AddElement(returnedDBCoordinate, rowClicked);
								}
							}
						}
					else
						{
						//blank out the names in the name tracking linked list for this row
						oVars_DBNT_AddElement(blank, rowClicked);
						}
					}
				else //if user clicked cancel
					{
					//do nothing
					}
				}
			}
			
		#ifdef EQ_NoItemColumnExists
			else if(colClicked == O_VAR_NO_ITEM_COL)
				{
				if(StrFind(oVars_Types_str[rowClicked], "Connector", FALSE, FALSE) >= 0)
					oVars_ShowNoItemOptionsPopup();
				}
		#endif
		
		}//else if(dName == "oVars_ttbl"  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows)
		
	else if(dName == "incl_Prototypes_pop")
		{
		Incl_BuildPrototypesArray();
		incl_Prototypes_pop = PopupMenuArray (incl_Prototypes_DA, 1);
		}

	else if(dName == "Cancel")
		{
		if(EQE_EditorIsOpen == TRUE)
			{
			UserError("Please close the equation editor window before closing your equation dialog.");
			abort;
				//NOTE:  can't do this in "on Cancel" because all the static data that changed after 
				//the dialog was opened will be gone by the time the "on Cancel" message is sent.
			}
		}
		
}//procedure EQ_OnDialogClick()
*/
		
procedure EQ_OnCreateBlock(integer calledFrom)
{

	integer i, j;
	integer me;
	integer iVars_DBNameTrackingListIndex;
	integer oVars_DBNameTrackingListIndex;
	integer numBlocksInModel;
	integer blockTypeArray[4];
	string nameOfBlock;
	integer execCheckBoxVal;
	
	me = MyBlockNumber();

	rowClicked = -1;
	colClicked = -1;
	
	dbg_HiddenBlock = -1;
	
	EQE_EditorIsOpen = FALSE;
	
	inLinkStructure = FALSE;

	#ifdef respondToLinkAlerts_chk
		respondToLinkAlerts_chk = FALSE;
	#endif
	
	//random seed stuff
	MySeed = randomGetSeed() + MyBlockNumber() + 1;
	previousSeed = MySeed;

	//set up input variable stuff
	iVars_NumTableRows = 1;
	iVars_OldNumTableRows = iVars_NumTableRows;
//	iVars_ResizeDynamicArrays(RESIZE_ADD_SUBTRACT_FROM_END);
	
	//setup iVarsIn connectors
	iVarsIn_NumCons = iVars_NumTableRows;
	iVarsIn_NumConsOld = iVarsIn_NumCons;
	MakeArray(iVarsIn_NumBlocksConnected, iVarsIn_NumCons);
	MakeArray(iVarsIn_ConNums, iVarsIn_NumCons);
	ConArraySetNumCons(MyBlockNumber(), "iVarsIn", iVarsIn_NumCons, TRUE);
	for(i=0; i<iVarsIn_NumCons; i++)									// Look through the connector array
		iVarsIn_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "iVarsIn", i);
//	iVarsIn_ConnectorsSetup();

	//setup output variable stuff
	oVars_NumTableRows = 1;
	oVars_OldNumTableRows = oVars_NumTableRows;
//	oVars_ResizeDynamicArrays(calledFrom, RESIZE_ADD_SUBTRACT_FROM_END);

	#ifdef oVars_Initialize_prm
		oVars_Initialize_prm = 0.0;
	#endif
	
	#ifdef oVarsOut
		//setup oVarsOut connectors
		oVarsOut_NumCons = oVars_NumTableRows;
		oVarsOut_NumConsOld = oVarsOut_NumCons;
		MakeArray(oVarsOut_NumBlocksConnected, oVarsOut_NumCons);
		MakeArray(oVarsOut_ConNums, oVarsOut_NumCons);
		ConArraySetNumCons(MyBlockNumber(), "oVarsOut", oVarsOut_NumCons, TRUE);
		for(i=0; i<oVarsOut_NumCons; i++)									// Look through the connector array
			oVarsOut_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "oVarsOut", i);
//		oVarsOut_ConnectorsSetup();
	#endif
			
	equation_DTxt = DynamicTextArrayNumber(EQ_EquationText);	//points "equation_dtxt" to "EQ_EquationText".
	MakeArray(EQ_EquationText, 1);
	if(calledFrom == EQUATION_QUEUE_BLOCK)
		EQ_EquationText[0] = "iRank_0 = inCon0;";
	else if(calledFrom == EQUATION_QUERY_BLOCK_VALUE)
		{
		EQ_EquationText[0] = "rRank_0 = inCon0;";
		}
	else if(calledFrom == EQUATION_QUERY_BLOCK_ITEM)
		{
		EQ_EquationText[0] = "prRank_0 = inCon0;";
		}
	else
		EQ_EquationText[0] = "outCon0 = inCon0;";
		
	//set up db name tracking
	iVars_DBNameTrackingListIndex = ListCreate(me, 2, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);	//2 sets sort type as integer
	ListLocked(me, iVars_DBNameTrackingListIndex, TRUE);
	ListAddString63s(me, iVars_DBNameTrackingListIndex, 4);
	ListSetName(me, iVars_DBNameTrackingListIndex, DBNT_IVARS_LIST_NAME);
	oVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);	//2 sets sort type as integer
	ListLocked(me, oVars_DBNameTrackingListIndex, TRUE);
	ListAddString63s(me, oVars_DBNameTrackingListIndex, 4);
	ListSetName(me, oVars_DBNameTrackingListIndex, DBNT_OVARS_LIST_NAME);

	//10/13/08, AJN:  check Executive to see if this block should show property names on connector labels
	numBlocksInModel = NumBlocks();
	for(i=0; i<numBlocksInModel; i ++)									//look through all of the blocks in the model
		{
		if(i != me && GetBlockTypePosition(i,blockTypeArray) == 3)		//if this is a block from a library
			{
			nameOfBlock = BlockName(i);
			
			if(nameOfBlock == "Executive")
				{
				execCheckBoxVal = StrToReal(GetDialogVariable(i, "ShowPropertyName_chk", 0, 0));
				if(execCheckBoxVal == TRUE)
					{
					iVars_ShowConNames_chk = TRUE;
					oVars_ShowConNames_chk = TRUE;
					}
				else
					{
					iVars_ShowConNames_chk = FALSE;
					oVars_ShowConNames_chk = FALSE;
					}
				}
			}
		}
		
	//4/20/11
	convertDateTimeData_chk = FALSE;
	modelIs_802_OrOlder = TRUE;		//ensures convertDateTimeData_chk wont get alteredin OpenModel 

}//procedure EQ_OnCreateBlock()

/*
procedure EQ_OnBlockMove()
{

	
	#ifdef CW_IVarsIn_CalcControl_chk
		//CW_IVarsIn_Animate();				//7/5/11
		CW_ConnectorAnimate();
	#endif
	
	#ifdef CW_OVarsOut_CalcControl_chk
		//CW_OVarsOut_Animate();			//7/5/11
		CW_ConnectorAnimate();
	#endif
	
	#ifdef CMC_chk
		//CMC_IVarsIn_Animate();			//7/6/11
		//CMC_OVarsOut_Animate();			//7/6/11
		CMC_ConnectorAnimate();
	#endif

}//procedure EQ_OnBlockMove()


procedure EQ_OnDialogOpen()
{

	//make "Calc When" popups behave like buttons
	#ifdef CW_LAM_CalcControl_chk
		DIPopupButton(MyBlockNumber(), "CW_LAM_RespondToWhich_pop", TRUE);
		DIPopupButton(MyBlockNumber(), "CW_LAM_RespondWhen_pop", TRUE);
	#endif
	
	//make "Calc When" popups behave like buttons
	#ifdef CW_IVarsIn_CalcControl_chk
		DIPopupButton(MyBlockNumber(), "CW_IVarsIn_RespondToWhich_pop", TRUE);
		DIPopupButton(MyBlockNumber(), "CW_IVarsIn_RespondWhen_pop", TRUE);
	#endif
	
	//make "Calc When" popups behave like buttons
	#ifdef CW_OVarsOut_CalcControl_chk
		DIPopupButton(MyBlockNumber(), "CW_OVarsOut_RespondToWhich_pop", TRUE);
		DIPopupButton(MyBlockNumber(), "CW_OVarsOut_RespondWhen_pop", TRUE);
	#endif
	
	iVars_TableSetup();
	oVars_TableSetup();
	
	EQ_DialogItemsShow();
	
	EQ_CheckForSpaces(FALSE);

	Incl_TableSetup();
	
	if(Incl_chk)
		incl_PrototypesDisplay_dtxt = DynamicTextArrayNumber(incl_PrototypesDisplay_DA); //points "incl_PrototypesDisplay_dtxt" to "incl_PrototypesDisplay_DA".

}//procedure EQ_OnDialogOpen()
*/
/*
procedure EQ_OnPasteBlock()
{

	integer i;

	MySeed = randomGetSeed() + MyBlockNumber() + 1;
	previousSeed = MySeed;

	EQ_BlockRegisterStructure();
	EQ_BlockRegisterContent();
	
	EQE_EditorIsOpen = FALSE;
	
	#ifdef EQ_IsItemBlock
	
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)
				Attrib_AddName(iVars_Names[i], iVars_AttribTypes[i]);		//because openModel is called when add an H-Block to a model
			}

		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0)
				Attrib_AddName(oVars_Names[i], oVars_AttribTypes[i]);		//because openModel is called when add an H-Block to a model
			}
			
	#endif
	
}//procedure EQ_OnPasteBlock()
*/
/*
procedure EQ_OnFinalCalc()
{

	previousSeed = mySeed;

	#ifdef EQ_IsValueBlock
	
		inFinalCalc = TRUE;
		
		//executed only if the user has chosen the option to calc at end of sim
		if(calcAtEnd_chk  &&  calcAtEnd_pop == CALC_AT_END_FINAL_CALC)
			{
			if(modelType == DISCRETE_EVENT)
				{
				//send iVarsIn msgs
				iVarsIn_SendMsgs(MSG_RECEIVED_FROM_FINAL_CALC);
	
				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
	
				#ifdef EQ_IsQueryEquationValueBlock
					DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
	
				//send oVarsOut msgs
				oVarsOut_SendMsgs(MSG_RECEIVED_FROM_FINAL_CALC);
				}
			else //if(modelType == CONTINUOUS)
				{
				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
	
				#ifdef EQ_IsQueryEquationValueBlock
					DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
				}
			}
			
		inFinalCalc = FALSE;
		
	#endif //EQ_IsValueBlock
	
	//5/20/11
	oVars_TableSetup();
		//NOTE:	I included this call for equations of all types because it's possible someone
		//		could have the Scenario Manager pointing to an item based equation and just like 
		//		value based equations may not have updated it's outputs table.  
		
}//procedure EQ_OnFinalCalc()
*/

//*****************************************************
//End "Eqn_" Message Handlers
//*****************************************************
//*****************************************************


//*****************************************************
//*****************************************************
//Start "Eqn_" Functions
//*****************************************************

			
//6/7/11
procedure EQ_DBIndexCheck()
{
	integer i, j;
	integer me;
	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	integer dbExists;
	integer tableExists;
	integer fieldExists;
	integer recordExists;
	integer error;
	integer numElements;
	integer whichVarRow;
	string63 databaseName;
	string63 tableName;
	string63 fieldName;
	string63 recordName;
	integer iVars_DBNameTrackingListIndex;
	integer recordIDFieldIndex;
	integer dbqDatabaseExists;
	integer dbqTableExists;
	integer dbqfpTableExists;

	me = MyBlockNumber();
	
	//get name tracking info
	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
	
	//get the query db and query table
	#ifdef EQ_IsQueryEquationTypeBlock
		//can we pin down the database and table the user selected?
		if(
			(DBQ_DatabaseOptionChosen == DBQ_USE_LIST || DBQ_DatabaseOptionChosen == DBQ_USE_CONSTANT)  &&
			(DBQ_TableOptionChosen == DBQ_USE_LIST || DBQ_TableOptionChosen == DBQ_USE_CONSTANT)				
		  )
		  	{
			//does db exist
			if(DBQ_DatabaseOptionChosen == DBQ_USE_LIST)
		  		{
		  		DBQ_DatabaseIndex_prm = DBDatabaseGetIndex(DBQ_DatabaseName);
		  		}
		  	dbqDatabaseExists = DBDatabaseExists(DBQ_DatabaseIndex_prm);
		  	
		  	//does table exist
		  	if(DBQ_TableOptionChosen == DBQ_USE_LIST)
		  		{
			  	DBQ_TableIndex_prm = DBTableGetIndex(DBQ_DatabaseIndex_prm, DBQ_TableName);
			  	}
		  	dbqTableExists = DBTableExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm);
		  	}
	#endif
	
	//START:  check db indexes of iVar db vars
	error = FALSE;	
	for(i=0; i<iVars_NumTableRows; i++)
		{
	  	databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
	  	dbExists = DBDatabaseExists(databaseIndex);
	  	
	  	tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
	  	tableExists = DBTableExists(databaseIndex, tableIndex);
	  	
	  	fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
	  	fieldExists = DBFieldExists(databaseIndex, tableIndex, fieldIndex);
	  	
	  	recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
		recordExists = DBRecordExists(databaseIndex, tableIndex, fieldIndex, recordIndex);
		
		if(
			iVars_Types_Int[i] == EQ_DB_READ_VAL	||  
			iVars_Types_Int[i] == EQ_DB_READ_PRI	||  
			iVars_Types_Int[i] == EQ_DB_RECORD_INDEX
		  )
			{
		  	if(!recordExists)
				{
		  		error = TRUE;
		  		break;
				}
			}
		else if(iVars_Types_Int[i] == EQ_DB_ADDRESS)
			{
			//if db address variable, we have to consult the name tracking list in order to determine
			//how many coordinates this particular db address var is pointing to 
			
			for(j=0; j<numElements; j++)
				{
				whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, j, DBNT_WHICH_ROW_IN_TABLE_FIELD);
				
				//do we have the correct list element?
				if(whichVarRow == i)
					{
					recordName = ListGetString(me, iVars_DBNameTrackingListIndex, j, 6, DBNT_RECORD_NAME_FIELD);	//6 for string63
					fieldName = ListGetString(me, iVars_DBNameTrackingListIndex, j, 6, DBNT_FIELD_NAME_FIELD);	//6 for string63
					tableName = ListGetString(me, iVars_DBNameTrackingListIndex, j, 6, DBNT_TABLE_NAME_FIELD);	//6 for string63
					databaseName = ListGetString(me, iVars_DBNameTrackingListIndex, j, 6, DBNT_DB_NAME_FIELD);	//6 for string63
					recordIDFieldIndex = DBRecordIDFieldGetIndex(databaseIndex, tableIndex);
					
					if(
						recordName != ""  ||		//if this db address var is pointing to a record name
						recordIndex >= 1			//if this db address var is pointing to a record index
					  )
						{
					  	if(!recordExists)
							{
					  		error = TRUE;
							}
						}
					else if(fieldName != "")	//if this db address var is pointing to a field
						{
					  	if(!fieldIndex)
							{
					  		error = TRUE;
							}
						}
					else if(tableName != "")	//if this db addres var is pointing to a table
						{
					  	if(!tableExists)
							{
					  		error = TRUE;
							}
						}
					else if(databaseName != "")	//if this db addres var is pointing to a database
						{
					  	if(!dbExists)
							{
					  		error = TRUE;
							}
						}
					
					break;		//break if we found the element matching the current iVar
					}
				}
			
			if(error == TRUE)
				{
				break;
				}
			}
		
		#ifdef EQ_IsQueryEquationTypeBlock

			//can we pin down the database and table the user selected?
			else if(
				(DBQ_DatabaseOptionChosen == DBQ_USE_LIST || DBQ_DatabaseOptionChosen == DBQ_USE_CONSTANT)  &&
				(DBQ_TableOptionChosen == DBQ_USE_LIST || DBQ_TableOptionChosen == DBQ_USE_CONSTANT)				
			  )
			  	{
				if(dbqDatabaseExists  &&  dbqTableExists)
					{
					if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  &&  DBQF_OptionsChosen[i] == DBQ_USE_LIST)
						{
					  	DBQF_FieldIndex[i] = DBFieldGetIndex(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldName[i]);
					  	fieldExists = DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]);
			
					  	if(!fieldExists)
							{
					  		error = TRUE;
					  		break;
							}
						}
					else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQF_OptionsChosen[i] == DBQ_USE_LIST)
						{
					  	//if not doing parent indirection
					  	if(DBQFP_OptionsChosen[i] == DBQ_NOT_DEFINED)
					  		{
						  	DBQF_FieldIndex[i] = DBFieldGetIndex(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldName[i]);
						  	fieldExists = DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]);
				
						  	if(!fieldExists)
								{
						  		error = TRUE;
						  		break;
								}
							}
					  	
					  	else //if doing parent indirection
					  		{
					  		//NOTE:	the only time we can do a parent indirection is if the query table AND the
					  		//		query field are fixed (ie can have a variable query table or variable query
					  		//		field).
						  	
						  	
						  	//error!  fix in 8.0.3!
						  	//DBQFP_TableName[] never gets filled out.  so can't do name tracking on it.
						  	//add code to store name of parent table at the time the user makes the selection.
						  	//for legacy models (pre 8.0.3), add code to openModel and try to get the name of 
						  	//the parent table that you should have been storing all along but weren't.
						  	/*
						  	if(DBQFP_OptionsChosen[i] == DBQ_USE_LIST  ||  DBQFP_OptionsChosen[i] == DBQ_USE_CONSTANT)
						  		{
						  		DBQFP_TableIndex[i] = DBTableGetIndex(DBQ_DatabaseIndex_prm, DBQFP_TableName[i]);
						  		dbqfpTableExists = DBTableExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i]);
						  		if(dbqfpTableExists)
						  			{
							  		if(DBQFP_OptionsChosen[i] == DBQ_USE_LIST)
							  			{
									  	DBQFP_FieldIndex[i] = DBFieldGetIndex(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldName[i]);
									  	}
								  	fieldExists = DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQFP_FieldIndex[i]);
						
								  	if(!fieldExists)
										{
								  		error = TRUE;
								  		break;
										}
									}
								else
									{
								  	error = TRUE;
								  	break;
									}
								}
							*/
							}
						}
					}
				else
					{
					error = TRUE;
					break;
					}
				}
				
		#endif //EQ_IsQueryEquationTypeBlock
		
		else if(iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX)
			{
		  	if(!dbExists)
				{
		  		error = TRUE;
		  		break;
				}
			}
		else if(iVars_Types_Int[i] == EQ_DB_TABLE_INDEX)
			{
		  	if(!tableExists)
				{
		  		error = TRUE;
		  		break;
				}
			}
		else if(iVars_Types_Int[i] == EQ_DB_FIELD_INDEX)
			{
		  	if(!fieldExists)
				{
		  		error = TRUE;
		  		break;
				}
			}
		  }
	if(error == TRUE)
		{
  		UserError("There is a problem in " + BlockName(me) + " block " + me + ". The coordinates for input variable " + (i+1) + " do not exist.");
  		AbortAllSims();
  		}
	
	//END:  check db indexes of iVar db vars
		
	
	
	//check db indexes of oVar db vars
	error = FALSE;
	for(i=0; i<oVars_NumTableRows; i++)
		{
	  	databaseIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[i]);
	  	dbExists = DBDatabaseExists(databaseIndex);
	  	
	  	tableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[i]);
	  	tableExists = DBTableExists(databaseIndex, tableIndex);
	  	
	  	fieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[i]);
	  	fieldExists = DBFieldExists(databaseIndex, tableIndex, fieldIndex);
	  	
	  	recordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[i]);
		recordExists = DBRecordExists(databaseIndex, tableIndex, fieldIndex, recordIndex);
		
		if(
			oVars_Types_Int[i] == EQ_DB_WRITE_VAL	||  
			oVars_Types_Int[i] == EQ_DB_WRITE_PRI
		  )
			{
		  	if(!recordExists)
				{
		  		error = TRUE;
		  		break;
				}
			}
		  }
	if(error == TRUE)
		{
  		UserError("There is a problem in " + BlockName(me) + " block " + me + ". The coordinates for output variable " + (i+1) + " do not exist.");
  		AbortAllSims();
  		}

}//procedure EQ_DBIndexCheck()


procedure EQ_DialogItemsShow()
{

	//show breakpoint dialog items
	if(dbg_chk == TRUE)
		DisableDialogItem("dbg_OpenBreakpointsWindow_btn", FALSE);
	else
		DisableDialogItem("dbg_OpenBreakpointsWindow_btn", TRUE);

	//show include file dialog items
	if(incl_chk == TRUE)
		{
		HideDialogItem("incl_frm", FALSE);
		HideDialogItem("Incl_FileNames_ttbl", FALSE);
		HideDialogItem("Incl_Add_btn", FALSE);
		HideDialogItem("Incl_Create_btn", FALSE);
		HideDialogItem("Incl_Remove_btn", FALSE);
		HideDialogItem("incl_Prototypes_lbl", FALSE);
		HideDialogItem("incl_Prototypes_pop", FALSE);
		HideDialogItem("incl_FunctionPrototype_lbl", FALSE);
		HideDialogItem("incl_PrototypesDisplay_dtxt", FALSE);
		}
	else
		{
		HideDialogItem("incl_frm", TRUE);
		HideDialogItem("Incl_FileNames_ttbl", TRUE);
		HideDialogItem("Incl_Add_btn", TRUE);
		HideDialogItem("Incl_Create_btn", TRUE);
		HideDialogItem("Incl_Remove_btn", TRUE);
		HideDialogItem("incl_Prototypes_lbl", TRUE);
		HideDialogItem("incl_Prototypes_pop", TRUE);
		HideDialogItem("incl_FunctionPrototype_lbl", TRUE);
		HideDialogItem("incl_PrototypesDisplay_dtxt", TRUE);
		}
	
	dialogIsOpen = BlockDialogIsOpen(MyBlockNumber());
	
	EQ_DialogSetSize();

}//procedure EQ_DialogItemsShow()


procedure EQ_DialogSetSize()
{

	integer me;
	integer width;
	integer height;
	
	me = MyBlockNumber();
	
	height = 1000;

	#ifdef EQ_IsEquationValue
		width = 850;
		if(!Incl_chk)
			height = 560;
	#endif
	

	#ifdef EQ_IsQueryEquationValueBlock
		width = 875;
		if(!Incl_chk)
			height = 650;
	#endif
	
	
	#ifdef EQ_IsQueueEquation
		width = 770;
		if(!Incl_chk)
			{
			height = 575;
			
			DIMoveTo(me, "blockType_lbl", 515, 10);
			DIMoveTo(me, "BlockType_lbl2", 515, 79);
			DIMoveTo(me, "attribSpaceNote_lbl", 515, 199);
			}
		else
			{
			DIMoveTo(me, "blockType_lbl", 620, 10);
			DIMoveTo(me, "BlockType_lbl2", 620, 79);
			DIMoveTo(me, "attribSpaceNote_lbl", 620, 199);
			}
	#endif
	
	
	#ifdef EQ_IsQueryEquationItemBlock
		width = 1000;
		if(!Incl_chk)
			{
			height = 665;
			
			DIMoveTo(me, "blockType_lbl", 605, 10);
			DIMoveTo(me, "BlockType_lbl2", 605, 79);
			DIMoveTo(me, "attribSpaceNote_lbl", 605, 166);
			}
		else
			{
			DIMoveTo(me, "blockType_lbl", 717, 10);
			DIMoveTo(me, "BlockType_lbl2", 717, 79);
			DIMoveTo(me, "attribSpaceNote_lbl", 717, 166);
			}
	#endif
	
	
	#ifdef EQ_IsEquationItemBlock
		width = 1000;
		if(!Incl_chk)
			{
			height = 565;
			
			DIMoveTo(me, "blockType_lbl", 510, 10);
			DIMoveTo(me, "BlockType_lbl2", 510, 79);
			DIMoveTo(me, "attribSpaceNote_lbl", 510, 166);
			}
		else
			{
			DIMoveTo(me, "blockType_lbl", 618, 10);
			DIMoveTo(me, "BlockType_lbl2", 618, 79);
			DIMoveTo(me, "attribSpaceNote_lbl", 618, 166);
			}
	#endif
	
	
	DialogSetSize(me, width, height);
	
}//procedure EQ_DialogSetSize()


//	8/21/09
#ifdef EQ_IsValueBlock
real EQ_GetNextCalcEventTime()
{

	integer me;
	integer nextEvent;
	real currentDate;
	real startDate;
	real futureDate;
	real lrCalculatedEventTime;
	real lrIntervalEventTime;
	real lrNextCalcEventTime;
	
	me = MyBlockNumber();
	lrNextCalcEventTime =  1e300;
	lrIntervalEventTime = 1e300;
	lrCalculatedEventTime = 1e300;
	
	if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
		{

		//get lrNextCalcEventTime
		if(CW_CalcEventTime_chk  &&  oVars_CalcNextEventIndex >= 0)
			{
			//get lrCalculatedEventTime
			if(oVars_CalcNextEventIndex >= 0)											//	4/14/09
				{
				//CW_Intervals_prm = oVars_Values[0];							//	4/14/09
				lrCalculatedEventTime = oVars_Values[oVars_CalcNextEventIndex];
				
				//was the future event variable not assigned a value?  if so,...
				if( NoValue(lrCalculatedEventTime) ) 
					{
					//...then set it to infinity
					if(lastCalculatedEventTime < currentTime)			//5/15/09
						lrCalculatedEventTime = 1e300;
					}
		
				//1/15/10:  commented out to fix a bug in Pizza Dough model.
				//assume user calculates the next event in the generic absulute
				//simulation time units required for the next event.
				/*
				if(EDCalendarDates())													//	8/1/08
					{
					//	8/3/09
					//CurrentDate = EDSimTimeToDate(CurrentTime, GetTimeUnits());
					//CurrentDate = EDConvertDate(calcAtEventIntervals_prm, blockTimeUnits, CurrentDate);
					currentDate = EDSimTimeToDate(CurrentTime, GetTimeUnits());
					futureDate = EDConvertDate(lrCalculatedEventTime, blockTimeUnits, currentDate);
					lrCalculatedEventTime = EDDateToSimTime(futureDate, GetTimeUnits());
					}
				else
					lrCalculatedEventTime = lrCalculatedEventTime * timeUnitConversionFactor;
				*/
	
				//just in case there's a problem
				if(lrCalculatedEventTime < currentTime)
					lrCalculatedEventTime = 1e300;
				}
			}
		
		
		//get lrIntervalEventTime
		if(CW_Intervals_chk)
			{
			lrIntervalEventTime = currentTime + CW_Intervals_prm;

			if(EDCalendarDates())													//	8/1/08	7.0.4
				{
				currentDate = EDSimTimeToDate(CurrentTime, GetTimeUnits());
				futureDate = EDConvertDate(CW_Intervals_prm, blockTimeUnits, currentDate);
				lrIntervalEventTime = EDDateToSimTime(futureDate, GetTimeUnits());
				}
			else
				lrIntervalEventTime = currentTime + (CW_Intervals_prm * timeUnitConversionFactor);
			}
	
		
		//get lrNextCalcEventTime by comparing lrCalculatedEventTime with lrIntervalEventTime
		if( !NoValue(lrCalculatedEventTime)  &&  !NoValue(lrIntervalEventTime) )
			{
			if(lrCalculatedEventTime <= lrIntervalEventTime)
				{
				lrNextCalcEventTime = lrCalculatedEventTime;
				}
			else
				{
				lrNextCalcEventTime = lrIntervalEventTime;
				}
			}
		else if( !NoValue(lrCalculatedEventTime) )
			{
			lrNextCalcEventTime = lrCalculatedEventTime;
			}
		else if( !NoValue(lrIntervalEventTime) )
			{
			lrNextCalcEventTime = lrIntervalEventTime;
			}
		else
			{
			lrNextCalcEventTime = 1e300;
			}

		//if lrNextCalcEventTime is too small
		if(lrNextCalcEventTime < currentTime)
			lrNextCalcEventTime = 1e300;
		
		}//if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
		
	return(lrNextCalcEventTime);

}//integer EQ_GetNextCalcEventTime()
#endif //EQ_IsValueBlock


procedure EQ_BlockRegisterContent()
{

	integer i;
	integer me;
	integer numElements;
	string63 databaseName;
	integer databaseIndex;
	string63 tableName;
	integer tableIndex;
	string63 fieldName;
	integer fieldIndex;
	string63 recordName;
	integer recordIndex;
	integer iVars_DBNameTrackingListIndex;
	integer oVars_DBNameTrackingListIndex;
	integer recordIDFieldIndex;
	integer whichRowInTable;
	
	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
	
	//remove all possible points of registration
	DBBlockUnregisterContent(MyBlockNumber(), -1, -1, -1, -1);	//-1 to unregister the entire block
	
	//for the "db read" type variables, register if the read table has a record ID field, ie, 
	//register if we're doing name tracking of the chosen record name.  if we are, then we want
	//to be alerted in LinkContent if the location of the record name changes
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_DB_READ_VAL  ||  iVars_Types_Int[i] == EQ_DB_READ_PRI)
			{
			databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
			tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
			
			//if the chosen table has a record ID field, register it
			recordIDFieldIndex = DBRecordIDFieldGetIndex(databaseIndex, tableIndex);
			if(recordIDFieldIndex >= 1)
				{
				DBBlockRegisterContent(me, databaseIndex, tableIndex, recordIDFieldIndex, -1);
				}
			
			}
		}
	
	#ifdef respondToLinkAlerts_chk		//v7 code
		
		if(respondToLinkAlerts_chk == TRUE)
			{
			numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
			
			for(i=0; i<numElements; i++)
				{
				databaseName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
				databaseIndex = DBDatabaseGetIndex(databaseName);
				tableName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
				tableIndex = DBTableGetIndex(databaseIndex, tableName);
				fieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
				fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);
				
				//if the chosen table has a record ID field, do name tracking on the record ID	//11/04/08, 7.0.5, AJN
				recordIDFieldIndex = DBRecordIDFieldGetIndex(databaseIndex, tableIndex);
				if(recordIDFieldIndex >= 1)
					{
					recordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
					recordIndex = DBRecordFind(databaseIndex, 		//database to search
											   tableIndex, 			//table to search
											   0, 					//use the record ID field as the search field
											   1, 					//the start record index
											   TRUE, 				//exact record match
											   recordName);			//the search string
					if(recordIndex == 0)
						recordIndex = -1;
					}
				else
					{
					whichRowInTable = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
					recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichRowInTable]);
					}
				
				if(databaseIndex >= 1  &&  tableIndex >= 1)
					DBBlockRegisterContent(MyBlockNumber(), databaseIndex, tableIndex, fieldIndex, recordIndex);
				}
			}
			
	#else				//v8 code

		#ifdef CW_LAM_CalcControl_chk
			
			if(CW_LAM_CalcControl_chk == TRUE)
				{
				
				numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
				
				for(i=0; i<numElements; i++)
					{
					whichRowInTable = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
					
					if(
						iVars_Types_Int[whichRowInTable] == EQ_DB_READ_VAL  ||  
						iVars_Types_Int[whichRowInTable] == EQ_DB_READ_PRI  ||  
						iVars_Types_Int[whichRowInTable] == EQ_DB_ADDRESS
					  )
						{
						databaseName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
						databaseIndex = DBDatabaseGetIndex(databaseName);
						tableName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
						tableIndex = DBTableGetIndex(databaseIndex, tableName);
						fieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
						fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);
						recordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
	
						if(CW_LAM_WhichDBReadIVar == whichRowInTable  ||  CW_LAM_WhichDBReadIVar == -1)
							{
							//if the chosen table has a record ID field, do name tracking on the record ID	//11/04/08, 7.0.5, AJN
							recordIDFieldIndex = DBRecordIDFieldGetIndex(databaseIndex, tableIndex);
							if(recordIDFieldIndex >= 1)
								{
								recordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
								recordIndex = DBRecordFind(databaseIndex, 		//database to search
														   tableIndex, 			//table to search
														   0, 					//use the record ID field as the search field
														   1, 					//the start record index
														   TRUE, 				//exact record match
														   recordName);			//the search string
								if(recordIndex == 0)
									recordIndex = -1;
								}
							else
								{
								recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichRowInTable]);
								}
						
							if(databaseIndex >= 1  &&  tableIndex >= 1)
								{
								DBBlockRegisterContent(MyBlockNumber(), databaseIndex, tableIndex, fieldIndex, recordIndex);
								}
							}
						}
					}
				
				}
		
		#endif

	#endif

}//procedure EQ_BlockRegisterContent()


procedure EQ_BlockRegisterStructure()
{

	integer i;
	integer me;
	integer numElements;
	string63 databaseName;
	integer databaseIndex;
	string63 tableName;
	integer tableIndex;
	string63 fieldName;
	integer fieldIndex;
	string63 recordName;
	integer recordIndex;
	integer iVars_DBNameTrackingListIndex;
	integer oVars_DBNameTrackingListIndex;
	integer recordIDFieldIndex;
	integer whichRow;
	
	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
	
	//remove all possible points of registration
	DBBlockUnregisterStructure(MyBlockNumber(), -1, -1);	//-1 to unregister the entire block

	//register iVar DB variables
	numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
	for(i=0; i<numElements; i++)
		{
		databaseName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
		databaseIndex = DBDatabaseGetIndex(databaseName);
		tableName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
		tableIndex = DBTableGetIndex(databaseIndex, tableName);
		fieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
		fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);

		//if the chosen table has a record ID field, do name tracking on the record ID	//11/04/08, 7.0.5, AJN
		recordIDFieldIndex = DBRecordIDFieldGetIndex(databaseIndex, tableIndex);
		if(recordIDFieldIndex >= 1)
			{
			recordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
			recordIndex = DBRecordFind(databaseIndex, 		//database to search
									   tableIndex, 			//table to search
									   0, 					//use the record ID field as the search field
									   1, 					//the start record index
									   TRUE, 				//exact record match
									   recordName);			//the search string
			if(recordIndex == 0)
				recordIndex = -1;
			}
		else
			{
			whichRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichRow]);
			}
		
		if(databaseIndex >= 1  &&  tableIndex >= 1)
			DBBlockRegisterStructure(me, databaseIndex, tableIndex);
		}

	//register oVar DB variables
	numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
	for(i=0; i<numElements; i++)
		{
		databaseName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
		databaseIndex = DBDatabaseGetIndex(databaseName);
		tableName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
		tableIndex = DBTableGetIndex(databaseIndex, tableName);
		fieldName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
		fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);

		//if the chosen table has a record ID field, do name tracking on the record ID	//11/04/08, 7.0.5, AJN
		recordIDFieldIndex = DBRecordIDFieldGetIndex(databaseIndex, tableIndex);
		if(recordIDFieldIndex >= 1)
			{
			recordName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
			recordIndex = DBRecordFind(databaseIndex, 		//database to search
									   tableIndex, 			//table to search
									   0, 					//use the record ID field as the search field
									   1, 					//the start record index
									   TRUE, 				//exact record match
									   recordName);			//the search string
			if(recordIndex == 0)
				recordIndex = -1;
			}
		else
			{
			whichRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			recordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[whichRow]);
			}
		
		if(databaseIndex >= 1  &&  tableIndex >= 1)
			DBBlockRegisterStructure(me, databaseIndex, tableIndex);
		}

	#ifdef EQ_IsQueryEquationTypeBlock
	
		DBQ_DatabaseIndex_prm = DBDatabaseGetIndex(DBQ_DatabaseName);
		DBQ_TableIndex_prm = DBTableGetIndex(DBQ_DatabaseIndex_prm, DBQ_TableName);
		
		if(DBQ_DatabaseIndex_prm >= 1  &&  DBQ_TableIndex_prm >= 1)
			{
			DBBlockRegisterStructure(me, DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm);
			}
			
	#endif //EQ_IsQueryEquationTypeBlock
			
}//procedure EQ_BlockRegisterStructure()


//called in LinkStructure if the database this block is pointing to gets deleted
procedure EQ_BlockUnRegisterStructure()
{

	DBBlockUnregisterStructure(MyBlockNumber(), -1, -1);	//"-1" for every param unregisters the block from ALL possible points of registration

}//procedure EQ_BlockUnRegisterStructure()

/*
//6/14/10
procedure EQ_InitDataStructures()
{

	integer me;
	integer simPhase;
	integer i, j;
	integer randomVal;
	string15 attribName;
	integer itemInConNum;
	integer numInBlocks;
	integer numIncludes;
	real latestModDate;
	integer recompile;
	
	me = MyBlockNumber();
	simPhase = GetSimulationPhase();
	
	#ifdef EQ_IsValueBlock
	if(
		(calcBeforeStart_chk == FALSE  &&  simPhase == PHASE_INITSIM)  ||
		(calcBeforeStart_chk == TRUE  &&  calcBeforeStart_pop == CALC_BEFORE_START_POSTINITSIM  &&  simPhase == PHASE_INITSIM)  ||
		(calcBeforeStart_chk == TRUE  &&  calcBeforeStart_pop != CALC_BEFORE_START_POSTINITSIM  &&  simPhase == PHASE_PRECHECKDATA)
	  )
	#else
	if(simPhase == PHASE_INITSIM)
	#endif
		{

		EQ_Calcing = FALSE;
		EQ_Calcing2 = FALSE;
		inLinkStructure = FALSE;
		me = MyBlockNumber();

		InitSeeds();															// initialize seeds for random number generator
	
		dialogIsOpen = BlockDialogIsOpen(MyBlockNumber());
		
		//get iVarsIn con nums
		for(i=0; i<iVarsIn_NumCons; i++)
			iVarsIn_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "IVarsIn", i);
	
		//conditionally initialize the iVars_Values
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(iVars_Types_Int[i] != EQ_STATIC_FRI  &&  iVars_Types_Int[i] != EQ_STATIC_MRI  &&  iVars_Types_Int[i] != EQ_STATIC_OPEN_MODEL)
				iVars_Values[i] = blank;
			}
		
		//recompile if include file is out of date
		if(currentSim == 0)
			{
			if(Incl_chk)
				{
				recompile = FALSE;
				numIncludes = GetDimension(Incl_FileNames_ttbl);
				for(i=0; i<numIncludes; i++)
					{
					latestModDate = FileInfo(incl_PathNames[i], 2);
					if(incl_ModifiedFileDates[i] != latestModDate)	//2 for modified date
						{
						incl_ModifiedFileDates[i] = latestModDate;
						recompile = TRUE;
						}
					}
				if(recompile == TRUE)
					{
					EQ_Compile(FALSE);
					}
				}
			}
		
		#ifdef EQ_IsValueBlock		//if is the Equation(I) or Query Equation(I)
			
			//time units conversion stuff
			if(CW_Intervals_TimeUnits_pop == DEFAULT_MODEL_TIME_UNITS)	//if true, then default model time units selected
				blockTimeUnits = GetTimeUnits();	
			else
				blockTimeUnits = CW_Intervals_TimeUnits_pop;
			
			if(EDCalendarDates()  &&  blockTimeUnits == TU_MILLISECONDS)
				{
				UserError("There is a problem in "+BlockName(me)+" block number, " + me + ".  Since model time is in Julian dates, this block's time units must be in seconds or greater.");
				abort;
				}
		
			if(EDCalendarDates())
				timeUnitConversionFactor = 1.;	//used to convert block time units to global time units
			else
				timeUnitConversionFactor = ConvertTimeUnits(1,blockTimeUnits, GetTimeUnits());	//used to convert block time units to global time units
		
		#endif //EQ_IsValueBlock
	
		//set up iVarsIn connector arrays
		if(CurrentSim == 0)
			{
			#ifdef iVarsIn
				iVarsIn_VarIsWhichConUpdate();
				iVarsIn_ConIsWhichVarUpdate();	//12/16/08	7.0.5	AJN
			#endif
			}
	
		
		//conditionally initialize the oVars_Values
		#ifdef oVars_Initialize_prm
			for(i=0; i<oVars_NumTableRows; i++)
				oVars_Values[i] = oVars_Initialize_prm;
		#else
			for(i=0; i<oVars_NumTableRows; i++)
				oVars_Values[i] = 0.0;
				//oVars_Values[i] = blank;	
					//"blank" was causing problems in continuous models, eg, a model where simulation order is such that the equation 
					//needs to provide a result before it has received it's first "on simulate" message.  (reference Inventory Mgt.mox)
		#endif
	
		#ifdef oVarsOut
		
			//set oVarsOut
			if(CurrentSim == 0)
				{
				oVarsOut_VarIsWhichConUpdate();	//Note!  must get oVarsOut_VarIsWhichCon first
				oVarsOut_ConIsWhichVarUpdate();
				}
	
			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(oVars_VarIsWhichCon[i] != -1)
					ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);	//	6/25/08	7.0.3		AJN	
				}
		
			//get oVarsOut con nums
			for(i=0; i<oVarsOut_NumCons; i++)
				oVarsOut_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "oVarsOut", i);
	
		#endif //oVarsOut
	
	
		//fill out oVars_GetValFromIVars
		if(CurrentSim == 0)
			{
			for(i=0; i<oVars_NumTableRows; i++)
				oVars_GetValFromIVars[i] = -1;
		
			for(i=0; i<oVars_NumTableRows; i++)
				{
				for(j=0; j<iVars_NumTableRows; j++)
					{
					if(oVars_Names[i] == iVars_Names[j])
						oVars_GetValFromIVars[i] = j;
						//if the same variable name is used to declare both an iVar and and oVar 
						//EquationCalculateDynamicVariables() will actually store the value of the 
						//oVar in the iVar.  oVars_GetValFromIVars[i] is used to go grab the value 
						//from the iVars array, stuff it in the oVars array, and then restore the 
						//original value of iVar.
					}
				}
			}
		
		//initialize the equation's static variables
		if(CurrentSim == 0)
			{
			for(i=0;i<iVars_NumTableRows;i++)
				{
				if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI)
					{
					iVars_Values[i] = iVars_StaticInitValues[i];
					iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i];
					}
				}
			}
		else
			{
			for(i=0;i<iVars_NumTableRows;i++)
				{
				if(iVars_Types_Int[i] == EQ_STATIC_MRI)
					{
					iVars_Values[i] = iVars_StaticInitValues[i];
					iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i];
					}
				}
			}
			
		}//

}//procedure EQ_InitDataStructures()
*/

//called in EQ_OnOK(), EQ_OnCheckData()
procedure EQ_CheckVariables()
{

	integer i, k;
	integer me;
	integer dbIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	
	me = MyBlockNumber();

	//check for input variables that have not been given a name
	for(i=0; i<iVars_NumTableRows; i++)
		{
		//copy user's iVar names from the input table to the associated individual array
		iVars_Names[i] = iVars_ttbl[i][I_VAR_NAME_COL];

		if(iVars_Names[i] == "")
			{
			UserError("A name needs to be specified for the input variable in row " + (i+1) + ".");
			AbortAllSims();
			}
		}
		
	//check for attrib input variables that have not had an attribute selected
	for(i=0; i<iVars_NumTableRows; i++)
		{
		//copy user's iVar names from the input table to the associated individual array
		iVars_Names[i] = iVars_ttbl[i][I_VAR_NAME_COL];

		if(iVars_Names[i] == "None")
			{
			UserError("An attribute needs to be specified for the input variable in row " + (i+1) + ".");
			AbortAllSims();
			}
		}
		
	//make sure no two input variables have the same name
	k=0;
	while(k < iVars_NumTableRows)
		{
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(iVars_Names[k] == iVars_Names[i]  &&  i!= k)
				{
				//if(iVars_Types_str[k] == iVars_Types_str[i])	//AJN, 7.0.5, 10/24/08
				//if(iVars_Types_Int[k] == iVars_Types_Int[i])	//allow "Attribute" and "QEQ attrib last item to exit" to both be pointing to the same attrib name		//4/18/11
					
				//4/18/11	
				if
				  (
					(iVars_Types_Int[k] == EQ_ITEM_ATTRIBUTE  &&  iVars_Types_Int[i] == EQ_QEQ_LAST_ITEM_TO_EXIT)
					||
					(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  &&  iVars_Types_Int[k] == EQ_QEQ_LAST_ITEM_TO_EXIT)
				  )
					{
					//do nothing
					}
				else
					{
					UserError("Two or more of your input variables have been given the same name. This is not allowed in the equation based blocks.");
					AbortAllSims();
					}
				}
			}
		k++;
		}

	//check for output variables that have not been given a name
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//copy user's result names from the output table to the associated individual array
		oVars_Names[i] = oVars_ttbl[i][O_VAR_NAME_COL];

		if(oVars_Names[i] == "")
			{
			UserError("A name needs to be specified for the output variable in row " + i + ".");
			AbortAllSims();
			}
		}

	//check for attrib output variables that have not had an attribute selected
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//copy user's oVar names from the output table to the associated individual array
		oVars_Names[i] = oVars_ttbl[i][I_VAR_NAME_COL];

		if(oVars_Names[i] == "None")
			{
			UserError("An attribute needs to be specified for the input variable in row " + (i+1) + ".");
			AbortAllSims();
			}
		}
		
	//make sure no two output variables have the same name
	k=0;
	while(k < oVars_NumTableRows)
		{
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(oVars_Names[k] == oVars_Names[i]  &&  i!= k)
				{
				//if(oVars_Types_str[k] == oVars_Types_str[i])	//AJN, 7.0.5, 10/24/08
				//if(oVars_Types_Int[k] == oVars_Types_Int[i])	//allow "Attribute" and "DBQS Attribute" to both be pointing to the same attrib name		//4/18/11
				
				//4/18/11
				if
				  (
					(oVars_Types_Int[k] == EQ_ITEM_ATTRIBUTE  &&  oVars_Types_Int[i] == EQ_DBQS_ATTRIB)
					||
					(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE  &&  oVars_Types_Int[k] == EQ_DBQS_ATTRIB)
				  )
					{
					//do nothing
					}
				else
					{
					UserError("Two or more of your output variables have been given the same name. This is not allowed in the equation based blocks.");
					AbortAllSims();
					}
				}
			}
		k++;
		}

	//5/10/11:  make sure a static input variable's name is also not used as an output variable name
	for(i=0; i<iVars_NumTableRows; i++)
		{
		for(k=0; k<oVars_NumTableRows; k++)
			{
			if(iVars_Names[i] == oVars_Names[k])
				{
				if(
					iVars_Types_Int[i] == EQ_STATIC_FRI  ||
					iVars_Types_Int[i] == EQ_STATIC_MRI  ||
					iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL  ||
					iVars_Types_Int[i] == EQ_QEQ_STATIC_CALC_CYCLE_INIT  ||
					iVars_Types_Int[i] == EQ_QEQ_STATIC_ITEM_VALUE  ||
					iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT
				  )
					{
					UserError("Error in equation block " + me + ". Duplicate input and output variable names are not allowed for the 'static' type variables. " + 
							  "The row " + (i+1) + " static input variable, """ + iVars_Names[i] + """, has the same name as the row " + (k+1) + " output variable.");
					
					AbortAllSims();
					}
				}
			}
		}
	
	//10/21/10:	make sure the required number of db indexes have been specified, if read/write index checking is on.
	//			we don't check to see if the locations actually exist because any missing database structures may 
	//			dynamically be added during the run.  instead we just check to see if the required index have at least been specified.	
	if( IsMenuItemOn(1931) )												
		{
		//check iVar db indexes 
		for(i=0; i<iVars_NumTableRows; i++)
			{
	
			//check database index
			if(
				iVars_Types_Int[i] ==  EQ_DB_DATABASE_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_TABLE_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_FIELD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_RECORD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_ADDRESS  ||
				iVars_Types_Int[i] ==  EQ_DB_READ_VAL  ||  
				iVars_Types_Int[i] ==  EQ_DB_READ_PRI
			  )
				{
				dbIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
				if( dbIndex < 1  ||  NoValue(dbIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the database index for the input variable named """ + iVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				}
				
			//check table index
			if(
				iVars_Types_Int[i] ==  EQ_DB_TABLE_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_FIELD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_RECORD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_READ_VAL  ||  
				iVars_Types_Int[i] ==  EQ_DB_READ_PRI
			  )
				{
				tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
				if( tableIndex < 1  ||  NoValue(tableIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the table index for the input variable named """ + iVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				}
				
			//check field index
			if(
				iVars_Types_Int[i] ==  EQ_DB_FIELD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_RECORD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_READ_VAL  ||  
				iVars_Types_Int[i] ==  EQ_DB_READ_PRI
			  )
				{
				fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
				if( fieldIndex < 1  ||  NoValue(fieldIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the field index for the input variable named """ + iVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				}
				
			//check record index
			if(
				iVars_Types_Int[i] ==  EQ_DB_RECORD_INDEX  ||
				iVars_Types_Int[i] ==  EQ_DB_READ_VAL  ||  
				iVars_Types_Int[i] ==  EQ_DB_READ_PRI  
			  )
				{
				recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
				if( recordIndex < 1  ||  NoValue(recordIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the record index for the input variable named """ + iVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				}
			}
		
		//check oVar db indexes
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(
				oVars_Types_Int[i] ==  EQ_DB_WRITE_VAL  ||  
				oVars_Types_Int[i] ==  EQ_DB_WRITE_PRI
			  )
				{
				dbIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[i]);
				if( dbIndex < 1  ||  NoValue(dbIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the database index for the output variable named """ + oVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				
				tableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[i]);
				if( tableIndex < 1  ||  NoValue(tableIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the table index for the output variable named """ + oVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				
				fieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[i]);
				if( fieldIndex < 1  ||  NoValue(fieldIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the field index for the output variable named """ + oVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				
				recordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[i]);
				if( recordIndex < 1  ||  NoValue(recordIndex) )
					{
					UserError("In " + BlockName(me) + " block " + me + " the record index for the output variable named """ + oVars_Names[i] + """ has not been specified.");
					AbortAllSims();
					}
				}
			}
		
		}//if( IsMenuItemOn(1931) )

}//procedure EQ_CheckVariables()


//used to determine what the size of iVars_TypesPop should be.  call BEFORE EQ_BuildVarTypesPopContentsArray() is called
integer EQ_GetVarPopSize(integer varPopOptions[])
{

	integer numAttribs;
	integer numElements;
	integer i;
	
	numElements = 0;

	//item info variables
	if(varPopOptions[EQ_ITEM_ATTRIBUTE] == TRUE)
	  	numElements = numElements + 1;
  
	if(varPopOptions[EQ_ITEM_QTY] == TRUE)
	  	numElements = numElements + 1;
  
	if(varPopOptions[EQ_ITEM_PRIORITY] == TRUE)
	  	numElements = numElements + 1;
  
	if(varPopOptions[EQ_ITEM_AR_ORDER_ID] == TRUE)
	  	numElements = numElements + 1;
  
	if(varPopOptions[EQ_ITEM_INDEX] == TRUE)
	  	numElements = numElements + 1;
  
	if(varPopOptions[EQ_ITEM_BATCH_SIZE] == TRUE)
	  	numElements = numElements + 1;
	  	
 	if(varPopOptions[EQ_QEQ_LAST_ITEM_TO_EXIT] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_ITEM_3D_ID] == TRUE)
	  	numElements = numElements + 1;
  
	//item info separator
	if(varPopOptions[EQ_ITEM_ATTRIBUTE] == TRUE  ||  
		varPopOptions[EQ_ITEM_QTY] == TRUE  ||  
		varPopOptions[EQ_ITEM_PRIORITY] == TRUE  ||  
		varPopOptions[EQ_ITEM_AR_ORDER_ID] == TRUE  ||  
		varPopOptions[EQ_ITEM_INDEX] == TRUE  ||  
		varPopOptions[EQ_ITEM_BATCH_SIZE] == TRUE  ||  
		varPopOptions[EQ_QEQ_LAST_ITEM_TO_EXIT] == TRUE  ||  
		varPopOptions[EQ_ITEM_3D_ID] == TRUE)
	 	{ 	
	  	numElements = numElements + 1;
	  	}
 
 	//Static variables
 	if(varPopOptions[EQ_STATIC_FRI] == TRUE)
	  	numElements = numElements + 1;
  
 	if(varPopOptions[EQ_STATIC_MRI] == TRUE)
	  	numElements = numElements + 1;
  
 	if(varPopOptions[EQ_STATIC_OPEN_MODEL] == TRUE)
	  	numElements = numElements + 1;
  
	//Static separator
	if(
		varPopOptions[EQ_STATIC_FRI] == TRUE  ||  
		varPopOptions[EQ_STATIC_MRI] == TRUE  ||
		varPopOptions[EQ_STATIC_OPEN_MODEL] == TRUE
	  )  
	 	{ 	
	  	numElements = numElements + 1;
	  	}
 
 	//4/16/11:  next calc event time variable + separator
 	if(varPopOptions[EQ_NEXT_CALC_EVENT_TIME] == TRUE)
	  	numElements = numElements + 2;						//NOTE:  there can only be one of these types of variables
 	
 	//DB variables
 	if(varPopOptions[EQ_DB_READ_VAL] == TRUE)
	  	numElements = numElements + 1;
  
 	if(varPopOptions[EQ_DB_READ_PRI] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_WRITE_VAL] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_WRITE_PRI] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_READ_VAL_USING_ATTRIB] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_READ_PRI_USING_ATTRIB] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_WRITE_VAL_USING_ATTRIB] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_WRITE_PRI_USING_ATTRIB] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DB_ADDRESS] == TRUE)
	  	numElements = numElements + 1;

 	//6/25/09
 	//if(varPopOptions[EQ_DB_INDEX] == TRUE)
	//  	numElements = numElements + 1;
 	
 	if(varPopOptions[EQ_DB_DATABASE_INDEX] == TRUE)
	  	numElements = numElements + 1;
 	
 	if(varPopOptions[EQ_DB_TABLE_INDEX] == TRUE)
	  	numElements = numElements + 1;
 	
 	if(varPopOptions[EQ_DB_FIELD_INDEX] == TRUE)
	  	numElements = numElements + 1;
 	
 	if(varPopOptions[EQ_DB_RECORD_INDEX] == TRUE)
	  	numElements = numElements + 1;

	//DB separator
	if(
		varPopOptions[EQ_DB_READ_VAL] == TRUE  ||  
		varPopOptions[EQ_DB_READ_PRI] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_VAL] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_PRI] == TRUE  ||  
		varPopOptions[EQ_DB_READ_VAL_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_READ_PRI_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_VAL_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_PRI_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_ADDRESS] == TRUE  ||  
		//varPopOptions[EQ_DB_INDEX] == TRUE  ||  					//6/25/09
		varPopOptions[EQ_DB_DATABASE_INDEX] == TRUE  ||  
		varPopOptions[EQ_DB_TABLE_INDEX] == TRUE  ||  
		varPopOptions[EQ_DB_FIELD_INDEX] == TRUE  ||  
		varPopOptions[EQ_DB_RECORD_INDEX] == TRUE
	  )  
	 	{ 	
	  	numElements = numElements + 1;
	  	}

	//EQ_QEQ type variables
 	if(varPopOptions[EQ_QEQ_ITEM_ARRIVAL_TIME] == TRUE)
	  	numElements = numElements + 1;
  
 	if(varPopOptions[EQ_QEQ_CURR_BEST_RANK_RESULT] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_QEQ_NUM_ITEMS_IN_QUEUE] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_QEQ_STATIC_CALC_CYCLE_INIT] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_QEQ_STATIC_ITEM_VALUE] == TRUE)			//11/17/10
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_QEQ_HALT_CALCULATION_CYCLE] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_QEQ_FIFO_POSTION] == TRUE)
	  	numElements = numElements + 1;
  
 	if(varPopOptions[EQ_QEQ_ITEM_RANK] == TRUE)
	  	numElements = numElements + 1;
  
	//EQ_Q separator
	if(
		varPopOptions[EQ_QEQ_ITEM_ARRIVAL_TIME] == TRUE  ||  
		varPopOptions[EQ_QEQ_CURR_BEST_RANK_RESULT] == TRUE  ||  
		varPopOptions[EQ_QEQ_NUM_ITEMS_IN_QUEUE] == TRUE  ||  
		varPopOptions[EQ_QEQ_STATIC_CALC_CYCLE_INIT] == TRUE  ||  
		varPopOptions[EQ_QEQ_STATIC_ITEM_VALUE] == TRUE  ||  						//11/17/10
		varPopOptions[EQ_QEQ_HALT_CALCULATION_CYCLE] == TRUE  ||  
		varPopOptions[EQ_QEQ_FIFO_POSTION] == TRUE  ||  
		varPopOptions[EQ_QEQ_ITEM_RANK] == TRUE
	  )
	 	{ 	
	  	numElements = numElements + 1;
	  	}
	  	
	//QEQ AR type variables
 	if(varPopOptions[EQ_QEQ_AR_REQUIREMENT_IS_AVAIL] == TRUE)
	  	numElements = numElements + 1;
	
 	if(varPopOptions[EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL] == TRUE)
	  	numElements = numElements + 1;
	
 	if(varPopOptions[EQ_QEQ_AR_ALLOCATE_REQUIREMENT] == TRUE)
	  	numElements = numElements + 1;
	
	//QEQ AR separator
	if(
		varPopOptions[EQ_QEQ_AR_REQUIREMENT_IS_AVAIL] == TRUE  || 
		varPopOptions[EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL] == TRUE  || 
		varPopOptions[EQ_QEQ_AR_ALLOCATE_REQUIREMENT] == TRUE
	  )
	 	{ 	
	  	numElements = numElements + 1;
	  	}
 
	//DBQ type variables
 	if(varPopOptions[EQ_DBQ_STATIC_QUERY_INIT] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_QUERY_FIELD_VALUE] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_QUERY_FIELD_PRI] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_START_RECORD] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_CURRENT_RECORD] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_NUM_RECORDS] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_HALT_QUERY] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_NEXT_RECORD] == TRUE)
	  	numElements = numElements + 1;

	//DBQ separator
	if(
		varPopOptions[EQ_DBQ_STATIC_QUERY_INIT] == TRUE  ||  
		varPopOptions[EQ_DBQ_QUERY_FIELD_VALUE] == TRUE  ||
		varPopOptions[EQ_DBQ_QUERY_FIELD_PRI] == TRUE  ||
		varPopOptions[EQ_DBQ_START_RECORD] == TRUE  ||
		varPopOptions[EQ_DBQ_CURRENT_RECORD] == TRUE ||
		varPopOptions[EQ_DBQ_NUM_RECORDS] == TRUE  ||
		varPopOptions[EQ_DBQ_HALT_QUERY] == TRUE  ||
		varPopOptions[EQ_DBQ_NEXT_RECORD] == TRUE
	  )
	 	{ 	
	  	numElements = numElements + 1;
	  	}

	//DBQPT type variables
 	if(varPopOptions[EQ_DBQ_CURR_BEST_RANK_RESULT] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS] == TRUE)
	  	numElements = numElements + 1;
 	
 	if(varPopOptions[EQ_DBQ_RECORD_RANK] == TRUE)
	  	numElements = numElements + 1;

	//DBQPT separator
	if(	varPopOptions[EQ_DBQ_CURR_BEST_RANK_RESULT] == TRUE  ||
		varPopOptions[EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS] == TRUE  ||
		varPopOptions[EQ_DBQ_RECORD_RANK] == TRUE)
	 	{ 	
	  	numElements = numElements + 1;
	  	}

 	//DBQS type variables
 	if(varPopOptions[EQ_DBQS_CURR_BEST_RANK_RESULT] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS] == TRUE)
	  	numElements = numElements + 1;
 	
 	if(varPopOptions[EQ_DBQS_RECORD_RANK] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQS_ATTRIB] == TRUE)
	  	numElements = numElements + 1;


 	if(varPopOptions[EQ_DBQS_ITEM_QTY] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQS_ITEM_PRIORITY] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_DBQS_3D_OBJECT_ID] == TRUE)
	  	numElements = numElements + 1;

	//DBQS separator
	if(	
		varPopOptions[EQ_DBQS_CURR_BEST_RANK_RESULT] == TRUE  ||
		varPopOptions[EQ_DBQS_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DBQS_ITEM_QTY] == TRUE  ||  
		varPopOptions[EQ_DBQS_ITEM_PRIORITY] == TRUE  ||  
		varPopOptions[EQ_DBQS_3D_OBJECT_ID] == TRUE  ||  
		varPopOptions[EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS] == TRUE  ||
		varPopOptions[EQ_DBQS_RECORD_RANK] == TRUE
	  )
	 	{ 	
	  	numElements = numElements + 1;
	  	}

 	//random type variables
 	if(varPopOptions[EQ_CALC_NEXT_EVENT] == TRUE)
	  	numElements = numElements + 1;

	//random separator
	if(varPopOptions[EQ_CALC_NEXT_EVENT] == TRUE)
		{
		numElements = numElements + 1;
		}

	//Carollo
	if(varPopOptions[EQ_Integer] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_Real] == TRUE)
	  	numElements = numElements + 1;

 	if(varPopOptions[EQ_String] == TRUE)
	  	numElements = numElements + 1;
	  	
	//add elements for connector vars
   	if(varPopOptions[EQ_CONNECTORS] == TRUE)
   		numElements = numElements + 1;	//+1 for the connector var


	return(numElements);
  
}//integer EQ_GetVarPopSize(integer varPopOptions[])


//called in Attrib_AttachNamesToPopup, Attrib_GetPopVal, Attrib_DoOnAttribPop.  this procedure builds up 
//the varTypesPopContents array which is used to display a list of possible variable types in a popup menu
procedure EQ_BuildVarTypesPopContentsArray(string varTypesPopContents[], integer varPopOptions[])
{
  	integer i, j;
	integer numNames;	//number of rows in _attributeList, ie, number attributes used in the model
	integer nextOpenContentsSlot;
	integer nextAttribSlot;
	integer nextSASlot;
	integer nextDBSlot;
	string15 nextAttribName;
	string15 currAttribName;
	integer currDBType;
	integer nextDBType;
    
	//erase contents of varTypesPopContents
	nextOpenContentsSlot = 0;
    	
	//itemInfo variables
	if(varPopOptions[EQ_ITEM_ATTRIBUTE] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Attribute";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_ITEM_QTY] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Item quantity";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_ITEM_PRIORITY] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Item priority";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_ITEM_INDEX] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Item index";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_ITEM_BATCH_SIZE] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Batch size";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_ITEM_3D_ID] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "3D object ID";
		nextOpenContentsSlot += 1;
	    }
	
	//EQ_QEQ separator
	if((varPopOptions[EQ_QEQ_ITEM_ARRIVAL_TIME] == TRUE  ||  
		varPopOptions[EQ_QEQ_FIFO_POSTION] == TRUE  ||  
		varPopOptions[EQ_QEQ_ITEM_RANK] == TRUE  ||  
		varPopOptions[EQ_QEQ_NUM_ITEMS_IN_QUEUE] == TRUE  ||  
		varPopOptions[EQ_QEQ_STATIC_CALC_CYCLE_INIT] == TRUE  ||  
		varPopOptions[EQ_QEQ_STATIC_ITEM_VALUE] == TRUE  || 				//11/17/10 
		varPopOptions[EQ_QEQ_LAST_ITEM_TO_EXIT] == TRUE  ||  
		varPopOptions[EQ_QEQ_HALT_CALCULATION_CYCLE] == TRUE  ||  
		varPopOptions[EQ_QEQ_CURR_BEST_RANK_RESULT] == TRUE)  &&
		nextOpenContentsSlot > 0)
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//EQ_QEQ variables
	if(varPopOptions[EQ_QEQ_ITEM_ARRIVAL_TIME] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ arrival time";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_FIFO_POSTION] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ FIFO position";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_ITEM_RANK] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ item rank";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_CURR_BEST_RANK_RESULT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ current best item rank";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_LAST_ITEM_TO_EXIT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ attrib last item to exit";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_NUM_ITEMS_IN_QUEUE] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ num items in queue";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_STATIC_CALC_CYCLE_INIT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ static calc cycle init";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_STATIC_ITEM_VALUE] == TRUE)						//11/17/10
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ static item value";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_HALT_CALCULATION_CYCLE] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "QEQ halt calculation cycle";
		nextOpenContentsSlot += 1;
		}
	
	//EQ_AR separator
	if(
		varPopOptions[EQ_QEQ_AR_ALLOCATE_REQUIREMENT] == TRUE  ||
		varPopOptions[EQ_QEQ_AR_REQUIREMENT_IS_AVAIL] == TRUE  ||
		varPopOptions[EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL] == TRUE
	  )
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//EQ_AR variables
	if(varPopOptions[EQ_QEQ_AR_REQUIREMENT_IS_AVAIL] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "AR requirement is avail";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "AR num requirements avail";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_QEQ_AR_ALLOCATE_REQUIREMENT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "AR allocate requirement";
		nextOpenContentsSlot += 1;
		}

	//DBQ separator
	if(
		(
		varPopOptions[EQ_DBQ_STATIC_QUERY_INIT] == TRUE				||  
		varPopOptions[EQ_DBQ_QUERY_FIELD_VALUE] == TRUE				||  
		varPopOptions[EQ_DBQ_QUERY_FIELD_PRI] == TRUE				||  
		varPopOptions[EQ_DBQ_START_RECORD] == TRUE					||  
		varPopOptions[EQ_DBQ_CURRENT_RECORD] == TRUE				||  
		varPopOptions[EQ_DBQ_NUM_RECORDS] == TRUE					||  
		varPopOptions[EQ_DBQ_HALT_QUERY] == TRUE					||  
		varPopOptions[EQ_DBQ_RECORD_RANK] == TRUE					||  
		varPopOptions[EQ_DBQ_NEXT_RECORD] == TRUE					||
		varPopOptions[EQ_DBQ_CURR_BEST_RANK_RESULT] == TRUE			||
		varPopOptions[EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS] == TRUE
		)  
		&&
		nextOpenContentsSlot > 0
	  )
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//DBQ variables
	if(varPopOptions[EQ_DBQ_STATIC_QUERY_INIT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ static query init";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_QUERY_FIELD_VALUE] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ read value";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_QUERY_FIELD_PRI] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ read PRI";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_START_RECORD] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ start record";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_CURRENT_RECORD] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ current record index";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_NEXT_RECORD] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ next record";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_NUM_RECORDS] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ num records";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_HALT_QUERY] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ halt query";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_RECORD_RANK] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ record rank";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_CURR_BEST_RANK_RESULT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ current best record rank";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQ num non-blank ranks";
		nextOpenContentsSlot += 1;
		}
	
	//DBQS separator
	if(
		(
		varPopOptions[EQ_DBQS_CURR_BEST_RANK_RESULT] == TRUE  ||  
		varPopOptions[EQ_DBQS_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DBQS_ITEM_QTY] == TRUE  ||  
		varPopOptions[EQ_DBQS_ITEM_PRIORITY] == TRUE  ||  
		varPopOptions[EQ_DBQS_3D_OBJECT_ID] == TRUE  ||  
		varPopOptions[EQ_DBQS_RECORD_RANK] == TRUE  ||  
		varPopOptions[EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS] == TRUE
		)  
	  &&
	  nextOpenContentsSlot > 0
	  )
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//DBQS variables
	if(varPopOptions[EQ_DBQS_RECORD_RANK] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS record rank";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQS_CURR_BEST_RANK_RESULT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS current best rank result";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DBQS_ATTRIB] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS attribute";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_DBQS_ITEM_QTY] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS item quantity";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_DBQS_ITEM_PRIORITY] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS item priority";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_DBQS_3D_OBJECT_ID] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS 3D object ID";
		nextOpenContentsSlot += 1;
	    }
	if(varPopOptions[EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DBQS num non-blank ranks";
		nextOpenContentsSlot += 1;
		}

	//DB separator
	if(
		(
		varPopOptions[EQ_DB_READ_VAL] == TRUE  ||  
		varPopOptions[EQ_DB_READ_PRI] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_VAL] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_PRI] == TRUE  ||  
		varPopOptions[EQ_DB_READ_VAL_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_READ_PRI_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_VAL_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_WRITE_PRI_USING_ATTRIB] == TRUE  ||  
		varPopOptions[EQ_DB_ADDRESS] == TRUE  ||  
		//varPopOptions[EQ_DB_INDEX] == TRUE		//6/25/09
		varPopOptions[EQ_DB_DATABASE_INDEX] == TRUE  ||
		varPopOptions[EQ_DB_TABLE_INDEX] == TRUE  ||
		varPopOptions[EQ_DB_FIELD_INDEX] == TRUE  ||
		varPopOptions[EQ_DB_RECORD_INDEX] == TRUE
		)
		&&  nextOpenContentsSlot > 0
	  )
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//DB variables 
	if(varPopOptions[EQ_DB_READ_VAL] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB read value";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_READ_VAL_USING_ATTRIB] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB read value using attrib";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_READ_PRI] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB read PRI";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_READ_PRI_USING_ATTRIB] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB read PRI using attrib";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_WRITE_VAL] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB write value";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_WRITE_VAL_USING_ATTRIB] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB write value using attrib";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_WRITE_PRI] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB write PRI";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_WRITE_PRI_USING_ATTRIB] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB write PRI using attrib";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_ADDRESS] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB address";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_DATABASE_INDEX] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB database index";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_TABLE_INDEX] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB table index";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_FIELD_INDEX] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB field index";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_DB_RECORD_INDEX] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "DB record index";
		nextOpenContentsSlot += 1;
		}

	//static separator
	if(
		(
		 varPopOptions[EQ_STATIC_FRI] == TRUE  ||  
		 varPopOptions[EQ_STATIC_MRI] == TRUE  ||
		 varPopOptions[EQ_STATIC_OPEN_MODEL] == TRUE
		)  &&
		(nextOpenContentsSlot > 0)
	  )
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//static variables
	if(varPopOptions[EQ_STATIC_FRI] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Static first run init";
		nextOpenContentsSlot += 1;
		}
	if(varPopOptions[EQ_STATIC_MRI] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Static multi run init";
		nextOpenContentsSlot += 1;
		}

	if(varPopOptions[EQ_STATIC_OPEN_MODEL] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Static open model init";
		nextOpenContentsSlot += 1;
		}

	//calc event separator
	if(varPopOptions[EQ_CALC_NEXT_EVENT] == TRUE  &&  nextOpenContentsSlot > 0)
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//calc event variable
	if(varPopOptions[EQ_CALC_NEXT_EVENT] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Calc event time";
		nextOpenContentsSlot += 1;
		}

	//4/16/11:  next event separator
	if(varPopOptions[EQ_NEXT_CALC_EVENT_TIME] == TRUE  &&  nextOpenContentsSlot > 0)
	 	{ 	
	    varTypesPopContents[nextOpenContentsSlot] = "-";
		nextOpenContentsSlot += 1;
	  	}
	
	//4/16/11:  next event variable
	if(varPopOptions[EQ_NEXT_CALC_EVENT_TIME] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Next calc event time";
		nextOpenContentsSlot += 1;
		}
	

	//Carollo
	if(varPopOptions[EQ_Integer] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Integer";
		nextOpenContentsSlot += 1;
		}

	//Carollo
	if(varPopOptions[EQ_Real] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "Real";
		nextOpenContentsSlot += 1;
		}

	//Carollo
	if(varPopOptions[EQ_String] == TRUE)
		{
		varTypesPopContents[nextOpenContentsSlot] = "String";
		nextOpenContentsSlot += 1;
		}

	//connector variables
   	if(varPopOptions[EQ_CONNECTORS] == TRUE)
   		{
		varTypesPopContents[nextOpenContentsSlot] = "Connector";
		nextOpenContentsSlot += 1;
		}


}//procedure EQ_BuildVarTypesPopContentsArray(string varTypesPopContents[], integer varPopOptions[])


//called in EQ_OnCheckData(), EQ_OnInitSim(), EQ_OnOpenModel(), iVars_ShowTypesPopup, oVars_ShowTypesPopup, 
//InitSim, and EQ_CalcNoItem, this function returns the integer ID of the variable type for "typeName"
integer EQ_VarTypeGet(string typeName)
{
	integer typeNumber;
	
	//update iVars_Types_Int, ie, create the integer equivalent
	if(typeName == "DB read value"  ||  typeName == "_DB read value")
		typeNumber = EQ_DB_READ_VAL;
	
	else if(typeName == "DB read PRI"  ||  typeName == "_DB read PRI")
		typeNumber = EQ_DB_READ_PRI;
	
	else if(typeName == "DB write value"  ||  typeName == "_DB write value")
		typeNumber = EQ_DB_WRITE_VAL;
	
	else if(typeName == "DB write PRI"  ||  typeName == "_DB write PRI")
		typeNumber = EQ_DB_WRITE_PRI;
	
	else if(typeName == "DB address"  ||  typeName == "_DB address")
		typeNumber = EQ_DB_ADDRESS;
	
	//6/25/09
	//else if(typeName == "_DB index")
	//	typeNumber = EQ_DB_INDEX;
	
	//4/16/11
	else if(typeName == "Next calc event time")
		typeNumber = EQ_NEXT_CALC_EVENT_TIME;
	
	else if(typeName == "DB database index"  ||  typeName == "_DB database index")
		typeNumber = EQ_DB_DATABASE_INDEX;
	
	else if(typeName == "DB table index"  ||  typeName == "_DB table index")
		typeNumber = EQ_DB_TABLE_INDEX;
	
	else if(typeName == "DB field index"  ||  typeName == "_DB field index")
		typeNumber = EQ_DB_FIELD_INDEX;
	
	else if(typeName == "DB record index"  ||  typeName == "_DB record index")
		typeNumber = EQ_DB_RECORD_INDEX;
	
	else if(typeName == "Static first run init"  ||  typeName == "_Static first run init")
		typeNumber = EQ_STATIC_FRI;
	
	else if(typeName == "Static multi run init"  ||  typeName == "_Static multi run init")
		typeNumber = EQ_STATIC_MRI;
		
	else if(typeName == "Static open model init"  ||  typeName == "_Static open model init")
		typeNumber = EQ_STATIC_OPEN_MODEL;
		
	else if(typeName == "Calc event time"  ||  typeName == "_Calc event time")
		typeNumber = EQ_CALC_NEXT_EVENT;
	

	//Carollo
	else if(typeName == "Integer"  ||  typeName == "_Integer")
		typeNumber = EQ_Integer;

	//Carollo
	else if(typeName == "Real"  ||  typeName == "_Real")
		typeNumber = EQ_Real;

	//Carollo
	else if(typeName == "String"  ||  typeName == "_String")
		typeNumber = EQ_String;



	#ifdef EQ_IsQueryEquationTypeBlock
	
		//iVars
		else if(typeName == "DBQ read value"  ||  typeName == "DBQ query field value"  ||  typeName == "_DBQ query field value")
			typeNumber = EQ_DBQ_QUERY_FIELD_VALUE;
	
		else if(typeName == "DBQ read PRI"  ||  typeName == "DBQ query field PRI"  ||  typeName == "_DBQ query field PRI")
			typeNumber = EQ_DBQ_QUERY_FIELD_PRI;

		else if(typeName == "DBQ start record"  ||  typeName == "_DBQ start record")
			typeNumber = EQ_DBQ_START_RECORD;
	
		else if(typeName == "DBQ current record index"  ||  typeName == "DBQ current record"  ||  typeName == "_DBQ current record")
			typeNumber = EQ_DBQ_CURRENT_RECORD;
	
		else if(typeName == "DBQ num records"  ||  typeName == "_DBQ num records")
			typeNumber = EQ_DBQ_NUM_RECORDS;
	
		else if(typeName == "DBQ current best record rank"  ||  typeName == "_DBQ current best record rank")
			typeNumber = EQ_DBQ_CURR_BEST_RANK_RESULT;

		else if(typeName == "DBQS current best rank result"  ||  typeName == "_DBQS current best rank result")
			typeNumber = EQ_DBQS_CURR_BEST_RANK_RESULT;

		else if(typeName == "DBQ num non-blank ranks"  ||  typeName == "_DBQ num non-blank ranks")
			typeNumber = EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS;

		else if(typeName == "DBQS num non-blank ranks"  ||  typeName == "_DBQS num non-blank ranks")
			typeNumber = EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS;

		else if(typeName == "DBQ static query init"  ||  typeName == "_DBQ static query init")
			typeNumber = EQ_DBQ_STATIC_QUERY_INIT;
		
		//oVars
		else if(typeName == "DBQ record rank"  ||  typeName == "_DBQ record rank")
			typeNumber = EQ_DBQ_RECORD_RANK;
	
		else if(typeName == "DBQ halt query"  ||  typeName == "_DBQ halt query")
			typeNumber = EQ_DBQ_HALT_QUERY;
	
		else if(typeName == "DBQ next record"  ||  typeName == "_DBQ next record")
			typeNumber = EQ_DBQ_NEXT_RECORD;
	
		else if(typeName == "DBQS record rank"  ||  typeName == "_DBQS record rank")
			typeNumber = EQ_DBQS_RECORD_RANK;
	
		else if(typeName == "DBQS attribute"  ||  typeName == "_DBQS attribute")
			typeNumber = EQ_DBQS_ATTRIB;
	
		else if(typeName == "DBQS item quantity"  ||  typeName == "_DBQS item quantity")
			typeNumber = EQ_DBQS_ITEM_QTY;
	
		else if(typeName == "DBQS item priority"  ||  typeName == "_DBQS item priority")
			typeNumber = EQ_DBQS_ITEM_PRIORITY;
	
		else if(typeName == "DBQS 3D object ID"  ||  typeName == "_DBQS 3D object ID")
			typeNumber = EQ_DBQS_3D_OBJECT_ID;
	
	#endif //EQ_IsQueryEquationTypeBlock
	
	#ifdef EQ_IsItemBlock
	
		else if(typeName == "Attribute"  ||  typeName == "_Attribute")
			typeNumber = EQ_ITEM_ATTRIBUTE;
		
		else if(typeName == "QEQ attrib last item to exit"  ||  typeName == "_QEQ attrib last item to exit")
			typeNumber = EQ_QEQ_LAST_ITEM_TO_EXIT;
		
		else if(typeName == "DB read value using attrib"  ||  typeName == "_DB read value using attrib")
			typeNumber = EQ_DB_READ_VAL_USING_ATTRIB;
		
		else if(typeName == "DB read PRI using attrib"  ||  typeName == "_DB read PRI using attrib")
			typeNumber = EQ_DB_READ_PRI_USING_ATTRIB;
		
		else if(typeName == "DB write value using attrib"  ||  typeName == "_DB write value using attrib")
			typeNumber = EQ_DB_WRITE_VAL_USING_ATTRIB;

		else if(typeName == "DB write PRI using attrib"  ||  typeName == "_DB write PRI using attrib")
			typeNumber = EQ_DB_WRITE_PRI_USING_ATTRIB;

		else if(typeName == "Item quantity"  ||  typeName == "_Item quantity")
			typeNumber = EQ_ITEM_QTY;
		
		else if(typeName == "Item priority"  ||  typeName == "_Item priority")
			typeNumber = EQ_ITEM_PRIORITY;
		
		else if(typeName == "Item index"  ||  typeName == "_Item index")
			typeNumber = EQ_ITEM_INDEX;
		
		else if(typeName == "3D object ID"  ||  typeName == "_3D object ID")
			typeNumber = EQ_ITEM_3D_ID;
		
		else if(typeName == "Batch size"  ||  typeName == "_Batch size")
			typeNumber = EQ_ITEM_BATCH_SIZE;
		
		else if(typeName == "QEQ arrival time"  ||  typeName == "_QEQ arrival time"  ||  typeName == "Arrival time"  ||  typeName == "_Arrival time")
			typeNumber = EQ_QEQ_ITEM_ARRIVAL_TIME;
		
		else if(typeName == "QEQ current best item rank"  ||  typeName == "_QEQ current best item rank"  ||  typeName == "Best result"  ||  typeName == "_Best result")
			typeNumber = EQ_QEQ_CURR_BEST_RANK_RESULT;
		
		else if(typeName == "QEQ FIFO position"  ||  typeName == "_QEQ FIFO position"  ||  typeName == "Queue rank"  ||  typeName == "_Queue rank")
			typeNumber = EQ_QEQ_FIFO_POSTION;
		
		else if(typeName == "QEQ item rank"  ||  typeName == "_QEQ item rank"  ||  typeName == "Result rank"  ||  typeName == "_Result rank")
			typeNumber = EQ_QEQ_ITEM_RANK;
		
		else if(typeName == "QEQ num items in queue"  ||  typeName == "_QEQ num items in queue")
			typeNumber = EQ_QEQ_NUM_ITEMS_IN_QUEUE;
		
		else if(typeName == "QEQ static calc cycle init"  ||  typeName == "_QEQ static calc cycle init")
			typeNumber = EQ_QEQ_STATIC_CALC_CYCLE_INIT;
		
		else if(typeName == "QEQ static item value")		//11/17/10
			typeNumber = EQ_QEQ_STATIC_ITEM_VALUE;
		
		else if(typeName == "QEQ halt calculation cycle"  ||  typeName == "_QEQ halt calculation cycle")
			typeNumber = EQ_QEQ_HALT_CALCULATION_CYCLE;
		
		else if(typeName == "AR requirement is avail"  ||  typeName == "_AR requirement is avail")
			typeNumber = EQ_QEQ_AR_REQUIREMENT_IS_AVAIL;
		
		else if(typeName == "AR num requirements avail"  ||  typeName == "_AR num requirements avail")
			typeNumber = EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL;
		
		else if(typeName == "AR allocate requirement"  ||  typeName == "_AR allocate requirement")
			typeNumber = EQ_QEQ_AR_ALLOCATE_REQUIREMENT;
		
	#endif //EQ_IsItemBlock
	
	else
		typeNumber = EQ_CONNECTORS;
		
	return(typeNumber);

}//integer EQ_VarTypeGet(string typeName)


integer EQ_IsReservedWord(string nameToCheck)
{

	if(nameToCheck == "CurrentTime"	||  nameToCheck == "CurrentSim"	||  nameToCheck == "CurrentStep"  ||
	   nameToCheck == "EndTime"		||  nameToCheck == "DeltaTime"	||  nameToCheck == "DeltaTime"	||  nameToCheck == "step")
		return TRUE;
	else
		return FALSE;
	
}//integer EQ_IsReservedWord(string nameToCheck)


//check for spaces in the variable names.  allow spaces for attribute input
//variable names for backwords compatibility.  called in "on iVars_ttbl",
//"on oVars_ttbl" and "on DialogOpen"
procedure EQ_CheckForSpaces(integer doAbort)
{
	
	integer i;
	integer spaceFound;

	spaceFound = FALSE;
	
	for(i=0;i<iVars_NumTableRows;i++)
		{
		if(StrFind(iVars_Names[i]," ",FALSE,FALSE) >= 0)
			{
			if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) < 0)
				{
				UserError("Variable names cannot have spaces in them.");
				
				if(doAbort == TRUE)
					AbortAllSims();
				}
			spaceFound = TRUE;
			}
		}
	
	for(i=0;i<oVars_NumTableRows;i++)
		{
		if(StrFind(oVars_Names[i]," ",FALSE,FALSE) >= 0)
			{
			if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) < 0)
				{
				UserError("Variable names cannot have spaces in them.");
				AbortAllSims();
				}
			spaceFound = TRUE;
			}
		}
	
	if(spaceFound)
		HideDialogItem("attribSpaceNote_lbl",FALSE);
	else
		HideDialogItem("attribSpaceNote_lbl",TRUE);

}//procedure EQ_CheckForSpaces()


//because spaces were allowed in attribute names until v7, backwords compatibility
//requires that we allow for old attributes names with spaces to be allowed as
//names for input variables.  consequently, this function substitutes an "_" for 
//the spaces in those old attrib names.  called in EQ_Compile()
string EQ_RemoveSpaces(string varName)			
{

	integer placeSpaceFound;
	integer varNameLength;
	string newName;
	integer i;

	newName = varName;
	i = 0;

	//remove all spaces from varName
	placeSpaceFound = StrFind(newName," ",FALSE,FALSE);
	while(placeSpaceFound >= 0)
		{
		newName = StrReplace(newName, placeSpaceFound, 1, "_");
		i++;
		placeSpaceFound = StrFind(newName, " ", 0, 0);
		}
		
	//if varName had any spaces in it,
	if(i > 0)
		{
		//then replace all occurrences of varName in the equation with newName
		varNameLength = strLen(newName);
		placeSpaceFound = StrFindDynamic(EQ_EquationText, varName, 0, 0, 0);
		while(placeSpaceFound >= 0)
			{
			StrReplaceDynamic(EQ_EquationText, placeSpaceFound, varNameLength, newName);
			placeSpaceFound = StrFindDynamic(EQ_EquationText, varName, 0, 0, 0);
			}
		}
		
	return(newName);

}//string EQ_RemoveSpaces(string varName)			


procedure EQ_TranslateEquation()
{

	integer i, j;
	integer sizeEquationArray;
	integer placeFound;
	integer stringLength;
	string15 stringToFind;
	string15 previousChar;
	string15 subsequentChar;
	integer startPoint;

	//fill EQ_TranslatedEquationText with the current contents of EQ_EquationText
	sizeEquationArray = GetDimension(EQ_EquationText);
	MakeArray(EQ_TranslatedEquationText, sizeEquationArray);
	for(i=0; i<sizeEquationArray; i++)
		EQ_TranslatedEquationText[i] = EQ_EquationText[i];
	
	//**********************
	//Start: Input Variables

	//replace every instance of the input variable name with iVars_Values[i]
	for(i=0; i<iVars_NumTableRows; i++)
		{
		stringToFind = iVars_Names[i];
		stringLength = strLen(stringToFind);
		startPoint = 0;
		
		do
			{
			placeFound = StrFindDynamicStartPoint(EQ_TranslatedEquationText, stringToFind, 0, 0, 1, startPoint);  //returns the place where the string was found or -1 if not found.
			if(placeFound > -1)
				{
				if(placeFound == 0)
					StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "iVars_Values[" + i + "]");
				
				else if(placeFound > 0)
					{
					//before replacing, check to make sure user did not put the input variable in quotes.
					previousChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound-1), 1);
					subsequentChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound+stringLength), 1);		//6/24/10
					//if(previousChar != """")	//6/24/10
					if(previousChar != """"  &&  subsequentChar != """")
						//weird syntax, but that's actually what you write to check for the presence of a " (ie a single double quote character)
						//replace only if "stringToFind" is not surrounded by quotes
						{
						StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "iVars_Values[" + i + "]");
						}
					}
				
				startPoint = placeFound + stringLength;
				}
			}while(placeFound > -1);  //keep replacing occurrences of the current variable until none are left.
		}

	//End: Input Variables
	//********************

	//***********************
	//Start: Output Variables

	//replace every instance of the output variable name with oVars_Values[i]
	for(i=0; i<oVars_NumTableRows; i++)
		{
		stringToFind = oVars_Names[i];
		stringLength = strLen(stringToFind);
		startPoint = 0;
		
		do
			{
			placeFound = StrFindDynamicStartPoint(EQ_TranslatedEquationText, stringToFind, 0, 0, 1, startPoint);  //returns the place where the string was found or -1 if not found.
			if(placeFound > -1)
				{
				if(placeFound == 0)
					StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "oVars_Values[" + i + "]");
				
				else if(placeFound > 0)
					{
					//before replacing, check to make sure user did not put the output variable in quotes.
					previousChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound-1), 1);
					subsequentChar = StrPartDynamic(EQ_TranslatedEquationText, (placeFound+stringLength), 1);
					//if(previousChar != """")	//6/24/10
					if(previousChar != """"  &&  subsequentChar != """")
						//weird syntax, but that's actually what you write to check for the presence of a " (ie a single double quote character)
						//replace only if "stringToFind" is not surrounded by quotes
						{
						StrReplaceDynamic(EQ_TranslatedEquationText, placeFound, stringLength, "oVars_Values[" + i + "]");
						}
					}
				
				startPoint = placeFound + stringLength;
				}
			}while(placeFound > -1);  //keep replacing occurrences of the current variable until none are left.
		}

	//End: Output Variables
	//*********************

}//procedure EQ_TranslateEquation()


Procedure InitSeeds()
{

integer SeedVal;
integer SeedInitOption;

	SeedInitOption = GetRunParameterLong(6);			// get the seed initialization from the simulation setup

	if(SeedInitOption == SEED_USEDB)					// database table is used for seeds
		SeedVal = randomGetSeed();						// 		get the system seed (from the database)
	else if(RandomSeed == 0)							// random seed is blank or 0
		SeedVal = randomGetSeed();						//		get the randomized system seed
	else												// seed is the system seed
		SeedVal = RandomSeed;							// 		get the current system seed

	if(UseBlockSeed_chk)								// use block seed is selected
		MySeed = RandomSeed_prm;								//		seed will be the block seed
	else if(currentSim == 0)							// 
		MySeed = SeedVal + myBlockNumber() + 1; 		// use the block number as the seed
	else if (SeedInitOption == SEED_CONTINUESEQUENCE)
		MySeed = previousSeed;	
	else
		MySeed = SeedVal + myBlockNumber() + 1; 		// use the block number as the seed

	if(UseBlockSeed_chk && MySeed != RandomSeed_prm)
		MySeed = RandomSeed_prm;								// if sensitivity has changed RandomSeed_prm use new seed

	//7/21/11:  moved to it's own function called CheckSeeds
	/*
	if(GetRunParameterLong(7))							// check for duplicate random number seeds
		{
		BadSeedBlockNum = SeedListRegister(MyBlockNumber(),mySeed);
		if(BadSeedBlockNum >= 0)
			{
			UserError(BlockName(MyBlockNumber())+" block number "+myblocknumber()+" has the same seed value as "+BlockName(BadSeedBlockNum)+" block number "+BadSeedBlockNum+". Either change the block seeds or unselect Check for duplicate seeds in the simulation setup.");
			OpenBlockDialogBox(BadSeedBlockNum);
			DialogMoveTo(BadSeedBlockNum, 50, 50);
			OpenDialogBox();
			abortsilent();
			}
		}
	*/

}// Procedure InitSeeds()


//7/21/11:  this function needs to be called immediately AFTER EQ_InitDataStructures() is called
procedure EQ_CheckSeeds()
{	
	
	real BadSeedBlockNum;			// block number of the block that has the same seed as this one. Must be real, because it will be blank if no block is found with the same seed
	
	if(GetRunParameterLong(7))							// check for duplicate random number seeds
		{
		BadSeedBlockNum = SeedListRegister(MyBlockNumber(),mySeed);
		if(BadSeedBlockNum >= 0)
			{
			UserError(BlockName(MyBlockNumber())+" block number "+myblocknumber()+" has the same seed value as "+BlockName(BadSeedBlockNum)+" block number "+BadSeedBlockNum+". Either change the block seeds or unselect Check for duplicate seeds in the simulation setup.");
			OpenBlockDialogBox(BadSeedBlockNum);
			DialogMoveTo(BadSeedBlockNum, 50, 50);
			OpenDialogBox();
			abortsilent();
			}
		}


}// Procedure EQ_CheckSeeds()


//destroy destroyRemoteBlock = TRUE when user turns on checkbox for debugging as a garbage safety mechanism
integer EQ_Compile(integer destroyRemoteBlock)
{
	
	integer i;
	integer error;
	integer outputsSize;
	integer numIncludes;
	string includeName;
	integer successfullCompile;
	
	//copy user's result names from the output table to the associated individual array
	for(i=0; i<oVars_NumTableRows; i++)
		{
		oVars_Names[i] = oVars_ttbl[i][O_VAR_NAME_COL];
		}

	EQ_TranslateEquation();

	//add any include files
	if(Incl_chk)
		{
		numIncludes = GetDimension(Incl_FileNames_ttbl);
		for(i=0; i<numIncludes; i++)
			{
			includeName = incl_FileNames_DA[i][INCL_NAME_COL];
			if(includeName != "")
				EquationIncludeSet(includeName);
			}
		}

	EquationCompileSetStaticArray(staticIncludeVars);			//1/19/11
	
	error = EquationCompileDynamicVariables("iVars_Values", 			//array containing the input values
									   		"oVars_Values", 			//array containing the output values
									    	EQ_TranslatedEquationText,	//array containing the dialog's equation_dtxt
									    	EQ_CompiledEquation,		//the compiled equation_dtxt in machine code- what this function returns
									    	EQUATION_TAB_ORDER);		//identifier for the "equation_dtxt" dialog item
										  
	if(error)
		{
		successfullCompile = FALSE;
		AbortAllSims();			// don't close the dialog box
		}
	
	else //good compile
		{
		successfullCompile = TRUE;
		
		DynamicTextSetDirty(MyBlockNumber(), "equation_dtxt", FALSE);

		if(dbg_chk == TRUE)
			{
			//after successful compile above, have to add includes again
			if(Incl_chk)
				{
				numIncludes = GetDimension(Incl_FileNames_ttbl);
				for(i=0; i<numIncludes; i++)
					{
					includeName = incl_FileNames_DA[i][INCL_NAME_COL];
					if(includeName != "")
						EquationIncludeSet(includeName);
					}
				}

			//first destroy the hidden debugger block
			if(destroyRemoteBlock == TRUE)
				{
				EquationDebugDispose(dbg_HiddenBlock);		
				dbg_HiddenBlock = -1;
					//NOTE:  any time the hidden debug block is destroyed, must set dbg_HiddenBlock = -1 
					//so that when EquationDebugCompile() is called, a new hidden debug block is created.
				}
			
			//second, create a new hidden debugger block
			dbg_HiddenBlock = EquationDebugCompile(dbg_HiddenBlock, 
												   iVars_Names, 
												   oVars_Names, 
												   EQ_EquationText, 
												   EQUATION_TAB_ORDER);					//1 for tab order.  isn't used for anything right now
			}
		}

	DisposeArray(iVars_NamesNoSpaces);
	DisposeArray(EQ_TranslatedEquationText);
	
	return(successfullCompile);

}//procedure EQ_Compile(integer disposeRemoteBlock)


//called in PassItem and oVarsOut
#ifdef EQ_IsQueryEquationItemBlock
	procedure EQ_Calc(integer itemIndex, integer recordIndex, integer sendIVarConMsgs, integer postResults, integer sendOVarConMsgs, integer preserveStatics)
#else
	#ifdef EQ_IsItemBlock
		procedure EQ_Calc(integer itemIndex, integer sendIVarConMsgs, integer postResults, integer sendOVarConMsgs, integer preserveStatics)
	#else
		#ifdef EQ_IsQueryEquationValueBlock
			procedure EQ_Calc(integer recordIndex, integer sendIVarConMsgs, integer sendOVarConMsgs)
		#else
			procedure EQ_Calc(integer sendIVarConMsgs, integer sendOVarConMsgs)
		#endif
	#endif
#endif
{
	
	integer i;
	integer me;
	integer tempseed;
	integer staticItemValueCount;
	integer whichElement;
	integer whichField;
	real setValue;
	
	me = MyBlockNumber();
	
	if(EQ_Calcing == TRUE)
		return;
	
	EQ_Calcing = TRUE;

	//compile the equation if necessary
	if(DynamicTextIsDirty(MyBlockNumber(), "equation_dtxt")  ||  GetDimension(EQ_CompiledEquation) == 0)
		EQ_Compile(FALSE);

	//get input values.  NOTE:  iVars_BackupVals[] will get writen to in iVars_BackupVals()
	#ifdef EQ_IsItemBlock
//		iVars_GetVals(itemIndex, sendIVarConMsgs);
	#else
//		iVars_GetVals(sendIVarConMsgs);
	#endif

	//initialize output values
//	oVars_InitVals();							//ajn, 7.0.4, 9/12/08

	#ifdef sendProof_chk
		if(sendProof_chk)
			GlobalProofStr = "";
	#endif

	//save system level seed before calculating the equation (because result of that equation calculation could change the system level seed)
	tempSeed = RandomGetSeed();
	RandomSetSeed(mySeed);

	if(dbg_chk == TRUE)
		EquationDebugCalculate(dbg_HiddenBlock, iVars_Values, oVars_Values);
	else
		EquationCalculateDynamicVariables(iVars_Values, oVars_Values, EQ_CompiledEquation);
	
	#ifdef sendProof_chk											// if we are sending a command to Proof
		if(sendProof_chk)
			{
			PassStringToProof[0] = GlobalProofStr;
			GASetInteger(MyBlockNumber(),GAProof,MyBlockNumber(),0);	// set the paused flag in the global array
			GASetInteger(-1,GAProof,PRF_COMMAND_TYPE,0);					// this indicates that the 
			SendMsgToBlock(ProofBlock,BlockReceive4Msg);			// Send the proof command to the proof control block
			}
	#endif

	//if the same variable name is used to declare both an iVar and an oVar (like when your getting and
	//setting the same attribute), EquationCalculateDynamicVariables() will actually store the value of
	//the oVar in iVars_Values[].  therefore, we have to go grab the value from the iVars array, stuff
	//it in the oVars array, and then restore the original value of iVar.
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_GetValFromIVars[i] > -1)
			{
			oVars_Values[i] = iVars_Values[oVars_GetValFromIVars[i]];
			iVars_Values[oVars_GetValFromIVars[i]] = iVars_BackupVals[oVars_GetValFromIVars[i]];
			}
		}
		
	//3/31/09:  in some cases (like when EQ_Calc is called from on oVarsOut of the Equation (I) block) we need to preserve any static variables
	#ifdef EQ_IsItemBlock
		if(preserveStatics == TRUE)
			{
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(
					iVars_Types_Int[i] == EQ_STATIC_FRI  ||  
					iVars_Types_Int[i] == EQ_STATIC_MRI  ||  
					iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL  ||  
					iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT  ||  
					iVars_Types_Int[i] == EQ_QEQ_STATIC_CALC_CYCLE_INIT
					//iVars_Types_Int[i] == EQ_QEQ_STATIC_ITEM_VALUE			//11/17/10:  Note:  we don't need to do this here because the static values for "static item value" variables are stored in the queue's item linked list
				  )
					iVars_Values[i] = iVars_BackupVals[i];
				}
			}
	#endif
	
	//11/17/10:  store results for variables of type "static item values" in the linked list
	#ifdef EQ_IsQueueEquation
		
		if( GetDimension(iVars_StaticItemValuesRowIndexes) )	
			{
			staticItemValueCount = 0;

			whichElement = ListSearch(me, queueListIndex, 2, 0, itemIndex, 0, "", 0);
					//find where this item is represented in the linked list because 
					//we'll need it.  do this here so we only have to search once.
		
			for(i=0;i<iVars_NumTableRows;i++)
				{
				if(iVars_Types_Int[i] == EQ_QEQ_STATIC_ITEM_VALUE)
					{
					whichField = staticItemValueCount + 1;										//+1 because the first double field is reserved for arrival time
					setValue = iVars_Values[i];
					ListSetDouble(me, queueListIndex, whichElement, whichField, setValue);
					staticItemValueCount++;
					}
				}
			}
	
	#endif //EQ_IsQueueEquation
	
	//6/22/10:  only need to show updated static variable values if iVars_ttbl is showing
	if(iVars_TableIsCloned  ||  dialogIsOpen)
		{
		//update the values column of iVars_ttbl.  this is necessary for debugging static variables because they potentially change after each calculation
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(
				iVars_Types_Int[i] == EQ_STATIC_FRI  ||  
				iVars_Types_Int[i] == EQ_STATIC_MRI  ||  
				iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL  ||  
				iVars_Types_Int[i] == EQ_QEQ_STATIC_CALC_CYCLE_INIT  ||  
				iVars_Types_Int[i] == EQ_QEQ_STATIC_ITEM_VALUE  ||  			//11/17/10
				iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT
			  )
				iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_StaticInitValues[i] + " : " + iVars_Values[i];
			}
		}
	
	//set result values in various places like as attrib on an item or in a database cell
	#ifdef EQ_IsItemBlock
		if(postResults)
			oVars_PostResults(itemIndex, sendOVarConMsgs);
	#else
		#ifdef EQ_IsQueryEquationValueBlock
			//do nothing.  will post from DBQ_DoQuery
		#else
//			oVars_PostResults(sendOVarConMsgs);
		#endif
	#endif
	
 	//restore the system level seed.
 	mySeed = RandomGetSeed();
 	RandomSetSeed(tempSeed);

	EQ_Calcing = FALSE;

}//procedure EQ_Calc()


//called in oVarsOut and EQ_TestEquation_btn
procedure EQ_CalcNoItem(integer whoCalled)
{
	
	integer i, j;


	if(EQ_Calcing2 == TRUE)
		return;
	
	EQ_Calcing2 = TRUE;

	if(whoCalled == O_VARS_OUT)
		{
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(oVars_NoItemOptions[i] == O_VAR_USE_NO_VALUE)
				{
				oVars_Values[i] = blank;
				}
			else if(oVars_NoItemOptions[i] == O_VAR_USE_CONSTANT)
				{
				oVars_Values[i] = oVars_NoItemConstants[i];
				}
			else if(oVars_NoItemOptions[i] == O_VAR_USE_LAST_VALUE)
				{
				//do nothing
				}
			}

		//update output connectors
		#ifdef oVarsOut
			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(oVars_VarIsWhichCon[i] != -1)
					ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);
				}
		#endif
		}

		
	EQ_Calcing2 = FALSE;

}//procedure EQ_CalcNoItem(integer whoCalled)
	


//**********************************************************************
//End "Eqn_" Functions
//**********************************************************************
//**********************************************************************




//**********************************************************************
//**********************************************************************
//Start "iVars" Functions
//**********************************************************************


on iVars_ShowConNames_chk
{

//	iVarsIn_ConLabelsSet();

}//on showResultValues_chk



on iVars_ShowConVals_chk
{

//	iVarsIn_ConLabelsSet();

}//on showResultNames_chk

/*
on iVars_ttbl
{
	
	real oldInitVal;
	real newInitVal;
	integer whichCol;
	integer whichRow;

	if(WhoInvoked() == 1)	//9/22/10:  1 == called by SetDialogVariable()
		{
		whichCol = WhichDTCellClicked(1);
		if(whichCol == I_VAR_VALUE_COL)
			{
			whichRow = WhichDTCellClicked(0);
			iVars_StaticInitValues[whichRow] = StrToReal(iVars_ttbl[whichRow][I_VAR_VALUE_COL]);
			}
		}
	
	else //if not invokded by SetDialogVariable
		{
	
		if(colClicked == I_VAR_TYPE_COL  &&  rowClicked >= 0  &&  rowClicked < iVars_NumTableRows)
			{
			StopDataTableEditing();
			SetDataTableSelection("iVars_ttbl", -2, -2, -2, -2, FALSE);
			}
			
		if(colClicked == I_VAR_NAME_COL  &&  rowClicked >= 0  &&  rowClicked < iVars_NumTableRows  &&  iVars_Types_str[rowClicked] == "Attribute")
			{
			StopDataTableEditing();
			SetDataTableSelection("iVars_ttbl", -2, -2, -2, -2, FALSE);
			}
			
		if(colClicked == I_VAR_VALUE_COL  &&  rowClicked >= 0  &&  rowClicked < iVars_NumTableRows)
			{
			if(
				iVars_Types_str[rowClicked] == "Static first run init"  ||  
				iVars_Types_str[rowClicked] == "Static multi run init"  ||  
				iVars_Types_str[rowClicked] == "Static open model init"  ||  
				iVars_Types_str[rowClicked] == "QEQ static calc cycle init"  ||  
				iVars_Types_str[rowClicked] == "QEQ static item value"  ||  			//11/17/10
				iVars_Types_str[rowClicked] == "DBQ static query init"
			  )
				{
				StopDataTableEditing();
				oldInitVal = iVars_StaticInitValues[rowClicked];
				newInitVal = NumericParameter("Please enter the initial value for this static variable.", oldInitVal);
				if(NoValue(newInitVal))
					{
					iVars_Values[rowClicked] = oldInitVal;
					iVars_StaticInitValues[rowClicked] = oldInitVal;
					}
				else
					{
					iVars_Values[rowClicked] = newInitVal;
					iVars_StaticInitValues[rowClicked] = newInitVal;
					}
				SetDataTableSelection("iVars_ttbl", -2, -2, -2, -2, FALSE);
				}
			
			if(iVars_Types_str[rowClicked] == "DBQ num records"  ||  iVars_Types_str[rowClicked] == "DBQ current record index")
				{
				StopDataTableEditing();
				SetDataTableSelection("iVars_ttbl", -2, -2, -2, -2, FALSE);
				}
			
			if(iVars_Types_str[rowClicked] == "DBQ read value"  ||  
			   iVars_Types_str[rowClicked] == "DBQ read PRI"  ||  
			   iVars_Types_str[rowClicked] == "DBQ start record")
				{
				StopDataTableEditing();
				SetDataTableSelection("iVars_ttbl", -2, -2, -2, -2, FALSE);
				}
			}
			
		if(colClicked == I_VAR_PARENT_FIELD_COL  &&  rowClicked >= 0  &&  rowClicked < iVars_NumTableRows)
			{
			StopDataTableEditing();
			SetDataTableSelection("iVars_ttbl", -2, -2, -2, -2, FALSE);
			}
			
		iVarsIn_ConnectorsSetup();
		iVars_TableSetup();
		iVarsIn_ConLabelsSet();
		iVars_DBNT_GarbageCollection();
		EQ_BlockRegisterContent();
		EQ_BlockRegisterStructure();
		
		#ifdef CW_IVarsIn_CalcControl_chk
			//CW_IVarsIn_Animate();				//7/5/11
			CW_ConnectorAnimate();
		#endif
		
		#ifdef CMC_chk
			//CMC_IVarsIn_Animate();			//7/6/11
			CMC_ConnectorAnimate();
		#endif
		}
		
	SetConVisibility(MyBlockNumber(), GetConNumber(MyBlockNumber(), "iVarsIn"), FALSE);
	SetConVisibility(MyBlockNumber(), GetConNumber(MyBlockNumber(), "oVarsOut"), FALSE);
	SetConVisibility(MyBlockNumber(), GetConNumber(MyBlockNumber(), "goIn"), FALSE);
	
}//on iVars_ttbl
*/
/*
procedure iVars_CopyRow()
{
	integer i, j;
	real numRowsToInsert;			//note: must be a real so we can tell if user clicked "cancel"
	integer oldNumRows;
	integer newNumRows;
	integer whatGotSelected[4];
	integer startInsertRow;
	integer endInsertRow;
	integer leftCol;
	integer sourceRow;
	integer targetRow;
	integer me;
	integer sourceElement;
	integer iVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();

	GetDataTableSelection("iVars_ttbl", whatGotSelected);
	startInsertRow = whatGotSelected[0];
	rowClicked = startInsertRow;
	leftCol = whatGotSelected[2];
	
	if(leftCol == 0  &&  startInsertRow >= 0  && startInsertRow < iVars_NumTableRows)
		{
		numRowsToInsert = NumericParameter("Please enter the number of times you would like to copy the selected row.", 1);
		
		if(!NoValue(numRowsToInsert))	//if user did not click cancel
			{
			if(numRowsToInsert >= 1)
				{
				oldNumRows = iVars_NumTableRows;
				newNumRows = oldNumRows + numRowsToInsert;
				endInsertRow = startInsertRow + numRowsToInsert;
				iVars_NumTableRows = newNumRows;

				//first, grow the arrays...
				iVars_ResizeDynamicArrays(RESIZE_COPY);
				
				//...then move exiisting rows down...
				for(i=iVars_NumTableRows-1; i>endInsertRow; i--)
					{
					sourceRow = i-numRowsToInsert;
					targetRow = i;
					
					iVars_Types_str[targetRow] = iVars_Types_str[sourceRow];
					iVars_Types_int[targetRow] = iVars_Types_int[sourceRow];
					iVars_Names[targetRow] = iVars_Names[sourceRow];
					
					iVars_StaticInitValues[targetRow] = iVars_StaticInitValues[sourceRow];
					iVars_Values[targetRow] = iVars_Values[sourceRow];
					iVars_AttribTypes[targetRow] = iVars_AttribTypes[sourceRow];
					iVars_IndexesForDBIndexVars[targetRow] = iVars_IndexesForDBIndexVars[sourceRow];
				
					//8/16/10:  change DBNT_WHICH_ROW_IN_TABLE_FIELD so that the DBNT element is pointing to the correct row in the iVars table
					iVars_DBCoords[targetRow] = iVars_DBCoords[sourceRow];
					if(
					   iVars_Types_Int[sourceRow] == EQ_DB_READ_VAL  ||  
					   iVars_Types_Int[sourceRow] == EQ_DB_READ_PRI  ||  
					   iVars_Types_Int[sourceRow] == EQ_DB_ADDRESS  ||  
					   iVars_Types_Int[sourceRow] == EQ_DB_DATABASE_INDEX  ||
					   iVars_Types_Int[sourceRow] == EQ_DB_TABLE_INDEX  ||
					   iVars_Types_Int[sourceRow] == EQ_DB_FIELD_INDEX  ||
					   iVars_Types_Int[sourceRow] == EQ_DB_RECORD_INDEX
					  )
						{
						iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
						if(iVars_DBNameTrackingListIndex >= 0)
							{
							//get source element...
							sourceElement = ListSearch(me, iVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, sourceRow, 0, "", 0);	//2- search for integer
							if(sourceElement >= 0)
								{
								//change the value in the "which row in table" field to the target row
								ListSetLong(me, iVars_DBNameTrackingListIndex, sourceElement, DBNT_WHICH_ROW_IN_TABLE_FIELD, targetRow);
								}
							else
								{
								UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
								}
							}
						else
							{
							UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							}
						}

					#ifdef CMC_chk
					if(CMC_chk)
						CMC_IVarsIn_Settings[targetRow] = CMC_IVarsIn_Settings[sourceRow];
					#endif
					
					#ifdef EQ_IsQueryEquationTypeBlock
						DBQF_OptionsChosen[targetRow] = DBQF_OptionsChosen[sourceRow];
						DBQF_FieldIndex[targetRow] = DBQF_FieldIndex[sourceRow];
						DBQF_FieldName[targetRow] = DBQF_FieldName[sourceRow];
						DBQF_WhichConnector[targetRow] = DBQF_WhichConnector[sourceRow];
						
						DBQFP_OptionsChosen[targetRow] = DBQFP_OptionsChosen[sourceRow];
						DBQFP_TableIndex[targetRow] = DBQFP_TableIndex[sourceRow];
						DBQFP_TableName[targetRow] = DBQFP_TableName[sourceRow];
						DBQFP_FieldIndex[targetRow] = DBQFP_FieldIndex[sourceRow];
						DBQFP_FieldName[targetRow] = DBQFP_FieldName[sourceRow];
						DBQFP_WhichConnector[targetRow] = DBQFP_WhichConnector[sourceRow];
						
						DBQSR_OptionsChosen[targetRow] = DBQSR_OptionsChosen[sourceRow];
						DBQSR_WhichConnector[targetRow] = DBQSR_WhichConnector[sourceRow];
						DBQSR_StartRecord[targetRow] = DBQSR_StartRecord[sourceRow];
						
						#ifdef EQ_IsQueryEquationItemBlock
							DBQF_AttribNamesChosen[targetRow] = DBQF_AttribNamesChosen[sourceRow];
							DBQF_AttribType[targetRow] = DBQF_AttribType[sourceRow];
							
							DBQFP_AttribNamesChosen[targetRow] = DBQFP_AttribNamesChosen[sourceRow];
							DBQFP_AttribType[targetRow] = DBQFP_AttribType[sourceRow];
							
							DBQSR_AttribNamesChosen[targetRow] = DBQSR_AttribNamesChosen[sourceRow];
							DBQSR_AttribType[targetRow] = DBQSR_AttribType[sourceRow];
						#endif
					#endif
					}
				
				//...then, add the inserted rows...
				for(i=0; i<numRowsToInsert; i++)
					{
					sourceRow = startInsertRow;
					targetRow = startInsertRow + 1 + i;
					
					iVars_Types_str[targetRow] = iVars_Types_str[sourceRow];
					iVars_Types_int[targetRow] = iVars_Types_int[sourceRow];
					
					if(iVars_Types_int[sourceRow] == EQ_ITEM_ATTRIBUTE)
						iVars_Names[targetRow] = "None";
					else
						iVars_Names[targetRow] = iVars_Names[sourceRow] + sourceRow + i;
					
					iVars_StaticInitValues[targetRow] = iVars_StaticInitValues[sourceRow];
					iVars_Values[targetRow] = iVars_Values[sourceRow];
					iVars_AttribTypes[targetRow] = iVars_AttribTypes[sourceRow];
					iVars_IndexesForDBIndexVars[targetRow] = iVars_IndexesForDBIndexVars[sourceRow];

					//8/16/10:  update the DBNT list with its newest member
					iVars_DBCoords[targetRow] = iVars_DBCoords[sourceRow];
					iVars_DBNT_AddElement(iVars_DBCoords[targetRow], targetRow);
				
					#ifdef CMC_chk
					if(CMC_chk)
						CMC_IVarsIn_Settings[targetRow] = CMC_IVarsIn_Settings[sourceRow];
					#endif
					
					#ifdef EQ_IsQueryEquationTypeBlock
						DBQF_OptionsChosen[targetRow] = DBQF_OptionsChosen[sourceRow];
						DBQF_FieldIndex[targetRow] = DBQF_FieldIndex[sourceRow];
						DBQF_FieldName[targetRow] = DBQF_FieldName[sourceRow];
						DBQF_WhichConnector[targetRow] = DBQF_WhichConnector[sourceRow];
						
						DBQFP_OptionsChosen[targetRow] = DBQFP_OptionsChosen[sourceRow];
						DBQFP_TableIndex[targetRow] = DBQFP_TableIndex[sourceRow];
						DBQFP_TableName[targetRow] = DBQFP_TableName[sourceRow];
						DBQFP_FieldIndex[targetRow] = DBQFP_FieldIndex[sourceRow];
						DBQFP_FieldName[targetRow] = DBQFP_FieldName[sourceRow];
						DBQFP_WhichConnector[targetRow] = DBQFP_WhichConnector[sourceRow];
						
						DBQSR_OptionsChosen[targetRow] = DBQSR_OptionsChosen[sourceRow];
						DBQSR_WhichConnector[targetRow] = DBQSR_WhichConnector[sourceRow];
						DBQSR_StartRecord[targetRow] = DBQSR_StartRecord[sourceRow];
						
						#ifdef EQ_IsQueryEquationItemBlock
							DBQF_AttribNamesChosen[targetRow] = DBQF_AttribNamesChosen[sourceRow];
							DBQF_AttribType[targetRow] = DBQF_AttribType[sourceRow];
							
							DBQFP_AttribNamesChosen[targetRow] = DBQFP_AttribNamesChosen[sourceRow];
							DBQFP_AttribType[targetRow] = DBQFP_AttribType[sourceRow];
							
							DBQSR_AttribNamesChosen[targetRow] = DBQSR_AttribNamesChosen[sourceRow];
							DBQSR_AttribType[targetRow] = DBQSR_AttribType[sourceRow];
						#endif
					#endif
					}
					
				//...then, redo connector accounting, ie, make sure connectors are listed in ascending order
				j = 0;
				for(i=0; i<iVars_NumTableRows; i++)
					{
					if(StrFind(iVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
						{
						iVars_Types_str[i] = "Connector " + j;
						j++;
						}

					#ifdef EQ_IsQueryEquationTypeBlock
						
						else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
							{
							if(DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//it's a connector variable
								{
								DBQF_WhichConnector[i] = j;
								j++;							//advance the connecor index
								}
							else
								{
								DBQF_WhichConnector[i] = -1;
								}
							
							if(DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//it's a connector variable
								{
								DBQFP_WhichConnector[i] = j;
								j++;							//advance the connecor index
								}
							else
								{
								DBQFP_WhichConnector[i] = -1;
								}
							}
							
						else if(iVars_Types_str[i] == "DBQ start record")
							{
							if(DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
								{
								DBQSR_WhichConnector[i] = j;
								j++;
								}
							else
								{
								j++;
								}
							}
							
					#endif //EQ_IsQueryEquationTypeBlock
		
					}
				
				iVarsIn_Reconnect(DATA_TABLE_RESIZE);
				
				}//if(numRowsToInsert >= 1)
			
			}//if(!NoValue(numRowsToInsert))

		}
	
	else
		{
		UserError("Copying requires you to first select one whole row in the table by clicking on the left-most column (the one that displays the row numbers).");
		}

}//procedure iVars_CopyRow()
*/
/*
procedure iVars_DeleteRows()
{

	integer i, j;
	real numRowsToCopy;			//note: must be a real so we can tell if user clicked "cancel"
	integer numDeletableRows;
	integer oldNumRows;
	integer oldLastRow;
	integer newNumRows;
	integer whatGotSelected[4];
	integer startDeleteRow;
	integer endDeleteRow;
	integer lastDeleteRow;
	integer numRowsToDelete;
	integer leftCol;
	integer sourceRow;
	integer targetRow;
	integer me;
	integer sourceElement;
	integer iVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();
	
	GetDataTableSelection("iVars_ttbl", whatGotSelected);
	startDeleteRow = whatGotSelected[0];
	rowClicked = startDeleteRow;
	endDeleteRow = whatGotSelected[1];
	numDeletableRows = iVars_NumTableRows - startDeleteRow;
	leftCol = whatGotSelected[2];
	StopDataTableEditing();				//for some reason this is needed in order for this procedure to work properly.
	
	if(leftCol == 0  &&  startDeleteRow >= 0  && startDeleteRow < iVars_NumTableRows  &&  endDeleteRow >= 0  &&  endDeleteRow < iVars_NumTableRows)
		{
		numRowsToDelete = endDeleteRow - startDeleteRow + 1;
		
		oldNumRows = iVars_NumTableRows;
		oldLastRow = oldNumRows - 1;
		newNumRows = oldNumRows - numRowsToDelete;
		iVars_NumTableRows = newNumRows;
		lastDeleteRow = startDeleteRow + numRowsToDelete - 1;

		//6/15/11:  delete the DBNT elements pointing to the rows that are getting deleted
		for(i=startDeleteRow; i<=endDeleteRow; i++)
			{
			if(
			   iVars_Types_Int[i] == EQ_DB_READ_VAL  ||  
			   iVars_Types_Int[i] == EQ_DB_READ_PRI  ||  
			   iVars_Types_Int[i] == EQ_DB_ADDRESS  ||  
			   iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX  ||
			   iVars_Types_Int[i] == EQ_DB_TABLE_INDEX  ||
			   iVars_Types_Int[i] == EQ_DB_FIELD_INDEX  ||
			   iVars_Types_Int[i] == EQ_DB_RECORD_INDEX
			  )
			  	{
			  	iVars_DBNT_DeleteElement(i);
			  	}
			  }
		
		//first copy the rows that are moving up,...
		if(lastDeleteRow < oldLastRow)
			{
			numRowsToCopy = oldLastRow - lastDeleteRow;
			for(i=0; i<numRowsToCopy; i++)
				{
				targetRow = startDeleteRow + i;
				sourceRow = lastDeleteRow + 1 + i;
				
				iVars_Types_str[targetRow] = iVars_Types_str[sourceRow];
				iVars_Types_int[targetRow] = iVars_Types_int[sourceRow];
				iVars_Names[targetRow] = iVars_Names[sourceRow];
				
				iVars_StaticInitValues[targetRow] = iVars_StaticInitValues[sourceRow];
				iVars_Values[targetRow] = iVars_Values[sourceRow];
				iVars_AttribTypes[targetRow] = iVars_AttribTypes[sourceRow];
				iVars_IndexesForDBIndexVars[targetRow] = iVars_IndexesForDBIndexVars[sourceRow];

				//8/16/10:  change DBNT_WHICH_ROW_IN_TABLE_FIELD so that the DBNT element is pointing to the correct row in the iVars table
				iVars_DBCoords[targetRow] = iVars_DBCoords[sourceRow];
				if(
				   iVars_Types_Int[sourceRow] == EQ_DB_READ_VAL  ||  
				   iVars_Types_Int[sourceRow] == EQ_DB_READ_PRI  ||  
				   iVars_Types_Int[sourceRow] == EQ_DB_ADDRESS  ||  
				   iVars_Types_Int[sourceRow] == EQ_DB_DATABASE_INDEX  ||
				   iVars_Types_Int[sourceRow] == EQ_DB_TABLE_INDEX  ||
				   iVars_Types_Int[sourceRow] == EQ_DB_FIELD_INDEX  ||
				   iVars_Types_Int[sourceRow] == EQ_DB_RECORD_INDEX
				  )
					{
					iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
					if(iVars_DBNameTrackingListIndex >= 0)
						{
						//get source element...
						sourceElement = ListSearch(me, iVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, sourceRow, 0, "", 0);	//2- search for integer
						if(sourceElement >= 0)
							{
							//change the value in the "which row in table" field to the target row
							ListSetLong(me, iVars_DBNameTrackingListIndex, sourceElement, DBNT_WHICH_ROW_IN_TABLE_FIELD, targetRow);
							}
						else
							{
							UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							}
						}
					else
						{
						UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
						}
					}

				#ifdef CMC_chk
				if(CMC_chk)
					CMC_IVarsIn_Settings[targetRow] = CMC_IVarsIn_Settings[sourceRow];
				#endif
				
				#ifdef EQ_IsQueryEquationTypeBlock
					DBQF_OptionsChosen[targetRow] = DBQF_OptionsChosen[sourceRow];
					DBQF_FieldIndex[targetRow] = DBQF_FieldIndex[sourceRow];
					DBQF_FieldName[targetRow] = DBQF_FieldName[sourceRow];
					DBQF_WhichConnector[targetRow] = DBQF_WhichConnector[sourceRow];
					
					DBQFP_OptionsChosen[targetRow] = DBQFP_OptionsChosen[sourceRow];
					DBQFP_TableIndex[targetRow] = DBQFP_TableIndex[sourceRow];
					DBQFP_TableName[targetRow] = DBQFP_TableName[sourceRow];
					DBQFP_FieldIndex[targetRow] = DBQFP_FieldIndex[sourceRow];
					DBQFP_FieldName[targetRow] = DBQFP_FieldName[sourceRow];
					DBQFP_WhichConnector[targetRow] = DBQFP_WhichConnector[sourceRow];
					
					DBQSR_OptionsChosen[targetRow] = DBQSR_OptionsChosen[sourceRow];
					DBQSR_WhichConnector[targetRow] = DBQSR_WhichConnector[sourceRow];
					DBQSR_StartRecord[targetRow] = DBQSR_StartRecord[sourceRow];
					
					#ifdef EQ_IsQueryEquationItemBlock
						DBQF_AttribNamesChosen[targetRow] = DBQF_AttribNamesChosen[sourceRow];
						DBQF_AttribType[targetRow] = DBQF_AttribType[sourceRow];
						
						DBQFP_AttribNamesChosen[targetRow] = DBQFP_AttribNamesChosen[sourceRow];
						DBQFP_AttribType[targetRow] = DBQFP_AttribType[sourceRow];
						
						DBQSR_AttribNamesChosen[targetRow] = DBQSR_AttribNamesChosen[sourceRow];
						DBQSR_AttribType[targetRow] = DBQSR_AttribType[sourceRow];
					#endif
				#endif
				}
			
			}//if(lastDeleteRow < iVars_NumTableRows)
		
		//...then, redo connector accounting, ie, make sure connectors are listed in ascending order
		j = 0;
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(StrFind(iVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
				{
				iVars_Types_str[i] = "Connector " + j;
				j++;
				}

			#ifdef EQ_IsQueryEquationTypeBlock
				
				else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
					{
					if(DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//it's a connector variable
						{
						DBQF_WhichConnector[i] = j;
						j++;							//advance the connecor index
						}
					else
						{
						DBQF_WhichConnector[i] = -1;
						}
					
					if(DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//it's a connector variable
						{
						DBQFP_WhichConnector[i] = j;
						j++;							//advance the connecor index
						}
					else
						{
						DBQFP_WhichConnector[i] = -1;
						}
					}
					
				else if(iVars_Types_str[i] == "DBQ start record")
					{
					if(DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
						{
						DBQSR_WhichConnector[i] = j;
						j++;
						}
					else
						{
						j++;
						}
					}
					
			#endif //EQ_IsQueryEquationTypeBlock

			}
		
		//...then reconnect...
		iVarsIn_Reconnect(DATA_TABLE_RESIZE);
		
		//...then delete rows off from bottom of table...
		iVars_ResizeDynamicArrays(RESIZE_DELETE_SELECTION);

		iVars_DBNT_GarbageCollection();	//8/16/10: some rows that got deleted may have had elements in the DBNT list
		
		iVars_NumTableRows = GetDimension(iVars_ttbl);	//6/15/11
		}
	
	else
		{
		UserError("Deleting rows requires you to first select at least one row in the table by clicking on the left-most column (the one that displays the row numbers).");
		}

}//procedure iVars_DeleteRows()
*/
/*
//called in iVars_GetVals(), EQ_OnDialogClick(), EQ_CalcNoItem()
integer iVars_CheckChosenField(integer whichVar, real theCoords)
{

	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	integer fieldType;
	integer parentField;
	integer parentInfo[3];
	integer legitField;
	integer me;
	
	me = MyBlockNumber();
	databaseIndex = DBDatabaseGetIndexFromAddress(theCoords);
	tableIndex = DBTableGetIndexFromAddress(theCoords);
	fieldIndex = DBFieldGetIndexFromAddress(theCoords);
		
	if( !DBRecordExists(databaseIndex, tableIndex, fieldIndex, 1) )		//8/17/10
		{
		UserError("There is a problem in " + BlockName(me) + " " + me + ". The field specified for input variable " + (whichVar+1) + 
				  "does not exist.");
		AbortAllSims();
		}

	legitField = TRUE;

	//if the variable is of type "DB read value" or "DB read value using attrib", the chosen field cannot be a string field
	//if(iVars_Types_str[whichVar] == "DB read value"  ||  iVars_Types_str[whichVar] == "DB read value using attrib")	//AJN, 7.0.5, 10/24/08
	if(iVars_Types_Int[whichVar] == EQ_DB_READ_VAL  ||  iVars_Types_Int[whichVar] == EQ_DB_READ_VAL_USING_ATTRIB)
		{

		fieldType = DBFieldGetPropertiesUsingAddress(theCoords, 1) ;	//where 1 = fieldType
		
		if( fieldType == DB_FIELDTYPE_STRING_VALUE)
			{
			UserError("There is a problem in equation block " + MyBlockNumber() + ". The input """ + iVars_ttbl[whichVar][I_VAR_NAME_COL] + 
					  """ is pointing to a string field which is not allowed with ""DB read value"" or ""DB read value using attrib"" type variables. " +
					  "Consider ""DB read PRI"" or ""DB read PRI using attrib"" variables instead.");
			legitField = FALSE;
			}
			
		}
		
	//if the variable is of type "DB read PRI" or "DB read PRI using attrib", the chosen field must be a child
	//else if(iVars_Types_str[whichVar] == "DB read PRI"  ||  iVars_Types_str[whichVar] == "DB read PRI using attrib")	//AJN, 7.0.5, 10/24/08
	else if(iVars_Types_Int[whichVar] == EQ_DB_READ_PRI  ||  iVars_Types_Int[whichVar] == EQ_DB_READ_PRI_USING_ATTRIB)
		{
		DBDataGetParent(databaseIndex, tableIndex, fieldIndex, 1, parentInfo);	//use a "1" for row index b/ just interested in finding out if the field is a child
		parentField = parentInfo[PARENT_FIELD];
		
		if(parentField == 0)		//if the chosen field is not a child
			{
			UserError("There is a problem in equation block " + MyBlockNumber() + ". Because the input """ + iVars_ttbl[whichVar][I_VAR_NAME_COL] + 
					  """ is of type ""DB read PRI"" or ""DB read PRI using attrib"", the chosen field must be a child. change the field or consider " +
					  """DB read value"" or ""DB read value using attrib"" variables  instead.");
			legitField = FALSE;
			}
		}
		
	return(legitField);

}//procedure iVars_CheckDBValChosenField(integer whichVar)
*/
/*
integer iVars_GetNumConVars()
{
	
	integer i;
	integer numConVars;

	//first find out what the next connector index (j) should be...
	numConVars = 0;
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(StrFind(iVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
			numConVars++;
		
		#ifdef EQ_IsQueryEquationTypeBlock
			else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI"  ||  iVars_Types_str[i] == "DBQ start record")
				{
				if(
					DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR  ||
					DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR  ||
					DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR
				  )
					{
					numConVars++;
					}
				}
		#endif //EQ_IsQueryEquationTypeBlock
		}
		
	return(numConVars);
		
}//integer iVars_GetNumConVars()
*/			
/*
//called in InitSim, iVars_NumTableRows, iVars_TableSetup
procedure iVars_ResizeDynamicArrays(integer doWhat)
{
	
	integer i;
	integer numConVars;
	integer lastRowSize;
	
	MakeArray(iVars_AttribColumnIndexes, iVars_NumTableRows);
	MakeArray(iVars_Names, iVars_NumTableRows);
	MakeArray(iVars_Types_str, iVars_NumTableRows);
	MakeArray(iVars_Types_Int, iVars_NumTableRows);
	MakeArray(iVars_Values, iVars_NumTableRows);
	MakeArray(iVars_ValuesStr, iVars_NumTableRows);
	MakeArray(iVars_Units, iVars_NumTableRows);
	MakeArray(iVars_BackupVals, iVars_NumTableRows);
	MakeArray(iVars_ValueWasFound, iVars_NumTableRows);
	MakeArray(iVars_AttribTypes, iVars_NumTableRows);
	MakeArray(iVars_VarIsWhichCon, iVars_NumTableRows);
	MakeArray(iVars_VarIsWhichConOld, iVars_NumTableRows);
	MakeArray(iVars_StaticInitValues, iVars_NumTableRows);
	MakeArray(iVars_DBCoords, iVars_NumTableRows);
	MakeArray(iVars_IndexesForDBIndexVars, iVars_NumTableRows);
	
	#ifdef EQ_IsQueryEquationTypeBlock
		MakeArray(DBQF_OptionsChosen, iVars_NumTableRows);
		MakeArray(DBQF_FieldName, iVars_NumTableRows);
		MakeArray(DBQF_FieldIndex, iVars_NumTableRows);
		MakeArray(DBQF_WhichConnector, iVars_NumTableRows);
		
		MakeArray(DBQFP_OptionsChosen, iVars_NumTableRows);
		MakeArray(DBQFP_TableName, iVars_NumTableRows);
		MakeArray(DBQFP_TableIndex, iVars_NumTableRows);
		MakeArray(DBQFP_FieldName, iVars_NumTableRows);
		MakeArray(DBQFP_FieldIndex, iVars_NumTableRows);
		MakeArray(DBQFP_WhichConnector, iVars_NumTableRows);
	
		MakeArray(DBQSR_StartRecord, iVars_NumTableRows);
		MakeArray(DBQSR_OptionsChosen, iVars_NumTableRows);
		MakeArray(DBQSR_WhichConnector, iVars_NumTableRows);
	#endif
	
	#ifdef EQ_IsQueryEquationItemBlock
		MakeArray(DBQF_AttribNamesChosen, iVars_NumTableRows);
		MakeArray(DBQF_AttribColumnIDs, iVars_NumTableRows);
		MakeArray(DBQF_AttribType, iVars_NumTableRows);
		
		MakeArray(DBQFP_AttribNamesChosen, iVars_NumTableRows);
		MakeArray(DBQFP_AttribColumnIDs, iVars_NumTableRows);
		MakeArray(DBQFP_AttribType, iVars_NumTableRows);
		
		MakeArray(DBQSR_AttribNamesChosen, iVars_NumTableRows);
		MakeArray(DBQSR_AttribColumnIDs, iVars_NumTableRows);
		MakeArray(DBQSR_AttribType, iVars_NumTableRows);
	#endif
	
	//redim iVars_ttbl
	lastRowSize = GetDimension(iVars_DA);
	DILinkMsgs(FALSE);
	MakeArray(iVars_DA, iVars_NumTableRows);
	DynamicDataTable(MyBlockNumber(), "iVars_ttbl", iVars_DA);
	DILinkMsgs(TRUE);

	//if more rows were added to the table
	if(lastRowSize < iVars_NumTableRows)
		{
		numConVars = iVars_GetNumConVars();
			
		for(i=lastRowSize; i<iVars_NumTableRows; i++)
			{
			if(i == 0  ||  doWhat != RESIZE_ADD_SUBTRACT_FROM_END)	//if row 0 or if inserting rows into middle of table,...
				{
				//..., then use default settings for the rows we're adding to the bottom.  NOTE: even if 
				//user requested an "insert row into middle" operation, we are going to add rows to the bottom
				//first.  Then we'll move everything down later in the "copy rows" function

				//use "numConVars" in the connector variable name
				iVars_Types_str[i] = "Connector " + numConVars;
				iVars_Names[i] = "inCon" + numConVars;
				numConVars++;
				
				iVars_StaticInitValues[i] = blank;
				iVars_DBCoords[i] = DBAddressCreate(-1, -1, -1, -1);
				iVars_Types_Int[i] = EQ_CONNECTORS;
				iVars_Values[i] = blank;
				iVars_AttribTypes[i] = ATTRIB_TYPE_NO_ATTRIB; 
				iVars_IndexesForDBIndexVars[i] = 0;
			
				#ifdef EQ_IsQueryEquationTypeBlock
					DBQF_OptionsChosen[i] = DBQ_NOT_DEFINED;
					DBQF_FieldIndex[i] = -1;
					DBQF_FieldName[i] = "";
					DBQF_WhichConnector[i] = -1;
					
					DBQFP_OptionsChosen[i] = DBQ_NOT_DEFINED;
					DBQFP_TableIndex[i] = -1;
					DBQFP_TableName[i] = "";
					DBQFP_FieldIndex[i] = -1;
					DBQFP_FieldName[i] = "";
					DBQFP_WhichConnector[i] = -1;
					
					DBQSR_OptionsChosen[i] = DBQ_NOT_DEFINED;
					DBQSR_WhichConnector[i] = -1;
					DBQSR_StartRecord[i] = -1;
					
					#ifdef EQ_IsQueryEquationItemBlock
						DBQF_AttribNamesChosen[i] = "";
						DBQF_AttribType[i] = ATTRIB_TYPE_NO_ATTRIB; 
						
						DBQFP_AttribNamesChosen[i] = "";
						DBQFP_AttribType[i] = ATTRIB_TYPE_NO_ATTRIB; 
						
						DBQSR_AttribNamesChosen[i] = "";
						DBQSR_AttribType[i] = ATTRIB_TYPE_NO_ATTRIB; 
					#endif //EQ_IsQueryEquationItemBlock
				#endif //EQ_IsQueryEquationTypeBlock
				}
		
			else //if adding rows to the end, use the previous row's settings to define the new row's settings.
				{
				iVars_Types_Int[i] = iVars_Types_Int[i-1];		//NOTE: set oVars_Types_Int[] first!!

				if(StrFind(iVars_Types_str[i-1], "Connector", FALSE, FALSE) >= 0)
					{
					iVars_Types_str[i] = "Connector " + numConVars;
					iVars_Names[i] = "inCon" + numConVars;
					numConVars++;
					}
				else
					{
					iVars_Types_str[i] = iVars_Types_str[i-1];
					
					//create new name for the new variable
					if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE)
						iVars_Names[i] = "None";
					else
						iVars_Names[i] = iVars_Names[i-1] + i;
					}

				iVars_DBCoords[i] = iVars_DBCoords[i-1];
				if(
					iVars_Types_str[i] == "DB read value"  	||  
					iVars_Types_str[i] == "DB read PRI"  		||  
					iVars_Types_str[i] == "DB address"  		||  
					iVars_Types_str[i] == "DB database index"  ||  
					iVars_Types_str[i] == "DB table index"  	||  
					iVars_Types_str[i] == "DB field index"  	||  
					iVars_Types_str[i] == "DB record index"
				  )
					{
					//if this row already exists in the iVars name tracking linked list, blank out the names
					iVars_DBNT_AddElement(iVars_DBCoords[i], i);
					}
			
				iVars_StaticInitValues[i] = iVars_StaticInitValues[i-1];
				iVars_Values[i] = iVars_Values[i-1];
				iVars_AttribTypes[i] = iVars_AttribTypes[i-1];
				iVars_IndexesForDBIndexVars[i] = iVars_IndexesForDBIndexVars[i-1];

				#ifdef EQ_IsQueryEquationTypeBlock
					DBQF_OptionsChosen[i] = DBQF_OptionsChosen[i-1];
					DBQF_FieldIndex[i] = DBQF_FieldIndex[i-1];
					DBQF_FieldName[i] = DBQF_FieldName[i-1];
					DBQF_WhichConnector[i] = DBQF_WhichConnector[i-1];
					
					DBQFP_OptionsChosen[i] = DBQFP_OptionsChosen[i-1];
					DBQFP_TableIndex[i] = DBQFP_TableIndex[i-1];
					DBQFP_TableName[i] = DBQFP_TableName[i-1];
					DBQFP_FieldIndex[i] = DBQFP_FieldIndex[i-1];
					DBQFP_FieldName[i] = DBQFP_FieldName[i-1];
					DBQFP_WhichConnector[i] = DBQFP_WhichConnector[i-1];
					
					DBQSR_OptionsChosen[i] = DBQSR_OptionsChosen[i-1];
					DBQSR_WhichConnector[i] = DBQSR_WhichConnector[i-1];
					DBQSR_StartRecord[i] = DBQSR_StartRecord[i-1];
					
					#ifdef EQ_IsQueryEquationItemBlock
						DBQF_AttribNamesChosen[i] = DBQF_AttribNamesChosen[i-1];
						DBQF_AttribType[i] = DBQF_AttribType[i-1];
						
						DBQFP_AttribNamesChosen[i] = DBQFP_AttribNamesChosen[i-1];
						DBQFP_AttribType[i] = DBQFP_AttribType[i-1];
						
						DBQSR_AttribNamesChosen[i] = DBQSR_AttribNamesChosen[i-1];
						DBQSR_AttribType[i] = DBQSR_AttribType[i-1];
					#endif //EQ_IsQueryEquationItemBlock
				#endif //EQ_IsQueryEquationTypeBlock
				}
			}
		
		}//if(lastRowSize < iVars_NumTableRows)

	#ifdef CMC_chk
		CMC_IVars_ResizeArrays(doWhat);
	#endif

}//procedure iVars_ResizeDynamicArrays(integer doWhat)
*/
/*
integer iVars_SetValuesColTagArray()
{

	integer i;
	integer valuesColTagArrayIndex;
	
	MakeArray(iVars_ValuesColTagArray, iVars_NumTableRows);
	
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(
		   StrFind(iVars_Types_str[i], "start record", FALSE, FALSE) > -1  ||  
		   StrFind(iVars_Types_str[i], "DB ", FALSE, FALSE) > -1  ||  
		   StrFind(iVars_Types_str[i], "DBQ query", FALSE, FALSE) > -1
		  )
			iVars_ValuesColTagArray[i] = "usePopupTag";
		else
			iVars_ValuesColTagArray[i] = "";
		}
	
	valuesColTagArrayIndex = DynamicTextArrayNumber(iVars_ValuesColTagArray);
	
	return(valuesColTagArrayIndex);

}//procedure iVars_SetValuesColTagArray()
*/
	
#ifdef EQ_IsItemBlock

	integer iVars_SetNamesColTagArray()
	{
	
		integer i;
		integer namesColTagArrayIndex;
		
		MakeArray(iVars_NamesColTagArray, iVars_NumTableRows);
		
		for(i=0; i<iVars_NumTableRows; i++)
			{
			if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) > -1)
				iVars_NamesColTagArray[i] = "usePopupTag";
			else
				iVars_NamesColTagArray[i] = "";
			}
		
		namesColTagArrayIndex = DynamicTextArrayNumber(iVars_NamesColTagArray);
		
		return(namesColTagArrayIndex);
	
	}//procedure iVars_SetNamesColTagArray()
	
#endif //EQ_IsItemBlock

	
#ifdef EQ_IsQueryEquationTypeBlock

	integer iVars_SetColTagArray(integer whichCol)
		{
	
		integer i;
		integer columnTagArrayIndex;
		
		if(whichCol == DBQ_READ_VAL_INDIRECT_PARENT_FIELD)
			{
			MakeArray(iVars_ColTagArray_ParentIndirectionField, iVars_NumTableRows);
			
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(iVars_Types_str[i] == "DBQ read PRI")
					{
					//if the chosen query field is a child field
					if(DBQFP_TableIndex[i] >= 1  ||  DBQF_OptionsChosen[i] == DBQ_USE_ATTRIBUTE  ||  DBQF_OptionsChosen[i] == DBQ_USE_CONSTANT  ||  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)
						{
						iVars_ColTagArray_ParentIndirectionField[i] = "usePopupTag";
						}
					else
						{
						iVars_ColTagArray_ParentIndirectionField[i] = "";
						}
					}
				else
					iVars_ColTagArray_ParentIndirectionField[i] = "";
				}
			
			columnTagArrayIndex = DynamicTextArrayNumber(iVars_ColTagArray_ParentIndirectionField);
			}
			
		else if(whichCol == DBQ_READ_VAL_FIELD)
			{
			MakeArray(iVars_ColTagArray_DBQ_READ, iVars_NumTableRows);
			
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
					{
					iVars_ColTagArray_DBQ_READ[i] = "usePopupTag";
					}
				else
					{
					iVars_ColTagArray_DBQ_READ[i] = "";
					}
				}
			
			columnTagArrayIndex = DynamicTextArrayNumber(iVars_ColTagArray_DBQ_READ);
			}
		
		return(columnTagArrayIndex);
	
		}//procedure iVars_SetColTagArray()
	
#endif //EQ_IsQueryEquationTypeBlock
	
/*
//called in ConArrayChanged, on iVars_NumTableRows, DialogOpen, DialogClick
procedure iVars_TableSetup()
{

	integer i;
	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	string63 dbCoordinate;
	string staticValues;
	integer parentInfo[3];
	integer numRecords;
	integer positionArray[4];
	integer namesColTagArrayIndex;
	integer valuesColTagArrayIndex;
	integer colTagArrayIndex;
	
	#ifdef EQ_IsQueryEquationTypeBlock
		DBQ_GetAllChosenAddressIndexes(-1, CALLED_FROM_IVARS_TABLE_SETUP);
		numRecords = DBRecordsGetNum(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm);
	#endif

	iVars_DBNT_UpdateDBCoordsArray();

	//update iVars_ttbl with current information
	for(i=0; i<iVars_NumTableRows; i++)
		{
		iVars_ttbl[i][I_VAR_NAME_COL] = iVars_Names[i];
		

		//********************************
		//START:  Write to I_VAR_TYPE_COL
		//********************************
		
		#ifdef CMC_chk
		if(CMC_chk  &&  iVars_Types_Int[i] == EQ_CONNECTORS  )
			{
			if(CMC_IVarsIn_Settings[i] == CMC_IVAR_MSG_EMULATION)
				{
				iVars_ttbl[i][I_VAR_TYPE_COL] = "Con" + iVars_VarIsWhichCon[i] + " [ME]";
				}
			else if(CMC_IVarsIn_Settings[i] == CMC_IVAR_ALWAYS)
				{
				iVars_ttbl[i][I_VAR_TYPE_COL] = "Con" + iVars_VarIsWhichCon[i] + " [A]";
				}
			else if(CMC_IVarsIn_Settings[i] == CMC_IVAR_NEVER)
				{
				iVars_ttbl[i][I_VAR_TYPE_COL] = "Con" + iVars_VarIsWhichCon[i] + " [N]";
				}
			}
		else
			{
			iVars_ttbl[i][I_VAR_TYPE_COL] = iVars_Types_str[i];
			}
		#else
		iVars_ttbl[i][I_VAR_TYPE_COL] = iVars_Types_str[i];
		#endif


		//********************************
		//END:  Write to I_VAR_TYPE_COL
		//********************************


		//********************************
		//START:  Write to I_VAR_VALUE_COL
		//********************************
		
		//blank out the cell first
		iVars_ttbl[i][I_VAR_VALUE_COL] = "";
		
		if(StrFind(iVars_Types_str[i], "connector", FALSE, FALSE) > -1)	
			{
			iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_Values[i];
			}
		else if(StrFind(iVars_Types_str[i], "Integer", FALSE, FALSE) > -1)	// Carollo
			{
			iVars_ttbl[i][I_VAR_VALUE_COL] = Int(iVars_Values[i]);
			}
		else if(StrFind(iVars_Types_str[i], "Real", FALSE, FALSE) > -1)		// Carollo
			{
			iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_Values[i];
			}
		else if(StrFind(iVars_Types_str[i], "String", FALSE, FALSE) > -1)		// Carollo
			{
			iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_ValuesStr[i];
			}

		else if(
				iVars_Types_Int[i] == EQ_STATIC_FRI  ||  
				iVars_Types_Int[i] == EQ_STATIC_MRI  ||  
				iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL  ||  
				iVars_Types_Int[i] == EQ_QEQ_STATIC_CALC_CYCLE_INIT  ||  
				iVars_Types_Int[i] == EQ_QEQ_STATIC_ITEM_VALUE  ||  				//11/17/10
				iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT
			   )
			{
			staticValues = iVars_StaticInitValues[i] + " : " + iVars_Values[i];
			iVars_ttbl[i][I_VAR_VALUE_COL] = staticValues;
			}

		#ifdef EQ_IsQueryEquationTypeBlock
			
			else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
				{
				
				dbCoordinate = "";
				
				if(DBQF_OptionsChosen[i] == DBQ_USE_LIST)
					{
					//database index
					if(DBQ_DatabaseIndex_prm >= 1)
						dbCoordinate += DBQ_DatabaseIndex_prm + ":";
					else
						dbCoordinate += "x:";

					//table index
					if(DBQ_TableIndex_prm >= 1)
						dbCoordinate += DBQ_TableIndex_prm + ":";
					else
						dbCoordinate += "x:";
					
					//fieldIndex
					if(DBQF_FieldIndex[i] >= 1)
						dbCoordinate += DBQF_FieldIndex[i];
					else
						dbCoordinate += "x";
					}
				
				else if(DBQF_OptionsChosen[i] == DBQ_USE_CONSTANT)
					{
					if(DBQF_FieldIndex[i] >= 1  &&  !NoValue(DBQF_FieldIndex[i]))
						dbCoordinate = DBQF_FieldIndex[i];
					else
						dbCoordinate = "x";
					}
				
				else if(DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					dbCoordinate = "Connector " + DBQF_WhichConnector[i];
					}
				
				else if(DBQF_OptionsChosen[i] == DBQ_NOT_DEFINED)
					{
					dbCoordinate = "Choose a field";
					}
				
				#ifdef EQ_IsQueryEquationItemBlock
				else if(DBQF_OptionsChosen[i] == DBQ_USE_ATTRIBUTE)
					{
					dbCoordinate = "{" + DBQF_AttribNamesChosen[i] + "}";
					}
				#endif
				
				iVars_ttbl[i][I_VAR_VALUE_COL] = dbCoordinate;
				
				}//else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
	
			else if(iVars_Types_str[i] == "DBQ start record")
				{
					
				dbCoordinate = "";
					
				if(DBQSR_OptionsChosen[i] == DBQ_USE_LIST)
					{
					//database index
					if(DBQ_DatabaseIndex_prm >= 1)
						dbCoordinate += DBQ_DatabaseIndex_prm + ":";
					else
						dbCoordinate += "x:";
					
					//table index
					if(DBQ_TableIndex_prm >= 1)
						dbCoordinate += DBQ_TableIndex_prm + ":";
					else
						dbCoordinate += "x:";
					
					//fieldIndex
					dbCoordinate += "x:";

					//record index
					if(DBQSR_StartRecord[i] >= 1)
						dbCoordinate += DBQSR_StartRecord[i];
					else
						dbCoordinate += "x";
					}
										
				if(DBQSR_OptionsChosen[i] == DBQ_USE_CONSTANT)
					{
					if(DBQSR_StartRecord[i] >= 1  &&  !NoValue(DBQSR_StartRecord[i]))
						dbCoordinate = DBQSR_StartRecord[i];
					else
						dbCoordinate = "x";
					}
										
				#ifdef EQ_IsQueryEquationItemBlock
				else if(DBQSR_OptionsChosen[i] == DBQ_USE_ATTRIBUTE)
					{
					dbCoordinate = "{" + DBQSR_AttribNamesChosen[i] + "}";
					}
				#endif
				
				else if(DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					dbCoordinate = "Connector " + DBQSR_WhichConnector[i];
					}

				else if(DBQSR_OptionsChosen[i] == DBQ_NOT_DEFINED)
					{
					dbCoordinate = "Choose a record";
					}
				
				iVars_ttbl[i][I_VAR_VALUE_COL] = dbCoordinate;
	
				}//else if(iVars_Types_str[i] == "DBQ start record")
	
			else if(iVars_Types_str[i] == "DBQ num records")
				{
				if(DBQ_TableOptionChosen == DBQ_USE_LIST  &&  DBQ_DatabaseOptionChosen == DBQ_USE_LIST)
					{
					iVars_Values[i] = numRecords;
					iVars_ttbl[i][I_VAR_VALUE_COL] = numRecords;
					}
				else
					{
					iVars_ttbl[i][I_VAR_VALUE_COL] = "x";
					}
				}
	
			//if the variable type is "num records", store the current number of records if possible
			if(iVars_Types_str[i] == "DBQ num records")
				{
				if(DBQ_TableOptionChosen == DBQ_USE_LIST  &&  DBQ_DatabaseOptionChosen == DBQ_USE_LIST)
					{
					iVars_Values[i] = numRecords;
					}
				}
	
			else if(iVars_Types_str[i] == "DBQ current record index")
				{
				iVars_ttbl[i][I_VAR_VALUE_COL] = "-";
				}
		
		#endif //EQ_IsQueryEquationTypeBlock
		
		else if(iVars_Types_str[i] == "DB read value"  ||  
				iVars_Types_str[i] == "DB read PRI"  ||  
				iVars_Types_str[i] == "DB address"  ||  
				iVars_Types_str[i] == "DB read value using attrib"  ||  
				iVars_Types_str[i] == "DB read PRI using attrib")
			{
			dbCoordinate = "";
			
			if( NoValue(iVars_DBCoords[i]) )
				{
				dbCoordinate = "x:x:x:x";
				}
			else
				{
				databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
				if(databaseIndex < 1  ||  NoValue(databaseIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += databaseIndex + ":";
				
				tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
				if(tableIndex < 1  ||  NoValue(tableIndex))
						dbCoordinate += "x:";
				else
					dbCoordinate += tableIndex + ":";
				
				fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
				if(fieldIndex < 1  ||  NoValue(fieldIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += fieldIndex + ":";
				
				recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
				if(recordIndex < 1  ||  NoValue(recordIndex))
						dbCoordinate += "x";
				else
					dbCoordinate += recordIndex;
				}
			iVars_ttbl[i][I_VAR_VALUE_COL] = dbCoordinate;
			}

		//else if(iVars_Types_str[i] == "_DB index")		//6/25/09
		else if(
				iVars_Types_str[i] == "DB database index"  ||  
				iVars_Types_str[i] == "DB table index"  ||  
				iVars_Types_str[i] == "DB field index"  ||  
				iVars_Types_str[i] == "DB record index"
			   )
			{
			if( NoValue(iVars_DBCoords[i]) )
				{
				iVars_ttbl[i][I_VAR_VALUE_COL] = "x";
				}
			else
				{
				recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
				if(recordIndex >= 1)
					iVars_ttbl[i][I_VAR_VALUE_COL] = recordIndex;
				else
					{
					fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
					if(fieldIndex >= 1)
						iVars_ttbl[i][I_VAR_VALUE_COL] = fieldIndex;
					else
						{
						tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
						if(tableIndex >= 1)
							iVars_ttbl[i][I_VAR_VALUE_COL] = tableIndex;
						else
							{
							databaseIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
							if(databaseIndex >= 1)
								iVars_ttbl[i][I_VAR_VALUE_COL] = databaseIndex;
							}
						}
					}
				}
			}

		else if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) > -1)	
			{
			#ifdef EQ_IsItemBlock
				
				if(iVars_AttribTypes[i] == ATTRIB_TYPE_VALUE)
					{
					iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_Values[i];
					}
				
				else if(iVars_AttribTypes[i] == ATTRIB_TYPE_STRING)	
					{
					iVars_ttbl[i][I_VAR_VALUE_COL] = SLStringGet(iVars_ttbl[i][I_VAR_NAME_COL], iVars_Values[i]);
					}
					
				else if(iVars_AttribTypes[i] == ATTRIB_TYPE_DB)	
					{
					dbCoordinate = "";
					if( NoValue(iVars_Values[i]) )
						{
						dbCoordinate = "x:x:x:x";
						}
					else
						{
						databaseIndex = DBDatabaseGetIndexFromAddress(iVars_Values[i]);
						if(databaseIndex < 1  ||  NoValue(databaseIndex))
							dbCoordinate += "x:";
						else
							dbCoordinate += databaseIndex + ":";
						
						tableIndex = DBTableGetIndexFromAddress(iVars_Values[i]);
						if(tableIndex < 1  ||  NoValue(tableIndex))
							dbCoordinate += "x:";
						else
							dbCoordinate += tableIndex + ":";
						
						fieldIndex = DBFieldGetIndexFromAddress(iVars_Values[i]);
						if(fieldIndex < 1  ||  NoValue(fieldIndex))
							dbCoordinate += "x:";
						else
							dbCoordinate += fieldIndex + ":";
						
						recordIndex = DBRecordGetIndexFromAddress(iVars_Values[i]);
						if(recordIndex < 1  ||  NoValue(recordIndex))
							dbCoordinate += "x";
						else
							dbCoordinate += recordIndex;
						}
					iVars_ttbl[i][I_VAR_VALUE_COL] = dbCoordinate;
					}

			#endif
			
			}
			
		//4/16/11
		#ifdef CW_CalcEventTime_chk
		else if(iVars_Types_str[i] == "Next calc event time")
			{
			iVars_ttbl[i][I_VAR_VALUE_COL] = nextCalcEventTime;
			}
		#endif
	

		
		//********************************
		//END:  Write to I_VAR_VALUE_COL
		//********************************
		

		
		//***************************************
		//START:  Write to I_VAR_PARENT_FIELD_COL
		//***************************************
		
		#ifdef EQ_IsQueryEquationTypeBlock
			
			if(iVars_Types_str[i] == "DBQ read PRI")
				{
					
				//if the chosen query field is a child field
				if(DBQFP_TableIndex[i] >= 1  ||  DBQF_OptionsChosen[i] == DBQ_USE_ATTRIBUTE  ||  DBQF_OptionsChosen[i] == DBQ_USE_CONSTANT  ||  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					dbCoordinate = "";
					
					if(DBQFP_OptionsChosen[i] == DBQ_USE_LIST)
						{
						//database index
						if(DBQ_DatabaseIndex_prm >= 1)
							dbCoordinate += DBQ_DatabaseIndex_prm + ":";
						else
							dbCoordinate += "x:";
						
						//table index
						if(DBQFP_TableIndex[i] >= 1)
							dbCoordinate += DBQFP_TableIndex[i] + ":";
						else
							dbCoordinate += "x:";
						
						//fieldIndex
						if(DBQFP_FieldIndex[i] >= 1)
							dbCoordinate += DBQFP_FieldIndex[i];
						else
							dbCoordinate += "x";
						}
						
					#ifdef EQ_IsQueryEquationItemBlock
					else if(DBQFP_OptionsChosen[i] == DBQ_USE_ATTRIBUTE)
						{
						dbCoordinate = "{" + DBQFP_AttribNamesChosen[i] + "}";
						}
					#endif
					
					else if(DBQFP_OptionsChosen[i] == DBQ_USE_CONSTANT)
						{
						if(DBQFP_FieldIndex[i] < 1  ||  NoValue(DBQFP_FieldIndex[i]))
							dbCoordinate += "x:";
						else
							dbCoordinate += DBQFP_FieldIndex[i];
						}

					else if(DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)
						{
						dbCoordinate = "Connector " + DBQFP_WhichConnector[i];
						}
						
					else if(DBQFP_OptionsChosen[i] == DBQ_NOT_DEFINED)
						{
						dbCoordinate = "not used";
						}

					iVars_ttbl[i][I_VAR_PARENT_FIELD_COL] = dbCoordinate;
					}//if(DBQFP_TableIndex[i] >= 1)
				
				else //if the field chosen in the "Value" column is NOT a child field
					iVars_ttbl[i][I_VAR_PARENT_FIELD_COL] = "N/A";
				}
			
			else //if(iVars_Types_str[i] != "_DBQ_query field")
				{
				iVars_ttbl[i][I_VAR_PARENT_FIELD_COL] = "N/A";
				}
		
		#endif //EQ_IsQueryEquationTypeBlock
		
		//***************************************
		//END:  Write to I_VAR_PARENT_FIELD_COL
		//***************************************
		
		
		}//for(i=0; i<iVars_NumTableRows; i++)

	DTGrowButton(MyBlockNumber(), "iVars_ttbl", TRUE);
	DTHideLinkButton(MyBlockNumber(), "iVars_ttbl", TRUE);
	SetDTRowStart(MyBlockNumber(), "iVars_ttbl", 1);
	
	//get info on iVars_ttbl frame
	DIPositionGet(MyBlockNumber(), "iVars_ttbl", positionArray);
	DIPositionSet(MyBlockNumber(), "iVars_ttbl", positionArray[0], positionArray[1], positionArray[2], positionArray[3]+500);	//set max width of iVars_ttbl frame

	#ifdef EQ_IsQueryEquationTypeBlock
		SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 1, 90, TRUE);
		SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 3, 90, TRUE);// chiu, 05/26/2015
		SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 4, 80, TRUE);
	#else
		#ifdef EQ_IsItemBlock
			SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 1, 140, TRUE);
		#else
			SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 1, 110, TRUE);
		#endif
	#endif

	#ifdef EQ_IsQueryEquationTypeBlock
		//do nothing
	#else
		SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 4, 25, TRUE);	//hide the fourth column
		
	#endif
	
	SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 4, 1, TRUE);	//hide the fourth column
	SetDTColumnWidth(MyBlockNumber(), "iVars_ttbl", 5, 50, TRUE);	//hide the fourth column// chiu, 05/26/2015

	//I_VAR_TYPE_COL column tag
	DTColumnTagSet(MyBlockNumber(), "iVars_ttbl", I_VAR_TYPE_COL, TAG_POPUP, 0, "", "");
	
	//I_VAR_NAME_COL column tag
	#ifdef EQ_IsItemBlock
		namesColTagArrayIndex = iVars_SetNamesColTagArray();
		DTColumnTagSet(MyBlockNumber(), "iVars_ttbl", I_VAR_NAME_COL, TAG_CONDITIONAL_POPUP_ARRAY, namesColTagArrayIndex, "usePopupTag", "");
	#endif
		
	//I_VAR_VALUE_COL column tag
	valuesColTagArrayIndex = iVars_SetValuesColTagArray();
	DTColumnTagSet(MyBlockNumber(), "iVars_ttbl", I_VAR_VALUE_COL, TAG_CONDITIONAL_POPUP_ARRAY, valuesColTagArrayIndex, "usePopupTag", "");
	
	//I_VAR_PARENT_FIELD_COL column tag
	#ifdef EQ_IsQueryEquationTypeBlock

		//set the col tag for the value column of the DBQ Read Value and DBQ PRI
		colTagArrayIndex = iVars_SetColTagArray(DBQ_READ_VAL_FIELD);
		DTColumnTagSet(MyBlockNumber(), "iVars_ttbl", I_VAR_VALUE_COL, TAG_CONDITIONAL_POPUP_ARRAY, colTagArrayIndex, "usePopupTag", "");
		
		//set the indirect parent field column tag
		colTagArrayIndex = iVars_SetColTagArray(DBQ_READ_VAL_INDIRECT_PARENT_FIELD);
		DTColumnTagSet(MyBlockNumber(), "iVars_ttbl", I_VAR_PARENT_FIELD_COL, TAG_CONDITIONAL_POPUP_ARRAY, colTagArrayIndex, "usePopupTag", "");
	#endif
}//procedure iVars_TableSetup()
*/
/*
//called in EQ_Calc()
#ifdef EQ_IsItemBlock
	procedure iVars_GetVals(integer itemIndex, integer sendMsgs)
#else
	procedure iVars_GetVals(integer sendMsgs)
#endif
{
	
	integer i, j;
	integer me;
	integer simPhase;
	integer batchID;
	integer batchSize;
	integer whichCon;
	integer dbIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	integer updateCons;
	real oldValue;
	integer fieldType;
	integer legitField;
	integer parentInfo[3];
	real currBest;
	integer parentRecordIndex;
	integer parentParentRecordIndex;
	integer AR_ResourceOrderID;
	integer AR_ListFieldIndexForResourceOrderID;
	integer whichElement;
	integer whichField;
	integer staticItemValueCount;

	me = MyBlockNumber();
	
	if(sendMsgs == TRUE  &&  modelType == DISCRETE_EVENT)
		{
		//3/25/10
		//whichCon = ConArrayMsgFromCon();			//1/21/10
		
		for(i=0; i<iVarsIn_NumCons; i++)
			{
			if(iVarsIn_NumBlocksConnected[i] >= 1)
				#ifdef EQ_IsQueryEquationItemBlock
					if(
						iVars_Types_Int[iVars_ConIsWhichVar[i]] != EQ_DBQ_QUERY_FIELD_VALUE  &&  
						iVars_Types_Int[iVars_ConIsWhichVar[i]] != EQ_DBQ_QUERY_FIELD_PRI  &&  
						iVars_Types_Int[iVars_ConIsWhichVar[i]] != EQ_DBQ_START_RECORD
					  )
							SendMsgToOutputs(iVarsIn_ConNums[i]);
				#else
					#ifdef EQ_IsQueueEquation		//1/21/10
						if(inIVarsIn == TRUE)
							{
							//if(whichCon != i)
							if(iVarsIn_WhichConGotMsg != i)						//3/25/10
								SendMsgToOutputs(iVarsIn_ConNums[i]);
							}
						else
							{
							SendMsgToOutputs(iVarsIn_ConNums[i]);
							}
					#else
						SendMsgToOutputs(iVarsIn_ConNums[i]);
					#endif
				#endif
			}
		}

	updateCons = FALSE;
				
	#ifdef EQ_IsValueBlock	//if this is the equation from the Value library
	
		//3/31/11
		/*
		if(GetSimulationPhase() == PHASE_NOT_CURRENTLY_RUNNING)
			{
			//iVars_IndexesForDBIndexVars[] is used to store the value of the db index type vars.  since it 
			//gets updated once in checkdata or when the model is not running, this array helps to increase
			//speed during run time because conversion of the db address to an index only has to occur once.
			
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX)
					{
					iVars_IndexesForDBIndexVars[i] = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
					}
				else if(iVars_Types_Int[i] == EQ_DB_TABLE_INDEX)
					{
					iVars_IndexesForDBIndexVars[i] = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
					}
				else if(iVars_Types_Int[i] == EQ_DB_FIELD_INDEX)
					{
					iVars_IndexesForDBIndexVars[i] = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
					}
				else if(iVars_Types_Int[i] == EQ_DB_RECORD_INDEX)
					{
					iVars_IndexesForDBIndexVars[i] = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
					}
				}
			}
		*/
/*
		for(i=0; i<iVars_NumTableRows; i++)
			{
			oldValue = iVars_Values[i];
			
			if(iVars_Types_Int[i] == EQ_CONNECTORS)
				{
				whichCon = iVars_VarIsWhichCon[i];
				iVars_Values[i] = ConArrayGetValue(iVarsIn, whichCon);	
				iVars_ValueWasFound[i] = TRUE;
				
				if(oldValue != iVars_Values[i])
					updateCons = TRUE;
				}
	
			else if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI  ||  iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
				{
				//do nothing- static vars were initialized at initSim and updated during EquationCalculateDynamicVariables()
				iVars_ValueWasFound[i] = TRUE;
				}
	
			else if(iVars_Types_Int[i] == EQ_DB_READ_VAL)
				{
				if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
					{
					legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
					if(!legitField)
						AbortAllSims();
					
					iVars_Values[i] = DBDataGetAsNumberUsingAddress(iVars_DBCoords[i]);
				
					//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
					//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
					fieldType = DBFieldGetPropertiesUsingAddress(iVars_DBCoords[i], 1) ;	//where 1 = fieldType
					if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
						{
						iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
						}
	
					iVars_ValueWasFound[i] = TRUE;
					}
				else
					{
					UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
							  "'DB read value', but the specified location does not exist.");
					AbortAllSims();
					}
				}
				
			else if(iVars_Types_Int[i] == EQ_DB_READ_PRI)
				{
				if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
					{
					legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
					if(!legitField)
						AbortAllSims();
					
					DBDataGetParentUsingAddress(iVars_DBCoords[i], parentInfo);
					iVars_Values[i] = parentInfo[PARENT_RECORD];
	
					iVars_ValueWasFound[i] = TRUE;
					}
				else
					{
					UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
							  "'DB read PRI', but the specified location does not exist.");
					AbortAllSims();
					}
				}

			else if(iVars_Types_Int[i] == EQ_DB_ADDRESS)
				{
				iVars_Values[i] = iVars_DBCoords[i];
				iVars_ValueWasFound[i] = TRUE;
				}

			//else if(iVars_Types_Int[i] == EQ_DB_INDEX)		//6/25/09
			else if(
					iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX  ||  
					iVars_Types_Int[i] == EQ_DB_TABLE_INDEX  ||  
					iVars_Types_Int[i] == EQ_DB_FIELD_INDEX  ||  
					iVars_Types_Int[i] == EQ_DB_RECORD_INDEX
				   )
				{
//				iVars_Values[i] = StrToReal(iVars_ttbl[i][I_VAR_VALUE_COL]);	//7.0.5, 10/21/08
				iVars_Values[i] = iVars_IndexesForDBIndexVars[i];
				iVars_ValueWasFound[i] = TRUE;
				}
				
			//4/16/11
			else if(iVars_Types_Int[i] == EQ_NEXT_CALC_EVENT_TIME)
				{
				iVars_Values[i] = nextCalcEventTime;
				iVars_ValueWasFound[i] = TRUE;
				}
			}
	
	#endif //EQ_IsValueBlock


	#ifdef EQ_IsItemBlock	//if this is an item processing block like the Equation(I) or the Queue Equation or the Query Equation
	
		if(itemIndex > 0)
			{
			
			for(i=0; i<iVars_NumTableRows; i++)
				{
				oldValue = iVars_Values[i];

				if(iVars_Types_Int[i] == EQ_ITEM_QTY)
					{
					#ifdef itemArrayR
						
						iVars_Values[i] = itemArrayR[itemIndex][0];
						
						if(NoValue(iVars_Values[i]))
							{
							UserError("Error!  An item was found without an item value in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							AbortAllSims();
							}
						else
							iVars_ValueWasFound[i] = TRUE;
					
					#endif //itemArrayR
					}
				
				else if(iVars_Types_Int[i] == EQ_ITEM_3D_ID)
					{
					#ifdef ItemArray3D
					
						iVars_Values[i] = ItemArray3D[itemIndex][0];
						iVars_ValueWasFound[i] = TRUE;
					
					#endif //ItemArray3D
					}
					
				else if(iVars_Types_Int[i] == EQ_ITEM_PRIORITY)
					{
					#ifdef itemArrayR
					
						iVars_Values[i] = itemArrayR[itemIndex][1];
					
						if(NoValue(iVars_Values[i]))
							{
							UserError("Error!  An item was found without an item priority in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							AbortAllSims();
							}
						else
							iVars_ValueWasFound[i] = TRUE;
							
					#endif //itemArrayR
					}
						
				//else if(iVars_Types_Int[i] == EQ_ITEM_AR_ORDER_ID)
				//	{
				//	#ifdef itemArrayI2
				//	
				//		iVars_Values[i] = itemArrayI2[itemIndex][0];
				//		iVars_ValueWasFound[i] = TRUE;
				//		
				//	#endif
				//	}
						
				else if(iVars_Types_Int[i] == EQ_ITEM_BATCH_SIZE)
					{
					#ifdef itemArrayI
						
						batchID = itemArrayI[itemIndex][1];
					
						if(batchID > 0)			//if true, the batch has preserve uniqueness consequently the number reported is the index to this batch's global array
							{
							batchSize = GAGetRowsByIndex(batchID);
							iVars_Values[i] = batchSize;
							iVars_ValueWasFound[i] = TRUE;
							}
						else if(batchID < 0)	//if true, the batch does not have preserve uniqueness and the negative number reported in itemArrayI is the batch size
							{
							iVars_Values[i] = -batchID;
							iVars_ValueWasFound[i] = TRUE;
							}
						else					//else this item is not a batch
							{
							iVars_Values[i] = blank;
							iVars_ValueWasFound[i] = FALSE;
							}
					
					#endif //itemArrayI
					}
				
				//4/16/11
				#ifdef CW_CalcEventTime_chk
				else if(iVars_Types_Int[i] == EQ_NEXT_CALC_EVENT_TIME)
					{
					iVars_Values[i] = nextCalcEventTime;
					iVars_ValueWasFound[i] = TRUE;
					}
				#endif

				else if(iVars_Types_Int[i] == EQ_CONNECTORS)
					{
					whichCon = iVars_VarIsWhichCon[i];
					iVars_Values[i] = ConArrayGetValue(iVarsIn, whichCon);	
					iVars_ValueWasFound[i] = TRUE;
					
					if(oldValue != iVars_Values[i])
						updateCons = TRUE;
					}
	
				else if(iVars_Types_Int[i] == EQ_STATIC_FRI  ||  iVars_Types_Int[i] == EQ_STATIC_MRI  ||  iVars_Types_Int[i] == EQ_STATIC_OPEN_MODEL)
					{
					//do nothing- static vars were initialized at initSim and updated during EquationCalculateDynamicVariables()
					iVars_ValueWasFound[i] = TRUE;
					}
	
				else if(iVars_Types_Int[i] == EQ_DB_READ_VAL)
					{
					if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10	
						{
						legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
						if(!legitField)
							AbortAllSims();
	
						iVars_Values[i] = DBDataGetAsNumberUsingAddress(iVars_DBCoords[i]);
	
						//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
						//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
						fieldType = DBFieldGetPropertiesUsingAddress(iVars_DBCoords[i], 1) ;	//where 1 = fieldType
						if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
							{
							iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
							}
	
						iVars_ValueWasFound[i] = TRUE;
						}
					else
						{
						UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
								  "'DB read value', but the specified location does not exist.");
						AbortAllSims();
						}
					}
	
				else if(iVars_Types_Int[i] == EQ_DB_READ_PRI)
					{
					if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10	
						{
						legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
						if(!legitField)
							AbortAllSims();
						
						DBDataGetParentUsingAddress(iVars_DBCoords[i], parentInfo);
						iVars_Values[i] = parentInfo[PARENT_RECORD];
	
						iVars_ValueWasFound[i] = TRUE;
						}
					else
						{
						UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
								  "'DB read PRI', but the specified location does not exist.");
						AbortAllSims();
						}
					}
	
				else if(iVars_Types_Int[i] == EQ_DB_ADDRESS)
					{
					iVars_Values[i] = iVars_DBCoords[i];
					iVars_ValueWasFound[i] = TRUE;
					}

				//else if(iVars_Types_Int[i] == EQ_DB_INDEX)		//6/25/09
				else if(
						iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX  ||
						iVars_Types_Int[i] == EQ_DB_TABLE_INDEX  ||
						iVars_Types_Int[i] == EQ_DB_FIELD_INDEX  ||
						iVars_Types_Int[i] == EQ_DB_RECORD_INDEX
					   )
					{
//					iVars_Values[i] = StrToReal(iVars_ttbl[i][I_VAR_VALUE_COL]);	//7.0.5, 10/21/08
					iVars_Values[i] = iVars_IndexesForDBIndexVars[i];
					iVars_ValueWasFound[i] = TRUE;
					}

				else if(iVars_Types_Int[i] == EQ_ITEM_INDEX)
					{
					iVars_Values[i] = itemIndex;
					iVars_ValueWasFound[i] = TRUE;
					}

				else if(iVars_Types_Int[i] == EQ_DB_READ_VAL_USING_ATTRIB)
					{
					//...with this option user wants to get a value out of the db using a db attrib to specify the coordinate
					iVars_DBCoords[i] = Attrib_GetVal(itemIndex, iVars_AttribColumnIndexes[i], REPORT_NO_DB_INFO);
					
					if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10	
						{
						legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
						if(!legitField)
							AbortAllSims();
						
						iVars_Values[i] = DBDataGetAsNumberUsingAddress(iVars_DBCoords[i]);
	
						//if targeted field is of type "Date Time", then convert the number being read from calendar format to simTime.
						//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
						fieldType = DBFieldGetPropertiesUsingAddress(iVars_DBCoords[i], 1) ;	//where 1 = fieldType
						if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
							{
							iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
							}
	
						iVars_ValueWasFound[i] = TRUE;
						}
					else
						{
						UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
								  "'DB read value using attribute', but the specified location from the item's attribute does not exist.");
						AbortAllSims();
						}
					}

				else if(iVars_Types_Int[i] == EQ_DB_READ_PRI_USING_ATTRIB)
					{
					//...with this option user wants to get a record index from a parent using a db attrib to specify the coordinate
					iVars_DBCoords[i] = Attrib_GetVal(itemIndex, iVars_AttribColumnIndexes[i], REPORT_NO_DB_INFO);
					
					if(EQ_DBAddressLocationExists(iVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10	
						{
						legitField = iVars_CheckChosenField(i, iVars_DBCoords[i]);
						if(!legitField)
							AbortAllSims();
						
						DBDataGetParentUsingAddress(iVars_DBCoords[i], parentInfo);
						iVars_Values[i] = parentInfo[PARENT_RECORD];
	
						iVars_ValueWasFound[i] = TRUE;
						}
					else
						{
						UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
								  "'DB read PRI using attribute', but the specified location from the item's attribute does not exist.");
						AbortAllSims();
						}
					}

				else if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE)	//if variable is an attribute variable,...
					{
					iVars_Values[i] = Attrib_GetVal(itemIndex, iVars_AttribColumnIndexes[i], REPORT_NO_DB_INFO);
				
					if (!NoValue(iVars_Values[i]))	//if an attribute value was found
						iVars_ValueWasFound[i] = TRUE;
					
					else //if an attribute value was not found
						iVars_ValueWasFound[i] = FALSE;
					}
				
				}//for(i=0; i<iVars_NumTableRows; i++)
				
			}//if(itemIndex > 0)
			
		else
			{
			UserError("Trying to access an invalid itemIndex in Equation(I) block " + me + ".  Please contact Imagine That.");
			}
			
	#endif //EQ_IsItemBlock


	#ifdef EQ_IsQueueEquation

		if(itemIndex > 0)
			{
			//11/17/10:  if any iVars of type "static item values" have been defined
			if( GetDimension(iVars_StaticItemValuesRowIndexes) )	
				{
				staticItemValueCount = 0;

				whichElement = ListSearch(me, queueListIndex, 2, 0, itemIndex, 0, "", 0);
						//find where this item is represented in the linked list because 
						//we'll need it.  do this here so we only have to search once.
				}

			for(i=0; i<iVars_NumTableRows; i++)
				{
				oldValue = iVars_Values[i];
				
				if(iVars_Types_Int[i] == EQ_QEQ_ITEM_ARRIVAL_TIME)
					{
					iVars_Values[i] = GetArriveTime(itemIndex);
					iVars_ValueWasFound[i] = TRUE;
					}

				else if(iVars_Types_Int[i] == EQ_QEQ_LAST_ITEM_TO_EXIT)
					{
					iVars_Values[i] = iVars_LastItem_AttribVals[iVars_LastItem_RowIndex[i]];
					iVars_ValueWasFound[i] = TRUE;
					}

				else if(iVars_Types_Int[i] == EQ_QEQ_FIFO_POSTION)
					{
					iVars_Values[i] = siCurrentQueueListPosition + 1;
					iVars_ValueWasFound[i] = TRUE;
					}

				else if(iVars_Types_Int[i] == EQ_QEQ_CURR_BEST_RANK_RESULT)
					{
					iVars_Values[i] = currBestRankResult;
					iVars_ValueWasFound[i] = TRUE;
					}
				
				else if(iVars_Types_Int[i] == EQ_QEQ_NUM_ITEMS_IN_QUEUE)
					{
					iVars_Values[i] = queueLength;
					iVars_ValueWasFound[i] = TRUE;
					}
				
				else if(iVars_Types_Int[i] == EQ_QEQ_AR_REQUIREMENT_IS_AVAIL)
					{
					//ARG 1: the query type
					DBDataSetAsNumberReserved(AR_AdvancedResources_dBIdx[0],
											  AR_InterblockNumericParameters_TIdx[0],
											  AR_SND_ARG_REQUEST_TYPE_FIELDINDEX,
											  1,
											  AR_REQUIREMENT_IS_AVAILABLE_QUERY_MSG_TYPE);
					
					//ARG 2: the item's resource order ID
					if(IC_chk)
						AR_ListFieldIndexForResourceOrderID = 2;	//the 3rd integer field
					else
						AR_ListFieldIndexForResourceOrderID = 1;	//the 2nd integer field
					AR_ResourceOrderID = ListGetLong(me, queueListIndex, siCurrentQueueListPosition, AR_ListFieldIndexForResourceOrderID);
					DBDataSetAsNumberReserved(AR_AdvancedResources_dBIdx[0],
											  AR_InterblockNumericParameters_TIdx[0],
											  AR_SND_ARG_RESOURCE_ORDER_RECORD_FIELDINDEX,
											  1,
											  AR_ResourceOrderID);

					//wake resource manager
					SendMsgToBlock(AR_ResourceManager_blockNumber[0], 
								   AR_QEQ_MSG);
					
					//GET 1: get requirement availability back from resource manager
					iVars_Values[i] = DBDataGetAsNumber(AR_AdvancedResources_dBIdx[0],
											  			AR_InterblockNumericReturnedValues_TIdx[0],
											  			AR_RCV_ARG_REQ_IS_AVAILABLE_RESULT_FIELDINDEX, 
											   			1);	
					
					iVars_ValueWasFound[i] = TRUE;
					}
				
				else if(iVars_Types_Int[i] == EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL)
					{
					//ARG 1: the query type
					DBDataSetAsNumberReserved(AR_AdvancedResources_dBIdx[0],
											  AR_InterblockNumericParameters_TIdx[0],
											  AR_SND_ARG_REQUEST_TYPE_FIELDINDEX,
											  1,
											  AR_NUM_RESOURCES_AVAILABLE_QUERY_MSG_TYPE);
					
					//ARG 2: the item's resource order ID
					if(IC_chk)
						AR_ListFieldIndexForResourceOrderID = 2;	//the 3rd integer field
					else
						AR_ListFieldIndexForResourceOrderID = 1;	//the 2nd integer field
					AR_ResourceOrderID = ListGetLong(me, queueListIndex, siCurrentQueueListPosition, AR_ListFieldIndexForResourceOrderID);
					DBDataSetAsNumberReserved(AR_AdvancedResources_dBIdx[0],
											  AR_InterblockNumericParameters_TIdx[0],
											  AR_SND_ARG_RESOURCE_ORDER_RECORD_FIELDINDEX,
											  1,
											  AR_ResourceOrderID);

					//wake resource manager
					SendMsgToBlock(AR_ResourceManager_blockNumber[0], 
								   AR_QEQ_MSG);
					
					//GET 1: get num requirements available back from resource manager
					iVars_Values[i] = DBDataGetAsNumber(AR_AdvancedResources_dBIdx[0],
											  			AR_InterblockNumericReturnedValues_TIdx[0],
											  			AR_RCV_ARG_REQ_NUM_AVAILABLE_RESULT_FIELDINDEX, 
											   			1);	

					iVars_ValueWasFound[i] = TRUE;
					}
				
				else if(iVars_Types_Int[i] == EQ_QEQ_STATIC_CALC_CYCLE_INIT)
					{
					//do nothing- this static var was initialized at the start of the calc cycle in FindNextItem() and updated during EquationCalculateDynamicVariables()
					iVars_ValueWasFound[i] = TRUE;
					}
				
				else if(iVars_Types_Int[i] == EQ_QEQ_STATIC_ITEM_VALUE)			//11/17/10
					{
					//get static item value from the linked list
					whichField = staticItemValueCount + 1;										//+1 because the first double field is reserved for arrival time
					iVars_Values[i] = ListGetDouble(me, queueListIndex, whichElement, whichField);
					staticItemValueCount++;
					iVars_ValueWasFound[i] = TRUE;
					}

				}//for(i=0; i<iVars_NumTableRows; i++)
				
			}//if(itemIndex > 0)
				
		else
			{
			UserError("Trying to access an invalid itemIndex in Equation(I) block " + me + ".  Please contact Imagine That.");
			}
			
	#endif //EQ_IsQueueEquation


	#ifdef EQ_IsQueryEquationTypeBlock
				
		#ifdef EQ_IsQueryEquationItemBlock
		if(itemIndex > 0)
		#endif

			{
			
			for(i=0; i<iVars_NumTableRows; i++)
				{
				oldValue = iVars_Values[i];
				
				if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE)
					{
					//if a direct query field has been specified
					if(DBQF_OptionsChosen[i] != DBQ_NOT_DEFINED)
						{
						if(
							//8/17/10
							//DBQ_DatabaseIndex_prm >= 1  &&
							//DBQ_TableIndex_prm >= 1  &&
							//DBQF_FieldIndex[i] >= 1
							DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i])
						  )
							{
							if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
								{
								fieldType = DBFieldGetProperties(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], 1) ;	//where 1 = fieldType
								
								//if query field is a string field, we know we have a problem
								if(fieldType == DB_FIELDTYPE_STRING_VALUE)
									{
									parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
									
									//if direct query field is a string field that is also child field
									if(parentRecordIndex >= 0)	
										{
										//NOTE:  if parentRecordIndex = 0, then field is a child field, but no PRI has been selected yet.
										
										UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
												  "'DBQ read value', but the query field is a string child field. Either change the query field or change " +
												  "the variable type to 'DBQ read PRI'.");
										AbortAllSims();
										}
									
									//if direct query field is a string field
									else	
										{
										UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
												  "'DBQ read value', but the query field is a string field.");
										AbortAllSims();
										}
									}
								
								//if query field not a string field
								else
									{
									iVars_Values[i] = DBDataGetAsNumber(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle);
									
									//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
									//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
									if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
										{
										iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
										}
									}

								iVars_ValueWasFound[i] = TRUE;
								}
							else
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read value', and the current record, " + DBQ_CurrRecordInQueryCycle + " is out of bounds.");
								AbortAllSims();
								}
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " block " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read value', but the specified query field does not exist.");
							AbortAllSims();
							}
						}
					
					//if a direct query field has not been specified
					else
						{
						UserError("A query field has not yet been specified in row " + (i+1) + " of Equation Query block" + me + ".");
						AbortAllSims();
						}
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI)
					{
					//if an indirect parent query field has been specified
					if(DBQFP_OptionsChosen[i] != DBQ_NOT_DEFINED)
						{
						if(
							//8/17/10
							//DBQ_DatabaseIndex_prm >= 1  &&
							//DBQ_TableIndex_prm >= 1  &&
							//DBQF_FieldIndex[i] >= 1  &&
							//DBQFP_TableIndex[i] >= 1  &&
							//DBQFP_FieldIndex[i] >= 1
							DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i])  &&  
							DBFieldExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i])
						  )
							{
							if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
								{
								parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
								
								//if the direct query field is a child field and a PRI has been specified in the direct field's db cell
								if(parentRecordIndex >= 1)
									{
									if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex) )		//8/17/10
										{
										parentParentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex, parentInfo);
										
										//if the indirect query field is a child,...
										if(parentParentRecordIndex >= 0)
											{
											//...then by default grab the PRI found in the parent table- the "parentParent"
											iVars_Values[i] = parentParentRecordIndex;
											
											//note if parentParentRecordIndex = 0, then child cell has nothing selected yet
											}
		
										//if indirect query field is NOT a child
										else
											{
											iVars_Values[i] = DBDataGetAsNumber(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], parentRecordIndex);
											
											//if targeted field is of type "Date Time", then convert the number being read from Julian format to simTime.
											//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
											fieldType = DBFieldGetProperties(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i], 1) ;	//where 1 = fieldType
											if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
												{
												iVars_Values[i] = EDDateToSimTime(iVars_Values[i],0);
												}
											}
										}
									else
										{
										UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
												  "'DBQ read PRI', and parent record " + parentRecordIndex  + " does not exist.");
										AbortAllSims();
										}
									}
								
								//if the direct query field is a child field and a PRI has not been specified in the direct field's db cell
								else if(parentRecordIndex == 0)	
									{
									iVars_Values[i] = parentRecordIndex;
									}
								
								//if the direct query field not a child field
								else 
									{
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read PRI', but the query field is not a child field. Either change the query field or change " +
											  "the variable type to 'DBQ read value'.");
									AbortAllSims();
									}
									
								iVars_ValueWasFound[i] = TRUE;
								}
							else
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read value', and the current record, " + DBQ_CurrRecordInQueryCycle + " is out of bounds.");
								AbortAllSims();
								}
							}
						else
							{
							if( !DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i]) )
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', but the specified child field does not exist.");
								}
								
							else if( !DBFieldExists(DBQ_DatabaseIndex_prm, DBQFP_TableIndex[i], DBQFP_FieldIndex[i]) )
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', but the specified PARENT field does not exist.");
								}
								
							AbortAllSims();
							}
						}
						
					//else if a direct query field has been specified
					else if(DBQF_OptionsChosen[i] != DBQ_NOT_DEFINED)
						{
						if(
							//8/17/10
							//DBQ_DatabaseIndex_prm >= 1  &&
							//DBQ_TableIndex_prm >= 1  &&
							//DBQF_FieldIndex[i] >= 1
							DBFieldExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i])
						  )
							{
							if( DBRecordExists(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle) )		//8/17/10
								{
								parentRecordIndex = DBDataGetParent(DBQ_DatabaseIndex_prm, DBQ_TableIndex_prm, DBQF_FieldIndex[i], DBQ_CurrRecordInQueryCycle, parentInfo);
								
								//if direct query field is a child
								if(parentRecordIndex >= 0)
									{
									iVars_Values[i] = parentRecordIndex;	
									
									//note if parentRecordIndex = 0, then child cell has nothing selected yet
									}
	
								//else if direct query field is NOT a child field
								else
									{
									UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
											  "'DBQ read PRI', but the query field is not a child field. Either change the query field or change " +
											  "the variable type to 'DBQ read value'.");
									AbortAllSims();
									}
								
								iVars_ValueWasFound[i] = TRUE;
								}
							else
								{
								UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
										  "'DBQ read PRI', and the current record " + DBQ_CurrRecordInQueryCycle  + " does not exist.");
								AbortAllSims();
								}
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". Input variable " + (i+1) + " is of type " +
									  "'DBQ read PRI', but the specified field does not exist.");
							AbortAllSims();
							}
						}
						
					else
						{
						UserError("A field has not yet been specified in row " + (i+1) + " of Equation Query block" + me + ".");
						AbortAllSims();
						}
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_START_RECORD)
					{
					if(DBQSR_OptionsChosen[i]  != DBQ_NOT_DEFINED)
						{
						iVars_Values[i] = DBQ_StartRecord;
						iVars_ValueWasFound[i] = TRUE;
						}
					else
						{
						UserError("There is a problem in Equation Query block" + me + ". Please contact Imagine That.");
						AbortAllSims();
						}
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_CURRENT_RECORD)
					{
					iVars_Values[i] = DBQ_CurrRecordInQueryCycle;
					iVars_ValueWasFound[i] = TRUE;
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_NUM_RECORDS)
					{
					iVars_Values[i] = DBQ_NumRecords;
					iVars_ValueWasFound[i] = TRUE;
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_CURR_BEST_RANK_RESULT)
					{
					iVars_Values[i] = DBQPT_CurrBestRankResult;
					iVars_ValueWasFound[i] = TRUE;
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQS_CURR_BEST_RANK_RESULT)
					{
					iVars_Values[i] = DBQS_CurrBestRankResult;
					iVars_ValueWasFound[i] = TRUE;
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS)
					{
					iVars_Values[i] = DBQPT_NumNonBlankRankedRecords;
					iVars_ValueWasFound[i] = TRUE;
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS)
					{
					iVars_Values[i] = DBQS_NumNonBlankRankedRecords;
					iVars_ValueWasFound[i] = TRUE;
					}
			
				else if(iVars_Types_Int[i] == EQ_DBQ_STATIC_QUERY_INIT)
					{
					//do nothing- static query vars were initialized at the start of the query in DBQ_DoQuery() and updated during EquationCalculateDynamicVariables()
					iVars_ValueWasFound[i] = TRUE;
					}
					
				}//for(i=0; i<iVars_NumTableRows; i++)
			
			}//if(itemIndex > 0)
				
		#ifdef EQ_IsQueryEquationItemBlock
		else
			{
			UserError("Trying to access an invalid itemIndex in Equation(I) block " + me + ".  Please contact Imagine That.");
			}
		#endif
			
	#endif //EQ_IsQueryEquationTypeBlock

	//conditionally update the table dynamically.
	if(iVars_TableIsCloned  ||  dialogIsOpen)
		{
		for(i=0; i<iVars_NumTableRows; i++)
			{
			//if(StrFind(iVars_Types_str[i], "attrib", FALSE, FALSE) > -1    &&  iVars_AttribTypes[i] == 2)		//AJN, 7.0.5, 10/24/08
			
			//if(iVars_AttribTypes[i] == ATTRIB_TYPE_STRING)	//6/19/09
			if(iVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE)
				{
				if(iVars_AttribTypes[i] == ATTRIB_TYPE_STRING)	
					iVars_ttbl[i][I_VAR_VALUE_COL] = SLStringGet(iVars_ttbl[i][I_VAR_NAME_COL], iVars_Values[i]);
				}
			
			//else if(iVars_AttribColumnIndexes[i] != EQ_DB_READ_VAL  &&  iVars_AttribColumnIndexes[i] != EQ_DB_READ_PRI  &&  iVars_AttribColumnIndexes[i] != EQ_DB_ADDRESS)	//6/19/09
			else if(iVars_Types_Int[i] != EQ_DB_READ_VAL  &&  iVars_Types_Int[i] != EQ_DB_READ_PRI  &&  iVars_Types_Int[i] != EQ_DB_ADDRESS)
				iVars_ttbl[i][I_VAR_VALUE_COL] = iVars_Values[i];
			}
		}
		
	if(updateCons)
		iVarsIn_ConLabelsSet();

	//make backup of input variable values before eq-calc is called
	for(i=0; i<iVars_NumTableRows; i++)
		iVars_BackupVals[i] = iVars_Values[i];
	
}//procedure iVars_GetVals(integer itemIndex)


//store iVars_VarIsWhichCon[] in iVars_VarIsWhichConOld[] before the user has made his new 
//choice. these soon to be "old" settings need to be stored so that we can auto reconnect iVarsIn.
procedure iVars_GetVarIsWhichConOld()
{
	integer i;
	integer numRows;
	
	numRows = GetDimension(iVars_VarIsWhichCon);
	
	for(i=0; i<numRows; i++)
		{
		iVars_VarIsWhichConOld[i] = iVars_VarIsWhichCon[i];
		}

}//procedure iVars_GetVarIsWhichConOld()


procedure iVars_ShowTypesPopup()
{

	integer i, j;
	integer varTypePopSize;
	integer found;
	integer placeFound;
	integer usersResponse;
	string theString;
	integer numChars;
	integer numIvarCons;
	string15 types;
	string15 typesPop;

	iVars_GetVarIsWhichConOld();		//take a "pre-snapshot" before user changes settings
	
	//if query type block, reset the DBQ options back to "undefined" for the row that was clicked any time 
	//the user clicks on the var types colum.  this makes auto-reconnecting the iVarsIn connectors much easier
	#ifdef EQ_IsQueryEquationTypeBlock
		DBQF_OptionsChosen[rowClicked] = DBQ_NOT_DEFINED;
		DBQFP_OptionsChosen[rowClicked] = DBQ_NOT_DEFINED;
		DBQSR_OptionsChosen[rowClicked] = DBQ_NOT_DEFINED;
	#endif

	//fill the iVars_TypesPop array
	iVars_GetVarTypes();
	varTypePopSize = EQ_GetVarPopSize(iVars_PopOptions);
	MakeArray(iVars_TypesPop, varTypePopSize);
	EQ_BuildVarTypesPopContentsArray(iVars_TypesPop, iVars_PopOptions);
	
	//figure out where the CURRENT chosen variable type resides in the iVars_TypesPop array.
	found = FALSE;
	placeFound = 0;
	for(i=0; i<varTypePopSize; i++)
		{
		if(StrFind(iVars_Types_str[rowClicked], iVars_TypesPop[i], FALSE, FALSE) >= 0)
			{
			found = TRUE;
			placeFound = i+1;
			break;
			}
		}
	
	//show the popup menu and record the response
	usersResponse = PopupMenuArray(iVars_TypesPop, placeFound);	//show the iVar types pop and record the user's response

	//if user chose a different type of input variable for rowClicked
	if(usersResponse != placeFound)
		{
	
		//save the user's response as a string- used to build the first column of iVars_ttbl
		iVars_Types_str[rowClicked] = iVars_TypesPop[usersResponse - 1];	//-1 for popup menu indexing
		
		//set attrib type to no attrib
		iVars_AttribTypes[rowClicked] = ATTRIB_TYPE_NO_ATTRIB;
		
		//save the user's response as an integer
		iVars_Types_Int[rowClicked] = EQ_VarTypeGet(iVars_Types_str[rowClicked]);
		
		//set up iVars_Names based on what the user chose in the types column
		if(iVars_Types_str[rowClicked] != "Connector")
			{
			//item info variables
			if(StrFind(iVars_Types_str[rowClicked], "attrib", FALSE, FALSE) >= 0)
				iVars_Names[rowClicked] = "None";
			else if(iVars_Types_str[rowClicked] == "Item quantity")
				iVars_Names[rowClicked] = "qtyIn_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "Item index")
				iVars_Names[rowClicked] = "itemIndex_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "Item priority")
				iVars_Names[rowClicked] = "priorityIn_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "Batch size")
				iVars_Names[rowClicked] = "batchSize_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "3D object ID")
				iVars_Names[rowClicked] = "3DIn_" + rowClicked;
			
			//DB variables
			else if(iVars_Types_str[rowClicked] == "DB read value")
				iVars_Names[rowClicked] = "DBRVIn_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DB read PRI")
				iVars_Names[rowClicked] = "DBRPRIIn_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DB address")
				iVars_Names[rowClicked] = "DBAIn_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DB database index")
				iVars_Names[rowClicked] = "DBIndex_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DB table index")
				iVars_Names[rowClicked] = "TIndex_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DB field index")
				iVars_Names[rowClicked] = "FIndex_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DB record index")
				iVars_Names[rowClicked] = "RIndex_" + rowClicked;

			//DBQ variables
			else if(iVars_Types_str[rowClicked] == "DBQ read value")
				iVars_Names[rowClicked] = "DBQF_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ read PRI")
				iVars_Names[rowClicked] = "DBQF_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ start record")
				iVars_Names[rowClicked] = "DBQSR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ current record index")
				iVars_Names[rowClicked] = "DBQCR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ num records")
				iVars_Names[rowClicked] = "DBQNumR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ current best record rank")
				iVars_Names[rowClicked] = "DBQPTBRR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQS current best rank result")
				iVars_Names[rowClicked] = "DBQSBRR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ num non-blank ranks")
				iVars_Names[rowClicked] = "DBQPTNNBRR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQS num non-blank ranks")
				iVars_Names[rowClicked] = "DBQSNNBRR_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "DBQ static query init")
				iVars_Names[rowClicked] = "SQI_" + rowClicked;

			//QEQ variables
			else if(iVars_Types_str[rowClicked] == "QEQ arrival time")
				iVars_Names[rowClicked] = "arriveTime_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "QEQ FIFO position")		//position of the current item before receiving a rank result
				iVars_Names[rowClicked] = "FIFO_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "QEQ current best item rank")	
				iVars_Names[rowClicked] = "currBest_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "QEQ num items in queue")
				iVars_Names[rowClicked] = "numItems_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "QEQ static calc cycle init")	
				iVars_Names[rowClicked] = "staticCycle_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "QEQ static item value")			//11/17/10
				iVars_Names[rowClicked] = "staticItemVal_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "QEQ halt calculation cycle")			  
				iVars_Names[rowClicked] = "haltCalc_" + rowClicked;

			//QEQ AR variables
			else if(iVars_Types_str[rowClicked] == "AR requirement is avail")	
				iVars_Names[rowClicked] = "arIsAvail" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "AR num requirements avail")	
				iVars_Names[rowClicked] = "arNumAvail" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "AR allocate requirement")	
				iVars_Names[rowClicked] = "arAllocate";
			
			//static variables
			else if(iVars_Types_str[rowClicked] == "Static first run init")
				iVars_Names[rowClicked] = "SFRI_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "Static multi run init")
				iVars_Names[rowClicked] = "SMRI_" + rowClicked;
			else if(iVars_Types_str[rowClicked] == "Static open model init")
				iVars_Names[rowClicked] = "SOMI_" + rowClicked;

			//4/16/11
			else if(iVars_Types_str[rowClicked] == "Next calc event time")
				iVars_Names[rowClicked] = "nextEventTime";

			//"_Num items entered" variables
			else if(iVars_Types_str[rowClicked] == "Num items entered")
				iVars_Names[rowClicked] = "NPI_" + rowClicked;
			
			//legacy
			else if(iVars_Types_str[rowClicked] == "_Select con")
				{
				UserError("There is a problem with " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
				AbortAllSims();
				}
	
			iVars_Values[rowClicked] = blank;
			}
			
		//do connector index accounting
		j = 0;
		for(i=0; i<iVars_NumTableRows; i++)
			{
			
			//first, try to rename the connector varNames and varTypes
			if(StrFind(iVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)	//it's a connector variable
				{
				//make sure the varType has the correct connector index
				iVars_Types_str[i] = "Connector " + j;
				
				//if using default var name, rename it with the correct connector index
				if(StrFind(iVars_Names[i], "inCon", FALSE, FALSE) != -1  ||  i == rowClicked)
					iVars_Names[i] = "inCon" + j;

				//if i = rowClicked, set the varValue to blank
				if(i == rowClicked)
					iVars_Values[i] = blank;

				j++;	//advance the connecor index
				}

			//second, store the appropriate connector index in DBQF_WhichConnector
			#ifdef EQ_IsQueryEquationTypeBlock
				
				else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
					{
					if(DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//it's a connector variable
						{
						DBQF_WhichConnector[i] = j;
						j++;							//advance the connecor index
						}
					else
						{
						DBQF_WhichConnector[i] = -1;
						}
					
					if(DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//it's a connector variable
						{
						DBQFP_WhichConnector[i] = j;
						j++;							//advance the connecor index
						}
					else
						{
						DBQFP_WhichConnector[i] = -1;
						}
					}
					
				else if(iVars_Types_str[i] == "DBQ start record")
					{
					if(DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
						{
						DBQSR_WhichConnector[i] = j;
						j++;
						}
					else
						{
						j++;
						}
					}
					
			#endif //EQ_IsQueryEquationTypeBlock
			
			}//for(i=0; i<iVars_NumTableRows; i++)

		iVarsIn_Reconnect(DIALOG_CLICK_VAR_TYPE);
		
		}//if(usersResponse != placeFound)
	
	DisposeArray(iVars_TypesPop);
	DisposeArray(iVars_PopOptions);

}//procedure iVars_ShowTypesPopup()


//**********************************************************************
//END "iVars" Functions
//**********************************************************************
//**********************************************************************




//******************************************************************
//******************************************************************
//START iVarsIn_ Functions
//******************************************************************


//this function makes sure that the input connectors have been managed properly.
//this function can only be called during CHECKDATA!
procedure iVarsIn_CheckConInputs()
{
	
	integer	i, j;
	string varName;
	integer whichCon;
	integer conIsConnected;
	integer conUsedInEq;
	integer numChars;

	for(i=0; i<iVarsIn_NumCons; i++)
		{
		
		for(j=0; j<iVars_NumTableRows; j++)
			{
			
			//if(StrPart(iVars_Types_str[j], 0, 10) == "Connector")		//AJN, 7.0.5, 10/24/08
			if(iVars_Types_Int[j] == EQ_CONNECTORS)		//if we have a connector variable
				{
				
				//find out which connector was selected in this row
				numChars = StrLen(iVars_Types_str[j]);
				whichCon = StrToReal(StrPart(iVars_Types_str[j], 10, numChars));
				
				if(whichCon == i)
					{
					varName = iVars_Names[j];
					conUsedInEq = StrFindDynamic(EQ_EquationText, varName, FALSE, FALSE, TRUE);
					
					if(conUsedInEq == -1  &&  iVarsIn_NumBlocksConnected[i] >= 1)
						{
						UserError("Input connector " + i + " is connected, but it is not used in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".");
						AbortAllSims();
						}
					
					if(conUsedInEq > -1  &&  iVarsIn_NumBlocksConnected[i] < 1)
						{
						UserError("Input connector " + i + " is not connected, but it is used in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".");
						AbortAllSims();
						}
					}
				
				}//if(StrPart(iVars_Types_str[j], 0, 10) == "Connector")

			}//for(j=0; j<iVars_NumTableRows; j++)
			
		}//for(i=0; i<iVarsIn_NumCons; i++)

}//integer iVarsIn_CheckConInputs()


#ifdef EQ_IsValueBlock

procedure iVarsIn_SendMsgs(integer calledFrom)
{

	integer i;
	integer whichCon;

	//conditionally send oVarsOut msgs
	if(EQ_Calcing == TRUE)
		{
		return;
		}
	
	if(!CMC_chk)
		{
		//NOTE: if(!CMC_chk), then connector messaging behavior is exactly like message emulation
		for(i=0; i<iVarsIn_NumCons; i++)
			{
			if(iVarsIn_NumBlocksConnected[i] >= 1)
				{
				if(calledFrom == MSG_RECEIVED_FROM_IVARS_IN  ||  calledFrom == MSG_RECEIVED_FROM_OVARS_OUT)
					{
					//if(iVarsIn_MsgEverReceived[i] == FALSE)
					if(iVarsIn_MsgEverReceived[i] == FALSE  ||  calledFrom == MSG_RECEIVED_FROM_OVARS_OUT)	//10/28/10
						{
						SendMsgToOutputs(iVarsIn_ConNums[i]);
						}
					}
				else
					{
					SendMsgToOutputs(iVarsIn_ConNums[i]);
					}
				}
			}
		}
	
	else //if(CMC_chk)
		{
		if(calledFrom == MSG_RECEIVED_FROM_IVARS_IN)
			{
			whichCon = ConArrayMsgFromCon();
		
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				if(iVarsIn_NumBlocksConnected[i] >= 1  &&  i != whichCon)
					{
					if
					  (
						(CMC_IVarsIn_Settings[i] == CMC_IVAR_ALWAYS)  ||  
						(CMC_IVarsIn_Settings[i] == CMC_IVAR_MSG_EMULATION  &&  iVarsIn_MsgEverReceived[i] == FALSE)
					  )
						{
						SendMsgToOutputs(iVarsIn_ConNums[i]);
						}
					}
				}
			}
			
		else if(calledFrom == MSG_RECEIVED_FROM_OVARS_OUT)
			{
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				if(iVarsIn_NumBlocksConnected[i] >= 1)
					{
					if
					  (
						(CMC_IVarsIn_Settings[i] == CMC_IVAR_ALWAYS)  ||  
						(CMC_IVarsIn_Settings[i] == CMC_IVAR_MSG_EMULATION  &&  iVarsIn_MsgEverReceived[i] == FALSE)
					  )
						{
						SendMsgToOutputs(iVarsIn_ConNums[i]);
						}
					}
				}
			}
		
		else
			{
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				if(iVarsIn_NumBlocksConnected[i] >= 1)
					{
					if(CMC_IVarsIn_Settings[i] != CMC_IVAR_NEVER)
						{
						SendMsgToOutputs(iVarsIn_ConNums[i]);
						}
					}
				}
			}
		}

}//procedure iVarsIn_SendMsgs(integer calledFrom)

#endif //EQ_IsValueBlock



#ifdef EQ_IsValueBlock
/*
procedure iVarsIn_OnIVarsIn()
{

	integer i;
	//integer whichCon;					//3/25/10
	
	//whichCon = ConArrayMsgFromCon();	//3/25/10
	iVarsIn_WhichConGotMsg = ConArrayMsgFromCon();	//3/25/10
	
	iVarsIn_MsgEverReceived[iVarsIn_WhichConGotMsg] = TRUE;
	
	if(inIVarsIn == TRUE  ||  inOVarsOut == TRUE  ||  inGoIn == TRUE  ||  inLinkContent == TRUE  ||  inBlockReceive1 == TRUE  ||  inPostInitSim == TRUE    ||  inFinalCalc == TRUE)
		{
		return;
		}
	else
		{
		inIVarsIn = TRUE;
		}
	
	if(CW_IVarsIn_CalcControl_chk == TRUE)
		{
		
		if(CW_IVarsIn_WhichConnector == -1  ||  iVarsIn_WhichConGotMsg == CW_IVarsIn_WhichConnector)	//-1 if the  "respond to any connecter msg" option was chosen
			{
			if(CW_IVarsIn_RespondWhen_pop == WHEN_CALC_IMMEDIATE)
				{
				//iVarsIn msgs
				iVarsIn_SendMsgs(MSG_RECEIVED_FROM_IVARS_IN);

				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);			//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
				
				#ifdef EQ_IsQueryEquationValueBlock
					DBQ_DoQuery(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif

				//oVarsOut msgs
				oVarsOut_SendMsgs(MSG_RECEIVED_FROM_IVARS_IN);

				//post this block's next event
				if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
					{
					nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
					timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
					lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
					}
				}
			else //if(CW_IVarsIn_RespondWhen_pop == WHEN_CALC_CURRENT_EVENT)
				{
			  	//post current event
			  	if(!rescheduled)
			  		{
					rescheduled = TRUE;
					SysGlobalInt8 = MyBlockNumber();
					SendMsgToBlock(exec,BLOCKRECEIVE3MSG);		//schedules a BlockReceive0 current event
					}
				}
			}
		
		}//if(CW_IVarsIn_CalcControl_chk == TRUE)
	
	TCE_TraceConnectors();

	iVarsIn_WhichConGotMsg = -1;	//3/25/10
	inIVarsIn = FALSE;

}//procedure iVarsIn_OnIVarsIn()
*/
#endif //EQ_IsValueBlock


procedure iVarsIn_ConLabelsSet()
{

	integer i;
	string addString;
	integer iconView;
	string side;
	real conVal;
	integer whichCon;
	integer me;
	integer simPhase;
	
	me = MyBlockNumber();
	simPhase = GetSimulationPhase();


	//7/19/10
	if(!iVars_ShowConNames_chk  &&  !iVars_ShowConVals_chk)
		{
		if(simPhase == PHASE_NOT_CURRENTLY_RUNNING)
			{
			MakeArray(iVarsIn_ConnectorLabels, iVarsIn_NumCons);			
	
			//blank out labels
			for(i=0; i<iVarsIn_NumCons; i++)
				iVarsIn_ConnectorLabels[i] = "";
	
			ConnectorLabelsSet(me, ConArrayGetConNumber(me, "iVarsIn", 0), iVarsIn_NumCons, iVarsIn_ConnectorLabels, BOTTOM_SIDE, 0, 0, 0);
	
			DisposeArray(iVarsIn_ConnectorLabels);
			}
		}

	else
		{		

		//7/19/10
		if(simPhase == PHASE_NOT_CURRENTLY_RUNNING  ||  GetDimension(iVarsIn_ConnectorLabels) != iVarsIn_NumCons)
			{
			//7/19/10:  setup the iVarsIn_ConnectorLabels[] array
			if(iVars_ShowConNames_chk  ||  iVars_ShowConVals_chk)
				{
				iconView = IconGetView(me);
			
				if(iconView == 0)						//where 0 = "Left to right"
					side = "<l>";
				else
					side = "<r>";
			
				MakeArray(iVarsIn_ConnectorLabels, iVarsIn_NumCons);
				for(i=0; i<iVarsIn_NumCons; i++)
					{
					iVarsIn_ConnectorLabels[i] = side;
					}
				}
	
			//7/19/10:  add the connector names to iVarsIn_ConnectorLabels[] array
			if(iVars_ShowConNames_chk)
				{
				for(i=0; i<iVars_NumTableRows; i++)
					{
					#ifdef EQ_IsQueryEquationTypeBlock
					if( iVars_Types_Int[i] == EQ_CONNECTORS  ||  
						(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)  ||  
						(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)   ||  
						(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)  ||  
						(iVars_Types_Int[i] == EQ_DBQ_START_RECORD  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR) )
					#else
					if(iVars_Types_Int[i] == EQ_CONNECTORS)
					#endif
						{
						//add var name to iVarsIn_ConnectorLabels[]
						whichCon = iVars_VarIsWhichCon[i];
						iVarsIn_ConnectorLabels[whichCon] += iVars_Names[i];
						
						#ifdef EQ_IsQueryEquationTypeBlock
							//if one row in the table has two connector variables, then...
							if(
								iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR  &&
								iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR
							  )
								{
								//...we have to add the second connector name to the labels
								whichCon = iVars_VarIsWhichCon[i]+1;
									//NOTE: "+1" b/ here we have 2 connectors associated with just one row in 
									//iVars_ttbl and b/ the number of rows in iVars_VarIsWhichCon[] = iVars_NumTableRows
								
								iVarsIn_ConnectorLabels[whichCon] += iVars_Names[i];	
									//NOTE: use "+1" b/ here we have 2 connectors associated with just one row in 
									//iVars_ttbl and b/ the number of rows in iVars_VarIsWhichCon[] = iVars_NumTableRows
								}
						#endif
						}
					}
			
				//animate the iVars
				ConnectorLabelsSet(me, ConArrayGetConNumber(me, "iVarsIn", 0), iVarsIn_NumCons, iVarsIn_ConnectorLabels, BOTTOM_SIDE, 0, 0, 0);
				}
			}
	
		//else if(iVars_ShowConVals_chk)			//7/19/10
		if(iVars_ShowConVals_chk)				
			{
			MakeArray(iVarsIn_ConnectorLabelsTemp, iVarsIn_NumCons);

			for(i=0; i<iVars_NumTableRows; i++)
				{
				#ifdef EQ_IsQueryEquationTypeBlock
				if( iVars_Types_Int[i] == EQ_CONNECTORS  ||  
					(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)  ||  
					(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)   ||  
					(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)  ||  
					(iVars_Types_Int[i] == EQ_DBQ_START_RECORD  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR) )
				#else
				if(iVars_Types_Int[i] == EQ_CONNECTORS)
				#endif
					{
					//determine which connector we are referencing
					whichCon = iVars_VarIsWhichCon[i];
				
					//get connector value for the next connector
					conVal = ConArrayGetValue(iVarsIn, whichCon);
	
					//set label
					if(iVars_ShowConNames_chk)
						iVarsIn_ConnectorLabelsTemp[whichCon] = iVarsIn_ConnectorLabels[whichCon] + " = " + conVal;
					else
						iVarsIn_ConnectorLabelsTemp[whichCon] = iVarsIn_ConnectorLabels[whichCon] + conVal + " = ";
					
					#ifdef EQ_IsQueryEquationTypeBlock
						//if one row in the table has two connector variables, then...
						if(iVars_Types_str[i] == "DBQ read PRI"  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR  &&
						   iVars_Types_str[i] == "DBQ read PRI"  &&  DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)
						   {
						   //...we have to add the second connector info to the labels
						   whichCon = iVars_VarIsWhichCon[i]+1;
								//NOTE: "+1" b/ here we have 2 connectors associated with just one row in 
								//iVars_ttbl and b/ the number of rows in iVars_VarIsWhichCon[] = iVars_NumTableRows
						   
						   conVal = ConArrayGetValue(iVarsIn, whichCon);
	
							//set label
							if(iVars_ShowConNames_chk)
								iVarsIn_ConnectorLabelsTemp[whichCon] = iVarsIn_ConnectorLabels[whichCon] + " = " + conVal;
							else
								iVarsIn_ConnectorLabelsTemp[whichCon] = iVarsIn_ConnectorLabels[whichCon] + conVal + " = ";
						   }
					#endif
					}
				}
		
			//animate the iVars
			ConnectorLabelsSet(me, ConArrayGetConNumber(me, "iVarsIn", 0), iVarsIn_NumCons, iVarsIn_ConnectorLabelsTemp, BOTTOM_SIDE, 0, 0, 0);
			
			DisposeArray(iVarsIn_ConnectorLabelsTemp);	//7/19/10
			}
	
		}
	
}//procedure iVarsIn_ConLabelsSet()


procedure iVarsIn_ConnectorsSetup()
{

	integer i;
	integer showCon;
	integer numCons;
	
	//calc numCons and calc show/hide status
	numCons = 0;
	for(i=0; i<iVars_NumTableRows; i++)
		{
		//if(StrFind(iVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
		if(iVars_Types_Int[i] == EQ_CONNECTORS)
			{
			numCons++;
			}
		#ifdef EQ_IsQueryEquationTypeBlock
			//else if(iVars_Types_str[i] == "DBQ start record"  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)	//AJN, 7.0.5, 10/24/08
			else if(iVars_Types_Int[i] == EQ_DBQ_START_RECORD  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
				{
				numCons++;
				}
			//else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")	//AJN, 7.0.5, 10/24/08
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  ||  iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI)
				{
				if(DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					numCons++;
					}
				if(DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					numCons++;
					}
				}
		#endif
		}
	if(numCons >= 1)
		{
		showCon = TRUE;
		}
	else //if(numCons == 0)
		{
		showCon = FALSE;
		numCons = 1;		//always need at least one connector
		}
	
	//set num connectors
	iVarsIn_NumConsOld = iVarsIn_NumCons;
	iVarsIn_NumCons = numCons;
	ConArraySetNumCons(MyBlockNumber(), "iVarsIn", iVarsIn_NumCons, TRUE);
	
	//setup connector arrays and get connector info
	MakeArray(iVarsIn_NumBlocksConnected, iVarsIn_NumCons);
	MakeArray(iVarsIn_ConNums, iVarsIn_NumCons);
	for(i=0; i<iVarsIn_NumCons; i++)									
		{
		iVarsIn_ConNums[i] = ConArrayGetConNumber(MyBlockNumber(), "iVarsIn", i);
		iVarsIn_NumBlocksConnected[i] = GetConBlocks(MyBlockNumber(), iVarsIn_ConNums[i], connected);
		}
		
	//show/hide oVarsOut
	if(showCon == TRUE)
		SetConVisibility(MyBlockNumber(), iVarsIn_ConNums[0], TRUE);
	else
		SetConVisibility(MyBlockNumber(), iVarsIn_ConNums[0], FALSE);
		
	iVarsIn_VarIsWhichConUpdate();
	iVarsIn_ConIsWhichVarUpdate();	//12/16/08	7.0.5	AJN

	DisposeArray(connected);
		
}//procedure iVarsIn_ConnectorsSetup()


//called in iVarsIn_Reconnect only!  into the "old" connector arrays, store the state of the connectors before connection are deleted.
procedure iVarsIn_GetOldConInfo()
{

	integer i;
	integer nextCon;

	MakeArray(iVarsIn_ConnectedBlocksOld, iVarsIn_NumCons);
	MakeArray(iVarsIn_ConnectedConsOld, iVarsIn_NumCons);
	MakeArray(iVarsIn_TextBlockNums, iVarsIn_NumCons);

	//initialize the con info arrays
	for(i=0; i<iVarsIn_NumCons; i++)
		{
		iVarsIn_ConnectedBlocksOld[i] = -1;
		iVarsIn_ConnectedConsOld[i] = -1;
		}

	//get data about the connection to iVarsIn
	for(i=0; i<iVarsIn_NumCons; i++)
		{
		
		//get connected block info
		nextCon = ConArrayGetConNumber(MyBlockNumber(), "iVarsIn", i);
		iVarsIn_NumBlocksConnected[i] = GetConBlocks(MyBlockNumber(), nextCon, connected);
		iVarsIn_TextBlockNums[i] = GetConnectedTextBlock(MyBlockNumber(), iVarsIn_ConNums[i]);	//is conn is connected to a TEXT block?
		
		//if connector is connected to a TEXT block
		if(iVarsIn_TextBlockNums[i] >= 0)
			{
			iVarsIn_ConnectedBlocksOld[i] = iVarsIn_TextBlockNums[i];
			iVarsIn_ConnectedConsOld[i] = -1;
			}
		
		//if conn is connected to another conn
		else if(iVarsIn_NumBlocksConnected[i] >= 1)
			{
			iVarsIn_ConnectedBlocksOld[i] = connected[0][0];
			iVarsIn_ConnectedConsOld[i] = connected[0][1];
			}
		
		}

	DisposeArray(connected);

}//procedure iVarsIn_GetOldConInfo()


//called in iVarsIn_Reconnect only!  after connections have been deleted, reset connector info.
procedure iVarsIn_GetNewConInfo(integer calledFrom)
{
	
	integer i;
	string conVarName;
	integer conChange;
	integer firstAddedCon;
	integer lastAddedCon;
	integer firstDeletedCon;
	integer lastDeletedCon;
	integer oldNumCons;

	//dimension the con info arrays
	MakeArray(iVarsIn_ConnectedBlocks, iVarsIn_NumCons);
	MakeArray(iVarsIn_ConnectedCons, iVarsIn_NumCons);
	for(i=0; i<iVarsIn_NumCons; i++)
		{
		iVarsIn_ConnectedBlocks[i] = -1;
		iVarsIn_ConnectedCons[i] = -1;
		}

	conChange = iVarsIn_NumCons - iVarsIn_NumConsOld;

	//if the number of connectors did not change
	if(conChange == 0)
		{
		for(i=0; i<iVarsIn_NumCons; i++)
			{
			iVarsIn_ConnectedBlocks[i] = iVarsIn_ConnectedBlocksOld[i];
			iVarsIn_ConnectedCons[i] = iVarsIn_ConnectedConsOld[i];
			}
		}
	
	//if num connectors grew...
	else if(conChange > 0)
		{
		if(calledFrom == DIALOG_CLICK_VAR_TYPE)
			{
			firstAddedCon = iVars_VarIsWhichCon[rowClicked];
			}
		else //if(calledFrom == DATA_TABLE_RESIZE)
			{
			firstAddedCon = iVars_VarIsWhichCon[rowClicked+1];
			}
		lastAddedCon = firstAddedCon + conChange - 1;
		
		//if(iVarsIn_NumCons > 1)									//4/21/09
		if(iVarsIn_NumCons > 1  &&  firstAddedCon >= 0)		//this is a ">" not a ">=" because if going from zero to one con var, then there are no connections to remake
			{
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				if(i < firstAddedCon)
					{
					iVarsIn_ConnectedBlocks[i] = iVarsIn_ConnectedBlocksOld[i];
					iVarsIn_ConnectedCons[i] = iVarsIn_ConnectedConsOld[i];
					}
			
				else if(i >= firstAddedCon  &&  i <= lastAddedCon)
					{
					iVarsIn_ConnectedBlocks[i] = -1;
					iVarsIn_ConnectedCons[i] = -1;
					}
			
				else if(i > lastAddedCon)
					{
					iVarsIn_ConnectedBlocks[i] = iVarsIn_ConnectedBlocksOld[i-conChange];
					iVarsIn_ConnectedCons[i] = iVarsIn_ConnectedConsOld[i-conChange];
					}
				}
			}
		}
		
	//if num connectors shrunk...
	else if(conChange < 0)
		{
		oldNumCons = GetDimension(iVarsIn_ConnectedBlocksOld);
		firstDeletedCon = iVars_VarIsWhichConOld[rowClicked];
		lastDeletedCon = firstDeletedCon - conChange - 1;
			
		//if(iVarsIn_NumConsOld > 1)								//4/21/09
		if(iVarsIn_NumConsOld > 1  &&  firstDeletedCon >= 0)	//this is a ">" not a ">=" because if going from one to zero con vars, then there are no connectios to remake
			{
			for(i=0; i<oldNumCons; i++)
				{
				if(i < firstDeletedCon)
					{
					iVarsIn_ConnectedBlocks[i] = iVarsIn_ConnectedBlocksOld[i];
					iVarsIn_ConnectedCons[i] = iVarsIn_ConnectedConsOld[i];
					}
					
				else if(i > lastDeletedCon)
					{
					iVarsIn_ConnectedBlocks[i+conChange] = iVarsIn_ConnectedBlocksOld[i];
					iVarsIn_ConnectedCons[i+conChange] = iVarsIn_ConnectedConsOld[i];
					}
				}
			}
		}
			
}//procedure iVarsIn_GetNewConInfo()


//called in iVars_ShowTypesPop, this function reconnects iVarsIn connectors where needed
procedure iVarsIn_Reconnect(integer calledFrom)
{

	integer i, j;
	integer newWhichCon;
	integer oldWhichCon;
	integer nextCon;
	integer numConnections;
	integer blockType;
	integer blockTypeArray[4];

	iVars_GetVarIsWhichConOld();						//make sure "old" array is filled out correctly before fiddeling with the connector arrays
	iVarsIn_GetOldConInfo();
	
	//delete all connections to iVarsIn	
	for(i=0; i<iVarsIn_NumCons; i++)
		{
		nextCon = ConArrayGetConNumber(MyBlockNumber(), "iVarsIn", i);
		numConnections = GetConBlocks(MyBlockNumber(), nextCon, connected);
		if(numConnections > 0)
			{
			blockType = GetBlockTypePosition(iVarsIn_ConnectedBlocksOld[i], blockTypeArray);

			//if connected block is a TEXT block, ie, if have a named connection
			if(blockType == 2)
				ClearConnection(MyBlockNumber(), iVarsIn_ConNums[i], iVarsIn_ConnectedBlocksOld[i], 0);
			else
				ClearConnection(MyBlockNumber(), iVarsIn_ConNums[i], iVarsIn_ConnectedBlocksOld[i], iVarsIn_ConnectedConsOld[i]);
			}
		}

	iVarsIn_ConnectorsSetup();		//reset the number of connectors
	iVarsIn_GetNewConInfo(calledFrom);	

	//reconnect the iVarsIn cons based on the new "con block info" arrays
	for(i=0; i<iVarsIn_NumCons; i++)
		{
		if(iVarsIn_ConnectedBlocks[i] != -1)	//if connector should be connected
			{
			blockType = GetBlockTypePosition(iVarsIn_ConnectedBlocks[i], blockTypeArray);
			
			//if connected block is a TEXT block, ie, if have a named connection
			if(blockType == 2)
				MakeConnection(MyBlockNumber(), iVarsIn_ConNums[i], iVarsIn_ConnectedBlocks[i], 0);
				
			else //if connected to a connector on an executable block
				MakeConnection(MyBlockNumber(), iVarsIn_ConNums[i], iVarsIn_ConnectedBlocks[i], iVarsIn_ConnectedCons[i]);
			}
		}

	DisposeArray(iVarsIn_ConnectedBlocksOld);
	DisposeArray(iVarsIn_ConnectedConsOld);
	DisposeArray(iVarsIn_ConnectedBlocks);
	DisposeArray(iVarsIn_ConnectedCons);
	DisposeArray(iVarsIn_TextBlockNums);

}//procedure iVarsIn_Reconnect()


//this function fills out iVars_VarIsWhichCon
procedure iVarsIn_VarIsWhichConUpdate()
{
	integer i;
	integer	conNameLength;

	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_CONNECTORS)
			{
			conNameLength = StrLen(iVars_Types_str[i]);
			iVars_VarIsWhichCon[i] = StrToReal(StrPart(iVars_Types_str[i], 10, conNameLength));
			}
		
		#ifdef EQ_IsQueryEquationTypeBlock
			else if(iVars_Types_Int[i] == EQ_DBQ_START_RECORD  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
				{
				iVars_VarIsWhichCon[i] = DBQSR_WhichConnector[i];
				}
				
			//NOTE:  tricky code b/ we have only one row in the table even if both DBQF and DBQFP are using a connector
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  &&  DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)
				{
				iVars_VarIsWhichCon[i] = DBQF_WhichConnector[i];
				}
//			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  &&  DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI  &&  DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)
				{
				iVars_VarIsWhichCon[i] = DBQFP_WhichConnector[i];
				}
		#endif
		
		else
			iVars_VarIsWhichCon[i] = -1;
		}
				
}//procedure iVarsIn_VarIsWhichConUpdate()			


procedure iVarsIn_ConIsWhichVarUpdate()
{

	integer i, j;

	//initialize iVars_ConIsWhichVar
	MakeArray(iVars_ConIsWhichVar, iVarsIn_NumCons);
	for(i=0; i<iVarsIn_NumCons; i++)
		iVars_ConIsWhichVar[i] = -1;

	//fill out the "iVars_ConIsWhichVar" array
	j = 0;												//j is the next iVarsIn connector
	for(i=0; i<iVars_NumTableRows; i++)					//i is the next row in the attribs table
		{
		//AJN, 7.0.5, 10/24/05
		//if(StrFind(iVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
		if(iVars_Types_Int[i] == EQ_CONNECTORS)
			{
			iVars_ConIsWhichVar[j] = i;
			j++;
			}
			
		#ifdef EQ_IsQueryEquationTypeBlock
			//AJN, 7.0.5, 10/24/05
			//else if(iVars_Types_str[i] == "DBQ start record"  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
			else if(iVars_Types_Int[i] == EQ_DBQ_START_RECORD  &&  DBQSR_OptionsChosen[i] == DBQ_USE_CONNECTOR)
				{
				iVars_ConIsWhichVar[j] = i;
				j++;
				}
				
			//AJN, 7.0.5, 10/24/05
			//else if(iVars_Types_str[i] == "DBQ read value"  ||  iVars_Types_str[i] == "DBQ read PRI")
			else if(iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_VALUE  ||  iVars_Types_Int[i] == EQ_DBQ_QUERY_FIELD_PRI)
				{
				if(DBQF_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					iVars_ConIsWhichVar[j] = i;
					j++;
					}
				if(DBQFP_OptionsChosen[i] == DBQ_USE_CONNECTOR)
					{
					iVars_ConIsWhichVar[j] = i;
					j++;
					}
				}
		#endif
		}

}//procedure iVarsIn_ConIsWhichVarUpdate()


//******************************************************************
//END iVarsIn_ FUNCTIONS
//******************************************************************
//******************************************************************




//******************************************************************
//******************************************************************
//START iVars_DBNT Functions
//******************************************************************


procedure iVars_DBNT_AddElement(real dbAddress, integer whichRowInTable)
{

	integer i;
	integer me;
	integer dbIndex;
	string63 dbName;
	integer tableIndex;
	string63 tableName;
	integer fieldIndex;
	integer recordIDFieldIndex;
	string63 fieldName;
	integer recordIndex;
	string63 recordName;
	integer whichElement;
	integer currRow;
	integer whichCol;
	integer numElements;
	integer iVars_DBNameTrackingListIndex;
	
	
	integer listSetReturnCode;
	
	
	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);

	//if the iVars db name tracking lists doesn't exist, create it
	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	if(iVars_DBNameTrackingListIndex < 0)
		{
		iVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			//1 long field
			//2 sets sort type as integer
			//DBNT_WHICH_ROW_IN_TABLE_FIELD sets sort field
		ListLocked(me, iVars_DBNameTrackingListIndex, TRUE);
		ListAddString63s(me, iVars_DBNameTrackingListIndex, 4);
		ListSetName(me, iVars_DBNameTrackingListIndex, DBNT_IVARS_LIST_NAME);
		}
	
	//AJN, 7.0.5, 10/24/08
	//if(iVars_Types_str[whichRowInTable] == "DB read value"  ||  iVars_Types_str[whichRowInTable] == "DB read PRI"  ||  iVars_Types_str[whichRowInTable] == "DB address"  ||  iVars_Types_str[whichRowInTable] == "_DB index")
	//if(iVars_Types_Int[whichRowInTable] == EQ_DB_READ_VAL  ||  iVars_Types_Int[whichRowInTable] == EQ_DB_READ_PRI  ||  iVars_Types_Int[whichRowInTable] == EQ_DB_ADDRESS  ||  iVars_Types_Int[whichRowInTable] == EQ_DB_INDEX)	//6/25/09
	if(
	   iVars_Types_Int[whichRowInTable] == EQ_DB_READ_VAL  ||  
	   iVars_Types_Int[whichRowInTable] == EQ_DB_READ_PRI  ||  
	   iVars_Types_Int[whichRowInTable] == EQ_DB_ADDRESS  ||  
	   iVars_Types_Int[whichRowInTable] == EQ_DB_DATABASE_INDEX  ||
	   iVars_Types_Int[whichRowInTable] == EQ_DB_TABLE_INDEX  ||
	   iVars_Types_Int[whichRowInTable] == EQ_DB_FIELD_INDEX  ||
	   iVars_Types_Int[whichRowInTable] == EQ_DB_RECORD_INDEX
	  )
		{
		
		//is an element already associated with whichRowInTable?
		whichElement = -1;
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			currRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			
			if(currRow == whichRowInTable)
				{
				whichElement = i;
				break;
				}
			}
		
		if(whichElement == -1)
			ListCreateElement(me, iVars_DBNameTrackingListIndex);
		
		//add the "whichRowInTable" field to the element
		ListSetLong(me, iVars_DBNameTrackingListIndex, whichElement, DBNT_WHICH_ROW_IN_TABLE_FIELD, whichRowInTable);
		
		//add the "dbName" to the element
		dbIndex = DBDatabaseGetIndexFromAddress(dbAddress);
		if(dbIndex >= 1)
			dbName = DBDatabaseGetName(dbIndex);
		else
			dbName = "";
		listSetReturnCode = ListSetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_DB_NAME_FIELD, dbName);	//6 for string63
		
		//add the "tableName" to the element
		tableIndex = DBTableGetIndexFromAddress(dbAddress);
		if(tableIndex >= 1)
			tableName = DBTableGetName(dbIndex, tableIndex);
		else
			tableName = "";
		listSetReturnCode = ListSetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_TABLE_NAME_FIELD, tableName);	//6 for string63
		
		//add the "fieldName" to the element
		fieldIndex = DBFieldGetIndexFromAddress(dbAddress);
		if(fieldIndex >= 1)
			fieldName = DBFieldGetName(dbIndex, tableIndex, fieldIndex);
		else
			fieldName = "";
		listSetReturnCode = ListSetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_FIELD_NAME_FIELD, fieldName);	//6 for string63
		
		//add the "recordName" to the element
		recordIndex = DBRecordGetIndexFromAddress(dbAddress);
		if(recordIndex >= 1)
			{
			recordIDFieldIndex = DBRecordIDFieldGetIndex(dbIndex, tableIndex);
			if(recordIDFieldIndex >= 1)
				{
				recordName = DBDataGetAsString(dbIndex, tableIndex, recordIDFieldIndex, recordIndex);
				}
			else
				recordName = "";
			}
		else
			recordName = "";
		listSetReturnCode = ListSetString(me, iVars_DBNameTrackingListIndex, whichElement, 6, DBNT_RECORD_NAME_FIELD, recordName);	//6 for string63
		
		//add new elemnt to the "iVars_DBNameTrackingList" linked list
		if(whichElement == -1)
			ListAddElement(me, iVars_DBNameTrackingListIndex, -2);	//2 for added in a sorted fashion
		}

}//procedure iVars_DBNT_AddElement(real dbAddress, integer whichRowInTable)


//6/15/11
procedure iVars_DBNT_DeleteElement(integer whichRowInTable)
{

	integer i;
	integer me;
	integer dbIndex;
	string63 dbName;
	integer tableIndex;
	string63 tableName;
	integer fieldIndex;
	integer recordIDFieldIndex;
	string63 fieldName;
	integer recordIndex;
	string63 recordName;
	integer whichElement;
	integer currRow;
	integer whichCol;
	integer numElements;
	integer iVars_DBNameTrackingListIndex;
	
	
	integer listSetReturnCode;
	
	
	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);

	//if the iVars db name tracking lists doesn't exist, create it
	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	if(iVars_DBNameTrackingListIndex < 0)
		{
		iVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			//1 long field
			//2 sets sort type as integer
			//DBNT_WHICH_ROW_IN_TABLE_FIELD sets sort field
		ListLocked(me, iVars_DBNameTrackingListIndex, TRUE);
		ListAddString63s(me, iVars_DBNameTrackingListIndex, 4);
		ListSetName(me, iVars_DBNameTrackingListIndex, DBNT_IVARS_LIST_NAME);
		}
	
	if(
	   iVars_Types_Int[whichRowInTable] == EQ_DB_READ_VAL  ||  
	   iVars_Types_Int[whichRowInTable] == EQ_DB_READ_PRI  ||  
	   iVars_Types_Int[whichRowInTable] == EQ_DB_ADDRESS  ||  
	   iVars_Types_Int[whichRowInTable] == EQ_DB_DATABASE_INDEX  ||
	   iVars_Types_Int[whichRowInTable] == EQ_DB_TABLE_INDEX  ||
	   iVars_Types_Int[whichRowInTable] == EQ_DB_FIELD_INDEX  ||
	   iVars_Types_Int[whichRowInTable] == EQ_DB_RECORD_INDEX
	  )
		{
		//find which element in list to delete
		whichElement = -1;
		numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			currRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			
			if(currRow == whichRowInTable)
				{
				whichElement = i;
				break;
				}
			}
		
		if(whichElement >= 0)
			{
			ListDeleteElement(me, iVars_DBNameTrackingListIndex, whichElement);			
			}
			
		else //if can't find link in list to delete
			{
			//do nothing
			}
		}

}//procedure iVars_DBNT_DeleteElement(integer whichRowInTable)


//caled in EQ_OnDataTableResize(), EQ_OnOpenModel(), and on iVars_ttbl. 
//removes unwanted elements from iVars_DBNameTrackingListIndex
procedure iVars_DBNT_GarbageCollection()
{
	
	integer i;
	integer me;
	integer targetElement;
	integer whichVarRow;
	integer numElements;
	integer searchArray[2][2];	//col 0 = search field, col 1 = search value
	integer iVars_DBNameTrackingListIndex;

	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	
	//first, cycle through all rows in iVars table
	for(i=0; i<iVars_NumTableRows; i++)
		{
		//if(iVars_Types_str[i] != "DB read value"  &&  iVars_Types_str[i] != "DB read PRI"  &&  iVars_Types_str[i] != "DB address"  &&  iVars_Types_str[i] != "_DB index")	//AJN, 7.0.5, 10/24/08
		//if(iVars_Types_Int[i] != EQ_DB_READ_VAL  &&  iVars_Types_Int[i] != EQ_DB_READ_PRI  &&  iVars_Types_Int[i] != EQ_DB_ADDRESS  &&  iVars_Types_Int[i] != EQ_DB_INDEX)	//6/25/09
		if(
		   iVars_Types_Int[i] != EQ_DB_READ_VAL  &&  
		   iVars_Types_Int[i] != EQ_DB_READ_PRI  && 
		   iVars_Types_Int[i] != EQ_DB_ADDRESS  &&  
		   iVars_Types_Int[i] != EQ_DB_DATABASE_INDEX  &&
		   iVars_Types_Int[i] != EQ_DB_TABLE_INDEX  &&
		   iVars_Types_Int[i] != EQ_DB_FIELD_INDEX  &&
		   iVars_Types_Int[i] != EQ_DB_RECORD_INDEX 
		  )
			{
			targetElement = 0;
			while(targetElement >= 0)
				{
				targetElement = ListSearch(me, iVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, i, 0.0, "", 0);
				if(targetElement >= 0)
					{
					ListDeleteElement(me, iVars_DBNameTrackingListIndex, targetElement);
					}
				}
			}
		}
		
	//second, cycle through all elements in iVars_DBNameTrackingList
	numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
	for(i=0; i<numElements; i++)
		{
		whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
		
		if(
			whichVarRow >= iVars_NumTableRows
			||  
			(
			 //iVars_Types_str[whichVarRow] != "DB read value"  &&  iVars_Types_str[whichVarRow] != "DB read PRI"  &&  iVars_Types_str[whichVarRow] != "DB address"  &&  iVars_Types_str[whichVarRow] != "_DB index"	//AJN, 7.0.5, 10/24/08
			 //iVars_Types_Int[whichVarRow] != EQ_DB_READ_VAL  &&  iVars_Types_Int[whichVarRow] != EQ_DB_READ_PRI  &&  iVars_Types_Int[whichVarRow] != EQ_DB_ADDRESS  &&  iVars_Types_Int[whichVarRow] != EQ_DB_INDEX		//6/25/09
			 iVars_Types_Int[whichVarRow] != EQ_DB_READ_VAL  &&  
			 iVars_Types_Int[whichVarRow] != EQ_DB_READ_PRI  &&  
			 iVars_Types_Int[whichVarRow] != EQ_DB_ADDRESS  &&  
			 iVars_Types_Int[whichVarRow] != EQ_DB_DATABASE_INDEX  &&  
			 iVars_Types_Int[whichVarRow] != EQ_DB_TABLE_INDEX  &&  
			 iVars_Types_Int[whichVarRow] != EQ_DB_FIELD_INDEX  &&  
			 iVars_Types_Int[whichVarRow] != EQ_DB_RECORD_INDEX
		    )
		  )
		   {
		   ListDeleteElement(me, iVars_DBNameTrackingListIndex, i);
		   numElements--;
		   i--;
		   }
		}
		
}//procedure iVars_DBNT_GarbageCollection()


//called in EQ_OnCheckData(). use names stored in DBNT linked lists to ensure we have correct DB indexes
procedure iVars_DBNT_UpdateDBCoordsArray()
{

	integer i;
	integer me;
	integer numElements;
	integer whichVarRow;
	string63 databaseName;
	integer databaseIndex;
	string63 tableName;
	integer tableIndex;
	string63 fieldName;
	integer fieldIndex;
	string63 recordName;
	integer recordIndex;
	integer iVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();

	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	
	numElements = ListGetElements(me, iVars_DBNameTrackingListIndex);
	for(i=0; i<numElements; i++)
		{
		whichVarRow = ListGetLong(me, iVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
		
		//database index
		databaseName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);	//6 for string63
		if(databaseName == "")
			databaseName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 5, DBNT_DB_NAME_FIELD);	//5 for string31	//9/30/09
		if(databaseName != "")
			databaseIndex = DBDatabaseGetIndex(databaseName);
		else
			databaseIndex = -1;
		
		//table index
		tableName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);	//6 for string63
		if(tableName == "")
			tableName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 5, DBNT_TABLE_NAME_FIELD);	//5 for string31	//9/30/09
		if(tableName != "")
			tableIndex = DBTableGetIndex(databaseIndex, tableName);
		else
			tableIndex = -1;
		
		//field index
		fieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);	//6 for string63
		if(fieldName == "")
			fieldName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 5, DBNT_FIELD_NAME_FIELD);	//5 for string31	//9/30/09
		if(fieldName != "")
			fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);
		else
			fieldIndex = -1;
		
		//record index
		recordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);	//6 for string63
		if(recordName == "")
			recordName = ListGetString(me, iVars_DBNameTrackingListIndex, i, 5, DBNT_RECORD_NAME_FIELD);	//5 for string31	//9/30/09
		if(recordName != "")
			{
			recordIndex = DBRecordFind(databaseIndex, 		//database to search
									   tableIndex, 			//table to search
									   0, 					//use the record ID field as the search field
									   1, 					//the start record index
									   TRUE, 				//exact record match
									   recordName);			//the search string
			if(recordIndex == 0)
				recordIndex = -1;
			}
		else
			recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[whichVarRow]);
			
		//update iVars_DBCoords
		iVars_DBCoords[whichVarRow] = DBAddressCreate(databaseIndex, tableIndex, fieldindex, recordIndex);
		}

	//3/31/11:  iVars_IndexesForDBIndexVars[] is used to store the value of the db index type vars.  since it 
	//gets updated once in checkdata or when the model is not running, this array helps to increase
	//speed during run time because conversion of the db address to an index only has to occur once.
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX)
			{
			iVars_IndexesForDBIndexVars[i] = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
			}
		else if(iVars_Types_Int[i] == EQ_DB_TABLE_INDEX)
			{
			iVars_IndexesForDBIndexVars[i] = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
			}
		else if(iVars_Types_Int[i] == EQ_DB_FIELD_INDEX)
			{
			iVars_IndexesForDBIndexVars[i] = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
			}
		else if(iVars_Types_Int[i] == EQ_DB_RECORD_INDEX)
			{
			iVars_IndexesForDBIndexVars[i] = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
			}
		}

}//procedure iVars_DBNT_UpdateDBCoordsArray()


//called in open model this function is used to ensure iVars_DBNameTrackingList 
//exists since name tracking was only implemented after 7.0.3
procedure iVars_DBNT_BuildList()
{

	integer i;
	integer me;
	integer dbIndex;
	string63 dbName;
	integer tableIndex;
	string63 tableName;
	integer fieldIndex;
	integer recordIDFieldIndex;
	string63 fieldName;
	integer recordIndex;
	string63 recordName;
	integer iVars_DBNameTrackingListIndex;
	integer found;
	
	me = MyBlockNumber();
	
	//if the iVars db name tracking lists doesn't exist, create it
	iVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_IVARS_LIST_NAME);
	if(iVars_DBNameTrackingListIndex < 0)
		{
		iVars_DBNameTrackingListIndex = ListCreate(me, 2, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			//2 long field
			//2 sets sort type as integer
			//DBNT_WHICH_ROW_IN_TABLE_FIELD sets sort field
		ListLocked(me, iVars_DBNameTrackingListIndex, TRUE);
		ListAddString63s(me, iVars_DBNameTrackingListIndex, 4);
		ListSetName(me, iVars_DBNameTrackingListIndex, DBNT_IVARS_LIST_NAME);
		}
		
	for(i=0; i<iVars_NumTableRows; i++)
		{
		//AJN, 7.0.5, 10/24/08
		//if(iVars_Types_str[i] == "DB read value"  ||  iVars_Types_str[i] == "DB read PRI"  ||  iVars_Types_str[i] == "DB address"  ||  iVars_Types_str[i] == "_DB index")
		//if(iVars_Types_Int[i] == EQ_DB_READ_VAL  ||  iVars_Types_Int[i] == EQ_DB_READ_PRI  ||  iVars_Types_Int[i] == EQ_DB_ADDRESS  ||  iVars_Types_Int[i] == EQ_DB_INDEX)	//6/25/09
		if(
			iVars_Types_Int[i] == EQ_DB_READ_VAL  ||  
			iVars_Types_Int[i] == EQ_DB_READ_PRI  ||  
			iVars_Types_Int[i] == EQ_DB_ADDRESS  ||  
			iVars_Types_Int[i] == EQ_DB_DATABASE_INDEX  ||  
			iVars_Types_Int[i] == EQ_DB_TABLE_INDEX  ||  
			iVars_Types_Int[i] == EQ_DB_FIELD_INDEX  ||  
			iVars_Types_Int[i] == EQ_DB_RECORD_INDEX 
		  )	
			{
			//search for this db iVar in the linked list
			found = ListSearch(me, iVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, i, 0.0, "", 0);
			
			//if this db iVar is not represented in the linked list, then add it
			if(found < 0)
				{
				ListCreateElement(me, iVars_DBNameTrackingListIndex);
				
				//add the "whichRow" field to the new element
				ListSetLong(me, iVars_DBNameTrackingListIndex, -1, DBNT_WHICH_ROW_IN_TABLE_FIELD, i);
				
				//add the "dbName" to the new element
				dbIndex = DBDatabaseGetIndexFromAddress(iVars_DBCoords[i]);
				if(dbIndex >= 1  &&  !NoValue(iVars_DBCoords[i]))
					dbName = DBDatabaseGetName(dbIndex);
				else
					dbName = "";
				ListSetString(me, iVars_DBNameTrackingListIndex, -1, 6, DBNT_DB_NAME_FIELD, dbName);	//6 for string63
				
				//add the "tableName" to the new element
				tableIndex = DBTableGetIndexFromAddress(iVars_DBCoords[i]);
				if(tableIndex >= 1  &&  !NoValue(iVars_DBCoords[i]))
					tableName = DBTableGetName(dbIndex, tableIndex);
				else
					tableName = "";
				ListSetString(me, iVars_DBNameTrackingListIndex, -1, 6, DBNT_TABLE_NAME_FIELD, tableName);	//6 for string63
				
				//add the "fieldName" to the new element
				fieldIndex = DBFieldGetIndexFromAddress(iVars_DBCoords[i]);
				if(fieldIndex >= 1  &&  !NoValue(iVars_DBCoords[i]))
					fieldName = DBFieldGetName(dbIndex, tableIndex, fieldIndex);
				else
					fieldName = "";
				ListSetString(me, iVars_DBNameTrackingListIndex, -1, 6, DBNT_FIELD_NAME_FIELD, fieldName);	//6 for string63
				
				//add the "recordName" to the new element
				recordIndex = DBRecordGetIndexFromAddress(iVars_DBCoords[i]);
				if(recordIndex >= 1  &&  !NoValue(iVars_DBCoords[i]))
					{
					recordIDFieldIndex = DBRecordIDFieldGetIndex(dbIndex, tableIndex);
					if(recordIDFieldIndex >= 1)
						{
						if( DBRecordExists(dbIndex, tableIndex, recordIDFieldIndex, recordIndex) )			//8/17/10
							{
							recordName = DBDataGetAsString(dbIndex, tableIndex, recordIDFieldIndex, recordIndex);
							}
						else
							{
							UserError("There is a problem in " + BlockName(me) + " " + me + ". The location fo input variable " + (i+1) +
									  "is out of bounds.");
							AbortAllSims();
							}
						}
					else
						recordName = "";
					}
				else
					recordName = "";
				ListSetString(me, iVars_DBNameTrackingListIndex, -1, 6, DBNT_RECORD_NAME_FIELD, recordName);	//6 for string63
				
				//add new elemnt to the "iVars_DBNameTrackingList" linked list
				ListAddElement(me, iVars_DBNameTrackingListIndex, -2);	//2 for added in a sorted fashion
				}
			}
		}//for(i=0; i<iVars_NumTableRows; i++)

}//procedure iVars_DBNT_BuildList()


//**********************************************************************
//END iVars_DBNT Functions
//**********************************************************************
//**********************************************************************




//**********************************************************************
//**********************************************************************
//START "oVars" Functions
//**********************************************************************


//if an oVar is a dbWriteVal or dbWritePRI, we don't want to initialize it to BLANK because,
//if user doesn't set a value on this var in the equation, we will over-write the value in the
//db with a blank.  thereore, to init, go out and do a db read.
procedure oVars_InitVals()
{

	integer i;
	integer me;
	integer parentArray[3];
	
	me = MyBlockNumber();

	//CMC- connector message control. save old values before initializing oVars_Values[]
	#ifdef EQ_IsValueBlock
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(CMC_chk)
				CMC_OVars_ValuesOld[i] = oVars_Values[i];
			}
	#endif
	
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL)
			{
			oVars_Values[i] = DBDataGetAsNumberUsingAddress(oVars_DBCoords[i]);
			}
		
		else if(oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
			{
			if(EQ_DBAddressLocationExists(oVars_DBCoords[i], DB_ADDRESS_TYPE_RECORD))		//8/17/10
				{
				oVars_Values[i] = DBDataGetParentUsingAddress(oVars_DBCoords[i], parentArray);
				}
			else
				{
				UserError("There is a problem in " + BlockName(me) + " " + me + ". The location fo output variable " + (i+1) +
						  "is out of bounds.");
				AbortAllSims();
				}
			}
		
		else //if the oVar is anything other than 
			{
			oVars_Values[i] = blank;
			}
		}
		
}//procedure oVars_InitVals()

/*
on oVars_ttbl
{
	
	if(colClicked == O_VAR_TYPE_COL  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows)
		{
		StopDataTableEditing();
		SetDataTableSelection("oVars_ttbl", -2, -2, -2, -2, FALSE);
		}
	
	SetConVisibility(MyBlockNumber(), GetConNumber(MyBlockNumber(), "iVarsIn"), FALSE);
	SetConVisibility(MyBlockNumber(), GetConNumber(MyBlockNumber(), "oVarsOut"), FALSE);
	SetConVisibility(MyBlockNumber(), GetConNumber(MyBlockNumber(), "goIn"), FALSE);
		
	if( colClicked == O_VAR_NAME_COL  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows  &&  
		(StrFind(oVars_Types_str[rowClicked], "attrib", FALSE, FALSE) >= 0) )
		{
		StopDataTableEditing();
		SetDataTableSelection("oVars_ttbl", -2, -2, -2, -2, FALSE);
		}
		
	if(colClicked == O_VAR_NAME_COL  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows  &&  StrFind(oVars_Types_str[rowClicked], "_Select con", FALSE, FALSE) >= 0)
		{
		StopDataTableEditing();
		SetDataTableSelection("oVars_ttbl", -2, -2, -2, -2, FALSE);
		UserError("The name of the select variable may not be changed.");
		}
		
	if(colClicked == O_VAR_VALUE_COL  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows)
		{
		StopDataTableEditing();
		SetDataTableSelection("oVars_ttbl", -2, -2, -2, -2, FALSE);
		}

	#ifdef EQ_NoItemColumnExists
		if(colClicked == O_VAR_NO_ITEM_COL  &&  rowClicked >= 0  &&  rowClicked < oVars_NumTableRows)
			{
			StopDataTableEditing();
			SetDataTableSelection("oVars_ttbl", -2, -2, -2, -2, FALSE);
			}
	#endif
		
	oVarsOut_ConnectorsSetup();
	oVars_TableSetup();
	oVarsOut_ConLabelsSet();
	oVars_DBNT_GarbageCollection();
	EQ_BlockRegisterStructure();
	
	#ifdef CW_OVarsOut_CalcControl_chk
		//CW_OVarsOut_Animate();			//7/5/11
		CW_ConnectorAnimate();
	#endif
	#ifdef CMC_chk
		//CMC_OVarsOut_Animate();			//7/6/11
		CMC_ConnectorAnimate();
	#endif

}//on oVars_ttbl
*/

procedure oVars_CopyRow(integer calledFrom)
{
	integer i, j;
	real numRowsToInsert;			//note: must be a real so we can tell if user clicked "cancel"
	integer oldNumRows;
	integer newNumRows;
	integer whatGotSelected[4];
	integer startInsertRow;
	integer endInsertRow;
	integer leftCol;
	integer sourceRow;
	integer targetRow;
	integer oVars_DBNameTrackingListIndex;
	integer me;
	integer sourceElement;
	
	me = MyBlockNumber();

	GetDataTableSelection("oVars_ttbl", whatGotSelected);
	startInsertRow = whatGotSelected[0];
	rowClicked = startInsertRow;
	leftCol = whatGotSelected[2];
	
	if(leftCol == 0  &&  startInsertRow >= 0  && startInsertRow < oVars_NumTableRows)
		{
		numRowsToInsert = NumericParameter("Please enter the number of times you would like to copy the selected row.", 1);
		
		if(!NoValue(numRowsToInsert))	//if user did not click cancel
			{
			if(numRowsToInsert >= 1)
				{
				oldNumRows = oVars_NumTableRows;
				newNumRows = oldNumRows + numRowsToInsert;
				endInsertRow = startInsertRow + numRowsToInsert;
				oVars_NumTableRows = newNumRows;
				
				//first, grow the arrays...
				oVars_ResizeDynamicArrays(calledFrom, RESIZE_COPY);
				
				//then, move existing rows down...
				for(i=oVars_NumTableRows-1; i>endInsertRow; i--)
					{
					sourceRow = i-numRowsToInsert;
					targetRow = i;

					oVars_Types_str[targetRow] = oVars_Types_str[sourceRow];
					oVars_Types_Int[targetRow] = oVars_Types_Int[sourceRow];
					oVars_Names[targetRow] = oVars_Names[sourceRow];
					oVars_Values[targetRow] = oVars_Values[sourceRow];
					oVars_AttribTypes[targetRow] = oVars_AttribTypes[sourceRow];
					oVars_NoItemOptions[targetRow] = oVars_NoItemOptions[sourceRow];

					//8/16/10:  change DBNT_WHICH_ROW_IN_TABLE_FIELD so that the DBNT element is pointing to the correct row in the oVars table
					oVars_DBCoords[targetRow] = oVars_DBCoords[sourceRow];
					if(
					   oVars_Types_Int[sourceRow] == EQ_DB_READ_VAL  ||  
					   oVars_Types_Int[sourceRow] == EQ_DB_READ_PRI  ||  
					   oVars_Types_Int[sourceRow] == EQ_DB_ADDRESS  ||  
					   oVars_Types_Int[sourceRow] == EQ_DB_DATABASE_INDEX  ||
					   oVars_Types_Int[sourceRow] == EQ_DB_TABLE_INDEX  ||
					   oVars_Types_Int[sourceRow] == EQ_DB_FIELD_INDEX  ||
					   oVars_Types_Int[sourceRow] == EQ_DB_RECORD_INDEX
					  )
						{
						oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
						if(oVars_DBNameTrackingListIndex >= 0)
							{
							//get source element...
							sourceElement = ListSearch(me, oVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, sourceRow, 0, "", 0);	//2- search for integer
							if(sourceElement >= 0)
								{
								//change the value in the "which row in table" field to the target row
								ListSetLong(me, oVars_DBNameTrackingListIndex, sourceElement, DBNT_WHICH_ROW_IN_TABLE_FIELD, targetRow);
								}
							else
								{
								UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
								}
							}
						else
							{
							UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							}
						}
				
					#ifdef CMC_chk
						if(CMC_chk)
							CMC_OVarsOut_Settings[targetRow] = CMC_OVarsOut_Settings[sourceRow];
					#endif
					}
				
				//...then, add the inserted rows
				for(i=0; i<numRowsToInsert; i++)
					{
					sourceRow = startInsertRow;
					targetRow = startInsertRow + 1 + i;
					
					oVars_Types_str[targetRow] = oVars_Types_str[sourceRow];
					oVars_Types_Int[targetRow] = oVars_Types_Int[sourceRow];
					
					if(oVars_Types_int[sourceRow] == EQ_ITEM_ATTRIBUTE)
						oVars_Names[targetRow] = "None";
					else
						oVars_Names[targetRow] = oVars_Names[sourceRow] + sourceRow + i;

					oVars_Values[targetRow] = oVars_Values[sourceRow];
					oVars_AttribTypes[targetRow] = oVars_AttribTypes[sourceRow];
					oVars_NoItemOptions[targetRow] = oVars_NoItemOptions[sourceRow];

					//8/16/10:  update the DBNT list with its newest member
					oVars_DBCoords[targetRow] = oVars_DBCoords[sourceRow];
					oVars_DBNT_AddElement(oVars_DBCoords[targetRow], targetRow);

					#ifdef CMC_chk
					if(CMC_chk)
						CMC_OVarsOut_Settings[targetRow] = CMC_OVarsOut_Settings[sourceRow];
					#endif
					}
				
				//...then, redo connector accounting, ie, make sure connectors are listed in ascending order
				j = 0;
				for(i=0; i<oVars_NumTableRows; i++)
					{
					if(StrFind(oVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
						{
						oVars_Types_str[i] = "Connector " + j;
						j++;
						}
					}
					
				oVarsOut_Reconnect(DATA_TABLE_RESIZE);
				}//if(numRowsToInsert >= 1)
			
			}//if(!NoValue(numRowsToInsert))
		
		}
	
	else
		{
		UserError("Copying requires you to first select one whole row in the table by clicking on the left-most column (the one that displays the row numbers).");
		}

}//procedure oVars_CopyRow()


procedure oVars_DeleteRows(integer calledFrom)
{

	integer i, j;
	real numRowsToCopy;			//note: must be a real so we can tell if user clicked "cancel"
	integer numDeletableRows;
	integer oldNumRows;
	integer oldLastRow;
	integer newNumRows;
	integer whatGotSelected[4];
	integer startDeleteRow;
	integer endDeleteRow;
	integer lastDeleteRow;
	integer numRowsToDelete;
	integer leftCol;
	integer sourceRow;
	integer targetRow;
	integer oVars_DBNameTrackingListIndex;
	integer me;
	integer sourceElement;
	
	me = MyBlockNumber();
	
	GetDataTableSelection("oVars_ttbl", whatGotSelected);
	startDeleteRow = whatGotSelected[0];
	rowClicked = startDeleteRow;
	endDeleteRow = whatGotSelected[1];
	numDeletableRows = oVars_NumTableRows - startDeleteRow;
	leftCol = whatGotSelected[2];
	StopDataTableEditing();				//for some reason this is needed in order for this procedure to work properly.
	
	if(leftCol == 0  &&  startDeleteRow >= 0  && startDeleteRow < oVars_NumTableRows  &&  endDeleteRow >= 0  &&  endDeleteRow < oVars_NumTableRows)
		{
		numRowsToDelete = endDeleteRow - startDeleteRow + 1;
		
		oldNumRows = oVars_NumTableRows;
		oldLastRow = oldNumRows - 1;
		newNumRows = oldNumRows - numRowsToDelete;
		oVars_NumTableRows = newNumRows;
		lastDeleteRow = startDeleteRow + numRowsToDelete - 1;

		//6/15/11:  delete the DBNT elements pointing to the rows that are getting deleted
		for(i=startDeleteRow; i<=endDeleteRow; i++)
			{
			if(
			   oVars_Types_Int[i] == EQ_DB_WRITE_VAL  ||  
			   oVars_Types_Int[i] == EQ_DB_WRITE_PRI
			  )
			  	{
			  	oVars_DBNT_DeleteElement(i);
			  	}
			}
		
		//first copy the rows that are moving up,...
		if(lastDeleteRow < oldLastRow)
			{
			numRowsToCopy = oldLastRow - lastDeleteRow;
			for(i=0; i<numRowsToCopy; i++)
				{
				targetRow = startDeleteRow + i;
				sourceRow = lastDeleteRow + 1 + i;
				
				oVars_Types_str[targetRow] = oVars_Types_str[sourceRow];
				oVars_Types_Int[targetRow] = oVars_Types_Int[sourceRow];
				oVars_Names[targetRow] = oVars_Names[sourceRow];

				oVars_Values[targetRow] = oVars_Values[sourceRow];
				oVars_AttribTypes[targetRow] = oVars_AttribTypes[sourceRow];
				oVars_NoItemOptions[targetRow] = oVars_NoItemOptions[sourceRow];

				//8/16/10:  change DBNT_WHICH_ROW_IN_TABLE_FIELD so that the DBNT element is pointing to the correct row in the oVars table
				oVars_DBCoords[targetRow] = oVars_DBCoords[sourceRow];
				if(
				   oVars_Types_Int[sourceRow] == EQ_DB_WRITE_VAL  ||  
				   oVars_Types_Int[sourceRow] == EQ_DB_WRITE_PRI
				  )
					{
					oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
					if(oVars_DBNameTrackingListIndex >= 0)
						{
						//get source element...
						sourceElement = ListSearch(me, oVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, sourceRow, 0, "", 0);	//2- search for integer
						if(sourceElement >= 0)
							{
							//change the value in the "which row in table" field to the target row
							ListSetLong(me, oVars_DBNameTrackingListIndex, sourceElement, DBNT_WHICH_ROW_IN_TABLE_FIELD, targetRow);
							}
						else
							{
							UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							}
						}
					else
						{
						UserError("An unexpected condition has arisen in " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
						}
					}
				
				#ifdef CMC_chk
				if(CMC_chk)
					CMC_OVarsOut_Settings[targetRow] = CMC_OVarsOut_Settings[sourceRow];
				#endif
				}
			
			oVars_DBNT_GarbageCollection();	//8/16/10: some rows that got deleted may have had elements in the DBNT list
			}
		
		//...then, redo connector accounting, ie, make sure connectors are listed in ascending order
		j = 0;
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(StrFind(oVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
				{
				oVars_Types_str[i] = "Connector " + j;
				j++;
				}
			}
		
		//...then reconnect...
		oVarsOut_Reconnect(DATA_TABLE_RESIZE);
		
		//...then delete rows off from bottom of table...
		oVars_ResizeDynamicArrays(calledFrom, RESIZE_DELETE_SELECTION);
		
		oVars_NumTableRows = GetDimension(oVars_ttbl);	//6/15/11
		}
	
	else
		{
		UserError("Deleting rows requires you to first select at least one row in the table by clicking on the left-most column (the one that displays the row numbers).");
		}

}//procedure oVars_DeleteRows()


integer oVars_CheckChosenField(integer whichVar, real theCoords)
{

	integer me;
	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	integer fieldType;
	integer parentField;
	integer parentInfo[3];
	integer legitField;
	
	me = MyBlockNumber();
	
	legitField = TRUE;

	//if the variable is of type "DB write value" or "DB write value using attrib", the chosen field cannot be a string
	//if(oVars_Types_str[whichVar] == "DB write value"  ||  oVars_Types_str[whichVar] == "DB write value using attrib")	//AJN, 7.0.5, 10/24/08
	if(oVars_Types_Int[whichVar] == EQ_DB_WRITE_VAL  ||  oVars_Types_Int[whichVar] == EQ_DB_WRITE_VAL_USING_ATTRIB)
		{
	
		fieldType = DBFieldGetPropertiesUsingAddress(theCoords, 1) ;	//where 1 = fieldType

		if(fieldType == DB_FIELDTYPE_STRING_VALUE)
			{
			UserError("There is a problem in equation block " + MyBlockNumber() + ". The output """ + oVars_ttbl[whichVar][O_VAR_NAME_COL] + 
					  """ is pointing to a string field which is not allowed with ""DB write value"" or ""DB write value using attrib"" type variables. " +
					  "Consider using ""DB write PRI"" or ""DB write PRI using attrib"" variables instead.");
			legitField = FALSE;
			}
			
		}
		
	//if the variable is of type "DB write PRI" or "DB write PRI using attrib", the chosen field must be a child
	//if(oVars_Types_str[whichVar] == "DB write PRI"  ||  oVars_Types_str[whichVar] == "DB write PRI using attrib")	//AJN, 7.0.5, 10/24/08
	if(oVars_Types_Int[whichVar] == EQ_DB_WRITE_PRI  ||  oVars_Types_Int[whichVar] == EQ_DB_WRITE_PRI_USING_ATTRIB)
		{
		if( EQ_DBAddressLocationExists(theCoords, DB_ADDRESS_TYPE_FIELD) )		//8/17/10
			{
			databaseIndex = DBDatabaseGetIndexFromAddress(theCoords);
			tableIndex = DBTableGetIndexFromAddress(theCoords);
			fieldIndex = DBFieldGetIndexFromAddress(theCoords);
	
			DBDataGetParent(databaseIndex, tableIndex, fieldIndex, 1, parentInfo);	//use a "1" for row index b/ just interested in finding out if the field is a child
			parentField = parentInfo[PARENT_FIELD];
			
			//if the chosen field is not a child
			if(parentField == 0)
				{
				UserError("There is a problem in equation block " + MyBlockNumber() + ". Because the output variable """ + oVars_ttbl[whichVar][O_VAR_NAME_COL] + 
						  """ is of type ""DB write PRI"" or ""DB write PRI using attrib"", the chosen field must be a child. Consider " +
						  "using ""DB write value"" or ""DB write value using attrib"" variables  instead.");
				legitField = FALSE;
				}
			}
		else
			{
			UserError("There is a problem in " + BlockName(me) + " " + me + ". The location fo output variable " + (whichVar+1) +
					  "is out of bounds.");
			AbortAllSims();
			}
		}
	
	return(legitField);

}//procedure oVars_CheckDBValChosenField(real theCoords)


integer oVars_GetNumVars(string varName)
{
	
	integer i;
	integer numVars;
	
	numVars = 0;

	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(StrFind(oVars_Types_str[i], varName, FALSE, FALSE) >= 0)
			{
			numVars++;
			}
		}
		
	return(numVars);

}//integer oVars_GetNumVars(string varName)

/*
//called in InitSim, oVars_NumTableRows, oVars_TableSetup
procedure oVars_ResizeDynamicArrays(integer calledFrom, integer doWhat)
{
	
	integer i, j;
	integer lastRowSize;
	integer numDefaultVars;
	integer numOutConVars;
	
	#ifdef checkingForBlockers
		MakeArray(checkingForBlockers, oVars_NumTableRows);
	#endif
	
	#ifdef meBlocked
		MakeArray(meBlocked, oVars_NumTableRows);
	#endif

	MakeArray(oVars_AttribColumnIndexes, oVars_NumTableRows);
	MakeArray(oVars_Names, oVars_NumTableRows);
	MakeArray(oVars_Types_str, oVars_NumTableRows);
	MakeArray(oVars_Types_Int, oVars_NumTableRows);
	MakeArray(oVars_Values, oVars_NumTableRows);
	MakeArray(oVars_ValuesStr, oVars_NumTableRows);
	MakeArray(oVars_Units, oVars_NumTableRows);
	MakeArray(oVars_AttribTypes, oVars_NumTableRows);
	MakeArray(oVars_VarIsWhichCon, oVars_NumTableRows);
	MakeArray(oVars_VarIsWhichConOld, oVars_NumTableRows);
	MakeArray(oVars_DBCoords, oVars_NumTableRows);
	MakeArray(oVars_NoItemOptions, oVars_NumTableRows);
	MakeArray(oVars_NoItemConstants, oVars_NumTableRows);
	MakeArray(oVars_GetValFromIVars, oVars_NumTableRows);

	//redim oVars_ttbl
	lastRowSize = GetDimension(oVars_DA);
	MakeArray(oVars_DA, oVars_NumTableRows);
	DILinkMsgs(FALSE);
	DynamicDataTable(MyBlockNumber(), "oVars_ttbl", oVars_DA);
	DILinkMsgs(TRUE);

	//if more rows were added to the table
	if(lastRowSize < oVars_NumTableRows)
		{
		numOutConVars = oVars_GetNumVars("Connector");

		if(calledFrom == EQUATION_BLOCK  ||  calledFrom == EQUATION_ITEM_BLOCK)
			{
			numDefaultVars = oVars_GetNumVars("Connector");
			}
		else if(calledFrom == EQUATION_QUEUE_BLOCK)
			{
			numDefaultVars = oVars_GetNumVars("Result rank");
			numDefaultVars += oVars_GetNumVars("QEQ item rank");
			}
		else if(calledFrom == EQUATION_QUERY_BLOCK_ITEM)
			{
			numDefaultVars = oVars_GetNumVars("DBQ record rank");
			}
		else if(calledFrom == EQUATION_QUERY_BLOCK_VALUE)
			{
			numDefaultVars = oVars_GetNumVars("DBQ record rank");
			}
					
		for(i=lastRowSize; i<oVars_NumTableRows; i++)
			{
			if(i == 0  ||  doWhat != RESIZE_ADD_SUBTRACT_FROM_END)	//if row 0 or if inserting rows into middle of table,...
				{
				//..., then use default settings for the rows we're adding to the bottom.  NOTE: eventhough,
				//rows might have been inserted into the middle, we are going to add rows to the bottom
				//and then move everything down later in the "copy rows function
				
				if(calledFrom == EQUATION_BLOCK  ||  calledFrom == EQUATION_ITEM_BLOCK)
					{
					oVars_Types_str[i] = "Connector " + numDefaultVars;
					oVars_Types_Int[i] = EQ_CONNECTORS;
					oVars_Names[i] = "outCon" + numDefaultVars;
					numDefaultVars++;
					}
					
				else if(calledFrom == EQUATION_QUEUE_BLOCK)
					{
//					oVars_Types_str[i] = "_Result rank";
					oVars_Types_str[i] = "QEQ item rank";
					oVars_Types_Int[i] = EQ_QEQ_ITEM_RANK;
					oVars_Names[i] = "iRank_" + numDefaultVars;
					numDefaultVars++;
					}
				else if(calledFrom == EQUATION_QUERY_BLOCK_ITEM)
					{
					oVars_Types_str[i] = "DBQ record rank";
					oVars_Types_Int[i] = EQ_DBQ_RECORD_RANK;
					oVars_Names[i] = "prRank_" + numDefaultVars;
					numDefaultVars++;
					}
				else if(calledFrom == EQUATION_QUERY_BLOCK_VALUE)
					{
					oVars_Types_str[i] = "DBQ record rank";
					oVars_Types_Int[i] = EQ_DBQ_RECORD_RANK;
					oVars_Names[i] = "rRank_" + numDefaultVars;
					numDefaultVars++;
					}
				
				oVars_DBCoords[i] = blank;
				oVars_Values[i] = blank;
				oVars_AttribTypes[i] = ATTRIB_TYPE_NO_ATTRIB;  
				oVars_NoItemOptions[i] = O_VAR_USE_LAST_VALUE;
				}
			else  //if adding rows to the end, use the previous row's settings to define the new row's settings.
				{
				oVars_Types_Int[i] = oVars_Types_Int[i-1];		//NOTE: set oVars_Types_Int[] first!!

				if(StrFind(oVars_Types_str[i-1], "Connector", FALSE, FALSE) >= 0)
					{
					oVars_Types_str[i] = "Connector " + numOutConVars;
					oVars_Names[i] = "outCon" + numOutConVars;
					numOutConVars++;
					}
				else
					{
					oVars_Types_str[i] = oVars_Types_str[i-1];
					
					//create new name for the new variable
					if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE)
						oVars_Names[i] = "None";
					else
						oVars_Names[i] = oVars_Names[i-1] + i;
					}

				oVars_DBCoords[i] = oVars_DBCoords[i-1];
				oVars_Values[i] = oVars_Values[i-1];
				oVars_AttribTypes[i] = oVars_AttribTypes[i-1];
				oVars_NoItemOptions[i] = oVars_NoItemOptions[i-1];
				if(
					oVars_Types_str[i] == "DB write value"  ||  
					oVars_Types_str[i] == "DB write PRI"
				  )
					{
					oVars_DBNT_AddElement(oVars_DBCoords[i], i);
					}
				}
			}
			
		}//if(lastRowSize < oVars_NumTableRows)

	#ifdef CMC_chk
		CMC_OVars_ResizeArrays(doWhat);
	#endif

}//procedure oVars_ResizeDynamicArrays(integer calledFrom, integer doWhat)
*/

#ifdef EQ_IsItemBlock

integer oVars_SetNamesColTagArray()
{

	integer i;
	integer namesColTagArrayIndex;
	
	MakeArray(oVars_NamesColTagArray, oVars_NumTableRows);
	
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) > -1)
			oVars_NamesColTagArray[i] = "usePopupTag";
		else
			oVars_NamesColTagArray[i] = "";
		}
	
	namesColTagArrayIndex = DynamicTextArrayNumber(oVars_NamesColTagArray);
	
	return(namesColTagArrayIndex);

}//procedure oVars_SetNamesColTagArray()

#endif //EQ_IsItemBlock


//called in ConArrayChanged, on oVars_NumTableRows, DialogClick, DialogOpen
procedure oVars_TableSetup()
{

	integer i;
	integer dbIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	string63 dbCoordinate;
	integer positionArray[4];
	integer namesColTagArrayIndex;

	oVars_DBNT_UpdateDBCoordsArray();
	
	//update oVars_DA with current information
	for(i=0; i<oVars_NumTableRows; i++)
		{
		
		oVars_ttbl[i][O_VAR_NAME_COL] = oVars_Names[i];
		

		//********************************
		//START:  Write to I_VAR_TYPE_COL
		//********************************
		
		#ifdef CMC_chk
		if(CMC_chk  &&  oVars_Types_Int[i] == EQ_CONNECTORS)
			{
			if(CMC_OVarsOut_Settings[i] == CMC_OVAR_MSG_EMULATION)
				{
				oVars_ttbl[i][O_VAR_TYPE_COL] = "Con" + oVars_VarIsWhichCon[i] + " [ME]";
				}
			else if(CMC_OVarsOut_Settings[i] == CMC_OVAR_VAL_CHANGE_ONLY)
				{
				oVars_ttbl[i][O_VAR_TYPE_COL] = "Con" + oVars_VarIsWhichCon[i] + " [CVC]";
				}
			else if(CMC_OVarsOut_Settings[i] == CMC_OVAR_ALWAYS)
				{
				oVars_ttbl[i][O_VAR_TYPE_COL] = "Con" + oVars_VarIsWhichCon[i] + " [A]";
				}
			else if(CMC_OVarsOut_Settings[i] == CMC_OVAR_NEVER)
				{
				oVars_ttbl[i][O_VAR_TYPE_COL] = "Con" + oVars_VarIsWhichCon[i] + " [N]";
				}
			}
		else
			{
			oVars_ttbl[i][O_VAR_TYPE_COL] = oVars_Types_str[i];
			}
		#else
		oVars_ttbl[i][O_VAR_TYPE_COL] = oVars_Types_str[i];
		#endif


		//********************************
		//END:  Write to I_VAR_TYPE_COL
		//********************************


		//fill out the O_VAR_VALUE_COL column
		if( StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0  &&  oVars_AttribTypes[i] == ATTRIB_TYPE_STRING )
			{
			#ifdef EQ_IsItemBlock
				oVars_ttbl[i][O_VAR_VALUE_COL] = SLStringGet(oVars_ttbl[i][O_VAR_NAME_COL], oVars_Values[i]);
			#endif
			}
		else if(oVars_Types_str[i] == "DB write value"  ||  oVars_Types_str[i] == "DB write PRI"  ||  
				oVars_Types_str[i] == "DB write value using attrib"  ||  oVars_Types_str[i] == "DB write PRI using attrib")
			{
			dbCoordinate = "";
			
			if( NoValue(oVars_DBCoords[i]) )
				{
				dbCoordinate = "x:x:x:x";
				}
			else
				{
				dbIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[i]);
				if(dbIndex < 1  ||  NoValue(dbIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += dbIndex + ":";
				
				tableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[i]);
				if(tableIndex < 1  ||  NoValue(tableIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += tableIndex + ":";
				
				fieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[i]);
				if(fieldIndex < 1  ||  NoValue(fieldIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += fieldIndex + ":";
				
				recordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[i]);
				if(recordIndex < 1  ||  NoValue(recordIndex))
					dbCoordinate += "x";
				else
					dbCoordinate += recordIndex;
				}

			oVars_ttbl[i][O_VAR_VALUE_COL] = dbCoordinate;
			}
		else if(oVars_AttribTypes[i] == ATTRIB_TYPE_DB)	
			{
			dbCoordinate = "";
			if( NoValue(oVars_Values[i]) )
				{
				dbCoordinate = "x:x:x:x";
				}
			else
				{
				dbIndex = DBDatabaseGetIndexFromAddress(oVars_Values[i]);
				if(dbIndex < 1  ||  NoValue(dbIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += dbIndex + ":";
				
				tableIndex = DBTableGetIndexFromAddress(oVars_Values[i]);
				if(tableIndex < 1  ||  NoValue(tableIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += tableIndex + ":";
				
				fieldIndex = DBFieldGetIndexFromAddress(oVars_Values[i]);
				if(fieldIndex < 1  ||  NoValue(fieldIndex))
					dbCoordinate += "x:";
				else
					dbCoordinate += fieldIndex + ":";
				
				recordIndex = DBRecordGetIndexFromAddress(oVars_Values[i]);
				if(recordIndex < 1  ||  NoValue(recordIndex))
					dbCoordinate += "x";
				else
					dbCoordinate += recordIndex;
				}
			oVars_ttbl[i][O_VAR_VALUE_COL] = dbCoordinate;
			}
		else
			{
			oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_Values[i];
			}
		
		//fill out the O_VAR_NO_ITEM_COL column
		#ifdef EQ_NoItemColumnExists
			if(StrFind(oVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)
				{		
				if(oVars_NoItemOptions[i] == O_VAR_USE_NO_VALUE)
					oVars_ttbl[i][O_VAR_NO_ITEM_COL] = "a noValue";
				else if(oVars_NoItemOptions[i] == O_VAR_USE_LAST_VALUE)
					oVars_ttbl[i][O_VAR_NO_ITEM_COL] = "the last value";
				else //if(oVars_NoItemOptions[i] == O_VAR_USE_CONSTANT)
					oVars_ttbl[i][O_VAR_NO_ITEM_COL] = oVars_NoItemConstants[i];
				}
			else
				{
				oVars_ttbl[i][O_VAR_NO_ITEM_COL] = "-";
				}
		#endif
		
		}//for(i=0; i<oVars_NumTableRows; i++)

	DTGrowButton(MyBlockNumber(), "oVars_ttbl", TRUE);
	DTHideLinkButton(MyBlockNumber(), "oVars_ttbl", TRUE);
	SetDTRowStart(MyBlockNumber(), "oVars_ttbl", 1);
	//define column tag as popup menu for first column
	DTColumnTagSet(MyBlockNumber(), "oVars_ttbl", O_VAR_TYPE_COL, TAG_POPUP, 0, "", "");
	
	#ifdef EQ_IsItemBlock
		namesColTagArrayIndex = oVars_SetNamesColTagArray();
		DTColumnTagSet(MyBlockNumber(), "oVars_ttbl", O_VAR_NAME_COL, TAG_CONDITIONAL_POPUP_ARRAY, namesColTagArrayIndex, "usePopupTag", "");
	#endif
	
	DTColumnTagSet(MyBlockNumber(), "oVars_ttbl", O_VAR_VALUE_COL, TAG_CONDITIONAL_POPUP, O_VAR_TYPE_COL, "DB ", "");
	
	#ifdef EQ_NoItemColumnExists
		DTColumnTagSet(MyBlockNumber(), "oVars_ttbl", O_VAR_NO_ITEM_COL, TAG_CONDITIONAL_POPUP, O_VAR_TYPE_COL, "Connector", "");
	#endif

	//get info on iVars_ttbl frame
	DIPositionGet(MyBlockNumber(), "oVars_ttbl", positionArray);
	DIPositionSet(MyBlockNumber(), "oVars_ttbl", positionArray[0], positionArray[1], positionArray[2], positionArray[3]+60);	//set max width of iVars_ttbl frame

	//set conditional column widths
	#ifdef EQ_IsItemBlock
		SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 1, 140, TRUE);
	#else
		SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 1, 110, TRUE);
	#endif
	
	#ifdef v8
		SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 1, 140, TRUE);
		SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 2, 140, TRUE);
	#endif


	#ifdef EQ_IsItemBlock
		
		#ifdef EQ_IsEquationItemBlock
			SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 5, 1, TRUE);
		#endif
		
		#ifdef EQ_IsQueryEquationItemBlock
			SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 5, 1, TRUE);
		#endif
		
		#ifdef EQ_IsQueueEquation
			SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 4, 1, TRUE);
		#endif
	
	#else
		
		SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 4, 25, TRUE); // chiu, 05/26/2015
		
	#endif

	SetDTColumnWidth(MyBlockNumber(), "oVars_ttbl", 4, 50, TRUE); // chiu, 05/26/2015


}//procedure oVars_TableSetup()


//get the current settings before the user has made his new choice.  these soon to be "old" settings 
//need to be stored so that we can reconnect oVarsOut should the user's new choice demand that.
procedure oVars_GetOldSettings()
{
	integer i;
	
	for(i=0; i<oVars_NumTableRows; i++)
		{
		oVars_VarIsWhichConOld[i] = oVars_VarIsWhichCon[i];
		}

}//procedure oVars_GetOldSettings()


//store iVars_VarIsWhichCon[] in iVars_VarIsWhichConOld[] before the user has made his new 
//choice. these soon to be "old" settings need to be stored so that we can auto reconnect iVarsIn.
procedure oVars_GetVarIsWhichConOld()
{
	integer i;
	integer numRows;
	
	numRows = GetDimension(oVars_VarIsWhichCon);
	
	for(i=0; i<numRows; i++)
		{
		oVars_VarIsWhichConOld[i] = oVars_VarIsWhichCon[i];
		}

}//procedure oVars_GetVarIsWhichConOld()


procedure oVars_ShowTypesPopup()
{

	integer i, j;
	integer varTypePopSize;
	integer found;
	integer placeFound;
	integer usersResponse;
	string theString;
	integer numChars;
	integer numIvarCons;

	oVars_GetOldSettings();
	
	//fill the oVars_TypesPop array
	oVars_GetVarTypes();
	varTypePopSize = EQ_GetVarPopSize(oVars_PopOptions);
	MakeArray(oVars_TypesPop, varTypePopSize);
	EQ_BuildVarTypesPopContentsArray(oVars_TypesPop, oVars_PopOptions);
	
	//figure out where the CURRENT chosen variable type resides in the oVars_TypesPop array.
	found = FALSE;
	placeFound = 0;
	for(i=0; i<varTypePopSize; i++)
		{
		//4/19/11
		if(oVars_Types_int[rowClicked] == EQ_DBQS_ATTRIB)
			{
			if(oVars_Types_str[rowClicked] == oVars_TypesPop[i])
				{
				found = TRUE;
				placeFound = i+1;
				break;
				}
			}
		else
			{
			if(StrFind(oVars_Types_str[rowClicked], oVars_TypesPop[i], FALSE, FALSE) >= 0)
				{
				found = TRUE;
				placeFound = i+1;
				break;
				}
			}
		}
	
	//show the popup menu and record the response
	usersResponse = PopupMenuArray(oVars_TypesPop, placeFound);	//show the iVar types pop and record the user's response
	
	//if user chosen a different output variable type for rowClicked	
	if(usersResponse != placeFound)
		{
	
		//save the user's response as a string- used to build the first column of oVars_ttbl
		oVars_Types_str[rowClicked] = oVars_TypesPop[usersResponse - 1];	//-1 for popup menu indexing
		
		//set attrib type to no attrib
		oVars_AttribTypes[rowClicked] = ATTRIB_TYPE_NO_ATTRIB;

		//save the user's response as an integer
		oVars_Types_Int[rowClicked] = EQ_VarTypeGet(oVars_Types_str[rowClicked]);
		
		//set up oVars_Names based on what the user chose in the types column, ie, give the new variable a default name
		if(oVars_Types_str[rowClicked] != "Connector"  &&  oVars_Types_str[rowClicked] != "_Select con")
			{
			//item info variables
			if(StrFind(oVars_Types_str[rowClicked], "attrib", FALSE, FALSE) >= 0)
				oVars_Names[rowClicked] = "None";
			else if(oVars_Types_str[rowClicked] == "Item quantity")
				oVars_Names[rowClicked] = "qtyOut_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "Item priority")
				oVars_Names[rowClicked] = "priorityOut_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "3D object ID")
				oVars_Names[rowClicked] = "3DOut_" + rowClicked;
				
			//DB variables
			else if(oVars_Types_str[rowClicked] == "DB write value")
				oVars_Names[rowClicked] = "DBWVOut_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "DB write PRI")
				oVars_Names[rowClicked] = "DBWPRIOut_" + rowClicked;
			
			//DBQ variables
			else if(oVars_Types_str[rowClicked] == "DBQ record rank")
				oVars_Names[rowClicked] = "rRank_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "DBQ record rank")
				oVars_Names[rowClicked] = "prRank_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "DBQS record rank")
				oVars_Names[rowClicked] = "srRank_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "DBQ halt query")
				oVars_Names[rowClicked] = "DBQHQ_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "DBQ next record")
				oVars_Names[rowClicked] = "DBQNextR_" + rowClicked;
			
			//random variables
			else if(oVars_Types_str[rowClicked] == "Calc event time")
				oVars_Names[rowClicked] = "eventTime";
			
			//queue equation variables
			else if(oVars_Types_str[rowClicked] == "QEQ item rank")			//the rank assigned to an item after the euation has calculated
				oVars_Names[rowClicked] = "iRank_" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "QEQ halt calculation cycle")			//the rank assigned to an item after the euation has calculated
				oVars_Names[rowClicked] = "haltCycle" + rowClicked;
				
			//queue equation advance resources variables
			else if(oVars_Types_str[rowClicked] == "AR requirement is avail")			//the rank assigned to an item after the euation has calculated
				oVars_Names[rowClicked] = "arIsAvail" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "AR num requirements avail")			//the rank assigned to an item after the euation has calculated
				oVars_Names[rowClicked] = "arNumAvail" + rowClicked;
			else if(oVars_Types_str[rowClicked] == "AR allocate requirement")			//the rank assigned to an item after the euation has calculated
				oVars_Names[rowClicked] = "arAllocate";
			
			oVars_Values[rowClicked] = blank;
			}

		//rename the connector varNames and varTypes
		j = 0;
		for(i=0; i<oVars_NumTableRows; i++)
			{
			if(StrFind(oVars_Types_str[i], "Connector", FALSE, FALSE) >= 0)	//it's a connector variable
				{
				//make sure the varType has the correct connector index
				oVars_Types_str[i] = "Connector " + j;
				
				//if using default var name, rename it with the correct connector index
				if(StrFind(oVars_Names[i], "outCon", FALSE, FALSE) != -1  ||  i == rowClicked)
					oVars_Names[i] = "outCon" + j;

				//if i = rowClicked, set the varValue to blank
				if(i == rowClicked)
					oVars_Values[i] = blank;

				j++;
				}
			}
		
		oVarsOut_Reconnect(DIALOG_CLICK_VAR_TYPE);
		
		}//if(usersResponse != placeFound)
	
	DisposeArray(oVars_TypesPop);
	DisposeArray(oVars_PopOptions);

}//procedure oVars_ShowTypesPopup()

/*
procedure oVars_ShowNoItemOptionsPopup()
{

	integer i;
	string oVars_NoItemOptionsPop[3];
	real oldConstant;
	real newConstant;

	//build the oVars_NoItemOptionsPop[] array- used for creating the flying popup
	oVars_NoItemOptionsPop[0] = "No Value";
	oVars_NoItemOptionsPop[1] = "The last value";
	oVars_NoItemOptionsPop[2] = "The value...";
	
	//show the popup menu and record the response
	oVars_NoItemOptions[rowClicked] = PopupMenuArray(oVars_NoItemOptionsPop, oVars_NoItemOptions[rowClicked]);	//show the oVar types pop and record the user's response

	//show message box for user to enter a constant
	if(oVars_NoItemOptions[rowClicked] == O_VAR_USE_CONSTANT)
		{
		oldConstant = oVars_NoItemConstants[rowClicked];
		newConstant = NumericParameter("Please enter the value to report for " + oVars_Names[rowClicked] + " if no item is present.", oldConstant);
		
		if(NoValue(newConstant))
			oVars_NoItemConstants[rowClicked] = oldConstant;
		else
			oVars_NoItemConstants[rowClicked] = newConstant;
		}

	oVars_TableSetup();

}//procedure oVars_ShowNoItemOptionsPopup()
*/

//called in EQ_Calc()
#ifdef EQ_IsItemBlock
	procedure oVars_PostResults(integer itemIndex, integer sendMsgs)
#else
	procedure oVars_PostResults(integer sendMsgs)
#endif
{
	
	integer i;
	integer batchID;
	integer batchSize;
	integer	conNameLength;
	integer whichCon;
	integer databaseIndex;
	integer tableIndex;
	integer fieldIndex;
	integer recordIndex;
	integer fieldType;
	integer legitField;
	integer numRecords;
	
	#ifdef EQ_IsValueBlock
	
		for(i=0; i<oVars_NumTableRows; i++)
			{
			
			#ifdef oVarsOut
			
				if(oVars_Types_Int[i] == EQ_CONNECTORS)
					{
					if(oVars_VarIsWhichCon[i] == -1)
						{
						UserError("There is a problem with " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
						AbortAllSims();
						}
						
					ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);
					}
				
			#endif
	
			else if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL)
				{
				legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
				if(!legitField)
					AbortAllSims();

				//if targeted field is of type "Date Time", then convert the number being written to Julian format.
				//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
				fieldType = DBFieldGetPropertiesUsingAddress(oVars_DBCoords[i], 1) ;	//where 1 = fieldType
				if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
					{
					oVars_Values[i] = EDSimTimeToDate(oVars_Values[i], 0);
					}

				DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
				}

			else if(oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
				{
				//with this option, the chosen field must be a child
				legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
				if(!legitField)
					AbortAllSims();
				
				//with this option user wants to set a parent index in a child
				DBDataSetAsParentIndexUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
				}

			else if(oVars_Types_Int[i] == EQ_DB_ADDRESS)
				{
				//db addresses not allowed as an output variable
				UserError("There is a problem with " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
				AbortAllSims();
				}

			}
	
	#endif //EQ_IsValueBlock


	#ifdef EQ_IsItemBlock
	
		if(itemIndex > 0)
			{
			
			for(i=0; i<oVars_NumTableRows; i++)
				{
				
				if(oVars_Types_Int[i] == EQ_ITEM_QTY)
					{
					#ifdef itemArrayR
					
						if(NoValue(oVars_Values[i]))
							{
							UserError("Error!  About to set a 'noValue' as the quantity on an item in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
							AbortAllSims();
							}
					
						itemArrayR[itemIndex][0] = oVars_Values[i];
						
					#endif
					}
					
				else if(oVars_Types_Int[i] == EQ_ITEM_3D_ID)
					{
					#ifdef ItemArray3D
					
						if(NoValue(oVars_Values[i]))
							{
							UserError("Error!  About to set a 'noValue' as the 3D Object ID on an item in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
							AbortAllSims();
							}
					
						ItemArray3D[itemIndex][0] = oVars_Values[i];
						
					#endif
					}
					
				else if(oVars_Types_Int[i] == EQ_ITEM_PRIORITY)
					{
					#ifdef itemArrayR
						
						if(NoValue(oVars_Values[i]))
							{
							UserError("Error!  About to set a 'noValue' as the priority on an item in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
							AbortAllSims();
							}
		
						itemArrayR[itemIndex][1] = oVars_Values[i];
						
					#endif
					}
						
				else if(oVars_Types_Int[i] == EQ_CONNECTORS)
					{
					#ifdef oVarsOut
						
						if(oVars_VarIsWhichCon[i] == -1)
							{
							UserError("There is a problem with " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
							AbortAllSims();
							}
						
						ConArraySetValue(oVarsOut, oVars_VarIsWhichCon[i], oVars_Values[i]);
							
					#endif
					}
	
				else if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL)
					{
					legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
					if(!legitField)
						AbortAllSims();

					//if targeted field is of type "Date Time", then convert the number being written to Julian format.
					//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
					fieldType = DBFieldGetPropertiesUsingAddress(oVars_DBCoords[i], 1) ;	//where 1 = fieldType
					if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
						{
						oVars_Values[i] = EDSimTimeToDate(oVars_Values[i], 0);
						}

					DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
					}
	
				else if(oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
					{
					//with this option, the chosen field must be a child
					legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
					if(!legitField)
						AbortAllSims();
					
					//with this option user wants to set a parent index in a child
					DBDataSetAsParentIndexUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
					}
	
				else if(oVars_Types_Int[i] == EQ_DB_ADDRESS)
					{
					//db addresses not allowed as an output variable
					UserError("There is a problem with " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
					AbortAllSims();
					}

				else if(oVars_Types_Int[i] == EQ_QEQ_ITEM_RANK)
					{
					//do nothing
					}
					
				#ifdef EQ_IsQueryEquationTypeBlock
				
					else if(oVars_Types_Int[i] == EQ_DBQ_RECORD_RANK)
						{
						//do nothing
						}
					
					else if(oVars_Types_Int[i] == EQ_DBQ_RECORD_RANK)
						{
						//do nothing
						}
					
					else if(oVars_Types_Int[i] == EQ_DBQS_RECORD_RANK)
						{
						//do nothing
						}
					
					else if(oVars_Types_Int[i] == EQ_DBQ_HALT_QUERY)
						{
						DBQ_HaltQueryCycle = oVars_Values[i];
						}
					
					else if(oVars_Types_Int[i] == EQ_DBQ_NEXT_RECORD)
						{
						DBQ_NextRecordInQueryCycle = oVars_Values[i];
						}
						
				#endif
				
				else if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL_USING_ATTRIB)
					{
					//...with this option user wants to set a value in the db using a db attrib to specify the coordinate
					oVars_DBCoords[i] = Attrib_GetVal(itemIndex, oVars_AttribColumnIndexes[i], REPORT_NO_DB_INFO);

					legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
					if(!legitField)
						AbortAllSims();

					//if targeted field is of type "Date Time", then convert the number being written to Julian format.
					//why?  because all time numbers calculated in an equation are ALWAYS in simTime time units.
					fieldType = DBFieldGetPropertiesUsingAddress(oVars_DBCoords[i], 1) ;	//where 1 = fieldType
					if(fieldType == DB_FIELDTYPE_REAL_DATE_TIME  &&  convertDateTimeData_chk)
						{
						oVars_Values[i] = EDSimTimeToDate(oVars_Values[i], 0);
						}

					DBDataSetAsNumberUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
					}
				
				else if(oVars_Types_Int[i] == EQ_DB_WRITE_PRI_USING_ATTRIB)
					{						
					//with this option, the chosen field must be a child
					oVars_DBCoords[i] = Attrib_GetVal(itemIndex, oVars_AttribColumnIndexes[i], REPORT_NO_DB_INFO);
					legitField = oVars_CheckChosenField(i, oVars_DBCoords[i]);
					if(!legitField)
						AbortAllSims();
					
					//...with this option user wants to set a parent index in a child using a db attrib to specify the coordinate
					DBDataSetAsParentIndexUsingAddress(oVars_DBCoords[i], oVars_Values[i]);
					}
				
				else if(oVars_Types_Int[i] == EQ_ITEM_ATTRIBUTE)	//if oVar is an attrib var,...
					{
					Attrib_SetVal(oVars_Values[i], itemIndex, oVars_AttribColumnIndexes[i]);
					
					if(oVars_AttribTypes[i] == ATTRIB_TYPE_DB)
						{
						if(expandRecords_chk == TRUE)	//10/29/08, 7.0.5, AJN
							{
							databaseIndex = DBDatabaseGetIndexFromAddress(oVars_Values[i]);
							tableIndex = DBTableGetIndexFromAddress(oVars_Values[i]);
							recordIndex = DBRecordGetIndexFromAddress(oVars_Values[i]);
							numRecords = DBRecordsGetNum(databaseIndex, tableIndex);
							if(numRecords < recordIndex)
								{
								DBRecordsInsert(databaseIndex, tableIndex, 0, (recordIndex-numRecords));
								}
							}
						}
					}
						
				}//for(i=0; i<oVars_NumTableRows; i++)
				
			}//if(itemIndex > 0)
			
		else
			{
			UserError("Trying to access an invalid itemIndex in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".  Please contact Imagine That.");
			}
			
	#endif //if EQ_IsItemBlock
			
	//conditionally update the table dynamically.
	if(oVars_TableIsCloned  ||  dialogIsOpen)
		{
		for(i=0; i<oVars_NumTableRows; i++)
			{
			//if(StrFind(oVars_Types_str[i], "attrib", FALSE, FALSE) >= 0  &&  oVars_AttribTypes[i] == 2)	//10/24/08- don't need to reference oVars_Types_str[] here
			if(oVars_AttribTypes[i] == 2)
				oVars_ttbl[i][O_VAR_VALUE_COL] = SLStringGet(oVars_ttbl[i][I_VAR_NAME_COL], oVars_Values[i]);
			
			else if(oVars_Types_Int[i] != EQ_DB_WRITE_VAL  &&  oVars_Types_Int[i] != EQ_DB_WRITE_PRI  &&  oVars_Types_Int[i] != EQ_DB_ADDRESS)
				oVars_ttbl[i][O_VAR_VALUE_COL] = oVars_Values[i];
			}
		}

	oVarsOut_ConLabelsSet();

	//update proof
	#ifdef sendProof_chk
		if(sendProof_chk)				// DJK if the checkbox to send the proof string is turned on 
			GlobalProofStr = "";
		if(sendProof_chk)
			{
			PassStringToProof[0] = GlobalProofStr;
			GASetInteger(MyBlockNumber(),GAProof,PRF_BLOCK_NUMBER,0);	// set the paused flag in the global array
			GASetInteger(-1,GAProof,PRF_COMMAND_TYPE,0);					// this indicates that the 
			SendMsgToBlock(ProofBlock,BlockReceive4Msg);			// Send the proof command to the proof control block
			}
	#endif

	//conditionally send messages through output connectors
	if(sendMsgs == TRUE  &&  modelType == DISCRETE_EVENT)
		{
		for(i=0; i<oVarsOut_NumCons; i++)
			{
			if(oVarsOut_NumBlocksConnected[i] >= 1)
				SendMsgToInputs(oVarsOut_ConNums[i]);
			}
		}
		
}//procedure oVars_PostResults(integer itemIndex)



//**********************************************************************
//END "oVars" Functions
//**********************************************************************
//**********************************************************************



//**********************************************************************
//**********************************************************************
//START "oVarsOut_" Functions
//**********************************************************************


#ifdef EQ_IsValueBlock
/*
procedure oVarsOut_OnOVarsOut()
{

	integer i;
	integer whichCon;
	
	whichCon = ConArrayMsgFromCon();
	
	if(inIVarsIn == TRUE  ||  inOVarsOut == TRUE  ||  inGoIn == TRUE  ||  inLinkContent == TRUE  ||  inBlockReceive1 == TRUE  ||  inPostInitSim == TRUE    ||  inFinalCalc == TRUE)
		{
		return;
		}
	else
		{
		inOVarsOut = TRUE;
		}
	
	if(CW_OVarsOut_CalcControl_chk)
		{
		
		if(CW_OVarsOut_WhichConnector == -1  ||  whichCon == CW_OVarsOut_WhichConnector)	//-1 if the  "respond to any connecter msg" option was chosen
			{
			if(CW_OVarsOut_RespondWhen_pop == WHEN_CALC_IMMEDIATE)
				{
				//iVarsIn msgs
				iVarsIn_SendMsgs(MSG_RECEIVED_FROM_OVARS_OUT);

				#ifdef EQ_IsEquationValue
					EQ_Calc(FALSE, FALSE);		//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
									
				#ifdef EQ_IsQueryEquationValueBlock
					DBQPT_BestRecordInQueryCycle = DBQ_DoQuery(FALSE, FALSE);			//FALSE- no iVar msgs, FALSE- no oVar msgs
				#endif
									
				//oVarsOut msgs
				oVarsOut_SendMsgs(MSG_RECEIVED_FROM_OVARS_OUT);

				//post this block's next event
				if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
					{
					nextCalcEventTime = EQ_GetNextCalcEventTime();		//	8/21/09
					timeArray[myIndex_FutureEvent] = nextCalcEventTime;			
					lastCalculatedEventTime = nextCalcEventTime;	//	5/15/09
					}
				}
			else//if(CW_OVarsOut_RespondWhen_pop == WHEN_CALC_CURRENT_EVENT)
				{
			  	//post current event
			  	if(!rescheduled)
			  		{
					rescheduled = TRUE;
					SysGlobalInt8 = MyBlockNumber();
					SendMsgToBlock(exec,BLOCKRECEIVE3MSG);		//schedules a BlockReceive0 current event
					}
				}
			}
		
		}//if(CW_OVarsOut_CalcControl_chk)
	
	TCE_TraceConnectors();

	inOVarsOut = FALSE;

}//procedure oVarsOut_OnOVarsOut()
*/
#endif //EQ_IsValueBlock



#ifdef oVarsOut

	on oVars_ShowConNames_chk
		{
		oVarsOut_ConLabelsSet();
		}

	on oVars_ShowConVals_chk
		{
		oVarsOut_ConLabelsSet();
		}
	
#endif //oVarsOut


//this function makes sure that the output connectors have been managed properly.
//this function can only be called during CHECKDATA!
procedure oVarsOut_CheckConOutputs()
{
	
#ifdef oVarsOut

	integer	i, j;
	string varName;
	integer whichCon;
	integer conUsedInEq;
	integer numChars;
	integer varTypeIsConnector;
	integer varTypeIsSelect;

	for(i=0; i<oVarsOut_NumCons; i++)
		{

		for(j=0; j<oVars_NumTableRows; j++)
			{
			
			varTypeIsConnector = StrPart(oVars_Types_str[j], 0, 9) == "Connector";
			varTypeIsSelect = StrPart(oVars_Types_str[j], 0, 11) == "_Select con";
			
			if(varTypeIsConnector  ||  varTypeIsSelect)
				{
				
				//find out which connector was selected in this row
				numChars = StrLen(oVars_Types_str[j]);
				if(varTypeIsConnector)
					whichCon = StrToReal(StrPart(oVars_Types_str[j], 10, numChars));
				else //if(varTypeIsSelect)
					whichCon = StrToReal(StrPart(oVars_Types_str[j], 12, numChars));
					
				if(whichCon == i)
					{
					varName = oVars_Names[j];
					conUsedInEq = StrFindDynamic(EQ_EquationText, varName, FALSE, FALSE, TRUE);
					
					if(conUsedInEq == -1  &&  oVarsOut_NumBlocksConnected[i] >= 1)
						{
						UserError("Output connector " + i + " is connected, but it is not used in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".");
						AbortAllSims();
						}
							
					else if(conUsedInEq > -1  &&  oVarsOut_NumBlocksConnected[i] < 1)
						{
						UserError("Output connector " + i + " is not connected, but it is used in " + BlockName(MyBlockNumber()) + " block " + MyBlockNumber() + ".");
						AbortAllSims();
						}
					}
				
				}//if(varTypeIsConnector  ||  varTypeIsSelect)

			}//for(j=0; j<oVars_NumTableRows; j++)
			
		}//for(i=0; i<oVarsOut_NumCons; i++)
				
#endif //oVarsOut

}//integer oVarsOut_CheckConOutputs()


procedure oVarsOut_ConnectorsSetup()
{

#ifdef oVarsOut
	
	integer i;
	integer showCon;
	integer numCons;
	integer me;
	
	me = MyBlockNumber();
		
	//calc numCons and calc show/hide status
	numCons = 0;
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//if(StrFind(oVars_Types_str[i], "Connector", FALSE, FALSE) != -1  ||  StrFind(oVars_Types_str[i], "_Select con", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
		if(oVars_Types_Int[i] == EQ_CONNECTORS)
			{
			numCons++;
			}
		}
	if(numCons >= 1)
		{
		showCon = TRUE;
		}
	else //if(numCons == 0)
		{
		showCon = FALSE;
		numCons = 1;		//always need at least one connector
		}
	
	//set num connectors
	oVarsOut_NumConsOld = oVarsOut_NumCons;
	oVarsOut_NumCons = numCons;
	ConArraySetNumCons(me, "oVarsOut", oVarsOut_NumCons, TRUE);
		
	//setup connector arrays and get connector info
	MakeArray(oVarsOut_NumBlocksConnected, oVarsOut_NumCons);
	MakeArray(oVarsOut_ConNums, oVarsOut_NumCons);
	for(i=0; i<oVarsOut_NumCons; i++)									
		{
		oVarsOut_ConNums[i] = ConArrayGetConNumber(me, "oVarsOut", i);
		oVarsOut_NumBlocksConnected[i] = GetConBlocks(me, oVarsOut_ConNums[i], connected);
		}
		
	//show/hide oVarsOut
	if(showCon == TRUE)
		SetConVisibility(me, oVarsOut_ConNums[0], TRUE);
	else
		SetConVisibility(me, oVarsOut_ConNums[0], FALSE);

	oVarsOut_VarIsWhichConUpdate();
	oVarsOut_ConIsWhichVarUpdate();

#endif //oVarsOut

}//procedure oVarsOut_ConnectorsSetup()



#ifdef EQ_IsValueBlock
/*
procedure oVarsOut_SendMsgs(integer calledFrom)
{
	integer i, j;
	integer msgFromCon;
	integer numConBlocks;
	integer msgSendingBlock;
	
	//conditionally send oVarsOut msgs
	if(EQ_Calcing == TRUE)
		{
		return;
		}
	
	if(!CMC_chk)
		{
		//NOTE: if(!CMC_chk), then connector messaging behavior is exactly like message emulation
		if(calledFrom != MSG_RECEIVED_FROM_OVARS_OUT)
			{
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				if(oVarsOut_NumBlocksConnected[i] >= 1)
					SendMsgToInputs(oVarsOut_ConNums[i]);
				}
			}
		}
	
	else //if(CMC_chk)
		{
		if(calledFrom == MSG_RECEIVED_FROM_OVARS_OUT)
			{
			msgFromCon = ConArrayMsgFromCon();
			CMC_OVarsOut_GetConChanged();			//fills out the CMC_OVars_ValChanged[] array
			
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				if(oVarsOut_NumBlocksConnected[i] >= 1)						//if connector is connected
					{
					if(i != msgFromCon)										//if this con didn't receive the initiating msg
						{
						if
						  (
							(CMC_OVarsOut_Settings[i] == CMC_OVAR_ALWAYS)  ||
							(CMC_OVarsOut_Settings[i] == CMC_OVAR_VAL_CHANGE_ONLY  &&  CMC_OVars_ValChanged[i])
						  )
							{
							SendMsgToInputs(oVarsOut_ConNums[i]);
							}
							//NOTE!! if con behavior has been set to msg emulation, NEVER send a message here.  why?  because 
							//message emulation dictates that we NEVER send a message if the msg was received from oVarsOut
						}
					
					else //if this is the oVarsOut connector that received the initiating message,...
						{
						if(oVarsOut_NumBlocksConnected[i] > 1)	//...and if there is more than one block connected to this oVarsOut connector,...
							{
							if
							  (
								(CMC_OVarsOut_Settings[i] == CMC_OVAR_ALWAYS)  ||
								(CMC_OVarsOut_Settings[i] == CMC_OVAR_VAL_CHANGE_ONLY  &&  CMC_OVars_ValChanged[i])
							  )
								{
								msgSendingBlock = GetMsgSendingBlock();
								numConBlocks = oVarsOut_NumBlocksConnected[i];
								for(j=0; j<numConBlocks; j++)
									{
									if(CMC_OVarsOut_ConBlocks[j][0] != msgSendingBlock)
										SendConnectorMsgToBlock(CMC_OVarsOut_ConBlocks[j][0], CMC_OVarsOut_ConBlocks[j][1]);
									}
								}
							}
						}
					}
				}
			}		

		else //if(calledFrom != MSG_RECEIVED_FROM_OVARS_OUT)
			{
			CMC_OVarsOut_GetConChanged();			//fills out the CMC_OVars_ValChanged[] array
			
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				if(oVarsOut_NumBlocksConnected[i] >= 1)
					{
					if
					  (
						(CMC_OVarsOut_Settings[i] == CMC_OVAR_MSG_EMULATION)  ||  
						(CMC_OVarsOut_Settings[i] == CMC_OVAR_ALWAYS)  ||  
						(CMC_OVarsOut_Settings[i] == CMC_OVAR_VAL_CHANGE_ONLY  &&  CMC_OVars_ValChanged[i])  
					  )
						{
						SendMsgToInputs(oVarsOut_ConNums[i]);
						}
					}
				}
			}
		}

}//procedure oVarsOut_SendMsgs(integer calledFrom)
*/
#endif //EQ_IsValueBlock


procedure oVarsOut_ConLabelsSet()
{

#ifdef oVarsOut

	integer i;
	string addString;
	integer iconView;
	string side;
	integer me;
	integer whichCon;
	integer simPhase;
	real conVal;

	me = MyBlockNumber();
	simPhase = GetSimulationPhase();

	//7/19/10
	if(!oVars_ShowConNames_chk  &&  !oVars_ShowConVals_chk)
		{
		if(simPhase == PHASE_NOT_CURRENTLY_RUNNING)
			{
			MakeArray(oVarsOut_ConnectorLabels, oVarsOut_NumCons);				
	
			for(i=0; i<oVarsOut_NumCons; i++)
				oVarsOut_ConnectorLabels[i] = "";
	
			ConnectorLabelsSet(me, ConArrayGetConNumber(me, "oVarsOut", 0), oVarsOut_NumCons, oVarsOut_ConnectorLabels, BOTTOM_SIDE, 0, 0, 0);
		
			DisposeArray(oVarsOut_ConnectorLabels);
			}
		}
		
	else
		{
	
		//7/19/10
		if(simPhase == PHASE_NOT_CURRENTLY_RUNNING  ||  GetDimension(oVarsOut_ConnectorLabels) != oVarsOut_NumCons)
			{
			
			//7/19/10:  setup the oVarsOut_ConnectorLabels[] array
			if(oVars_ShowConNames_chk  ||  oVars_ShowConVals_chk)
				{
				iconView = IconGetView(me);
			
				if(iconView == 0)						//where 0 = "Left to right"
					side = "<r>";
				else
					side = "<l>";
			
				MakeArray(oVarsOut_ConnectorLabels, oVarsOut_NumCons);
				for(i=0; i<oVarsOut_NumCons; i++)
					{
					oVarsOut_ConnectorLabels[i] = side;
					}
				}
		
			//7/19/10:  add the connector names to oVarsOut_ConnectorLabels[] array
			if(oVars_ShowConNames_chk)
				{
				for(i=0; i<oVars_NumTableRows; i++)
					{
					if(oVars_Types_Int[i] == EQ_CONNECTORS)
						{
						whichCon = oVars_VarIsWhichCon[i];
						oVarsOut_ConnectorLabels[whichCon] += oVars_Names[i];
						}
					}
			
				//animate the oVars
				ConnectorLabelsSet(me, ConArrayGetConNumber(me, "oVarsOut", 0), oVarsOut_NumCons, oVarsOut_ConnectorLabels, BOTTOM_SIDE, 0, 0, 0);
				}
			
			}//if(simPhase == PHASE_NOT_CURRENTLY_RUNNING)
	
	
		if(oVars_ShowConVals_chk)
			{
			MakeArray(oVarsOut_ConnectorLabelsTemp, oVarsOut_NumCons);
			
			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(oVars_Types_Int[i] == EQ_CONNECTORS)
					{
					whichCon = oVars_VarIsWhichCon[i];
					conVal = oVars_Values[i];
					oVarsOut_ConnectorLabelsTemp[whichCon] = oVarsOut_ConnectorLabels[whichCon] + " = " + conVal;
					}
				}
		
			//animate the oVars
			ConnectorLabelsSet(me, ConArrayGetConNumber(me, "oVarsOut", 0), oVarsOut_NumCons, oVarsOut_ConnectorLabelsTemp, BOTTOM_SIDE, 0, 0, 0);
			
			DisposeArray(oVarsOut_ConnectorLabelsTemp);
			}
		}
	
#endif

}//procedure oVarsOut_ConLabelsSet()


//called in oVarsOut_Reconnect only!  into the "old" connector arrays, store the state of the connectors before connection are deleted.
procedure oVarsOut_GetOldConInfo()
{

#ifdef oVarsOut

	integer i;
	integer nextCon;

	MakeArray(oVarsOut_ConnectedBlocksOld, oVarsOut_NumCons);
	MakeArray(oVarsOut_ConnectedConsOld, oVarsOut_NumCons);
	MakeArray(oVarsOut_TextBlockNums, oVarsOut_NumCons);

	//initialize the con info arrays
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		oVarsOut_ConnectedBlocksOld[i] = -1;
		oVarsOut_ConnectedConsOld[i] = -1;
		}

	//get data about the connection to oVarsOut
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		//get connected block info
		nextCon = ConArrayGetConNumber(MyBlockNumber(), "oVarsOut", i);
		oVarsOut_NumBlocksConnected[i] = GetConBlocks(MyBlockNumber(), nextCon, connected);
		oVarsOut_TextBlockNums[i] = GetConnectedTextBlock(MyBlockNumber(), oVarsOut_ConNums[i]);	//is conn is connected to a TEXT block?

		//if connector is connected to a TEXT block
		if(oVarsOut_TextBlockNums[i] >= 0)
			{
			oVarsOut_ConnectedBlocksOld[i] = oVarsOut_TextBlockNums[i];
			oVarsOut_ConnectedConsOld[i] = -1;
			}
		
		//else if conn is connected to another conn
		else if(oVarsOut_NumBlocksConnected[i] >= 1)
			{
			oVarsOut_ConnectedBlocksOld[i] = connected[0][0];
			oVarsOut_ConnectedConsOld[i] = connected[0][1];
			}

		}

	DisposeArray(connected);

#endif

}//procedure oVarsOut_GetOldConInfo()

/*
//called in oVarsOut_Reconnect only!  after connections have been deleted, reset connector info.
procedure oVarsOut_GetNewConInfo()
{
	
#ifdef oVarsOut

	integer i;
	string conVarName;
	integer theConThatGotAdded;
	integer theConThatGotDeleted;
	integer conChange;
	
	//initialize the con info arrays
	MakeArray(oVarsOut_ConnectedBlocks, oVarsOut_NumCons);
	MakeArray(oVarsOut_ConnectedCons, oVarsOut_NumCons);
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		oVarsOut_ConnectedBlocks[i] = -1;
		oVarsOut_ConnectedCons[i] = -1;
		}

	conChange = oVarsOut_NumCons - oVarsOut_NumConsOld;

	//if the number of connectors did not change
	if(conChange == 0)
		{
		for(i=0; i<oVarsOut_NumCons; i++)
			{
			oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i];
			oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i];
			}
		}
	
	//if the number of connectors increased by 1 (ie, old will be smaller)...
	else if(conChange == 1)
		{
		theConThatGotAdded = oVars_VarIsWhichCon[rowClicked];

		//if(oVarsOut_NumCons > 1)									//4/21/09
		if(oVarsOut_NumCons > 1  &&  theConThatGotAdded >= 0)		//this is a ">" not a ">=" because if going from zero con vars to one con var, then there are no connectios to remake
			{
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				if(i < theConThatGotAdded)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i];
					}
			
				else if(i == theConThatGotAdded)
					{
					oVarsOut_ConnectedBlocks[i] = -1;
					oVarsOut_ConnectedCons[i] = -1;
					}
			
				else if(i > theConThatGotAdded)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i-1];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i-1];
					}
				}
			}
		}
			
	//if the number of connectors decreased by 1 (ie, old will be larger)...
	else if(conChange == -1)
		{
		theConThatGotDeleted = oVars_VarIsWhichConOld[rowClicked];
			
		//if(oVarsOut_NumConsOld > 1)									//4/21/09
		if(oVarsOut_NumConsOld > 1  &&  theConThatGotDeleted >= 0)		//this is a ">" not a ">=" because if going from one con var to zero con var, then there are no connectios to remake
			{
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				if(i < theConThatGotDeleted)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i];
					}
					
				if(i >= theConThatGotDeleted)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i+1];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i+1];
					}
				}
			}
		}
		
#endif //oVarsOut

}//procedure oVarsOut_GetNewConInfo()
*/

//called in oVarsOut_Reconnect only!  after connections have been deleted, reset connector info.
procedure oVarsOut_GetNewConInfo(integer calledFrom)
{
	
#ifdef oVarsOut

	integer i;
	string conVarName;
	integer conChange;
	integer firstAddedCon;
	integer lastAddedCon;
	integer firstDeletedCon;
	integer lastDeletedCon;
	integer oldNumCons;
	
	//initialize the con info arrays
	MakeArray(oVarsOut_ConnectedBlocks, oVarsOut_NumCons);
	MakeArray(oVarsOut_ConnectedCons, oVarsOut_NumCons);
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		oVarsOut_ConnectedBlocks[i] = -1;
		oVarsOut_ConnectedCons[i] = -1;
		}

	conChange = oVarsOut_NumCons - oVarsOut_NumConsOld;

	//if the number of connectors did not change
	if(conChange == 0)
		{
		for(i=0; i<oVarsOut_NumCons; i++)
			{
			oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i];
			oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i];
			}
		}
	
	//if num connectors grew...
	else if(conChange > 0)
		{
		if(calledFrom == DIALOG_CLICK_VAR_TYPE)
			{
			firstAddedCon = oVars_VarIsWhichCon[rowClicked];
			}
		else //if(calledFrom == DATA_TABLE_RESIZE)
			{
			firstAddedCon = oVars_VarIsWhichCon[rowClicked+1];
			}
		lastAddedCon = firstAddedCon + conChange - 1;
		
		//if(oVarsOut_NumCons > 1)									//4/21/09
		if(oVarsOut_NumCons > 1  &&  firstAddedCon >= 0)		//this is a ">" not a ">=" because if going from zero con vars to one con var, then there are no connectios to remake
			{
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				if(i < firstAddedCon)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i];
					}
			
				else if(i >= firstAddedCon  &&  i <= lastAddedCon)
					{
					oVarsOut_ConnectedBlocks[i] = -1;
					oVarsOut_ConnectedCons[i] = -1;
					}
			
				else if(i > lastAddedCon)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i-conChange];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i-conChange];
					}
				}
			}
		}
			
	//if num connectors shrunk...
	else if(conChange < 0)
		{
		oldNumCons = GetDimension(oVarsOut_ConnectedBlocksOld);
		firstDeletedCon = oVars_VarIsWhichConOld[rowClicked];
		lastDeletedCon = firstDeletedCon - conChange - 1;
		
		//if(oVarsOut_NumConsOld > 1)									//4/21/09
		if(oVarsOut_NumConsOld > 1  &&  firstDeletedCon >= 0)		//this is a ">" not a ">=" because if going from one con var to zero con var, then there are no connectios to remake
			{
			for(i=0; i<oldNumCons; i++)
				{
				if(i < firstDeletedCon)
					{
					oVarsOut_ConnectedBlocks[i] = oVarsOut_ConnectedBlocksOld[i];
					oVarsOut_ConnectedCons[i] = oVarsOut_ConnectedConsOld[i];
					}
					
				if(i > lastDeletedCon)
					{
					oVarsOut_ConnectedBlocks[i+conChange] = oVarsOut_ConnectedBlocksOld[i];
					oVarsOut_ConnectedCons[i+conChange] = oVarsOut_ConnectedConsOld[i];
					}
				}
			}
		}
		
#endif //oVarsOut

}//procedure oVarsOut_GetNewConInfo(integer calledFrom)

	integer theConThatGotAdded;
	integer theConThatGotDeleted;

procedure oVarsOut_Reconnect(integer calledFrom)
{

#ifdef oVarsOut

	integer i, j;
	integer newWhichCon;
	integer oldWhichCon;
	integer nextCon;
	integer numConnections;
	integer blockType;
	integer blockTypeArray[4];

	oVars_GetVarIsWhichConOld();						//make sure "old" array is filled out correctly before fiddeling with the connector arrays
	oVarsOut_GetOldConInfo();
	
	//get numbers of any connected TEXT blocks	
	MakeArray(oVarsOut_TextBlockNums, oVarsOut_NumCons);
	for(i=0; i<oVarsOut_NumCons; i++)
		oVarsOut_TextBlockNums[i] = GetConnectedTextBlock(MyBlockNumber(), oVarsOut_ConNums[i]);

	//delete all connections to oVarsOut	
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		nextCon = ConArrayGetConNumber(MyBlockNumber(), "oVarsOut", i);
		numConnections = GetConBlocks(MyBlockNumber(), nextCon, connected);
		if(numConnections > 0)
			{
			blockType = GetBlockTypePosition(oVarsOut_ConnectedBlocksOld[i], blockTypeArray);

			//if connected block is a TEXT block, ie, if have a named connection
			if(blockType == 2)
				ClearConnection(MyBlockNumber(), oVarsOut_ConNums[i], oVarsOut_ConnectedBlocksOld[i], 0);
			else
				ClearConnection(MyBlockNumber(), oVarsOut_ConNums[i], oVarsOut_ConnectedBlocksOld[i], oVarsOut_ConnectedConsOld[i]);
			}
		}

	oVarsOut_ConnectorsSetup();		//reset the number of connectors
	oVarsOut_GetNewConInfo(calledFrom);	

	//reconnect the oVarsOut cons based on the new "con block info" arrays
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		if(oVarsOut_ConnectedBlocks[i] != -1)	//if connector should be connected
			{
			blockType = GetBlockTypePosition(oVarsOut_ConnectedBlocks[i], blockTypeArray);
		
			//if connected block is a TEXT block, ie, if have a named connection
			if(blockType == 2)
				MakeConnection(MyBlockNumber(), oVarsOut_ConNums[i], oVarsOut_ConnectedBlocks[i], 0);
			else	
				MakeConnection(MyBlockNumber(), oVarsOut_ConNums[i], oVarsOut_ConnectedBlocks[i], oVarsOut_ConnectedCons[i]);
			}
		}

	DisposeArray(oVarsOut_ConnectedBlocksOld);
	DisposeArray(oVarsOut_ConnectedConsOld);
	DisposeArray(oVarsOut_ConnectedBlocks);
	DisposeArray(oVarsOut_ConnectedCons);
	DisposeArray(oVarsOut_TextBlockNums);

#endif

}//procedure oVarsOut_Reconnect(integer calledFrom)


//this function fills out oVars_VarIsWhichCon
procedure oVarsOut_VarIsWhichConUpdate()
{

#ifdef oVarsOut

	integer i;
	integer	conNameLength;

	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_Types_Int[i] == EQ_CONNECTORS)
			{
			conNameLength = StrLen(oVars_Types_str[i]);
			oVars_VarIsWhichCon[i] = StrToReal(StrPart(oVars_Types_str[i], 10, conNameLength));
			}
		
		else
			oVars_VarIsWhichCon[i] = -1;
		}
				
#endif		
				
}//procedure oVarsOut_VarIsWhichConUpdate()	


procedure oVarsOut_ConIsWhichVarUpdate()
{

	integer i, j;

	//initialize oVars_ConIsWhichVar
	MakeArray(oVars_ConIsWhichVar, oVarsOut_NumCons);
	for(i=0; i<oVarsOut_NumCons; i++)
		oVars_ConIsWhichVar[i] = -1;

	//fill out the "oVars_ConIsWhichVar" array
	j = 0;												//j is the next oVarsIn connector
	for(i=0; i<oVars_NumTableRows; i++)					//i is the next row in the attribs table
		{
		//if(StrFind(oVars_Types_str[i], "Connector", FALSE, FALSE) != -1  ||  StrFind(oVars_Types_str[i], "_Select", FALSE, FALSE) >= 0)	//AJN, 7.0.5, 10/24/08
		if(oVars_Types_Int[i] == EQ_CONNECTORS)
			{
			oVars_ConIsWhichVar[j] = i;
			j++;
			}
		}
	
}//procedure oVarsOut_ConIsWhichVarUpdate()



//**********************************************************************
//End "oVarsOut_" Functions
//**********************************************************************
//**********************************************************************




//******************************************************************
//******************************************************************
//START oVars_DBNT Functions
//******************************************************************


procedure oVars_DBNT_AddElement(real dbAddress, integer whichRowInTable)
{

	integer i;
	integer me;
	integer dbIndex;
	string63 dbName;
	integer tableIndex;
	string63 tableName;
	integer fieldIndex;
	integer recordIDFieldIndex;
	string63 fieldName;
	integer recordIndex;
	string63 recordName;
	integer whichElement;
	integer whichRow;
	integer numElements;
	integer oVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();

	//if the iVars db name tracking lists doesn't exist, create it
	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
	if(oVars_DBNameTrackingListIndex < 0)
		{
		oVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			//1 long field
			//2 sets sort type as integer
			//DBNT_WHICH_ROW_IN_TABLE_FIELD sets sort field
		ListLocked(me, oVars_DBNameTrackingListIndex, TRUE);
		ListAddString63s(me, oVars_DBNameTrackingListIndex, 4);
		ListSetName(me, oVars_DBNameTrackingListIndex, DBNT_OVARS_LIST_NAME);
		}

	//if(oVars_Types_str[whichRowInTable] == "DB write value"  ||  oVars_Types_str[whichRowInTable] == "DB write PRI")	//AJN, 7.0.5, 10/24/08
	if(oVars_Types_Int[whichRowInTable] == EQ_DB_WRITE_VAL  ||  oVars_Types_Int[whichRowInTable] == EQ_DB_WRITE_PRI)
		{
		
		//is an element already associated with whichRowInTable?
		whichElement = -1;
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			whichRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			
			if(whichRow == whichRowInTable)
				{
				whichElement = i;
				break;
				}
			}
		
		if(whichElement == -1)
			ListCreateElement(me, oVars_DBNameTrackingListIndex);
		
		//add the "whichRow" field to the element
		ListSetLong(me, oVars_DBNameTrackingListIndex, whichElement, DBNT_WHICH_ROW_IN_TABLE_FIELD, whichRowInTable);
		
		//add the "dbName" to the element
		dbIndex = DBDatabaseGetIndexFromAddress(dbAddress);
		if(dbIndex >= 1)
			dbName = DBDatabaseGetName(dbIndex);
		else
			dbName = "";
		ListSetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_DB_NAME_FIELD, dbName);	//6 for string63
		
		//add the "tableName" to the element
		tableIndex = DBTableGetIndexFromAddress(dbAddress);
		if(tableIndex >= 1)
			tableName = DBTableGetName(dbIndex, tableIndex);
		else
			tableName = "";
		ListSetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_TABLE_NAME_FIELD, tableName);	//6 for string63
		
		//add the "fieldName" to the element
		fieldIndex = DBFieldGetIndexFromAddress(dbAddress);
		if(fieldIndex >= 1)
			fieldName = DBFieldGetName(dbIndex, tableIndex, fieldIndex);
		else
			fieldName = "";
		ListSetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_FIELD_NAME_FIELD, fieldName);	//6 for string63
		
		//add the "recordName" to the element
		recordIndex = DBRecordGetIndexFromAddress(dbAddress);
		if(recordIndex >= 1)
			{
			recordIDFieldIndex = DBRecordIDFieldGetIndex(dbIndex, tableIndex);
			if(recordIDFieldIndex >= 1)
				{
				recordName = DBDataGetAsString(dbIndex, tableIndex, recordIDFieldIndex, recordIndex);
				}
			else
				recordName = "";
			}
		else
			recordName = "";
		ListSetString(me, oVars_DBNameTrackingListIndex, whichElement, 6, DBNT_RECORD_NAME_FIELD, recordName);	//6 for string63
		
		//add new elemnt to the "oVars_DBNameTrackingList" linked list
		if(whichElement == -1)
			ListAddElement(me, oVars_DBNameTrackingListIndex, -2);	//2 for added in a sorted fashion
		}

}//procedure oVars_DBNT_AddElement(real dbAddress, integer whichRowInTable)


//6/15/11
procedure oVars_DBNT_DeleteElement(integer whichRowInTable)
{

	integer i;
	integer me;
	integer dbIndex;
	string63 dbName;
	integer tableIndex;
	string63 tableName;
	integer fieldIndex;
	integer recordIDFieldIndex;
	string63 fieldName;
	integer recordIndex;
	string63 recordName;
	integer whichElement;
	integer currRow;
	integer whichCol;
	integer numElements;
	integer oVars_DBNameTrackingListIndex;
	
	
	integer listSetReturnCode;
	
	
	me = MyBlockNumber();

	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);

	//if the iVars db name tracking lists doesn't exist, create it
	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
	if(oVars_DBNameTrackingListIndex < 0)
		{
		oVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			//1 long field
			//2 sets sort type as integer
			//DBNT_WHICH_ROW_IN_TABLE_FIELD sets sort field
		ListLocked(me, oVars_DBNameTrackingListIndex, TRUE);
		ListAddString63s(me, oVars_DBNameTrackingListIndex, 4);
		ListSetName(me, oVars_DBNameTrackingListIndex, DBNT_OVARS_LIST_NAME);
		}
	
	if(
	   oVars_Types_Int[whichRowInTable] == EQ_DB_WRITE_VAL  ||  
	   oVars_Types_Int[whichRowInTable] == EQ_DB_WRITE_PRI 
	  )
		{
		//find which element in list to delete
		whichElement = -1;
		numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
		for(i=0; i<numElements; i++)
			{
			currRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			
			if(currRow == whichRowInTable)
				{
				whichElement = i;
				break;
				}
			}
		
		if(whichElement >= 0)
			{
			ListDeleteElement(me, oVars_DBNameTrackingListIndex, whichElement);			
			}
			
		else //if can't find link in list to delete
			{
			//do nothing
			}
		}

}//procedure oVars_DBNT_DeleteElement(integer whichRowInTable)


//caled in EQ_OnDataTableResize(), EQ_OnOpenModel(), and on oVars_ttbl. 
//remove unwanted elements from oVars_DBNameTrackingListIndex
procedure oVars_DBNT_GarbageCollection()
{
	
	integer i;
	integer me;
	integer targetElement;
	integer whichVarRow;
	integer numElements;
	integer searchArray[2][2];	//col 0 = search field, col 1 = search value
	integer oVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();

	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);

	//first, cycle through all rows in iVars table
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//if(oVars_Types_str[i] != "DB write value"  &&  oVars_Types_str[i] != "DB write PRI")	//AJN, 7.0.5, 10/24/08
		if(oVars_Types_Int[i] != EQ_DB_WRITE_VAL  &&  oVars_Types_Int[i] != EQ_DB_WRITE_PRI)
			{
			targetElement = 0;
			while(targetElement >= 0)
				{
				targetElement = ListSearch(me, oVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, i, 0.0, "", 0);
				if(targetElement >= 0)
					{
					ListDeleteElement(me, oVars_DBNameTrackingListIndex, targetElement);
					}
				}
			}
		}
		
	//second, cycle through all elements in oVars_DBNameTrackingList
	numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
	for(i=0; i<numElements; i++)
		{
		whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
		
		//if( whichVarRow >= oVars_NumTableRows  ||  (oVars_Types_str[whichVarRow] != "DB write value"  &&  oVars_Types_str[whichVarRow] != "DB write PRI") )	//AJN, 7.0.5, 10/24/08
		if( whichVarRow >= oVars_NumTableRows  ||  (oVars_Types_Int[whichVarRow] != EQ_DB_WRITE_VAL  &&  oVars_Types_Int[whichVarRow] != EQ_DB_WRITE_PRI) )
		   {
		   ListDeleteElement(me, oVars_DBNameTrackingListIndex, i);
		   numElements--;
		   i--;
		   }
		}
	
}//procedure oVars_DBNT_GarbageCollection()


//called in EQ_OnCheckData(). use names stored in DBNT linked lists to ensure we have correct DB indexes
procedure oVars_DBNT_UpdateDBCoordsArray()
{

	integer i;
	integer me;
	integer numElements;
	integer whichVarRow;
	string63 databaseName;
	integer databaseIndex;
	string63 tableName;
	integer tableIndex;
	string63 fieldName;
	integer fieldIndex;
	string63 recordName;
	integer recordIndex;
	integer oVars_DBNameTrackingListIndex;
	
	me = MyBlockNumber();

	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);

	numElements = ListGetElements(me, oVars_DBNameTrackingListIndex);
	for(i=0; i<numElements; i++)
		{
		whichVarRow = ListGetLong(me, oVars_DBNameTrackingListIndex, i, DBNT_WHICH_ROW_IN_TABLE_FIELD);
		
		//database indes
		databaseName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_DB_NAME_FIELD);
		if(databaseName != "")
			databaseIndex = DBDatabaseGetIndex(databaseName);
		else
			databaseIndex = -1;
		
		//table index
		tableName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_TABLE_NAME_FIELD);
		if(tableName != "")
			tableIndex = DBTableGetIndex(databaseIndex, tableName);
		else
			tableIndex = -1;
		
		//field index
		fieldName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_FIELD_NAME_FIELD);
		if(fieldName != "")
			fieldIndex = DBFieldGetIndex(databaseIndex, tableIndex, fieldName);
		else
			fieldIndex = -1;
		
		//record index
		recordName = ListGetString(me, oVars_DBNameTrackingListIndex, i, 6, DBNT_RECORD_NAME_FIELD);
		if(recordName != "")
			{
			recordIndex = DBRecordFind(databaseIndex, 		//database to search
									   tableIndex, 			//table to search
									   0, 					//use the record ID field as the search field
									   1, 					//the start record index
									   TRUE, 				//exact record match
									   recordName);			//the search string
			if(recordIndex == 0)
				recordIndex = -1;
			}
		else
			recordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[whichVarRow]);
			
		//update oVars_DBCoords
		oVars_DBCoords[whichVarRow] = DBAddressCreate(databaseIndex, tableIndex, fieldindex, recordIndex);
		}
	
}//procedure oVars_DBNT_UpdateDBCoordsArray()


//called in open model this function is used to ensure oVars_DBNameTrackingList 
//exists since name tracking was only implemented after 7.0.3
procedure oVars_DBNT_BuildList()
{

	integer i;
	integer me;
	integer dbIndex;
	string63 dbName;
	integer tableIndex;
	string63 tableName;
	integer fieldIndex;
	integer recordIDFieldIndex;
	string63 fieldName;
	integer recordIndex;
	string63 recordName;
	integer oVars_DBNameTrackingListIndex;
	integer found;
	
	me = MyBlockNumber();

	//if the oVars db name tracking lists doesn't exist, create it
	oVars_DBNameTrackingListIndex = ListGetIndex(me, DBNT_OVARS_LIST_NAME);
	if(oVars_DBNameTrackingListIndex < 0)
		{
		oVars_DBNameTrackingListIndex = ListCreate(me, 1, 0, 0, 0, 0, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD);
			//1 long field
			//2 sets sort type as integer
			//DBNT_WHICH_ROW_IN_TABLE_FIELD sets sort field
		ListLocked(me, oVars_DBNameTrackingListIndex, TRUE);
		ListAddString63s(me, oVars_DBNameTrackingListIndex, 4);
		ListSetName(me, oVars_DBNameTrackingListIndex, DBNT_OVARS_LIST_NAME);
		}
		
	for(i=0; i<oVars_NumTableRows; i++)
		{
		//if(oVars_Types_str[i] == "DB write value"  ||  oVars_Types_str[i] == "DB write PRI")	//AJN, 7.0.5, 10/24/08
		if(oVars_Types_Int[i] == EQ_DB_WRITE_VAL  ||  oVars_Types_Int[i] == EQ_DB_WRITE_PRI)
			{
			//search for this db oVar in the linked list
			found = ListSearch(me, oVars_DBNameTrackingListIndex, 2, DBNT_WHICH_ROW_IN_TABLE_FIELD, i, 0.0, "", 0);

			//if this db oVar is not represented in the linked list, then add it
			if(found < 0)
				{
				ListCreateElement(me, oVars_DBNameTrackingListIndex);
				
				//add the "whichRow" field to the new element
				ListSetLong(me, oVars_DBNameTrackingListIndex, -1, DBNT_WHICH_ROW_IN_TABLE_FIELD, i);
				
				//add the "dbName" to the new element
				dbIndex = DBDatabaseGetIndexFromAddress(oVars_DBCoords[i]);
				if(dbIndex >= 1  &&  !NoValue(oVars_DBCoords[i]))
					dbName = DBDatabaseGetName(dbIndex);
				else
					dbName = "";
				ListSetString(me, oVars_DBNameTrackingListIndex, -1, 6, DBNT_DB_NAME_FIELD, dbName);	//6 for string63
				
				//add the "tableName" to the new element
				tableIndex = DBTableGetIndexFromAddress(oVars_DBCoords[i]);
				if(tableIndex >= 1  &&  !NoValue(oVars_DBCoords[i]))
					tableName = DBTableGetName(dbIndex, tableIndex);
				else
					tableName = "";
				ListSetString(me, oVars_DBNameTrackingListIndex, -1, 6, DBNT_TABLE_NAME_FIELD, tableName);	//6 for string63
				
				//add the "fieldName" to the new element
				fieldIndex = DBFieldGetIndexFromAddress(oVars_DBCoords[i]);
				if(fieldIndex >= 1  &&  !NoValue(oVars_DBCoords[i]))
					fieldName = DBFieldGetName(dbIndex, tableIndex, fieldIndex);
				else
					fieldName = "";
				ListSetString(me, oVars_DBNameTrackingListIndex, -1, 6, DBNT_FIELD_NAME_FIELD, fieldName);	//6 for string63
				
				//add the "recordName" to the new element
				recordIndex = DBRecordGetIndexFromAddress(oVars_DBCoords[i]);
				if(recordIndex >= 1  &&  !NoValue(oVars_DBCoords[i]))
					{
					recordIDFieldIndex = DBRecordIDFieldGetIndex(dbIndex, tableIndex);
					if(recordIDFieldIndex >= 1)
						{
						recordName = DBDataGetAsString(dbIndex, tableIndex, recordIDFieldIndex, recordIndex);
						}
					else
						recordName = "";
					}
				else
					recordName = "";
				ListSetString(me, oVars_DBNameTrackingListIndex, -1, 6, DBNT_RECORD_NAME_FIELD, recordName);	//6 for string63
				
				//add new elemnt to the "oVars_DBNameTrackingList" linked list
				ListAddElement(me, oVars_DBNameTrackingListIndex, -2);	//2 for added in a sorted fashion
				}
			}
		}//for(i=0; i<oVars_NumTableRows; i++)
		
}//procedure oVars_DBNT_BuildList()


//******************************************************************
//END oVars_DBNT Functions
//******************************************************************
//******************************************************************





//**********************************************************************
//**********************************************************************
//Start Attrib Functions
//**********************************************************************



//****************************
//Start Input Attrib Functions
//****************************


/*
procedure iVars_OnDialogClickAttribName(integer whichOptions)
{

#ifdef EQ_IsItemBlock

	integer currentAttribPopVal;		//last value that the popup was set to
	integer newAttribPopVal;
	string15 newAttrib;
	integer newAttribType;
	string15 newAttribName;
	integer exec;

	Attrib_GetPopOptions(I_VARIABLES, whichOptions);
	//WARNING!:  must resize attribPopContents BEFORE you call Attrib_BuildAttribPopContentsArray
	MakeArray(attribPopContents, Attrib_GetPopSize(attribPopOptions));
	Attrib_BuildAttribPopContentsArray(attribPopContents, attribPopOptions, TRUE, TRUE);
	currentAttribPopVal = Attrib_GetPopVal(attribPopContents, iVars_Names, attribPopOptions, rowClicked, TRUE);
	newAttribPopVal = PopupMenuArray(attribPopContents, currentAttribPopVal);	//show the attrib pop and record the user's response

	if(newAttribPopVal != currentAttribPopVal)	
		{
	
		//record users response
		if(StrFind(attribPopContents[newAttribPopVal - 1], "  ", FALSE, FALSE) >= 0)	//if found 2 spaces for indenting, remove the indenting before storing the user's response
			iVars_Names[rowClicked] = StrPart(attribPopContents[newAttribPopVal - 1], 2, StrLen(attribPopContents[newAttribPopVal - 1]));
		else
			iVars_Names[rowClicked] = attribPopContents[newAttribPopVal - 1];

		//figure out what the user selected from the popup
		if(StrFind(iVars_Names[rowClicked], "New value", FALSE, FALSE) >= 0)
			{
			newAttribType = ATTRIB_TYPE_VALUE;
			}
		else if(StrFind(iVars_Names[rowClicked], "New string", FALSE, FALSE) >= 0)
			{
			newAttribType = ATTRIB_TYPE_STRING;
			}
		else if(StrFind(iVars_Names[rowClicked], "New DB", FALSE, FALSE) >= 0)
			{
			newAttribType = ATTRIB_TYPE_DB;
			}
		else if(StrFind(iVars_Names[rowClicked], "New Attach", FALSE, FALSE) >= 0)
			{
			newAttribType = ATTRIB_TYPE_DB_ATTACHED;
			}
		else
			{
			newAttribType = ATTRIB_TYPE_NOT_NEW;
			}
	
		//if user wants to create a new attribute...
		if(newAttribType != ATTRIB_TYPE_NOT_NEW)
			{
			
			newAttribName = Attrib_ShowNewAttribMsgBox(iVars_Names, rowClicked);
			iVars_AttribTypes[rowClicked] = newAttribType;
			
			if(StrFind(newAttribName, "New value", FALSE, FALSE) != -1  ||  StrFind(newAttribName, "New string", FALSE, FALSE) != -1  ||  StrFind(newAttribName, "New DB", FALSE, FALSE) != -1 )	//if user clicked "cancel" or clicked "ok" without typing anything
				{
				iVars_Names[rowClicked] = "None";
				iVars_AttribTypes[rowClicked] = ATTRIB_TYPE_NO_ATTRIB;
				}

			else  //if user typed in a new valid attrib name
				{
//				Attrib_AddName(newAttribName, newAttribType, TRUE);
				Attrib_AddName(newAttribName, newAttribType);

				iVars_Names[rowClicked] = newAttribName;
//				if(iVars_Types_str[rowClicked] == "_Last item")
//					iVars_Names[rowClicked] = "L_" + newAttribName;
	
				if(newAttribType == ATTRIB_TYPE_STRING)
					{
					SysGlobalStr2 = newAttribName;	//used by the executive to know the name of the new string attrib
					SysGlobalInt22 = TRUE;		//if TRUE, executive knows to open its dialog to the atributes tab showing the string attribs table
					SA_OpenExecutive();
					}
					
				}//if user typed in a new valid attrib name
			
			}//if(newAttribType != ATTRIB_TYPE_NOT_NEW)
			
		else //if user selects an existing attribute
			{
			iVars_AttribTypes[rowClicked] = Attrib_GetAttribType(iVars_Names[rowClicked]);
			}
		
		}//if(currentAttribPopVal != newAttribPopVal)
		

	iVars_TableSetup();
	
	DisposeArray(attribPopOptions);

#endif //EQ_IsItemBlock

}//procedure iVars_OnDialogClickAttribName(integer whichOptions)
*/

//***************************
//End Input Attrib Functions
//***************************


//*****************************
//Start Output Attrib Functions
//*****************************
/*
procedure oVars_OnDialogClickAttribName(integer whichOptions)
{

#ifdef EQ_IsItemBlock

	integer currentAttribPopVal;		//last value that the popup was set to
	integer newAttribPopVal;		//last value that the popup was set to
	string15 newAttribName;
	integer newAttribType;
	integer exec;

	Attrib_GetPopOptions(O_VARIABLES, whichOptions);
	//WARNING!:  must resize attribPopContents BEFORE you call Attrib_BuildAttribPopContentsArray
	MakeArray(attribPopContents, Attrib_GetPopSize(attribPopOptions));
	Attrib_BuildAttribPopContentsArray(attribPopContents, attribPopOptions, TRUE, TRUE);
	currentAttribPopVal = Attrib_GetPopVal(attribPopContents, oVars_Names, attribPopOptions, rowClicked, TRUE);
	newAttribPopVal = PopupMenuArray(attribPopContents, currentAttribPopVal);	//show the attrib pop and record the user's response
	
	if(newAttribPopVal != currentAttribPopVal)	
		{
	
		//record users response
		if(StrFind(attribPopContents[newAttribPopVal - 1], "  ", FALSE, FALSE) >= 0)	//if found 2 space for indenting, remove the indenting before storing the user's response
			oVars_Names[rowClicked] = StrPart(attribPopContents[newAttribPopVal - 1], 2, StrLen(attribPopContents[newAttribPopVal - 1]));
		else
			oVars_Names[rowClicked] = attribPopContents[newAttribPopVal - 1];
			
		//figure out what the user selected from the popup
		if(StrFind(oVars_Names[rowClicked], "New value", FALSE, FALSE) >= 0)
			newAttribType = ATTRIB_TYPE_VALUE;
		else if(StrFind(oVars_Names[rowClicked], "New string", FALSE, FALSE) >= 0)
			newAttribType = ATTRIB_TYPE_STRING;
		else if(StrFind(oVars_Names[rowClicked], "New DB", FALSE, FALSE) >= 0)
			newAttribType = ATTRIB_TYPE_DB;
		else
			newAttribType = ATTRIB_TYPE_NOT_NEW;
	
		//if user wants to create a new attribute...
		if(newAttribType != ATTRIB_TYPE_NOT_NEW)
			{
			
			newAttribName = Attrib_ShowNewAttribMsgBox(oVars_Names, rowClicked);
			oVars_AttribTypes[rowClicked] = newAttribType;
			
			if(StrFind(newAttribName, "New value", FALSE, FALSE) != -1  ||  StrFind(newAttribName, "New string", FALSE, FALSE) != -1  ||  StrFind(newAttribName, "New DB", FALSE, FALSE) != -1 )	//if user clicked "cancel" or clicked "ok" without typing anything
				{
				oVars_Names[rowClicked] = "None";
				oVars_AttribTypes[rowClicked] = ATTRIB_TYPE_NO_ATTRIB;
				}

			else  //if user typed in a new valid attrib name
				{
				Attrib_AddName(newAttribName, newAttribType);
				oVars_Names[rowClicked] = newAttribName;

				if(newAttribType == ATTRIB_TYPE_STRING)
					{
					SysGlobalStr2 = newAttribName;	//used by the executive to know the name of the new string attrib
					SysGlobalInt22 = TRUE;		//if TRUE, executive knows to open its dialog to the atributes tab showing the string attribs table
					SA_OpenExecutive();
					}
					
				}//if user typed in a new valid attrib name
			
			}//if(newAttribType != ATTRIB_TYPE_NOT_NEW)
			
		else //if user selects an existing attribute
			{
			oVars_AttribTypes[rowClicked] = Attrib_GetAttribType(oVars_Names[rowClicked]);
			oVars_Values[rowClicked] = blank;
			}
		
		}//if(currentAttribPopVal != newAttribPopVal)

	oVars_TableSetup();

	DisposeArray(attribPopOptions);

#endif //EQ_IsItemBlock

}//procedure oVars_OnDialogClickAttribName(integer whichOptions)
*/

//***************************
//End Output Attrib Functions
//***************************



//**********************************************************************
//End Attrib Functions
//**********************************************************************
//**********************************************************************



//**********************************************************************
//**********************************************************************
//START: "Calc When" message handlers for Equation and Query Equation
//**********************************************************************



//7/5/11


procedure CW_ConnectorAnimate()
{

	integer i;
	integer me;
	integer numRows;
	
	me = MyBlockNumber();
	
	//delete animation objects
	#ifdef CW_IVarsIn_CalcControl_chk
		numRows = GetDimension(CW_IVarsIn_AnimObjectIDs);
		for(i=0; i<numRows; i++)
			AnimationObjectDelete(CW_IVarsIn_AnimObjectIDs[i]);
	#endif //CW_IVarsIn_CalcControl_chk

	//delete animation objects
	#ifdef CW_OVarsOut_CalcControl_chk
		numRows = GetDimension(CW_OVarsOut_AnimObjectIDs);
		for(i=0; i<numRows; i++)
			AnimationObjectDelete(CW_OVarsOut_AnimObjectIDs[i]);
		DisposeArray(CW_OVarsOut_AnimObjectIDs);
	#endif //CW_OVarsOut_CalcControl_chk
	
	//animate iVarsIn cons
	#ifdef CW_IVarsIn_CalcControl_chk
		CW_IVarsIn_Animate();
	#endif //CW_IVarsIn_CalcControl_chk

	//animate oVarsOut cons
	#ifdef CW_OVarsOut_CalcControl_chk
		CW_OVarsOut_Animate();
	#endif //CW_OVarsOut_CalcControl_chk
	
}//procedure CW_ConnectorAnimate()


#ifdef CW_CalcEventTime_chk
on CW_CalcEventTime_chk
{

	nextCalcEventTime = blank;
	
	#ifdef EQ_IsValueBlock
		DialogItemsShow();
		IconSet(FALSE);
	#endif

}
#endif


#ifdef EQ_IsValueBlock

on calcBeforeStart_chk
{

	DialogItemsShow();
	IconSet(FALSE);

}


on calcEveryStep_chk
{

	DialogItemsShow();
	IconSet(FALSE);

}


on calcAtEnd_chk
{

	DialogItemsShow();
	IconSet(FALSE);

}


on CW_Intervals_chk
{

	DialogItemsShow();
	IconSet(FALSE);

}


on CW_GoIn_chk
{

	GoInShow();
	IconSet(FALSE);

}


//procedure IconSet(integer animationIVarsIn, integer animateOVarsOut)		//7/5/11
procedure IconSet(integer animateCons)										//7/5/11
{

	if(IconGetClass(MyBlockNumber()) != 0)
		return;
		
	//green circle
	if(calcBeforeStart_chk)
		{
		AnimationOval(1);
		AnimationBorder(1, FALSE);
		AnimationColor(1, 21845, 65534, 43690, 1);
		AnimationMoveTo(1, 0, 0, FALSE);
		AnimationShow(1);
		}
	else
		{
		AnimationHide(1,FALSE);
		}
	
	//blue circle
	if(CW_CalcEventTime_chk  ||  CW_Intervals_chk)
		{
		AnimationOval(2);
		AnimationBorder(2, FALSE);
		AnimationColor(2, 41506, 65535, 65535, 1);
		AnimationMoveTo(2, 10, 0, FALSE);
		AnimationShow(2);
		}
	else
		{
		AnimationHide(2,FALSE);
		}
	
	//red circle
	if(calcAtEnd_chk)
		{
		AnimationOval(3);
		AnimationBorder(3, FALSE);
		AnimationColor(3, 0, 65534, 56797, 1);
		AnimationMoveTo(3, 20, 0, FALSE);
		AnimationShow(3);
		}
	else
		{
		AnimationHide(3,FALSE);
		}

	//hollow circle
	if(CW_LAM_CalcControl_chk)
		{
		AnimationOval(4);
		AnimationBorder(4, TRUE);
		AnimationColor(4, 0, 0, 65535, 1);
		AnimationShow(4);
		}
	else
		{
		AnimationHide(4,FALSE);
		}
	
	//7/5/11
	/*
	if(animationIVarsIn)
		CW_IVarsIn_Animate();				
	if(animateOVarsOut)
		CW_OVarsOut_Animate();
	*/
	
	//7/5/11
	if(animateCons)
		{
		CW_ConnectorAnimate();
		}

}//procedure IconSet(integer animationIVarsIn, integer animateOVarsOut)


#endif //EQ_IsValueBlock




#ifdef CW_IVarsIn_CalcControl_chk


on CW_IVarsIn_CalcControl_chk 
{

	CW_IVarsIn_DialogItemsShow();
	CW_IVarsIn_GetWhichCon();
	//CW_IVarsIn_Animate();			//7/5/11
	CW_ConnectorAnimate();

	#ifdef EQ_IsValueBlock
		IconSet(FALSE);
	#endif
	
}


on CW_IVarsIn_RespondToWhich_pop
{

	integer i;
	integer userResponse;
	integer popupSize;
	integer currentSelection;
	
	//Build the CW_IVarsIn_ConnectorVarNamesArray list array
	popupSize = 0;
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(StrFind(iVars_Types_str[i], "connector", FALSE, FALSE) >= 0)
			{
			popupSize++;
			MakeArray(CW_IVarsIn_ConnectorVarNamesArray, popupSize);
			CW_IVarsIn_ConnectorVarNamesArray[popupSize-1] = iVars_Names[i];
			}
		}
	popupSize = popupSize+2;
	MakeArray(CW_IVarsIn_ConnectorVarNamesArray, popupSize);
	CW_IVarsIn_ConnectorVarNamesArray[popupSize - 2] = "-";
	CW_IVarsIn_ConnectorVarNamesArray[popupSize - 1] = "any input value con";
	
	//find location of user's current selection
	currentSelection = popupSize;					//set currentSelection to default
	for(i=0; i<popupSize; i++)
		{
		if(CW_IVarsIn_ConnectorVarNamesArray[i] == CW_IVarsIn_RespondToWhich_etxt)
			{
			currentSelection = i + 1;
			break;
			}
		}
	
	//make a flying popup using CW_LAM_RespondToWhich_etxt
	userResponse = PopupMenuArray (CW_IVarsIn_ConnectorVarNamesArray, currentSelection);
	CW_IVarsIn_RespondToWhich_etxt = CW_IVarsIn_ConnectorVarNamesArray[userResponse - 1];
	CW_IVarsIn_RespondToWhich_pop = userResponse;
	
	CW_IVarsIn_GetWhichCon();
	//CW_IVarsIn_Animate();			//7/5/11
	CW_ConnectorAnimate();
	
	DisposeArray(CW_IVarsIn_ConnectorVarNamesArray);
	
}//on CW_IVarsIn_RespondToWhich_pop


on CW_IVarsIn_RespondWhen_pop
{

	integer i;
	integer userResponse;
	integer popupSize;
	integer currentSelection;
	
	//Build the connector list array
	popupSize = 2;
	MakeArray(CW_IVarsIn_RespondWhenOptionsArray, popupSize);
	#ifdef EQ_IsQueueEquation
		CW_IVarsIn_RespondWhenOptionsArray[0] = "immediately- 1 item push";
	#else
		CW_IVarsIn_RespondWhenOptionsArray[0] = "immediately";
	#endif
	CW_IVarsIn_RespondWhenOptionsArray[1] = "after zero-time event";
	
	//find location of user's current selection
	currentSelection = 1;					//set currentSelection to default
	for(i=0; i<popupSize; i++)
		{
		if(CW_IVarsIn_RespondWhenOptionsArray[i] == CW_IVarsIn_RespondWhen_etxt)
			{
			currentSelection = i + 1;
			break;
			}
		}
	
	//make a flying popup using CW_IVarsIn_RespondWhenOptionsArray
	userResponse = PopupMenuArray (CW_IVarsIn_RespondWhenOptionsArray, currentSelection);
	CW_IVarsIn_RespondWhen_etxt = CW_IVarsIn_RespondWhenOptionsArray[userResponse - 1];
	CW_IVarsIn_RespondWhen_pop = userResponse;
	
	DisposeArray(CW_IVarsIn_RespondWhenOptionsArray);
	
}//on CW_IVarsIn_RespondWhen_pop


procedure CW_IVarsIn_OnCreateBlock()
{

	//Setup IVCM_- input value connector message
	#ifdef EQ_IsQueueEquation
		CW_IVarsIn_CalcControl_chk = TRUE;
		CW_IVarsIn_RespondToWhich_etxt = "any input value con";
		CW_IVarsIn_RespondWhen_etxt = "after zero-time event";
		CW_IVarsIn_RespondWhen_pop = WHEN_CALC_CURRENT_EVENT;
	#else
		//8/4/10
		CW_IVarsIn_CalcControl_chk = TRUE;
		CW_IVarsIn_RespondToWhich_etxt = "any input value con";
		CW_IVarsIn_RespondWhen_etxt = "immediate";
		CW_IVarsIn_RespondWhen_pop = WHEN_CALC_IMMEDIATE;
	#endif
	
}//procedure CW_IVarsIn_OnCreateBlock()


procedure CW_IVarsIn_DialogItemsShow()
{

	if(CW_IVarsIn_CalcControl_chk == TRUE)
		{
		DisableDialogItem("CW_IVarsIn_RespondToWhich_lbl", FALSE);
		DisableDialogItem("CW_IVarsIn_RespondToWhich_pop", FALSE);
		DisableDialogItem("CW_IVarsIn_RespondToWhich_etxt", FALSE);
		DisableDialogItem("CW_IVarsIn_RespondWhen_lbl", FALSE);
		DisableDialogItem("CW_IVarsIn_RespondWhen_pop", FALSE);
		DisableDialogItem("CW_IVarsIn_RespondWhen_etxt", FALSE);
		}
	else
		{
		DisableDialogItem("CW_IVarsIn_RespondToWhich_lbl", TRUE);
		DisableDialogItem("CW_IVarsIn_RespondToWhich_pop", TRUE);
		DisableDialogItem("CW_IVarsIn_RespondToWhich_etxt", TRUE);
		DisableDialogItem("CW_IVarsIn_RespondWhen_lbl", TRUE);
		DisableDialogItem("CW_IVarsIn_RespondWhen_pop", TRUE);
		DisableDialogItem("CW_IVarsIn_RespondWhen_etxt", TRUE);
		}

}//procedure CW_IVarsIn_DialogItemsShow()

procedure CW_IVarsIn_GetWhichCon()
{

	integer i;
	integer me;
	string myBlockName;
	
	me = MyBlockNumber();
	
	if(CW_IVarsIn_CalcControl_chk == TRUE)
		{
		CW_IVarsIn_WhichConnector = -1;

		//if(StrFind(CW_IVarsIn_RespondToWhich_etxt, "any", FALSE, FALSE) < 0)	//if one specific connector has been chosen instead of "any" connector
		if(CW_IVarsIn_RespondToWhich_etxt != "any input value con")
			{
			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(iVars_Names[i] == CW_IVarsIn_RespondToWhich_etxt)
					{
					CW_IVarsIn_WhichConnector = iVars_VarIsWhichCon[i];
					break;
					}
				}
			if(CW_IVarsIn_WhichConnector < 0)
				{
				myBlockName = BlockName(me);
				UserError("There is a problem in " + myBlockName + " block " + me + ". The connector variable named '" + CW_IVarsIn_RespondToWhich_etxt +
						  "' no longer exist, but it is being referenced in the 'Calc When' section of the Options tab.");
				}
			}
		else
			{
			CW_IVarsIn_WhichConnector = -1;
			}
		}

}//procedure CW_IVarsIn_GetWhichCon()


procedure CW_IVarsIn_Animate()
{
	integer i;
	integer me;
	integer numRows;
	integer animObject;
	integer conPosiArray[4];
	integer blockPosiArray[4];
	integer topConPosi;
	integer leftConPosi;
	integer leftObjectStartPosi;
	integer topObjectStartPosi;
	integer leftObjectPosi;
	integer topObjectPosi;
	integer numConVars;
	integer iconViewIndex;				//7/29/11
	string iconViewName;				//7/29/11
	
	me = MyBlockNumber();
	
	//7/5/11
	/*
	//delete animation objects
	numRows = GetDimension(CW_IVarsIn_AnimObjectIDs);
	for(i=0; i<numRows; i++)
		AnimationObjectDelete(CW_IVarsIn_AnimObjectIDs[i]);
	DisposeArray(CW_IVarsIn_AnimObjectIDs);
	*/

	numConVars = 0;
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_Int[i] == EQ_CONNECTORS)
			numConVars++;
		}
	
	if(numConVars > 0)
		{
		iVarsIn_ConnectorsSetup();
		
		//animate cons only if block is in default or reverse views
		iconViewIndex = IconGetView(me);						//7/29/11
		iconViewName = IconGetViewName(me, iconViewIndex);		//7/29/11
		if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse"  ||  iconViewName == "")	//7/29/11:  get null string if in beta view
			{
			//initialize the "CW_IVarsIn_AnimObjectIDs[]" array
			numRows = GetDimension(CW_IVarsIn_AnimObjectIDs);
			MakeArray(CW_IVarsIn_AnimObjectIDs, iVarsIn_NumCons);
			for(i=numRows; i<iVarsIn_NumCons; i++)
				{
				CW_IVarsIn_AnimObjectIDs[i] = -1;
				}
	
			//create animation objects
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				animObject = CW_IVarsIn_AnimObjectIDs[i];
				if(animObject == -1  ||  AnimationObjectExists(animObject) == FALSE)
					{
					CW_IVarsIn_AnimObjectIDs[i] = AnimationObjectCreate(FALSE);
					}
				}
			
			//shape and color animation objects
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				animObject = CW_IVarsIn_AnimObjectIDs[i];
				AnimationRectangle(animObject);
				AnimationStretchTo(animObject, 0, 0, 4, 11, TRUE);
				AnimationBorder(animObject, FALSE);
				AnimationColor(animObject, 0, 65534, 56797, 1);
				}
			
			//place animation objects
			for(i=0; i<iVarsIn_NumCons; i++)
				{
				animObject = CW_IVarsIn_AnimObjectIDs[i];
				
				//get connector position
				GetConnectorPosition(me, iVarsIn_ConNums[i], conPosiArray);
				topConPosi = conPosiArray[0];
				leftConPosi = conPosiArray[1];
				
				//get anim obejct's starting reference point
				GetBlockTypePosition(me, blockPosiArray);
				topObjectStartPosi = blockPosiArray[0];
				leftObjectStartPosi = blockPosiArray[1];
				
				//place anim object next to connector
				if(iconViewName == "Default View"  ||  iconViewName == "")			//7/29/11
					{
					topObjectPosi = topConPosi - topObjectStartPosi - 2;
					leftObjectPosi = leftObjectStartPosi - leftConPosi - 5;
					}
				else if(iconViewName == "Default View Reverse")						//7/29/11
					{
					topObjectPosi = topConPosi - topObjectStartPosi - 2;
					leftObjectPosi = leftConPosi - leftObjectStartPosi + 7;
					}
				
				AnimationMoveTo(animObject, leftObjectPosi, topObjectPosi, TRUE);
				}
				
			//show animation objects
			CW_IVarsIn_GetWhichCon();
			if(CW_IVarsIn_CalcControl_chk == TRUE)
				{
				for(i=0; i<iVarsIn_NumCons; i++)
					{
					if(CW_IVarsIn_WhichConnector == -1  ||  i == CW_IVarsIn_WhichConnector)	//-1 if the  "respond to any connecter msg" option was chosen
						{
						animObject = CW_IVarsIn_AnimObjectIDs[i];
						AnimationHide(animObject, TRUE);
						}
					else
						{
						animObject = CW_IVarsIn_AnimObjectIDs[i];
						AnimationShow(animObject);
						}
					}
				}
			else
				{
				for(i=0; i<iVarsIn_NumCons; i++)
					{
					animObject = CW_IVarsIn_AnimObjectIDs[i];
					AnimationShow(animObject);
					}
				}
			
			}//if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse")
					
		}//if(numConVars > 0)
	
}//procedure CW_IVarsIn_Animate()

#endif //CW_IVarsIn_CalcControl_chk



#ifdef CW_OVarsOut_CalcControl_chk

on CW_OVarsOut_CalcControl_chk 
{

	CW_OVarsOut_DialogItemsShow();
	CW_OVarsOut_GetWhichCon();
	//CW_OVarsOut_Animate();			//7/5/11
	CW_ConnectorAnimate();
	
	#ifdef EQ_IsValueBlock
		IconSet(FALSE);
	#endif
	
}


on CW_OVarsOut_RespondToWhich_pop
{

	integer i;
	integer userResponse;
	integer popupSize;
	integer currentSelection;
	
	//Build the CW_OVarsOut_ConnectorVarNamesArray list array
	popupSize = 0;
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(StrFind(oVars_Types_str[i], "connector", FALSE, FALSE) >= 0)
			{
			popupSize++;
			MakeArray(CW_OVarsOut_ConnectorVarNamesArray, popupSize);
			CW_OVarsOut_ConnectorVarNamesArray[popupSize-1] = oVars_Names[i];
			}
		}
	popupSize = popupSize+2;
	MakeArray(CW_OVarsOut_ConnectorVarNamesArray, popupSize);
	CW_OVarsOut_ConnectorVarNamesArray[popupSize - 2] = "-";
	CW_OVarsOut_ConnectorVarNamesArray[popupSize - 1] = "any output value con";
	
	//find location of user's current selection
	currentSelection = popupSize;					//set currentSelection to default
	for(i=0; i<popupSize; i++)
		{
		if(CW_OVarsOut_ConnectorVarNamesArray[i] == CW_OVarsOut_RespondToWhich_etxt)
			{
			currentSelection = i + 1;
			break;
			}
		}
	
	//make a flying popup using CW_LAM_RespondToWhich_etxt
	userResponse = PopupMenuArray (CW_OVarsOut_ConnectorVarNamesArray, currentSelection);
	CW_OVarsOut_RespondToWhich_etxt = CW_OVarsOut_ConnectorVarNamesArray[userResponse - 1];
	CW_OVarsOut_RespondToWhich_pop = userResponse;
	
	CW_OVarsOut_GetWhichCon();
	//CW_OVarsOut_Animate();			//7/5/11
	CW_ConnectorAnimate();
	
	DisposeArray(CW_OVarsOut_ConnectorVarNamesArray);
	
}//on CW_OVarsOut_RespondToWhich_pop


on CW_OVarsOut_RespondWhen_pop
{

	integer i;
	integer userResponse;
	integer popupSize;
	integer currentSelection;
	
	//Build the connector list array
	popupSize = 2;
	MakeArray(CW_OVarsOut_RespondWhenOptionsArray, popupSize);
	CW_OVarsOut_RespondWhenOptionsArray[0] = "immediately";
	CW_OVarsOut_RespondWhenOptionsArray[1] = "after zero-time event";
	
	//find location of user's current selection
	currentSelection = 1;					//set currentSelection to default
	for(i=0; i<popupSize; i++)
		{
		if(CW_OVarsOut_RespondWhenOptionsArray[i] == CW_OVarsOut_RespondWhen_etxt)
			{
			currentSelection = i + 1;
			break;
			}
		}
	
	//make a flying popup using CW_OVarsOut_RespondWhenOptionsArray
	userResponse = PopupMenuArray (CW_OVarsOut_RespondWhenOptionsArray, currentSelection);
	CW_OVarsOut_RespondWhen_etxt = CW_OVarsOut_RespondWhenOptionsArray[userResponse - 1];
	CW_OVarsOut_RespondWhen_pop = userResponse;
	
	DisposeArray(CW_OVarsOut_RespondWhenOptionsArray);
	
}//on CW_OVarsOut_RespondWhen_pop


procedure CW_OVarsOut_OnCreateBlock()
{

	//Setup OVCM_- output value connector message
	CW_OVarsOut_CalcControl_chk = TRUE;
	CW_OVarsOut_RespondToWhich_etxt = "any output value con";
	CW_OVarsOut_RespondWhen_etxt = "immediately";
	CW_OVarsOut_RespondWhen_pop = WHEN_CALC_IMMEDIATE;
	
}//procedure CW_OVarsOut_OnCreateBlock()


procedure CW_OVarsOut_DialogItemsShow()
{

	if(CW_OVarsOut_CalcControl_chk == TRUE)
		{
		DisableDialogItem("CW_OVarsOut_RespondToWhich_lbl", FALSE);
		DisableDialogItem("CW_OVarsOut_RespondToWhich_pop", FALSE);
		DisableDialogItem("CW_OVarsOut_RespondToWhich_etxt", FALSE);
		DisableDialogItem("CW_OVarsOut_RespondWhen_lbl", FALSE);
		DisableDialogItem("CW_OVarsOut_RespondWhen_pop", FALSE);
		DisableDialogItem("CW_OVarsOut_RespondWhen_etxt", FALSE);
		}
	else
		{
		DisableDialogItem("CW_OVarsOut_RespondToWhich_lbl", TRUE);
		DisableDialogItem("CW_OVarsOut_RespondToWhich_pop", TRUE);
		DisableDialogItem("CW_OVarsOut_RespondToWhich_etxt", TRUE);
		DisableDialogItem("CW_OVarsOut_RespondWhen_lbl", TRUE);
		DisableDialogItem("CW_OVarsOut_RespondWhen_pop", TRUE);
		DisableDialogItem("CW_OVarsOut_RespondWhen_etxt", TRUE);
		}

}//procedure CW_OVarsOut_DialogItemsShow()


procedure CW_OVarsOut_GetWhichCon()
{

	integer i;
	integer me;
	string myBlockName;
	
	me = MyBlockNumber();
	
	//get CW_OVarsOut_WhichConnector. 
	if(CW_OVarsOut_CalcControl_chk == TRUE)
		{
		//if(StrFind(CW_OVarsOut_RespondToWhich_etxt, "any", FALSE, FALSE) < 0)	//if one specific connector has been chosen instead of "any" connector
		if(CW_OVarsOut_RespondToWhich_etxt != "any output value con")
			{
			CW_OVarsOut_WhichConnector = -1;

			for(i=0; i<oVars_NumTableRows; i++)
				{
				if(oVars_Names[i] == CW_OVarsOut_RespondToWhich_etxt)
					{
					CW_OVarsOut_WhichConnector = oVars_VarIsWhichCon[i];
					break;
					}
				}
			if(CW_OVarsOut_WhichConnector < 0)
				{
				myBlockName = BlockName(me);
				UserError("There is a problem in " + myBlockName + " block " + me + ". The connector variable named '" + CW_OVarsOut_RespondToWhich_etxt +
						  "' no longer exist, but it is being referenced in the 'Calc When' section of the Options tab.");
				}
			}
		else
			CW_OVarsOut_WhichConnector = -1;
		}

}//procedure CW_OVarsOut_GetWhichCon()


procedure CW_OVarsOut_Animate()
{
	integer i;
	integer me;
	integer numRows;
	integer animObject;
	integer conPosiArray[4];
	integer blockPosiArray[4];
	integer topConPosi;
	integer leftConPosi;
	integer leftObjectStartPosi;
	integer topObjectStartPosi;
	integer leftObjectPosi;
	integer topObjectPosi;
	integer numConVars;
	integer iconViewIndex;				//7/29/11
	string iconViewName;				//7/29/11
	
	me = MyBlockNumber();
	
	//7/5/11
	/*
	//delete animation objects
	numRows = GetDimension(CW_OVarsOut_AnimObjectIDs);
	for(i=0; i<numRows; i++)
		AnimationObjectDelete(CW_OVarsOut_AnimObjectIDs[i]);
	DisposeArray(CW_OVarsOut_AnimObjectIDs);
	*/

	numConVars = 0;
	for(i=0; i<oVars_NumTableRows; i++)
		{
		if(oVars_Types_Int[i] == EQ_CONNECTORS)
			numConVars++;
		}
	
	if(numConVars > 0)
		{
		oVarsOut_ConnectorsSetup();
		
		//animate cons only if block is in default or reverse views
		iconViewIndex = IconGetView(me);						//7/29/11
		iconViewName = IconGetViewName(me, iconViewIndex);		//7/29/11
		if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse"  ||  iconViewName == "")	//7/29/11:  get null string if in beta view
			{
			//initialize the "CW_OVarsOut_AnimObjectIDs[]" array
			numRows = GetDimension(CW_OVarsOut_AnimObjectIDs);
			MakeArray(CW_OVarsOut_AnimObjectIDs, oVarsOut_NumCons);
			for(i=numRows; i<oVarsOut_NumCons; i++)
				{
				CW_OVarsOut_AnimObjectIDs[i] = -1;
				}
	
			//create animation objects
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				animObject = CW_OVarsOut_AnimObjectIDs[i];
				if(animObject == -1  ||  AnimationObjectExists(animObject) == FALSE)
					{
					CW_OVarsOut_AnimObjectIDs[i] = AnimationObjectCreate(FALSE);
					}
				}
			
			//shape and color animation objects
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				animObject = CW_OVarsOut_AnimObjectIDs[i];
				AnimationRectangle(animObject);
				AnimationStretchTo(animObject, 0, 0, 4, 11, TRUE);
				AnimationBorder(animObject, FALSE);
				AnimationColor(animObject, 0, 65534, 56797, 1);
				}
			
			//place animation objects
			for(i=0; i<oVarsOut_NumCons; i++)
				{
				animObject = CW_OVarsOut_AnimObjectIDs[i];
				
				//get connector position
				GetConnectorPosition(me, oVarsOut_ConNums[i], conPosiArray);
				topConPosi = conPosiArray[0];
				leftConPosi = conPosiArray[1];
				
				//get anim obejct's starting reference point
				GetBlockTypePosition(me, blockPosiArray);
				topObjectStartPosi = blockPosiArray[0];
				leftObjectStartPosi = blockPosiArray[1];
				
				//place anim object next to connector
				if(iconViewName == "Default View"  ||  iconViewName == "")			//7/29/11
					{
					topObjectPosi = topConPosi - topObjectStartPosi - 2;
					leftObjectPosi = leftObjectStartPosi - leftConPosi + 87;
					}
				else if(iconViewName == "Default View Reverse")						//7/29/11
					{
					topObjectPosi = topConPosi - topObjectStartPosi - 2;
					leftObjectPosi = leftConPosi - leftObjectStartPosi - 5;
					}
				
				AnimationMoveTo(animObject, leftObjectPosi, topObjectPosi, TRUE);
				}
				
			//show animation objects
			CW_OVarsOut_GetWhichCon();
			if(CW_OVarsOut_CalcControl_chk == TRUE)
				{
				for(i=0; i<oVarsOut_NumCons; i++)
					{
					if(CW_OVarsOut_WhichConnector == -1  ||  i == CW_OVarsOut_WhichConnector)	//-1 if the  "respond to any connecter msg" option was chosen
						{
						animObject = CW_OVarsOut_AnimObjectIDs[i];
						AnimationHide(animObject, TRUE);
						}
					else
						{
						animObject = CW_OVarsOut_AnimObjectIDs[i];
						AnimationShow(animObject);
						}
					}
				}
			else
				{
				for(i=0; i<oVarsOut_NumCons; i++)
					{
					animObject = CW_OVarsOut_AnimObjectIDs[i];
					AnimationShow(animObject);
					}
				}
				
			}//if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse")
		
		}//if(numConVars > 0)
	
}//procedure CW_OVarsOut_Animate()

#endif //CW_OVarsOut_CalcControl_chk



#ifdef CW_LAM_CalcControl_chk

on CW_LAM_CalcControl_chk 
{

	CW_LAM_DialogItemsShow();
	
	#ifdef EQ_IsValueBlock
		IconSet(FALSE);
	#endif
	
}


on CW_LAM_RespondToWhich_pop
{

	integer i;
	integer userResponse;
	integer popupSize;
	integer currentSelection;
	
	//Build the CW_LAM_DBReadVarNamesArray list array
	popupSize = 0;
	for(i=0; i<iVars_NumTableRows; i++)
		{
		if(iVars_Types_str[i] == "DB read value"  ||  iVars_Types_str[i] == "DB read PRI"  ||  
		   iVars_Types_str[i] == "DB address"  ||  iVars_Types_str[i] == "DB index")
			{
			popupSize++;
			MakeArray(CW_LAM_DBReadVarNamesArray, popupSize);
			CW_LAM_DBReadVarNamesArray[popupSize-1] = iVars_Names[i];
			}
		}
	popupSize = popupSize+2;
	MakeArray(CW_LAM_DBReadVarNamesArray, popupSize);
	CW_LAM_DBReadVarNamesArray[popupSize - 2] = "-";
	CW_LAM_DBReadVarNamesArray[popupSize - 1] = "any 'DB Read' variable";
	
	//find location of user's current selection
	currentSelection = popupSize;					//set currentSelection to default
	for(i=0; i<popupSize; i++)
		{
		if(CW_LAM_DBReadVarNamesArray[i] == CW_LAM_RespondToWhich_etxt)
			{
			currentSelection = i + 1;
			break;
			}
		}
	
	//make a flying popup using CW_LAM_RespondToWhich_etxt
	userResponse = PopupMenuArray (CW_LAM_DBReadVarNamesArray, currentSelection);
	CW_LAM_RespondToWhich_etxt = CW_LAM_DBReadVarNamesArray[userResponse - 1];
	CW_LAM_RespondToWhich_pop = userResponse;
	
	DisposeArray(CW_LAM_DBReadVarNamesArray);
	
}//on CW_LAM_RespondToWhich_pop


on CW_LAM_RespondWhen_pop
{

	integer i;
	integer userResponse;
	integer popupSize;
	integer currentSelection;
	
	//Build the connector list array
	popupSize = 2;
	MakeArray(CW_LAM_RespondWhenOptionsArray, popupSize);
	#ifdef EQ_IsQueueEquation
		CW_LAM_RespondWhenOptionsArray[0] = "immediately- 1 item push";
	#else
		CW_LAM_RespondWhenOptionsArray[0] = "immediately";
	#endif
	CW_LAM_RespondWhenOptionsArray[1] = "after zero-time event";
	
	//find location of user's current selection
	currentSelection = 1;					//set currentSelection to default
	for(i=0; i<popupSize; i++)
		{
		if(CW_LAM_RespondWhenOptionsArray[i] == CW_LAM_RespondWhen_etxt)
			{
			currentSelection = i + 1;
			break;
			}
		}
	
	//make a flying popup using CW_LAM_RespondWhenOptionsArray
	userResponse = PopupMenuArray (CW_LAM_RespondWhenOptionsArray, currentSelection);
	CW_LAM_RespondWhen_etxt = CW_LAM_RespondWhenOptionsArray[userResponse - 1];
	CW_LAM_RespondWhen_pop = userResponse;

	DisposeArray(CW_LAM_RespondWhenOptionsArray);
	
}//on CW_LAM_RespondWhen_pop


procedure CW_LAM_GetWhichDBReadVar()
{

	integer i;
	integer me;
	
	me = MyBlockNumber();
	
	//get CW_LAM_WhichDBReadIVar.  must do this BEFORE EQ_OnCheckData() is called because that's where EQ_RegisterLinkContent() is called
	if(CW_LAM_CalcControl_chk == TRUE)
		{
		//if(StrFind(CW_LAM_RespondToWhich_etxt, "any", FALSE, FALSE) < 0)	//if one specific db read ivar has been chosen instead of "any"
		if(CW_LAM_RespondToWhich_etxt != "any 'DB Read' variable")
			{
			CW_LAM_WhichDBReadIVar = -1;

			for(i=0; i<iVars_NumTableRows; i++)
				{
				if(iVars_Names[i] == CW_LAM_RespondToWhich_etxt)
					{
					CW_LAM_WhichDBReadIVar = i;
					break;
					}
				}
			if(CW_LAM_WhichDBReadIVar < 0)
				{
				UserError("There is a problem in Equation block number " + me + ". The DB Read variable named """ + CW_LAM_RespondToWhich_etxt +
						  """ does not exist, but it is being referenced in the ""Calc When"" section of the Options tab.");
				}
			}
		else
			CW_LAM_WhichDBReadIVar = -1;		
		}

}//procedure CW_LAM_GetWhichDBReadVar()


procedure CW_LAM_OnCreateBlock()
{

	//Setup LAM_- link alert message
	CW_LAM_CalcControl_chk =  FALSE;
	CW_LAM_RespondToWhich_etxt = "any 'DB Read' variable";
	#ifdef EQ_IsQueueEquation
		CW_LAM_RespondWhen_etxt = "after zero-time event";
		CW_LAM_RespondWhen_pop = WHEN_CALC_CURRENT_EVENT;
	#else
		CW_LAM_RespondWhen_etxt = "immediately";
		CW_LAM_RespondWhen_pop = WHEN_CALC_IMMEDIATE;
	#endif
	
}//procedure CW_LAM_OnCreateBlock()


procedure CW_LAM_DialogItemsShow()
{

	if(CW_LAM_CalcControl_chk == TRUE)
		{
		DisableDialogItem("CW_LAM_RespondToWhich_lbl", FALSE);
		DisableDialogItem("CW_LAM_RespondToWhich_pop", FALSE);
		DisableDialogItem("CW_LAM_RespondToWhich_etxt", FALSE);
		DisableDialogItem("CW_LAM_RespondWhen_lbl", FALSE);
		DisableDialogItem("CW_LAM_RespondWhen_pop", FALSE);
		DisableDialogItem("CW_LAM_RespondWhen_etxt", FALSE);
		}
	else
		{
		DisableDialogItem("CW_LAM_RespondToWhich_lbl", TRUE);
		DisableDialogItem("CW_LAM_RespondToWhich_pop", TRUE);
		DisableDialogItem("CW_LAM_RespondToWhich_etxt", TRUE);
		DisableDialogItem("CW_LAM_RespondWhen_lbl", TRUE);
		DisableDialogItem("CW_LAM_RespondWhen_pop", TRUE);
		DisableDialogItem("CW_LAM_RespondWhen_etxt", TRUE);
		}
		

}//procedure CW_LAM_DialogItemsShow()


#endif //CW_LAM_CalcControl_chk




//**********************************************************************
//END: "Calc When" message handlers for Equation and Query Equation
//**********************************************************************
//**********************************************************************





//**********************************************************************
//**********************************************************************
//Start CMC (Connector Message Control) Functions
//**********************************************************************


#ifdef CMC_chk

/*
on CMC_chk
{

	CMC_IVars_ResizeArrays(CMC_INITIALIZE);
	CMC_OVars_ResizeArrays(CMC_INITIALIZE);
	
	iVars_TableSetup();
	oVars_TableSetup();
	
	//CMC_IVarsIn_Animate();			//7/6/11
	//CMC_OVarsOut_Animate();			//7/6/11
	CMC_ConnectorAnimate();

}//on CMC_chk


//7/6/11
procedure CMC_ConnectorAnimate()
{

	integer i;
	integer me;
	integer numRows;
	
	me = MyBlockNumber();
	
	//delete iVarsIn connector animation objects
	numRows = GetDimension(CMC_IVarsIn_AnimObjectIDs);
	for(i=0; i<numRows; i++)
		AnimationObjectDelete(CMC_IVarsIn_AnimObjectIDs[i]);
	DisposeArray(CMC_IVarsIn_AnimObjectIDs);

	//delete oVarsOut connector animation objects
	numRows = GetDimension(CMC_OVarsOut_AnimObjectIDs);
	for(i=0; i<numRows; i++)
		AnimationObjectDelete(CMC_OVarsOut_AnimObjectIDs[i]);
	DisposeArray(CMC_OVarsOut_AnimObjectIDs);
	
	CMC_IVarsIn_Animate();
	CMC_OVarsOut_Animate();
	
}//procedure CMC_ConnectorAnimate()
*/



//***********************************
//***********************************
//START:  CMC_IVars Functions
//***********************************

procedure CMC_IVarsIn_Animate()
{

	integer i;
	integer me;
	integer numRows;
	integer animObject;
	integer conPosiArray[4];
	integer blockPosiArray[4];
	integer topConPosi;
	integer leftConPosi;
	integer leftObjectStartPosi;
	integer topObjectStartPosi;
	integer leftObjectPosi;
	integer topObjectPosi;
	integer numConVars;
	integer polyArray[3][2];
	integer settingsSize;
	integer iconViewIndex;			//7/29/11
	string iconViewName;			//7/29/11
	
	me = MyBlockNumber();
	
	//7/6/11
	/*
	//delete animation objects
	numRows = GetDimension(CMC_IVarsIn_AnimObjectIDs);
	for(i=0; i<numRows; i++)
		AnimationObjectDelete(CMC_IVarsIn_AnimObjectIDs[i]);
	DisposeArray(CMC_IVarsIn_AnimObjectIDs);
	*/

	
	if(CMC_chk)
		{
		iconViewIndex = IconGetView(me);						//7/29/11
		iconViewName = IconGetViewName(me, iconViewIndex);		//7/29/11
		if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse"  ||  iconViewName == "")	//7/29/11:  get null string if in beta view
			{
			settingsSize = GetDimension(CMC_IVarsIn_Settings);		//7/6/11
			if(settingsSize == iVars_NumTableRows)
				//7/6/11:	Note- need this condition here because there are certain sequences of code execution where CMC_IVarsIn_Animate() 
				//			gets called but CMC_IVarsIn_Settings[] hasn't been dimensioned yet.  this is all part of the code I wrote to support
				//			deleting both iVar and oVar animation objects up front BEFORE CMC_IVarsIn_Animate() and CMC_OVarsOut_Animate() get called.
				{
				numConVars = 0;
				for(i=0; i<iVars_NumTableRows; i++)
					{
					if(iVars_Types_Int[i] == EQ_CONNECTORS)
						numConVars++;
					}
				
				if(numConVars > 0)
					{
					iVarsIn_ConnectorsSetup();
					
					//initialize the "CMC_IVarsIn_AnimObjectIDs[]" array
					numRows = GetDimension(CMC_IVarsIn_AnimObjectIDs);
					MakeArray(CMC_IVarsIn_AnimObjectIDs, iVarsIn_NumCons);
					for(i=numRows; i<iVarsIn_NumCons; i++)
						{
						CMC_IVarsIn_AnimObjectIDs[i] = -1;
						}
			
					//create animation objects
					for(i=0; i<iVarsIn_NumCons; i++)
						{
						animObject = CMC_IVarsIn_AnimObjectIDs[i];
						if(animObject == -1  ||  AnimationObjectExists(animObject) == FALSE)
							{
							CMC_IVarsIn_AnimObjectIDs[i] = AnimationObjectCreate(FALSE);
							}
						}
					
					//shape and color animation objects
					for(i=0; i<iVarsIn_NumCons; i++)
						{
						
						if(iconViewName == "Default View"  ||  iconViewName == "")			//7/29/11
							{
							animObject = CMC_IVarsIn_AnimObjectIDs[i];
							AnimationStretchTo(animObject, 0, 0, 10, 10, TRUE);
							polyArray[0][0] = 0;
							polyArray[0][1] = 5;
							polyArray[1][0] = 10;
							polyArray[1][1] = 0;
							polyArray[2][0] = 10;
							polyArray[2][1] = 10;
							AnimationPoly(animObject, 3, polyArray);
							AnimationBorder(animObject, 0);
							}
						else if(iconViewName == "Default View Reverse")						//7/29/11
							{
							animObject = CMC_IVarsIn_AnimObjectIDs[i];
							AnimationStretchTo(animObject, 0, 0, 10, 10, TRUE);
							polyArray[0][0] = 10;
							polyArray[0][1] = 5;
							polyArray[1][0] = 0;
							polyArray[1][1] = 10;
							polyArray[2][0] = 0;
							polyArray[2][1] = 0;
							AnimationPoly(animObject, 3, polyArray);
							AnimationBorder(animObject, 0);
							}
						
						//set color
						if(CMC_IVarsIn_Settings[i] == CMC_IVAR_MSG_EMULATION)
							{
							//no animation object for message emulation
							//AnimationColor(animObject, 0, 0, 65535, 1);
							//AnimationBorder(animObject, 1);
							}
						else if(CMC_IVarsIn_Settings[i] == CMC_IVAR_ALWAYS)
							{
							AnimationColor(animObject, 21845, 65535, 39321, 1);
							}
						else if(CMC_IVarsIn_Settings[i] == CMC_IVAR_NEVER)
							{
							AnimationColor(animObject, 0, 65534, 56797, 1);
							}
						else
							{
							UserError("There is a problem with " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							}
						}
					
					//place animation objects
					for(i=0; i<iVarsIn_NumCons; i++)
						{
						animObject = CMC_IVarsIn_AnimObjectIDs[i];
						
						//get connector position
						GetConnectorPosition(me, iVarsIn_ConNums[i], conPosiArray);
						topConPosi = conPosiArray[0];
						leftConPosi = conPosiArray[1];
						
						//get anim obejct's original location
						GetBlockTypePosition(me, blockPosiArray);
						topObjectStartPosi = blockPosiArray[0];
						leftObjectStartPosi = blockPosiArray[1];
						
						//place anim object next to connector
						if(iconViewName == "Default View"  ||  iconViewName == "")			//7/29/11
							{
							topObjectPosi = topConPosi - topObjectStartPosi - 2;
							leftObjectPosi = leftObjectStartPosi - leftConPosi - 17;
							}
						else if(iconViewName == "Default View Reverse")						//7/29/11
							{
							topObjectPosi = topConPosi - topObjectStartPosi - 2;
							leftObjectPosi = leftConPosi - leftObjectStartPosi + 13;
							}
						
						AnimationMoveTo(animObject, leftObjectPosi, topObjectPosi, TRUE);
						}
						
					//show animation objects
					for(i=0; i<iVarsIn_NumCons; i++)
						{
						animObject = CMC_IVarsIn_AnimObjectIDs[i];
						if(CMC_IVarsIn_Settings[i] == CMC_IVAR_MSG_EMULATION)
							{
							AnimationHide(animObject, TRUE);
							}
						else
							{
							AnimationShow(animObject);
							}
						}
					
					}//if(numConVars > 0)
					
				}//if(settingsSize == iVars_NumTableRows)
				
			}//if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse"  ||  iconViewName == "")
			
		}//if(CMC_chk)

}//procedure CMC_IVarsIn_Animate()

/*
procedure CMC_IVarsIn_Set()
{
	
	integer me;
	integer conClicked;
	integer conIndex;
	integer popupChoice;
	string conName;
	string CMC_PopContents[3];
	
	if(CMC_chk)
		{
	
		me = MyBlockNumber();
		conClicked = GetRightClickedCon();
		conName = GetConName(me, conClicked);
		conIndex = ConArrayGetNthCon(conClicked);
		
		//show the options popup
		CMC_PopContents[0] = "Use message emulation [ME] (default)";
		CMC_PopContents[1] = "Always propagate message [A]";
		CMC_PopContents[2] = "Never propagate message [N]";
		popupChoice = PopupMenuArray (CMC_PopContents, 0);
	
		if(popupChoice == CMC_IVAR_MSG_EMULATION)	
			{
			CMC_IVarsIn_Settings[conIndex] = CMC_IVAR_MSG_EMULATION;
			}
		else if(popupChoice == CMC_IVAR_ALWAYS)	
			{
			CMC_IVarsIn_Settings[conIndex] = CMC_IVAR_ALWAYS;
			}
		else if(popupChoice == CMC_IVAR_NEVER)
			{
			CMC_IVarsIn_Settings[conIndex] = CMC_IVAR_NEVER;
			}
		
		iVars_TableSetup();
		
		//CMC_IVarsIn_Animate();			//7/6/11
		CMC_ConnectorAnimate();

		}//if(CMC_chk)
		
}//procedure CMC_IVarsIn_Set()


//called in iVars_ResizeDynamicArrays(), CMC_chk
procedure CMC_IVars_ResizeArrays(integer doWhat)
{

	integer i;
	integer lastRowSize;

	if(CMC_chk)
		{
		if(doWhat == CMC_INITIALIZE)
			{
			MakeArray(CMC_IVarsIn_Settings, iVars_NumTableRows);
			
			for(i=0; i<iVars_NumTableRows; i++)
				{
				CMC_IVarsIn_Settings[i] = CMC_IVAR_MSG_EMULATION;		//set to default always
				}
			}
		
		else
			{
			lastRowSize = GetDimension(CMC_IVarsIn_Settings);
			MakeArray(CMC_IVarsIn_Settings, iVars_NumTableRows);
		
			//if more rows were added to the table
			if(lastRowSize < iVars_NumTableRows)
				{
				for(i=lastRowSize; i<iVars_NumTableRows; i++)
					{
					
					if(i == 0  ||  doWhat != RESIZE_ADD_SUBTRACT_FROM_END)	//if row 0 or if inserting rows into middle of table,...
						{
						//..., then use default settings for the rows we're adding to the bottom.  NOTE: even if 
						//user requested an "insert row into middle" operation, we are going to add rows to the bottom
						//first.  Then we'll move everything down later in the "copy rows" function
						
						CMC_IVarsIn_Settings[i] = CMC_IVAR_MSG_EMULATION;		//set to default always
						}
				
					else //if adding rows to the end, use the previous row's settings to define the new row's settings.
						{
						CMC_IVarsIn_Settings[i] = CMC_IVarsIn_Settings[i-1];
						}
					
					}//for(i=lastRowSize; i<iVars_NumTableRows; i++)		
				
				}//if(lastRowSize < iVars_NumTableRows)
			}
		
		}
	
	else //if(!CMC_chk)
		{
		DisposeArray(CMC_IVarsIn_Settings);
		}	
		
	//CMC_IVarsIn_Animate();			//7/6/11
	CMC_ConnectorAnimate();

}//procedure CMC_IVars_ResizeArrays(integer doWhat)
*/

//***********************************
//END:  CMC_IVars Functions
//***********************************
//***********************************


//***********************************
//***********************************
//START:  CMC_OVars Functions
//***********************************

procedure CMC_OVarsOut_Animate()
{

	integer i;
	integer me;
	integer numRows;
	integer animObject;
	integer conPosiArray[4];
	integer blockPosiArray[4];
	integer topConPosi;
	integer leftConPosi;
	integer leftObjectStartPosi;
	integer topObjectStartPosi;
	integer leftObjectPosi;
	integer topObjectPosi;
	integer numConVars;
	integer polyArray[3][2];
	integer settingsSize;
	integer iconViewIndex;			//7/29/11
	string iconViewName;			//7/29/11
	
	me = MyBlockNumber();
	
	//7/6/11
	/*
	//delete animation objects
	numRows = GetDimension(CMC_OVarsOut_AnimObjectIDs);
	for(i=0; i<numRows; i++)
		AnimationObjectDelete(CMC_OVarsOut_AnimObjectIDs[i]);
	DisposeArray(CMC_OVarsOut_AnimObjectIDs);
	*/
	
	if(CMC_chk)
		{
		
		iconViewIndex = IconGetView(me);						//7/29/11
		iconViewName = IconGetViewName(me, iconViewIndex);		//7/29/11
		if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse"  ||  iconViewName == "")	//7/29/11:  get null string if in beta view
			{
			settingsSize = GetDimension(CMC_OVarsOut_Settings);		//7/6/11
			if(settingsSize == oVars_NumTableRows)
				//7/6/11:	Note- need this condition here because there are certain sequences of code execution where CMC_OVarsOut_Animate() 
				//			gets called but CMC_OVarsOut_Settings[] hasn't been dimensioned yet.  this is all part of the code I wrote to support
				//			deleting both iVar and oVar animation objects up front BEFORE CMC_IVarsIn_Animate() and CMC_OVarsOut_Animate() get called.
				{
				numConVars = 0;
				for(i=0; i<oVars_NumTableRows; i++)
					{
					if(oVars_Types_Int[i] == EQ_CONNECTORS)
						numConVars++;
					}
				
				if(numConVars > 0)
					{
					oVarsOut_ConnectorsSetup();
					
					//initialize the "CMC_OVarsOut_AnimObjectIDs[]" array
					numRows = GetDimension(CMC_OVarsOut_AnimObjectIDs);
					MakeArray(CMC_OVarsOut_AnimObjectIDs, oVarsOut_NumCons);
					for(i=numRows; i<oVarsOut_NumCons; i++)
						{
						CMC_OVarsOut_AnimObjectIDs[i] = -1;
						}
			
					//create animation objects
					for(i=0; i<oVarsOut_NumCons; i++)
						{
						animObject = CMC_OVarsOut_AnimObjectIDs[i];
						if(animObject == -1  ||  AnimationObjectExists(animObject) == FALSE)
							{
							CMC_OVarsOut_AnimObjectIDs[i] = AnimationObjectCreate(FALSE);
							}
						}
					
					//shape and color animation objects
					for(i=0; i<oVarsOut_NumCons; i++)
						{
						if(iconViewName == "Default View"  ||  iconViewName == "")			//7/29/11
							{
							animObject = CMC_OVarsOut_AnimObjectIDs[i];
							AnimationStretchTo(animObject, 0, 0, 10, 10, TRUE);
							polyArray[0][0] = 0;
							polyArray[0][1] = 0;
							polyArray[1][0] = 10;
							polyArray[1][1] = 5;
							polyArray[2][0] = 0;
							polyArray[2][1] = 10;
							AnimationPoly(animObject, 3, polyArray);
							AnimationBorder(animObject, 0);
							}
						else if(iconViewName == "Default View Reverse")						//7/29/11
							{
							animObject = CMC_OVarsOut_AnimObjectIDs[i];
							AnimationStretchTo(animObject, 0, 0, 10, 10, TRUE);
							polyArray[0][0] = 0;
							polyArray[0][1] = 5;
							polyArray[1][0] = 10;
							polyArray[1][1] = 0;
							polyArray[2][0] = 10;
							polyArray[2][1] = 10;
							AnimationPoly(animObject, 3, polyArray);
							AnimationBorder(animObject, 0);
							}
						
						//set color
						if(CMC_OVarsOut_Settings[i] == CMC_OVAR_MSG_EMULATION)
							{
							//no animation object for message emulation
							//AnimationColor(animObject, 0, 0, 65534, 1);
							//AnimationBorder(animObject, 1);
							}
						else if(CMC_OVarsOut_Settings[i] == CMC_OVAR_VAL_CHANGE_ONLY)
							{
							AnimationColor(animObject, 8738, 65535, 65535, 1);
							}
						else if(CMC_OVarsOut_Settings[i] == CMC_OVAR_ALWAYS)
							{
							AnimationColor(animObject, 21845, 65534, 43690, 1);
							}
		
						else if(CMC_OVarsOut_Settings[i] == CMC_OVAR_NEVER)
							{
							AnimationColor(animObject, 0, 65534, 56797, 1);
							}
						else
							{
							UserError("There is a problem with " + BlockName(me) + " block " + me + ".  Please contact Imagine That.");
							}
						}
					
					//place animation objects
					for(i=0; i<oVarsOut_NumCons; i++)
						{
						animObject = CMC_OVarsOut_AnimObjectIDs[i];
						
						//get connector position
						GetConnectorPosition(me, oVarsOut_ConNums[i], conPosiArray);
						topConPosi = conPosiArray[0];
						leftConPosi = conPosiArray[1];
						
						//get anim obejct's original location
						GetBlockTypePosition(me, blockPosiArray);
						topObjectStartPosi = blockPosiArray[0];
						leftObjectStartPosi = blockPosiArray[1];
						
						//place anim object next to connector
						if(iconViewName == "Default View"  ||  iconViewName == "")			//7/29/11
							{
							topObjectPosi = topConPosi - topObjectStartPosi - 2;
							leftObjectPosi = leftObjectStartPosi - leftConPosi + 93;
							}
						else if(iconViewName == "Default View Reverse")						//7/29/11
							{
							topObjectPosi = topConPosi - topObjectStartPosi - 2;
							leftObjectPosi = leftConPosi - leftObjectStartPosi - 17;
							}
						
						AnimationMoveTo(animObject, leftObjectPosi, topObjectPosi, TRUE);
						}
						
					//show animation objects
					for(i=0; i<oVarsOut_NumCons; i++)
						{
						animObject = CMC_OVarsOut_AnimObjectIDs[i];
						if(CMC_OVarsOut_Settings[i] == CMC_OVAR_MSG_EMULATION)
							{
							AnimationHide(animObject, TRUE);
							}
						else
							{
							AnimationShow(animObject);
							}
						}
						
					}//if(numConVars > 0)
					
				}//if(settingsSize == oVars_NumTableRows)
				
			}//if(iconViewName == "Default View"  ||  iconViewName == "Default View Reverse"  ||  iconViewName == "")
		
		}//if(CMC_chk)

}//procedure CMC_OVarsOut_Animate()

/*
procedure CMC_OVarsOut_Set()
{
	
	integer me;
	integer conClicked;
	integer conIndex;
	integer popupChoice;
	string conName;
	string CMC_PopContents[4];
	
	if(CMC_chk)
		{
	
		me = MyBlockNumber();
		conClicked = GetRightClickedCon();
		conName = GetConName(me, conClicked);
		conIndex = ConArrayGetNthCon(conClicked);
		
		//show the options popup
		CMC_PopContents[0] = "Use message emulation [ME] (default)";
		CMC_PopContents[1] = "Propagate message when con value changes [CVC]";
		CMC_PopContents[2] = "Always propagate message [A]";
		CMC_PopContents[3] = "Never propagate message [N]";
		popupChoice = PopupMenuArray (CMC_PopContents, 0);
	
		if(popupChoice == CMC_OVAR_MSG_EMULATION)	
			{
			CMC_OVarsOut_Settings[conIndex] = CMC_OVAR_MSG_EMULATION;
			}
		
		else if(popupChoice == CMC_OVAR_VAL_CHANGE_ONLY)
			{
			CMC_OVarsOut_Settings[conIndex] = CMC_OVAR_VAL_CHANGE_ONLY;
			}
		
		else if(popupChoice == CMC_OVAR_ALWAYS)	
			{
			CMC_OVarsOut_Settings[conIndex] = CMC_OVAR_ALWAYS;
			}
		
		else if(popupChoice == CMC_OVAR_NEVER)
			{
			CMC_OVarsOut_Settings[conIndex] = CMC_OVAR_NEVER;
			}
		
		oVars_TableSetup();
	
		//CMC_OVarsOut_Animate();			//7/6/11
		CMC_ConnectorAnimate();
	
		}//if(CMC_chk)

}//procedure CMC_OVarsOut_Set()
*/

procedure CMC_OVarsOut_GetConChanged()
{
	
	integer i;
	
	for(i=0; i<oVarsOut_NumCons; i++)
		{
		if(oVars_Values[i] != CMC_OVars_ValuesOld[i])
			{
			CMC_OVars_ValChanged[i] = TRUE;
			}
		else
			{
			CMC_OVars_ValChanged[i] = FALSE;
			}
		}
	
}//procedure CMC_OVarsOut_GetConChanged()

/*
procedure CMC_OVars_ResizeArrays(integer doWhat)
{

	integer i;
	integer lastRowSize;

	if(CMC_chk)
		{
		if(doWhat == CMC_INITIALIZE)
			{
			//init CMC_OVarsOut_Settings[]
			MakeArray(CMC_OVarsOut_Settings, oVars_NumTableRows);
			for(i=0; i<oVars_NumTableRows; i++)
				{
				CMC_OVarsOut_Settings[i] = CMC_OVAR_MSG_EMULATION;		//set to default always
				}			
			}
		
		else
			{
			lastRowSize = GetDimension(CMC_OVarsOut_Settings);
			MakeArray(CMC_OVarsOut_Settings, oVars_NumTableRows);
				
			//if more rows were added to the table
			if(lastRowSize < oVars_NumTableRows)
				{
				
				for(i=lastRowSize; i<oVars_NumTableRows; i++)
					{
					if(i == 0  ||  doWhat != RESIZE_ADD_SUBTRACT_FROM_END)	//if row 0 or if inserting rows into middle of table,...
						{
						//..., then use default settings for the rows we're adding to the bottom.  NOTE: even if 
						//user requested an "insert row into middle" operation, we are going to add rows to the bottom
						//first.  Then we'll move everything down later in the "copy rows" function
		
						CMC_OVarsOut_Settings[i] = CMC_OVAR_MSG_EMULATION;		//set to default always
						}
				
					else //if adding rows to the end, use the previous row's settings to define the new row's settings.
						{
						CMC_OVarsOut_Settings[i] = CMC_OVarsOut_Settings[i-1];
						}
					
					}//for(i=lastRowSize; i<oVars_NumTableRows; i++)		
				
				}//if(lastRowSize < Vars_oVarsNumTableRows)
			}
				
		MakeArray(CMC_OVars_ValChanged, oVars_NumTableRows);
		MakeArray(CMC_OVars_ValuesOld, oVars_NumTableRows);
		}
	
	else //if(!CMC_chk)
		{
		DisposeArray(CMC_OVarsOut_Settings);
		DisposeArray(CMC_OVars_ValChanged);
		DisposeArray(CMC_OVars_ValuesOld);
		DisposeArray(CMC_OVarsOut_ConBlocks);
		}	
		
	//CMC_OVarsOut_Animate();			//7/6/11
	CMC_ConnectorAnimate();
		
}//procedure CMC_OVars_ResizeArrays(integer doWhat)
*/


//***********************************
//END:  CMC_OVars Functions
//***********************************
//***********************************

#endif //CMC_chk


//**********************************************************************
//End CMC (Connector Message Control) Functions
//**********************************************************************
//**********************************************************************












