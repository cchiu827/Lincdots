
******************************************************************
**	Equation Constants & Prototypes v7.h Include				**
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




//************************************************
//Start Equation.h Constants and Prototypes
//************************************************


//ResizeTableArrays() calledFrom constants
constant RESIZE_ADD_SUBTRACT_FROM_END is 1;
constant RESIZE_COPY is 2;
constant RESIZE_DELETE_SELECTION is 3;
constant CMC_INITIALIZE is 4;

//constants for the "calledFrom" argument of iVarsIn_GetNewConInfo(), iVarsIn_Reconnect(), oVarsOut_GetNewConInfo() and oVarsOut_Reconnect()
constant DIALOG_CLICK_VAR_TYPE is 1;
constant DATA_TABLE_RESIZE is 2;

//block type constants
constant EQUATION_BLOCK is 1;
constant EQUATION_ITEM_BLOCK is 2;
constant EQUATION_QUEUE_BLOCK is 3;
constant EQUATION_QUERY_BLOCK_VALUE is 4;
constant EQUATION_QUERY_BLOCK_ITEM is 5;

//Eq_DBAddressLocationExists() constants			//8/17/10
constant DB_ADDRESS_TYPE_DATABASE is 1;
constant DB_ADDRESS_TYPE_TABLE is 2; 
constant DB_ADDRESS_TYPE_FIELD is 3;
constant DB_ADDRESS_TYPE_RECORD is 4;

//Incl_FileNames_ttbl column constants
constant INCL_TABLE_NUM_COLS is 3;
constant INCL_OPEN_BTN_COL is 0;
constant INCL_SELECT_COL is 1;
constant INCL_NAME_COL is 2;

//resize arrays called from constants
constant RESIZE_CALLED_FROM_IVARS is 1;
constant RESIZE_CALLED_FROM_OVARS is 2;

//iVarsIn CMC(Connector Message Control) constants
constant CMC_IVAR_MSG_EMULATION is 1;
constant CMC_IVAR_ALWAYS is 2;
constant CMC_IVAR_NEVER is 3;

//oVarsOut CMC(Connector Message Control) constants
constant CMC_OVAR_MSG_EMULATION is 1;
constant CMC_OVAR_VAL_CHANGE_ONLY is 2;
constant CMC_OVAR_ALWAYS is 3;
constant CMC_OVAR_NEVER is 4;

//messaging called from constants
constant MSG_RECEIVED_FROM_BR0 is 1;
constant MSG_RECEIVED_FROM_BR1 is 2;
constant MSG_RECEIVED_FROM_LINK_CONTENT is 3;
constant MSG_RECEIVED_FROM_IVARS_IN is 4;
constant MSG_RECEIVED_FROM_OVARS_OUT is 5;
constant MSG_RECEIVED_FROM_GO_IN is 6;
constant MSG_RECEIVED_FROM_POST_INITSIM is 7;
constant MSG_RECEIVED_FROM_ABORTSIM is 8;
constant MSG_RECEIVED_FROM_FINAL_CALC is 9;

//iVar column constants
constant I_VAR_TABLE_NUM_COLS is 5;
constant I_VAR_TYPE_COL is 0;
constant I_VAR_NAME_COL is 1;
constant I_VAR_VALUE_COL is 2;
constant I_VAR_UNIT_COL is 4; // Carollo, 05/26/2015
constant I_VAR_PARENT_FIELD_COL is 3;

//oVar column constants
constant O_VAR_TABLE_NUM_COLS is 4;
constant O_VAR_TYPE_COL is 0;
constant O_VAR_NAME_COL is 1;
constant O_VAR_VALUE_COL is 2;
constant O_VAR_UNIT_COL is 3; // Carollo, 05/26/2015
constant O_VAR_NO_ITEM_COL is 3;
constant O_VAR_UNUSED_COL is 4;

