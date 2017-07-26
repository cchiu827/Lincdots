******************************************************************
**	RightClick.h Include										**
**	Copyright © 2003-2010 by Imagine That, Inc.					**
**	All rights reserved.										**
**	Created by Dave Krahl										**
******************************************************************



******************************************************************
** Created 2003
**	Modified:
**	Date	Release		By			Description
**
******************************************************************


//Created to include code common to many blocks requiring the same right click behavior

#ifndef EXECUTABLE_BLOCK
	constant EXECUTABLE_BLOCK is 3;
#endif

constant LEFT_TO_RIGHT_BLOCK is 1;
constant RIGHT_TO_LEFT_BLOCK is 2;

//prototypes
#ifdef RCMC_chk
procedure RCMC_IVarsIn_Set();
procedure RCMC_OVarsOut_Set();
#endif



#IFDEF addTransport_btn

	integer GetBlockDirection()

	{	
	integer me;
	String ViewName;
	me = MyBlockNumber();
	ViewName = IconGetViewName(me, IconGetView(me));
	if(StrFind(ViewName, "to Right", FALSE, FALSE) >= 0 || StrFind(ViewName, "to the Right", FALSE, FALSE))
		return (LEFT_TO_RIGHT_BLOCK);
	else
		return(RIGHT_TO_LEFT_BLOCK);
	}


	Procedure AddTransport(Integer UseConnector)
	{
	integer transportBlockNum;
	integer NextBlockNum;
	integer ConPositionArray[4];
	integer xPos,YPos;
	integer NextBlockConNum;
	integer NumCons;
	
		if(PopupCanceled())
			return;
	
		Numcons = GetConBlocks(MyBlockNumber(), UseConnector, Connected);
		if(Numcons > 0)
			{
			NextBlockNum = Connected[0][0];
			NextBlockConNum = Connected[0][1];
			ClearConnection(MyBlockNumber(), UseConnector, NextBlockNum, NextBlockConNum);
			}
		else NextBlockNum = -1;
		
		if(GetEnclosingHBlockNum() == -1)
			{
			if(PlatformWindows)
				{
				OpenExtendFile("Item.lix");
				GetConnectorPosition(MyBlockNumber(), UseConnector, ConPositionArray);
//				if(IconGetViewName(MyBlockNumber(), IconGetView(MyBlockNumber())) == "Left to right")
				if(GetBlockDirection() == LEFT_TO_RIGHT_BLOCK)
					transportBlockNum = PlaceBlock("Transport", "Item.lix", (ConPositionArray[1] + ConPositionArray[3])/2 + 8, (ConPositionArray[0] + ConPositionArray[2])/2 -17, -1, 0);
				else
					transportBlockNum = PlaceBlock("Transport", "Item.lix", (ConPositionArray[1] + ConPositionArray[3])/2 - 48, (ConPositionArray[0] + ConPositionArray[2])/2 -22, -1, 0);
				}
			else			// macintosh
				{
				OpenExtendFile("Item lib");
				GetConnectorPosition(MyBlockNumber(), UseConnector, ConPositionArray);//				if(IconGetViewName(MyBlockNumber(), IconGetView(MyBlockNumber())) == "Left to right")
				if(GetBlockDirection() == LEFT_TO_RIGHT_BLOCK)
					transportBlockNum = PlaceBlock("Transport", "Item lib", (ConPositionArray[1] + ConPositionArray[3])/2 + 8, (ConPositionArray[0] + ConPositionArray[2])/2 -17, -1, 0);
				else
					transportBlockNum = PlaceBlock("Transport", "Item lib", (ConPositionArray[1] + ConPositionArray[3])/2 - 48, (ConPositionArray[0] + ConPositionArray[2])/2 -22, -1, 0);
				}
			}
		else
			{
			if(PlatformWindows)
				{
				OpenExtendFile("Item.lix");
				GetConnectorPosition(MyBlockNumber(), UseConnector, ConPositionArray);
//				if(IconGetViewName(MyBlockNumber(), IconGetView(MyBlockNumber())) == "Left to right")
				if(GetBlockDirection() == LEFT_TO_RIGHT_BLOCK)
					transportBlockNum = PlaceBlockInHBlock("Transport", "Item.lix", (ConPositionArray[1] + ConPositionArray[3])/2 + 8, (ConPositionArray[0] + ConPositionArray[2])/2 -17, GetEnclosingHBlockNum());
				else
					transportBlockNum = PlaceBlockInHBlock("Transport", "Item.lix", (ConPositionArray[1] + ConPositionArray[3])/2 - 48, (ConPositionArray[0] + ConPositionArray[2])/2 -22, GetEnclosingHBlockNum());
				}
			else			// macintosh
				{
				OpenExtendFile("Item lib");
				GetConnectorPosition(MyBlockNumber(), UseConnector, ConPositionArray);
//				if(IconGetViewName(MyBlockNumber(), IconGetView(MyBlockNumber())) == "Left to right")
				if(GetBlockDirection() == LEFT_TO_RIGHT_BLOCK)
					transportBlockNum = PlaceBlockInHBlock("Transport", "Item lib", (ConPositionArray[1] + ConPositionArray[3])/2 + 8, (ConPositionArray[0] + ConPositionArray[2])/2 -17, GetEnclosingHBlockNum());
				else
					transportBlockNum = PlaceBlockInHBlock("Transport", "Item lib", (ConPositionArray[1] + ConPositionArray[3])/2 - 48, (ConPositionArray[0] + ConPositionArray[2])/2 -22, GetEnclosingHBlockNum());
				}
			}
		
//		if(IconGetViewName(MyBlockNumber(), IconGetView(MyBlockNumber())) == "Left to right")
		if(GetBlockDirection() == LEFT_TO_RIGHT_BLOCK)
			IconSetViewByPartialName(TransportBlockNum, "Left to right (small)");
		else
			IconSetViewByPartialName(TransportBlockNum, "Right to left (small)");
		
		MakeConnection(MyBlockNumber(), UseConnector, transportBlockNum, GetConNumber(transportBlockNum, "ItemIn"));
		
		if(nextBlockNum > -1)
			MakeConnection(transportBlockNum, GetConNumber(transportBlockNum, "ItemOut"),NextBlockNum,NextBlockConNum);
		
		DisposeArray(Connected);
			
	}

	on AddTransport_btn
		{
		AddTransport(GetConNumber(MyBlockNumber(), "ItemOut"));
		}