//no item options constants
constant O_VAR_USE_NO_VALUE is 1;
constant O_VAR_USE_LAST_VALUE is 2;
constant O_VAR_USE_CONSTANT is 3;

constant I_VARIABLES is 1;
constant O_VARIABLES is 2; 

//options constants for attribPopOptions 
constant ATTRIB_OPTIONS_1 is 1;
constant ATTRIB_OPTIONS_2 is 2;

//calc procedure constants
constant O_VARS_OUT is -100;
constant TEST_EQUATION_BTN is -200;
constant PASS_ITEM is -300;
constant SEND_ITEM is -400;

//Infinite equation constants
constant EQUATION_TAB_ORDER is 1;			//specifies "equation_DTxt's" tab order in the dialog.  Is used as an ID in EquationCompileDynamic().

//IVCM and LAM "when to calculate" constants
constant WHEN_CALC_IMMEDIATE is 1;
constant WHEN_CALC_CURRENT_EVENT is 2;

//constants for calcBeforeStart_pop
constant CALC_BEFORE_START_CHECKDATA is 1;
constant CALC_BEFORE_START_STEP_SIZE is 2;
constant CALC_BEFORE_START_INITSIM is 3;
constant CALC_BEFORE_START_POSTINITSIM is 4;

//constants for calcAtEnd_pop
constant CALC_AT_END_FINAL_CALC is 1;
constant CALC_AT_END_END_SIM is 2;
constant CALC_AT_END_ABORTSIM is 3;

//constants for the "iVars_DBNameTrackingListIndex" and "oVars_DBNameTrackingListIndex" linked lists
//"DBNT"- DataBase Name Tracking
constant DBNT_WHICH_ROW_IN_TABLE_FIELD is 0;
constant DBNT_DB_NAME_FIELD is 0;
constant DBNT_TABLE_NAME_FIELD is 1;
constant DBNT_FIELD_NAME_FIELD is 2;
constant DBNT_RECORD_NAME_FIELD is 3;
constant DBNT_IVARS_LIST_NAME is "iVars_DBNameTrackingList";
constant DBNT_OVARS_LIST_NAME is "oVars_DBNameTrackingList";

//iVar and oVar variable types.
constant EQ_NUM_VAR_TYPES is 59;
constant EQ_NO_VAR_TYPE is -1;
constant EQ_ITEM_ATTRIBUTE is 0;
constant EQ_ITEM_QTY is 1;
constant EQ_ITEM_PRIORITY is 2;
constant EQ_ITEM_AR_ORDER_ID is 3;
constant EQ_ITEM_INDEX is 4;
constant EQ_ITEM_BATCH_SIZE is 5;
constant EQ_ITEM_3D_ID is 6;
constant EQ_CONNECTORS is 7;
constant EQ_STATIC_FRI is 8;
constant EQ_STATIC_MRI is 9;
constant EQ_STATIC_OPEN_MODEL is 10;
constant EQ_CALC_NEXT_EVENT is 11;
constant EQ_NEXT_CALC_EVENT_TIME is 12;					//4/16/11
constant EQ_DB_READ_VAL is 13;
constant EQ_DB_READ_PRI is 14;constant EQ_DB_READ_VAL_USING_ATTRIB is 15;
constant EQ_DB_READ_PRI_USING_ATTRIB is 16;
constant EQ_DB_WRITE_VAL is 17;
constant EQ_DB_WRITE_PRI is 18;
constant EQ_DB_WRITE_VAL_USING_ATTRIB is 19;
constant EQ_DB_WRITE_PRI_USING_ATTRIB is 20;
constant EQ_DB_ADDRESS is 21;
constant EQ_DB_DATABASE_INDEX is 22;
constant EQ_DB_TABLE_INDEX is 23;
constant EQ_DB_FIELD_INDEX is 24;
constant EQ_DB_RECORD_INDEX is 25;
constant EQ_QEQ_ITEM_ARRIVAL_TIME is 26;
constant EQ_QEQ_FIFO_POSTION is 27;
constant EQ_QEQ_ITEM_RANK is 28;
constant EQ_QEQ_CURR_BEST_RANK_RESULT is 29;
constant EQ_QEQ_LAST_ITEM_TO_EXIT is 30;
constant EQ_QEQ_NUM_ITEMS_IN_QUEUE is 31;
constant EQ_QEQ_STATIC_CALC_CYCLE_INIT is 32;
constant EQ_QEQ_STATIC_ITEM_VALUE is 33;					//11/17/10
constant EQ_QEQ_HALT_CALCULATION_CYCLE is 34;
constant EQ_QEQ_AR_REQUIREMENT_IS_AVAIL is 35;
constant EQ_QEQ_AR_NUM_REQUIREMENTS_AVAIL is 36;
constant EQ_QEQ_AR_ALLOCATE_REQUIREMENT is 37;
constant EQ_DBQ_QUERY_FIELD_VALUE is 38;
constant EQ_DBQ_QUERY_FIELD_PRI is 39;
constant EQ_DBQ_START_RECORD is 40;
constant EQ_DBQ_CURRENT_RECORD is 41;
constant EQ_DBQ_NUM_RECORDS is 42;constant EQ_DBQ_STATIC_QUERY_INIT is 43;constant EQ_DBQ_HALT_QUERY is 44;
constant EQ_DBQ_NEXT_RECORD is 45;
constant EQ_DBQ_RECORD_RANK is 46;
constant EQ_DBQ_CURR_BEST_RANK_RESULT is 47;				//PT- Pass Through
constant EQ_DBQ_NUM_NON_BLANK_RANKED_RECORDS is 48;			//PT- Pass Through
constant EQ_DBQS_RECORD_RANK is 49;constant EQ_DBQS_CURR_BEST_RANK_RESULT is 50;				//S- Spawn
constant EQ_DBQS_NUM_NON_BLANK_RANKED_RECORDS is 51;		//S- Spawn
constant EQ_DBQS_ATTRIB is 52;
constant EQ_DBQS_ITEM_QTY is 53;
constant EQ_DBQS_ITEM_PRIORITY is 54;
constant EQ_DBQS_3D_OBJECT_ID is 55;
constant EQ_INTEGER is 56; // Carollo, 05/26/2015
constant EQ_REAL is 57; // Carollo, 05/26/2015
constant EQ_STRING is 58; // Carollo, 05/26/2015




// system random seed settings
constant SEED_USEDEFAULT is 1;
constant SEED_CONTINUESEQUENCE is 2;
constant SEED_USEDB is 3;


//prototypes
//integer Eq_VarTypeGet(string typeName);
integer Eq_Compile(integer destroyRemoteBlock);
//procedure Eq_CheckForSpaces(integer doAbort);
//procedure Eq_CheckVariables();
//procedure Eq_CalcNoItem(integer whoCalled);
//procedure Eq_BlockRegisterContent();
//procedure Eq_BlockRegisterStructure();
//procedure Eq_BlockUnRegisterStructure();
//procedure Eq_DialogItemsShow();
//procedure Eq_DialogSetSize();
//procedure Eq_InitDataStructures();
//procedure Eq_OnBlockMove();
//integer Eq_DBAddressLocationExists(real dbAddress, integer addressType);			//8/17/10
//procedure EQ_DBIndexCheck();														//6/7/11


#ifdef Eq_IsValueBlock
//	real Eq_GetNextCalcEventTime();
//	procedure EQ_OnLinkContent();
//	procedure Eq_OnGoIn();
//	procedure Eq_OnBlockReceive0();
//	procedure Eq_OnBlockReceive1();
	procedure DialogItemsShow();
	//procedure IconSet(integer animationIVarsIn, integer animateOVarsOut);		//7/5/11