#ENDIF

#IFDEF addHistoryBlock_btn

	Procedure AddHistortyBlock(integer UseConnector)
	{
	integer infoBlockNum;
		

		if(PopupCanceled())
			return;
	
		
		if(UseConnector < 0)
			{
			UserError("Right-click on the connector where you want to add the History block");
			return;
			}
		if(PlatformWindows)
			{
			OpenExtendFile("Item.lix");
			infoBlockNum = PlaceBlock("History", "Item.lix", 20, 80, MyBlockNumber(), 2);
			}
		else			// macintosh
			{
			OpenExtendFile("Item lib");
			infoBlockNum = PlaceBlock("History", "Item lib", 20, 80, MyBlockNumber(), 2);
			}
		MakeConnection(MyBlockNumber(), UseConnector, InfoBlockNum, GetConNumber(InfoBlockNum, "SensorIn"));
		SetDialogVariable(infoBlockNum, "scriptCreated", 1, 0, 0);
//		MakeConnection(MyBlockNumber(), GetConNumber(MyBlockNumber(), "ItemOut"), InfoBlockNum, GetConNumber(InfoBlockNum, "ItemIn"));
		
	
	}//on addHistoryBlock_btn

	on addHistoryBlock_btn
		{
		AddHistortyBlock(GetConNumber(MyBlockNumber(), "ItemOut"));
		}

#ENDIF


#IFDEF deleteHistoryBlocks_btn


	Procedure deleteHistoryBlocks()
		{
	
		integer nextBlockNum;
		string nextBlockName;
		integer totalBlockCount;
		integer blockType;
		integer blockPosition[4];
		real scriptCreated;
		integer DeleteMe;
	

		if(PopupCanceled())
			return;
	
		nextBlockNum = 0;
		totalBlockCount = NumBlocks();
		DeleteMe = FALSE;
		
		//Search through the blocks in the model and activate an excel workbook if possible.
		While(nextBlockNum < totalBlockCount)
			{
			blockType = GetBlockTypePosition(nextBlockNum, blockPosition);
	
			if(blockType == EXECUTABLE_BLOCK)
				{
	
				nextBlockName = BlockName(nextBlockNum);
				if(nextBlockName == "History")
					{
					scriptCreated = StrToReal(GetDialogVariable(nextBlockNum, "scriptCreated", 0, 0));
					if(scriptCreated)
						{
						if(nextBlockNum == MyBlockNumber())			// we can't delete ourselves if we are in the middle of a loop
							DeleteMe = TRUE;
						else
							ClearBlock(nextBlockNum);
						}
					}
					
				}//if(blockType != EMPTY_GLOBAL_BLOCK_NUMBER_SLOT)
			
			nextBlockNum++;	
			
			}//While(nextBlockNum < totalBlockCount)
		
		if(DeleteMe)												// if we have to delete ourselves, it must be the last thing that we do.
			ClearBlock(MyBlockNumber());
		}// deleteHistoryBlocks_btn

	
	on deleteHistoryBlocks_btn
	{

		if(PopupCanceled())
			return;
	
		deleteHistoryBlocks();
	}

 