//	procedure IconSet(integer animateCons);										//7/5/11
#endif
/*
#ifdef CW_IVarsIn_CalcControl_chk
	procedure CW_IVarsIn_DialogItemsShow();
	procedure CW_IVarsIn_Animate();
	procedure CW_IVarsIn_GetWhichCon();
	procedure CW_IVarsIn_OnCreateBlock();
#endif

#ifdef CW_OVarsOut_CalcControl_chk
	procedure CW_OVarsOut_DialogItemsShow();
	procedure CW_OVarsOut_Animate();
	procedure CW_OVarsOut_OnCreateBlock();
	procedure CW_OVarsOut_GetWhichCon();
#endif

//7/5/11
#ifdef CW_IVarsIn_CalcControl_chk
	procedure CW_ConnectorAnimate();
#else
	#ifdef CW_OVarsOut_CalcControl_chk
		procedure CW_ConnectorAnimate();
	#endif
#endif

#ifdef CW_LAM_CalcControl_chk
	procedure CW_LAM_DialogItemsShow();
	procedure CW_LAM_OnCreateBlock();
	procedure CW_LAM_GetWhichDBReadVar();
#endif

//Eq_Calc
#ifdef Eq_IsQueryEquationItemBlock
	procedure Eq_Calc(integer itemIndex, integer recordIndex, integer sendIVarConMsgs, integer postResults, integer sendOVarConMsgs, integer preserveStatics);
#else
	#ifdef Eq_IsItemBlock
		procedure Eq_Calc(integer itemIndex, integer sendIVarConMsgs, integer postResults, integer sendOVarConMsgs, integer preserveStatics);
	#else
		#ifdef Eq_IsQueryEquationValueBlock
			procedure Eq_Calc(integer recordIndex, integer sendIVarConMsgs, integer sendOVarConMsgs);
		#else
			procedure Eq_Calc(integer sendIVarConMsgs, integer sendOVarConMsgs);
		#endif
	#endif
#endif


//iVars
//procedure iVars_OnDialogClickAttribName(integer whichOptions);
procedure iVars_TableSetup();
procedure iVars_GetVarIsWhichConOld();
procedure iVars_ShowTypesPopup();
procedure iVars_ResizeDynamicArrays(integer doWhat);
integer iVars_CheckChosenField(integer whichVar, real theCoords);
procedure iVars_GetVarTypes();
procedure iVars_CopyRow();
procedure iVars_DeleteRows();
/*
//iVars_DBNT
procedure iVars_DBNT_GarbageCollection();
procedure iVars_DBNT_BuildList();
procedure iVars_DBNT_UpdateDBCoordsArray();procedure iVars_DBNT_AddElement(real dbAddress, integer whichRow);
procedure iVars_DBNT_DeleteElement(integer whichRow);	//6/15/11


#ifdef Eq_IsItemBlock
	procedure iVars_GetVals(integer itemIndex, integer sendMsgs);
#else
	procedure iVars_GetVals(integer sendMsgs);
#endif
procedure iVarsIn_ConnectorsSetup();
procedure iVarsIn_Reconnect(integer calledFrom);
procedure iVarsIn_ConLabelsSet();
procedure iVarsIn_VarIsWhichConUpdate();
procedure iVarsIn_ConIsWhichVarUpdate();
procedure iVarsIn_CheckConInputs();
#ifdef Eq_IsValueBlock
//	procedure iVarsIn_SendMsgs(integer calledFrom);
//	procedure iVarsIn_OnIVarsIn();
#endif

//oVars
procedure oVars_ResizeDynamicArrays(integer calledFrom, integer doWhat);
//procedure oVars_OnDialogClickAttribName(integer whichOptions);
//procedure oVars_ShowNoItemOptionsPopup();
procedure oVars_TableSetup();
procedure oVarsOut_ConLabelsSet();
procedure oVars_GetVarIsWhichConOld();
procedure oVars_ShowTypesPopup();
integer oVars_CheckChosenField(integer whichVar, real theCoords);
procedure oVars_GetVarTypes();
procedure oVars_InitVals();
procedure oVars_CopyRow(integer calledFrom);
procedure oVars_DeleteRows(integer calledFrom);
/*
//oVars_DBNT
procedure oVars_DBNT_AddElement(real dbAddress, integer whatRowInTable);
procedure oVars_DBNT_GarbageCollection();
procedure oVars_DBNT_BuildList();
procedure oVars_DBNT_UpdateDBCoordsArray();procedure oVars_DBNT_DeleteElement(integer whichRowInTable);	//6/15/11

#ifdef Eq_IsItemBlock
	procedure oVars_PostResults(integer itemIndex, integer sendMsgs);
#else
	procedure oVars_PostResults(integer sendMsgs);
#endif

procedure oVarsOut_ConnectorsSetup();
procedure oVarsOut_Reconnect(integer calledFrom);procedure oVarsOut_VarIsWhichConUpdate();procedure oVarsOut_ConIsWhichVarUpdate();
procedure oVarsOut_CheckConOutputs();
#ifdef Eq_IsValueBlock
//	procedure oVarsOut_SendMsgs(integer calledFrom);
//	procedure oVarsOut_OnOVarsOut();
#endif
*/
//include file prototypes
//procedure Incl_TableSetup();
//procedure Incl_TableResize(integer numRows);
//procedure Incl_Hover();
//procedure Incl_BuildPrototypesArray();


//equation editor prototypes
procedure EQE_CreateEditorFile();
procedure EQE_DeleteEditorFile();
procedure EQE_CloseEditor();


//CMC (Connector Message Control) prototypes
#ifdef CMC_chk
//procedure CMC_IVars_ResizeArrays(integer doWhat);
//procedure CMC_IVarsIn_Set();
//procedure CMC_ConnectorAnimate();
//procedure CMC_IVarsIn_Animate();
//procedure CMC_OVars_ResizeArrays(integer doWhat);//procedure CMC_OVarsOut_Set();
//procedure CMC_OVarsOut_Animate();
//procedure CMC_OVarsOut_GetConChanged();
#endif



//Procedure InitSeeds();					// initializes seed values for random number generator
//Procedure EQ_CheckSeeds();					// initializes seed values for random number generator


//************************************************
//End Equation.h Constants and Prototypes
//************************************************



//************************************************
//Start Query Equation.h Constants and Prototypes
//************************************************

#ifdef Eq_IsQueryEquationTypeBlock

	//constants for the iVars_SetParentFieldColTagArray() function
	constant DBQ_READ_VAL_FIELD is 1;
	constant DBQ_READ_VAL_INDIRECT_PARENT_FIELD is 2;
	
	//calledFrom constants for DBQ_GetAllChosenAddressIndexes
	constant CALLED_FROM_CHECK_DATA is 1;
	constant CALLED_FROM_DBQ_DO_QUERY is 2;
	constant CALLED_FROM_IVARS_TABLE_SETUP is 3;
	
	//DBQ_AttribNamesChosen[] and DBQ_AttribType[] arrays constants
	constant DBQ_DATABASE_ATTRIB is 0;
	constant DBQ_TABLE_ATTRIB is 1;
	constant DBQPT_BEST_RANK_AS_ATTRIB is 2;
	
	//DBQ constants for a number of different query arrays
	constant DBQ_NOT_DEFINED is 0;
	constant DBQ_USE_LIST is 1;
	constant DBQ_USE_CONSTANT is 2;
	constant DBQ_USE_ATTRIBUTE is 3;
	constant DBQ_USE_CONNECTOR is 4;
	
	//DBQ_CoordsIn constants
	constant DBQ_COORDS_IN_MAX_NUM_CONS is 2;
	constant DBQ_COORDS_IN_TABLE is 0;			//the table connector is in the 0th position
	constant DBQ_COORDS_IN_DATABASE is 1;		//the db connector is in the 1st position
	
	//constants for DBQ_AttribNamesChosen[]
	constant DBQ_DB_ATRRIB is 0;
	constant DBQ_TABLE_ATRRIB is 1;
	
	//DBQPT_RecordRankRule_pop constants
	constant DBQPT_RECORD_RANK_RULE_USE_HIGHEST is 1;
	constant DBQPT_RECORD_RANK_RULE_USE_LOWEST is 2;
	constant DBQPT_RECORD_RANK_RULE_USE_FIRST_TRUE is 3;
		//DBQS_RecordRankRule_pop constants
	constant DBQS_RECORD_RANK_RULE_USE_HIGHEST is 1;
	constant DBQS_RECORD_RANK_RULE_USE_LOWEST is 2;
	constant DBQS_RECORD_RANK_RULE_USE_FIRST_TRUE is 3;
	constant DBQS_RECORD_RANK_RULE_USE_ALL is 4;
	
	//DBQS_PassThruOptions_pop constants
	constant DBQS_PASS_THRU_ALWAYS is 1;
	constant DBQS_PASS_THRU_NEVER is 2;
	constant DBQS_PASS_THRU_IF_NO_SPAWNS is 3;
	constant DBQS_PASS_THRU_IF_ANY_SPAWNS is 4;
	
	//spawn attrib constants
	constant DBQS_NUM_SPAWNS_AS_ATTRIB is 0;
	constant DBQS_SPAWN_IS_WHICH_RECORD_INDEX_ATTRIB is 1;
	
	//prototypes
	procedure DBQ_DialogItemsUpdate();
	procedure DBQ_CallDIPopupButton();
	procedure DBQ_VariablesReset();
	procedure DBQ_ConnectorSetup();
	procedure DBQ_OnCheckData();
	procedure DBQ_OnInitSim();
	procedure DBQ_OnOpenModel();
	
	procedure DBQ_GetAllChosenAddressIndexes(integer itemIndex, integer calledFrom);
	integer DBQ_DatabaseGetChosenIndex(integer itemIndex);
	integer DBQ_TableGetChosenIndex(integer dbqDatabaseIndex, integer itemIndex);

	integer DBQF_FieldGetChosenIndex(integer dbqDatabaseIndex, integer dbqTableIndex, integer row, integer itemIndex);
	procedure DBQF_OnDialogClickQueryField(integer row);
		
	integer DBQFP_TableGetChosenIndex(integer dbqDatabaseIndex, integer dbqTableIndex, integer dbqfFieldIndex, integer row, integer itemIndex);
	integer DBQFP_FieldGetChosenIndex(integer dbqDatabaseIndex, integer dbqfpTableIndex, integer row, integer itemIndex);
	procedure DBQFP_OnDialogClickQueryField(integer row);
		
	integer DBQSR_RecordGetChosenIndex(integer dbqDatabaseIndex, integer dbqTableIndex, integer row, integer itemIndex);
	procedure DBQSR_OnDialogClickStartRecord(integer row);
		
	#ifdef Eq_IsQueryEquationItemBlock
		integer DBQ_DoQuery(integer itemIndex, integer sendIVarConMsgs, integer postResults, integer sendOVarConMsgs, integer retainStatics);

		procedure DBQF_AttribShowPopup(integer whichRow);
		procedure DBQFP_AttribShowPopup(integer whichRow);
		
		procedure DBQS_DialogItemsShow();
		procedure DBQS_CreateSpawnedItem(integer passThroughItemIndex, integer spawnWhichRecord, real equationResults[]);
	#else
		integer DBQ_DoQuery(integer sendIVarConMsgs, integer sendOVarConMsgs);
	#endif
	

#endif //Eq_IsQueryEquationTypeBlock

//************************************************
//End QUERY Equation.h Constants and Prototypes
//************************************************