#ENDIF


on ConnectorRightClick
{
integer WhichPopup;
String ConName;
integer ClickedCon;
integer ConType;
String PopupList;
integer AddInfoSelected;
integer DeleteInfoSelected;
integer AddTransportSelected;

	ClickedCon = GetRightClickedCon();
	
	ConName = GetConName(MyBlockNumber(), ClickedCon);
	
	ConType = GetConnectorType(MyBlockNumber(), ClickedCon);

	if(ConType == 13)
		{
		
		#IFDEF CMC_chk
		
			if(StrFind(ConName, "iVarsIn", FALSE, FALSE) > -1)
				CMC_IVarsIn_Set();
		
			if(StrFind(ConName, "oVarsOut", FALSE, FALSE) > -1)
				CMC_OVarsOut_Set();
		
		#ENDIF
		
		}
	
	else if(ConType == 14 && (StrPart(ConName, StrLen(ConName) - 1, 1) == "t") || (StrFind(ConName, "out[", FALSE, FALSE) > -1))
		{
		PopupList = "";
		
		AddInfoSelected = 0;
		DeleteInfoSelected = 0;
		AddTransportSelected = 0;
		
		#IFDEF addHistoryBlock_btn
		
			AddInfoSelected = 1;
			DeleteInfoSelected = 1;
			AddTransportSelected = 1;
			PopupList += "Add History block;";
		
		#ENDIF
		
		#IFDEF deleteHistoryBlocks_btn
		
			DeleteInfoSelected++;
			AddTransportSelected++;
			PopupList += "Delete all auto-created History blocks;";
		
		#ENDIF
		
		#IFDEF addTransport_btn
		
			AddTransportSelected++;
			PopupList += "Add Transport following this block";
		
		#ENDIF
		
		WhichPopup = CreatePopupMenu(PopupList, "", 1);
//		WhichPopup = CreatePopupMenu("Add History block;Delete all auto-created History blocks;-;Add transport time following this block", "", 1);


		#IFDEF addHistoryBlock_btn
		
			if(WhichPopup == AddInfoSelected)
				AddHistortyBlock(ClickedCon);
		
		#ENDIF
		
		#IFDEF deleteHistoryBlocks_btn
		
			if(WhichPopup == DeleteInfoSelected)
				deleteHistoryBlocks();
		
		
		#ENDIF
		
		#IFDEF addTransport_btn
	
			if(WhichPopup == AddTransportSelected)
				AddTransport(ClickedCon);
		
		#ENDIF

//		UserError("WhichPopup = "+WhichPopup);
		}
		
}

#IFDEF In_On_ConnectionMake

	Procedure MakeCollapsedConnection(String ConName)
	{
	integer ConNum;
	integer NumConnected;
	integer me;
	String OutputConName;
	integer i;
	integer NumOutputCons;
	integer NumInputCons;
	integer FromWhere;
	
		if(In_on_connectionMake)						// if we are alreadyin on connection make return. Making new connections will call this message handler. Withoutthis there is an infinite loop
			return;
		
		In_on_connectionMake = TRUE;					
	
		me = MyBlockNumber();
	
		if(ConArrayGetCollapsed(me, ConName))							// if the input connector is connected
			{
			ConNum = ConArrayGetConNumber(me, ConName, 0);
			NumConnected = GetConBlocks(me, ConNum, ConArray);
			if(NumConnected == 1)
				{
				OutputConName = GetConName(ConArray[0][0], ConArray[0][1]);
				NumOutputCons = ConArrayGetNumCons(ConArray[0][0], OutputConName);
				NumInputCons = ConArrayGetNumCons(me, ConName);
				if(NumInputCons == NumOutputCons && ConArrayGetCollapsed(ConArray[0][0], OutputConName))
					{
					for(i=1;i<NumInputCons;i++)
						{
						MakeConnection(ConArray[0][0], ConArrayGetConNumber(ConArray[0][0], OutputConName, i), me, ConArrayGetConNumber(me, ConName, i));
						}
					}
				}
			}
		In_on_connectionMake = FALSE;
		DisposeArray(ConArray);
	}
#endif

constant ALT_POPUP_KEY is 16; // shift key
constant ALT_POPUP_KEY_MAC is 56;

constant LEFTCLICKDBNAME is "_leftClickDB";
constant LEFTCLICKTABLENAME is "_leftClickTable";

//
//		This function adds a popup menu when a dialog variable is clicked with the shift key held down
//	 		which adds the dialog variable to the Scenario Manager, Optimizer, or Statistics block. Additional 
//			blocks can be added to this list by adding one or more records in the LEFTCLICKDBNAME database.
//

integer do_keydown_mouse_click()
{
integer AltKeyDown;
string dName;
	integer DBIndex;
	integer TableIndex;
	integer BlockNum_field;
	integer OptionNumber_field;
	integer PopupLabel_field;
	integer DialogVar_field;
	integer StringVar_field;
	integer RowColumn_field;
	integer i;
	string popupString1;
	string popupString2;
	integer NumRecords;
	integer me;
	integer PopupResult;
	integer SendToBlockNum;
	integer DIType;
	integer row,column;
//	integer DTInfo[4];
	
	me = MyBlockNumber();
	dName = whichDialogItemClicked();		// get the name of the dialog item that was clicked

	if(PlatformWindows)
		AltKeyDown = IsKeyDown(ALT_POPUP_KEY);	// is the shift key down?
	else
		AltKeyDown = IsKeyDown(ALT_POPUP_KEY_MAC);	// is the shift key down?
		
	if(AltKeyDown)
		{
		DBIndex = DBDatabaseGetIndex(LEFTCLICKDBNAME);				// get the database index for the block to send the dialog variable to
		if(DBindex <= 0)
			return(AltKeyDown);
		TableIndex = DBTableGetIndex(DBIndex, LEFTCLICKTABLENAME);	// get the table index
		if(TableIndex <= 0)
			return(altKeyDown);
		}
	else
		return(altKeyDown);											// alternate (shift) key was not down, there is no reason to do anything else
		
	BlockNum_Field = DBFieldGetIndex(DBIndex, tableIndex, "Block Number");		// get the block number to send the dialog item to

	// add option number field
		
	OptionNumber_field = DBFieldGetIndex(DBIndex, tableIndex, "Option Number");	// get the option number (so that blocks may have multiple entries in the database)

		
	// add popup label field
		
	PopupLabel_Field = DBFieldGetIndex(DBIndex, tableIndex, "Popup label");		// popup label
		
	// add dialog dialog variable field	
	
	DialogVar_Field = DBFieldGetIndex(DBIndex, tableIndex, "Dialog variable");	// This is the numeric dialog variable that we set in the receiving block. It stores the block number where the dialog variable is coming from
		
	// add string variable field
		
	StringVar_Field = DBFieldGetIndex(DBIndex, tableIndex, "String variable");	// This is the string variable that we set in the receiving block. It stores the dialog variable name
	
	RowColumn_Field = DBFieldGetIndex(DBIndex, tableIndex, "Table row and column");	// This is the string variable that we set in the receiving block. It stores the dialog variable name

		
	// build the popup for all of the blocks that can access this dialog variable
		
	NumRecords = DBRecordsGetNum(DBIndex, tableIndex);
	PopupString1 = "";
	popupString2 = "";
	for(i=1;i<=NumRecords;i++)
		{
		if(StrLen(DBDataGetAsString(DBIndex, tableIndex, popupLabel_field, i)) + StrLen(popupString1) < 255)
			{
			PopupString1 += DBDataGetAsString(DBIndex, tableIndex, popupLabel_field, i)+";";
			}
		else if(StrLen(DBDataGetAsString(DBIndex, tableIndex, popupLabel_field, i)) + StrLen(popupString1) < 255)
			PopupString2 += DBDataGetAsString(DBIndex, tableIndex, popupLabel_field, i)+";";

		}
	PopupResult = CreatePopupMenu(PopupString1, PopupString2, 1);
	
	// send the dialog variable to the receiving block
	
	if(PopupResult > 0 && PopupResult <= NumRecords)
		{
		SendToBlockNum = DBDataGetAsNumber(DBIndex, tableIndex, BlockNum_field, PopupResult);
			{
			DIType = GetDialogItemInfo(me, dName, DI_DITYPE);
			if(DIType == DI_DATA_TABLE || DIType == DI_TEXT_TABLE)
				{
//				GetDataTableSelection(dName, DTInfo);
				SetDialogVariableNoMsg(SendToBlockNum, DBDataGetAsString(DBIndex, tableIndex, RowColumn_Field, PopupResult), WhichDTCell(DTWHICH_ROW), 0, 0);
				SetDialogVariableNoMsg(SendToBlockNum, DBDataGetAsString(DBIndex, tableIndex, RowColumn_Field, PopupResult), WhichDTCell(DTWHICH_COLUMN), 1, 0);
				}
			else
				{
				SetDialogVariableNoMsg(SendToBlockNum, DBDataGetAsString(DBIndex, tableIndex, RowColumn_Field, PopupResult), -1, 0, 0);
				SetDialogVariableNoMsg(SendToBlockNum, DBDataGetAsString(DBIndex, tableIndex, RowColumn_Field, PopupResult), -1, 1, 0);
				}
			}

		SetDialogVariableNoMsg(SendToBlockNum, DBDataGetAsString(DBIndex, tableIndex, StringVar_Field, PopupResult), dName, 0, 0);
		SetDialogVariable(SendToBlockNum, DBDataGetAsString(DBIndex, tableIndex, DialogVar_Field, PopupResult), me, 0, 0);				// Note: this will call a message handler in the remote block. This adds the dialog variable to the list in the block
		}
	return(AltKeyDown);
}



//constant LEFTCLICKDBNAME is "_leftClickDB";
//constant LEFTCLICKTABLENAME is "_leftClickTable";


// This adds a description of this block to the list of blocks can add a popup option to the shift-left-click popup menu
// This should be called in the CreateBlock, PasteBlock, and Open Model message handlers
// Arguments:
//		String DialogParam: This is a numeric dialog parameter in the stand-alone block. Use the message handler for this dialog item to process the stand-alone block's response to the shift-right-click popup menu in another block. After the modeler has made the selection in the shift-right-click popup menu, the SetDialogVariable function is called setting it to the block number of the block with the remote dialog variable. This results in a message for this dialog variable.
//		String StringParam: A static string63 dialog variable that is set to the dialog variable name of the remote block
//		String RowColumnParam: A two column integer static variable that stores the row and column of the remote dialog variable. This will be set to -1,-1 if the remote dialog variable is not a table.
//		String PopupText: The text that will appear in the popup menu for this block
//		integer OptionNumber: If this block has more than one popup menu option, this is a unique identifier for each option. For example the Scenario manager has two options, add factor and add response. These are OptionNumbers 1 and 2





#ifdef REGISTERLEFTCLICKBLOCK

Procedure RegisterBlockInLeftClickDB(String DialogParam, String StringParam, String RowColumnParam, String PopupText, integer OptionNumber)
{
	integer DBIndex;
	integer TableIndex;
	integer BlockNum_field;
	integer OptionNumber_field;
	integer PopupLabel_field;
	integer DialogVar_field;
	integer StringVar_field;
	integer RowColumnVar_field;
	integer NumRecords;
	integer me;
	integer MyRecord;
	integer InsertedRecord;
	
	me = MyBlockNumber();
	
	DBIndex = DBDatabaseGetIndex(LEFTCLICKDBNAME);
	if(DBIndex <= 0)
		DBIndex = DBDatabaseCreate(LEFTCLICKDBNAME);
	if(DBIndex <= 0)
		{
		return;
		}
	TableIndex = DBTableGetIndex(DBIndex, LEFTCLICKTABLENAME);
	if(TableIndex <= 0)
		TableIndex = DBTableCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME );
	if(TableIndex <= 0)
		return;
		
	// add block number field

	BlockNum_Field = DBFieldGetIndex(DBIndex, tableIndex, "Block Number");
	if(BlockNum_Field <= 0)
		BlockNum_Field = DBFieldCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME, "Block Number", DB_FIELDTYPE_INTEGER_VALUE, 0, FALSE, FALSE, FALSE);

	// add option number field
		
	OptionNumber_field = DBFieldGetIndex(DBIndex, tableIndex, "Option Number");
	if(OptionNumber_field <= 0)
		OptionNumber_field = DBFieldCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME, "Option Number", DB_FIELDTYPE_INTEGER_VALUE, 0, FALSE, FALSE, FALSE);

		
	// add popup label field
		
	PopupLabel_Field = DBFieldGetIndex(DBIndex, tableIndex, "Popup label");
	if(PopupLabel_Field <= 0)
		PopupLabel_Field = DBFieldCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME, "Popup label", DB_FIELDTYPE_STRING_VALUE, 0, FALSE, FALSE, FALSE);
		
	// add dialog dialog variable field	
	
	DialogVar_Field = DBFieldGetIndex(DBIndex, tableIndex, "Dialog variable");
	if(DialogVar_Field <= 0)
		DialogVar_Field = DBFieldCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME, "Dialog variable", DB_FIELDTYPE_STRING_VALUE, 0, FALSE, FALSE, FALSE);
		
	// add string variable field
		
	StringVar_Field = DBFieldGetIndex(DBIndex, tableIndex, "String variable");
	if(StringVar_Field <= 0)
		StringVar_Field = DBFieldCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME, "String variable", DB_FIELDTYPE_STRING_VALUE, 0, FALSE, FALSE, FALSE);
		
	// add row column variable field
		
	RowColumnVar_Field = DBFieldGetIndex(DBIndex, tableIndex, "Table row and column");
	if(RowColumnVar_Field <= 0)
		RowColumnVar_Field = DBFieldCreate(LEFTCLICKDBNAME,LEFTCLICKTABLENAME, "Table row and column", DB_FIELDTYPE_STRING_VALUE, 0, FALSE, FALSE, FALSE);
		
		
	NumRecords = DBRecordsGetNum(DBIndex, tableIndex);
	if(NumRecords > 0)
		{
//		MyRecord = DBRecordFind(DBIndex, tableIndex, BlockNum_Field, 1, TRUE, me);
		MyRecord = DBRecordFindMultipleFields(DBIndex, tableIndex, 1, BlockNum_field, me, FALSE, OptionNumber_field, OptionNumber, FALSE, 0, 0, 0);
		}
	else
		{
		MyRecord = -1;
		}
	if(MyRecord < 0)	
		{
		InsertedRecord = DBRecordsInsert(DBIndex, tableIndex, 1, 1);
		if(InsertedRecord < 0)
			{
			Usererror("Unable to add "+BlockName(me)+" to left click database");
			return;
			}
//		MyRecord = DBRecordFindMultipleFields(DBIndex, tableIndex, 1, BlockNum_field, me, FALSE, OptionNumber_field, OptionNumber, FALSE, 0, 0, 0);
		MyRecord = 1;
		}
	NumRecords ++;
	DBDataSetAsNumberReserved(DBIndex, tableIndex, BlockNum_Field, MyRecord, me);
	DBDataSetAsNumberReserved(DBIndex, tableIndex, OptionNumber_Field, MyRecord, OptionNumber);
	DBDataSetAsStringReserved(DBIndex, tableIndex, PopupLabel_Field, MyRecord, PopupText);
	DBDataSetAsStringReserved(DBIndex, tableIndex, DialogVar_Field, MyRecord, DialogParam);
	DBDataSetAsStringReserved(DBIndex, tableIndex, StringVar_Field, MyRecord, StringParam);
	DBDataSetAsStringReserved(DBIndex, tableIndex, RowColumnVar_Field, MyRecord, RowColumnParam);
	
	DBTableSort(DBIndex, tableIndex, PopupLabel_Field, TRUE, 0, TRUE, 0, TRUE);
	
}



Procedure UnRegisterBlockInLeftClickDB()
{
integer MyRecord;
integer me;
integer BlockNum_Field;
integer DBIndex;
integer TableIndex;

	me = MyBlockNumber();

	DBIndex = DBDatabaseGetIndex(LEFTCLICKDBNAME);
	if(DBIndex <= 0)
		return;
	TableIndex = DBTableGetIndex(DBIndex, LEFTCLICKTABLENAME);
	if(TableIndex <= 0)
		Return;

	BlockNum_Field = DBFieldGetIndex(DBIndex, tableIndex, "Block Number");
	if(BlockNum_Field < 0)
		Return;
	MyRecord = DBRecordFind(DBIndex, tableIndex, BlockNum_Field, 1, TRUE, me);
	while(MyRecord > 0)
		{
		DBRecordsDelete(DBIndex, tableIndex, MyRecord, MyRecord);
		MyRecord = DBRecordFind(DBIndex, tableIndex, BlockNum_Field, 1, TRUE, me);
		}
}

#endif
