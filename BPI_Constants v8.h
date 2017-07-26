******************************************************************
**	Constants v7.h Include										**
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
// 1/2/08 	7.0.1		DJK			Moved constants in from BTB Animation v7.h
// 8/4/09	8.0.0		PHT			Added set of constants for the 5 different block types as returned from getBlockTypePosition()
// 8/4/09	8.0.0		PHT			Added Extend version "which" argument values
// 8/6/09	8.0.0		PHT			Added index constants for position array returned by GetBlockTypePosition
// 8/7/09	8.0.0		PHT			Added remaining constants for run parameters
// 8/18/09	8.0.0		PHT			Added "which" field property types for database function call
// 9/4/09	8.0.0		PHT			Added "which" argument values for DialogGetSize
// 11/13/09	8.0.0		PHT			Added constant for offset pixels for invisible dialog variables
// 2/11/10	8.0.0		PHT			Added block dialog formatting constants
// 2/11/10	8.0.0		PHT			Added itemArrayI2 column constants
// 2/15/10	8.0.0		PHT			Added shifts global array column constants
// 2/24/10	8.0.0		PHT			Added resource pool global array column constants
// 7/28/10	8.0.1		PHT			Added constants for values returned from GetExtendType function
// 12/23/10	8.0.2		PHT			Added constants for popup menu options
//	3/2/11	8.0.2		PHT			Added new section and constants for font IDs


//general constants
constant cMAX_CONNECTORS	is 256;		// Maximum connectors per block
Constant cDISTANCE_BETWEEN_CONN	is 13;	//Distance in pixel between variable connectors

//"on AttribInfo" message handler constants
#ifdef IC_AttribNamesChosen
	constant ATTRIB_NAMES_ARRAY_IC is "IC_AttribNamesChosen";
		//NOTE:  this declaration has to be here in Constants.h and not in "Item Contents.h" AND
		//		 the statement "#define constants.h" must be the first "# define" in the block.
		//		 why?  to ensure that ATTRIB_NAMES_ARRAY_IC has been defined before "procedure 
		//		 OnAttribInfo()" gets comiled.
#endif

//constants for attribPopOptions[]
constant NUM_ATTRIB_POP_OPTIONS is 10;
constant INCLUDE_ITEM_INDEX is 0;
constant INCLUDE_ITEM_VALUE is 1;
constant INCLUDE_ITEM_PRIORITY is 2;
constant INCLUDE_AR_ORDER_ID is 3;			//2/9/10
constant INCLUDE_BATCH_SIZE is 4;
constant INCLUDE_VALUE_ATTRIBS is 5;
constant INCLUDE_STRING_ATTRIBS is 6;
constant INCLUDE_DB_ATTRIBS is 7;
constant INCLUDE_DB_ATTACHED_ATTRIBS is 8;	//2/7/10
constant INCLUDE_3D_OBJECT_ID is 9;

//simulation phase constants
constant PHASE_NOT_CURRENTLY_RUNNING is 0;
constant PHASE_PRECHECKDATA is 9;
constant PHASE_CHECKDATA is 1;
constant PHASE_STEPSIZE is 2;
constant PHASE_INITSIM is 3;
constant PHASE_POST_INITSIM is 10;
constant PHASE_SIMULATE is 4;
constant PHASE_FINALCALC is 5;
constant PHASE_BLOCKREPORT is 6;
constant PHASE_ENDSIM is 7;
constant PHASE_ABORTSIM is 8;
constant PHASE_OPEN_MODEL is 14;

// run parameter constants

constant RUNPARAM_ENDTIME is 1;
constant RUNPARAM_STARTTIME is 2;
constant RUNPARAM_NUMSIMS is 3;
constant RUNPARAM_NUMSTEPS is 4;
constant RUNPARAM_RANDOMSEED is 5;
constant RUNPARAM_WKSEEDCONTROL is 6;
constant RUNPARAM_CHECKRANDOMSEEDS is 7;
constant RUNPARAM_TIMEUNITS is 8;
constant RUNPARAM_CALENDARDATES is 9;
constant RUNPARAM_STARTDATE is 10;

// menu commands

constant	MENUCOMMAND_OPENMODEL is 3;
constant	MENUCOMMAND_CLOSEMODEL is 4;
constant	MENUCOMMAND_SAVEMODEL is 5;


//costing constants
constant COST_ACCUM_ITEM is 1;
constant RESOURCE_ITEM is 2;
constant ITEM_COST_TYPE is 0;
constant RES_COST_RATE_1_COL_INDEX is 1;	//itemArrayC column index for Resource Rate 1- the cost per time unit of resource type 1 batched to cost accumulating item.
constant BATCH_NUM_1_COL_INDEX is 2;		//itemArrayC column index for Batch Number 1- the amount of resource 1 batched to the cost accumulating item.
constant RES_COST_RATE_2_COL_INDEX is 3;	//itemArrayC column index for Resource Rate 2- the cost per time unit of resource type 2 batched to cost accumulating item.
constant BATCH_NUM_2_COL_INDEX is 4;		//itemArrayC column index for Batch Number 2- the amount of resource 2 batched to the cost accumulating item.
constant RES_POOL_RATE_COL_INDEX is 5;		//itemArrayC column index for Resource Pool Rate- the accumulated cost per time unit of resources batched to the cost accumulating item using the Queue, Resource Pool block.
constant AGV_RATE_COL_INDEX is 6;			//itemArrayC column index for AGV Rate- the cost per time unit of any AGV's batched with the cost accumulating it.
constant ORIGINAL_COST_COL_INDEX is 7;		//itemArrayC column index for Original Cost- used in calculating cost when unbatching items using the Unbatch, Variable block.
constant resRate1 is 1;
constant batchNum1 is 2;
constant resRate2 is 3;
constant batchNum2 is 4;
constant rPoolRate is 5;
constant AGVRate is 6;
constant originalCost is 7;
constant type is 0;
**	3/11/11		8.0.2		PHT		Moved to ItemArrayConstants v8.h
//itemArrayI2 column constants
//constant	IAI2_RESOURCE_ORDER_ID_COL_INDEX is 0;	// itemArrayI2 column index for the resource order ID - used by advanced resources feature



//attribute type identifiers
constant ATTRIB_TYPE_NOT_NEW is -2;
constant ATTRIB_TYPE_NO_ATTRIB is -1;
constant ATTRIB_TYPE_VALUE is 1;
constant ATTRIB_TYPE_STRING is 2;
constant ATTRIB_TYPE_DB is 3;
constant ATTRIB_TYPE_DB_ATTACHED is 4;		//2/7/10

//item property identifiers.  NOTE! these constants MUST be negative since they are used in Attrib_GetColumnIndex(string whichAttrib) 
//which returns the column index in the _attributeList GA that is associated with "whichAttrib".  therefore, if Attrib_GetColumnIndex()
//gets called with an item property type other than attribute, the function must use the constants below to return a number that is 
//outside the bounds of the GA.
constant PROPERTY_TYPE_NO_PROPERTY is -1;
constant PROPERTY_TYPE_ITEM_ATTRIBUTE is -2;
constant PROPERTY_TYPE_ITEM_QUANTITY is -3;
constant PROPERTY_TYPE_ITEM_PRIORITY is -4;
constant PROPERTY_TYPE_AR_ORDER_ID is -5;			//2/9/10
constant PROPERTY_TYPE_ITEM_INDEX is -6;
constant PROPERTY_TYPE_ITEM_BATCH_SIZE is -7;
constant PROPERTY_TYPE_ITEM_3D_OBJECT_ID is -8;

/*
//var type constants.  used in many places to ID a variable
//NOTE 1: non-attrib properties must be negative because positive ID's are reserved for the column index into the _attribValues GA
//NOTE 2: these constants are used in both attribs v7.h and equation v7.h
constant VAR_TYPE_NUM_VAR_TYPES is 47;
constant VAR_TYPE_NO_VAR_TYPE is -1;
constant VAR_TYPE_ITEM_ATTRIBUTE is 1;		//used in equation not for the column ID of an attrib but to ID the var type as an attribute 
constant VAR_TYPE_ITEM_QUANTITY is 2;
constant VAR_TYPE_ITEM_PRIORITY is 3;
constant VAR_TYPE_ITEM_INDEX is 4;
constant VAR_TYPE_ITEM_BATCH_SIZE is 5;
constant VAR_TYPE_ITEM_3D_OBJECT_ID is 6;
constant VAR_TYPE_CONNECTOR is 7;
constant VAR_TYPE_STATIC_VARIABLE is 8;
constant VAR_TYPE_STATIC_VARIABLE_MRI is 9;
constant VAR_TYPE_CALC_NEXT_EVENT is 10;
constant VAR_TYPE_DB_READ_VAL is 11;
constant VAR_TYPE_DB_READ_PRI is 12;
constant VAR_TYPE_DB_READ_VAL_USING_ATTRIB is 13;
constant VAR_TYPE_DB_READ_PRI_USING_ATTRIB is 14;
constant VAR_TYPE_DB_WRITE_VAL is 15;
constant VAR_TYPE_DB_WRITE_PRI is 16;
constant VAR_TYPE_DB_WRITE_VAL_USING_ATTRIB is 17;
constant VAR_TYPE_DB_WRITE_PRI_USING_ATTRIB is 18;
constant VAR_TYPE_DB_ADDRESS is 19;
constant VAR_TYPE_DB_INDEX is 20;
constant VAR_TYPE_QEQ_LAST_ITEM_TO_EXIT is 21;
constant VAR_TYPE_QEQ_FIFO_POSITION is 22;
constant VAR_TYPE_QEQ_ITEM_RANK is 23;
constant VAR_TYPE_QEQ_ARRIVAL_TIME is 24;
constant VAR_TYPE_QEQ_CURR_BEST_RANK_RESULT is 25;
constant VAR_TYPE_QEQ_NUM_ITEMS_IN_QUEUE is 26;
constant VAR_TYPE_QEQ_STATIC_CALC_CYCLE_INIT is 27;
constant VAR_TYPE_QEQ_HALT_CALCULATION_CYCLE is 28;
constant VAR_TYPE_DBQ_QUERY_FIELD_VALUE is 29;
constant VAR_TYPE_DBQ_QUERY_FIELD_PRI is 30;
constant VAR_TYPE_DBQ_START_RECORD is 31;
constant VAR_TYPE_DBQ_CURRENT_RECORD is 32;
constant VAR_TYPE_DBQ_NUM_RECORDS is 33;
constant VAR_TYPE_DBQ_STATIC_QUERY_INIT is 34;
constant VAR_TYPE_DBQ_HALT_QUERY is 35;
constant VAR_TYPE_DBQ_NEXT_RECORD is 36;
constant VAR_TYPE_DBQ_RECORD_RANK is 37;
constant VAR_TYPE_DBQPT_NUM_NON_BLANK_RANKED_RECORDS is 38;
constant VAR_TYPE_DBQPT_CURR_BEST_RANK_RESULT is 39;
constant VAR_TYPE_DBQPT_RECORD_RANK is 40;
constant VAR_TYPE_DBQS_CURR_BEST_RANK_RESULT is 41;
constant VAR_TYPE_DBQS_NUM_NON_BLANK_RANKED_RECORDS is 42;
constant VAR_TYPE_DBQS_RECORD_RANK is 43;
constant VAR_TYPE_DBQS_ATTRIB is 44;
constant VAR_TYPE_DBQS_ITEM_QTY is 45;
constant VAR_TYPE_DBQS_ITEM_PRIORITY is 46;
constant VAR_TYPE_DBQS_3D_OBJECT_ID is 47;
*/


//connector constants
Constant cCONNECTOR_TYPE_FLOW	is 25;	// type for "flow" connector return by the function "GetConnectedType"


//connector label positions
constant TOP_SIDE is 0;
constant RIGHT_SIDE is 1;
constant BOTTOM_SIDE is 2;
constant LEFT_SIDE is 3;


// Constants for dialog item type
//1 = Button, 2 = Check Box, 3 = Radio Button, 4 = Meter,
//5 = Parameter, 6 = Slider, 7 = Data Table, 8 = Editable Text, 9 = Static Text, 12 = Switch, 13 = Text Table, 16 = Popup Menu, 17 = Embedded object. 

//constants for dialog item types
constant DI_BUTTON is 1;
constant DI_CHECK_BOX is 2;
constant DI_RADIO_BUTTON is 3;
constant DI_METER is 4;
constant DI_PARAMETER is 5;
constant DI_SLIDER is 6;
constant DI_DATA_TABLE is 7;
constant DI_EDITABLE_TEXT is 8;
constant DI_STATIC_TEXT is 9;
constant DI_SWITCH is 12;
constant DI_TEXT_TABLE is 13;
constant DI_POPUP_MENU is 16;
constant DI_EMBEDDED_OBJECT is 17;
constant DI_DYNAMIC_TEXT is 18;
constant DI_TEXT_FRAME is 19;
constant DI_CALENDAR is 20;
constant DI_TEXT_31 is 21;


// Constants for GetDialogItemInfo

//1: hidden, 2: enabled, 3: display only. Returns the values for: 4: dialog
//item type, 5: rows, 6: columns, 7: width, 8: height.

constant DI_HIDDEN is 1;
constant DI_ENABLED is 2;
constant DI_DISPLAYONLY is 3;
constant DI_DITYPE is 4;
constant DI_ROWS is 5;
constant DI_COLUMNS is 6;
constant DI_WIDTH is 7;
constant DI_HEIGHT is 8;

// Constants for WhichDTCell
// 1 Column: 0 Row

constant DTWHICH_ROW is 0;
constant DTWHICH_COLUMN is 1;



constant XLOCATION is 0;
constant YLOCATION is 1;
constant ZLOCATION is 2;


//Constants for the time units
constant TU_GENERIC is 1;
constant TU_MILLISECONDS is 2;
constant TU_SECONDS is 3;
constant TU_MINUTES is 4;
constant TU_HOURS is 5;
constant TU_DAYS is 6;
constant TU_WEEKS is 7;
constant TU_MONTHS is 8;
constant TU_YEARS is 9;

//btb animation constants
constant ANIM_ATTRIB_COL is 0;		
constant GREEN_CIRCLE  is 1;
constant ATTRIB_VALS_COL is 0;
constant WHICH_PICTS_COL is 1;
constant WHICH_3DPICTS_COL is 2;
constant WHICH_3DSKIN1_COL is 3;
constant WHICH_3DSKIN2_COL is 4;
constant ATTRIB_TABLE_NUM_COLS is 2;
constant ATTRIB_ANIMATION is 0;
constant NUM_BTB_ATTRIBS is 1;
constant USER_PICTS is 2;					//when PictureList() is called the second parameter specifies 
constant OPTIONS_TABLE_NUM_COLS is 2;

//BTB_MultiOutOptions_ttbl column constants
constant MULTI_OUT_OPTIONS_COL is 0;
constant MULTI_OUT_PICTS_COL is 1;
constant MULTI_OUT_3DOBJECT_COL is 2;
constant MULTI_OUT_SKIN1_COL is 3;
constant MULTI_OUT_SKIN2_COL is 4;

//btb multiOut options constants
constant NUM_MULTI_OUT_OPTIONS is 2;
constant MULTI_OUT_NO_CHANGE is 1;
constant MULTI_OUT_CHANGE_TO is 2;

//BTB_AnimOptions_pop
constant ANIM_OPTIONS_POP_NO_CHANGE is 1;
constant ANIM_OPTIONS_POP_CHANGE_TO is 2;
constant ANIM_OPTIONS_POP_USE_CONVERSION_TABLE is 3;

constant CREATEWAYPOINT is 1;
constant CREATEOBJECT is 2;
constant CREATENONE is 3;

//E3D constants
constant E3DQUICKVIEWMODE is	0;
constant E3DCONCURRENTMODE is	1;
constant E3DBUFFEREDMODE is		2;
constant BLOCKMOVED is 			1;
constant E3DMOVED is 			2;

constant SKIN1CREATE_NAME is 1;
constant SKIN1CREATE_BASE is 2;
constant SKIN2CREATE_NAME is 3;
constant SKIN2CREATE_BASE is 4;

Constant B3DEDITOR is 0;
Constant B3DITEM is 1;
Constant B3DBLOCK is 2;
Constant B3DSCENERY is 3;
Constant B3DPATH is 4;

#ifndef ANIMATELEVEL			// animateLevel is a dialog variable in the Animate Value Block
Constant ANIMATELEVEL is 1;
Constant ANIMATEINPUTRATE is 2;
Constant ANIMATEOUTPUTRATE is 3;
Constant ANIMATEPROGRESS is 4;
#endif

//constant for animation attrib array name
constant ATTRIB_ARRAY_NAME_BTB is "BTB_AttribNamesChosen";

// 1/2/08 	7.0.1		DJK			Moved constants in from BTB Animation v7.h

constant RANDOMPERSON is -2;

// for 3d quick view animation this is where the scale and rotation information is stored.


constant QV_OBJECTID is 0;
constant QV_SKIN_1_ID is 1;
constant QV_SKIN_2_ID is 2;
constant QV_OBJECTSCALE is 3;
constant QV_OBJECTROTATION is 4;
constant QV_OBJECTZ is 5;
constant QV_OBJECTTYPE is 6;
constant QV_OBJECT_TEMPORARY_Z is 7;
constant QV_RESTORE_Z_AT_BLOCK is 8;
constant QV_SCALEFACTOR is 100000.0;


// constants for distance units popups

#ifndef FEET
constant FEET is 1;
constant METERS is 2;
constant METERSPERFOOT is 0.3048;
#endif


constant DT_STANDARD_COLUMN_WIDTH is 76;

// Block types

constant	BT_EMPTYSLOT is 0;
constant	BT_ANCHORPOINT is 1;
constant	BT_TEXT is 2;
constant	BT_EXECUTABLE is 3;
constant	BT_HIERARCHICAL is 4;

//	Indexes for the position array returned by GetBlockTypePosition

constant	PI_TOP is 0;
constant	PI_LEFT is 1;
constant	PI_BOTTOM is 2;
constant	PI_RIGHT is 3;

//	Extend version "which" argument values

constant	EV_APPLICATION is 0;
constant	EV_FILE is 1;

//	ExtendSim types returned from GetExtendType

constant	ET_NORMAL is 0;
constant	ET_LTRUNTIME is 2;
constant	ET_DEMOPLAYER is 4;

// Proof constants
constant PRF_CONTROL_ROW is 0;			// proof control block number
constant PRF_CONCURRENT_ROW is 1;			// true if the concurrent flag is turned on
constant PRF_TRACE_ROW is 2;					// true if the proof connands are sent to a trace file
constant PRF_FILE_NUM_ROW is 3;				// file number for the proof trace file
constant PRF_PAUSE_ROW is 4;					// true if the proof animation is currently paused
constant PRF_PAUSING_BLOCK is 5;				// block number of the pausing block
constant PRF_BLOCK_NUMBER is 6;				// block number of the block which is sending a message to the control block
constant PRF_ITEM_INDEX_ROW is 7;				// item index of the animated item
constant PRF_COMMAND_TYPE is 8;				// animation command associated with this block

// Database field property "which" arguments

constant	DB_TYPE_PROPERTY is 1;
constant	DB_DECIMALS_PROPERTY is 2;
constant	DB_UNIQUE_PROPERTY is 3;
constant	DB_READONLY_PROPERTY is 4;
constant	DB_INVISIBLE_PROPERTY is 5;
constant	DB_IDFIELD_PROPERTY is 6;

// Database address component limits
constant	DB_ADDRESS_MAX_DATABASES is 500;
constant	DB_ADDRESS_MAX_TABLES is 10000;
constant	DB_ADDRESS_MAX_FIELDS is 1000;
constant	DB_ADDRESS_MAX_RECORDS is 1000000;

constant	DB_RESERVED_DATABASE_CHARACTER is "_";

constant	DB_STRING_FIELD_CHARACTERS is 255;


// Database field type constants as defined by the application  !!! do not uncomment !!!
//DB_FIELDTYPE_INTEGER_VALUE,
//DB_FIELDTYPE_INTEGER_BOOLEAN (checkbox),
//DB_FIELDTYPE_REAL_GENERAL,
//DB_FIELDTYPE_REAL_SCIENTIFIC,
//DB_FIELDTYPE_REAL_PERCENT,
//DB_FIELDTYPE_REAL_CURRENCY,
//DB_FIELDTYPE_REAL_DATE_TIME,
//DB_FIELDTYPE_REAL_DB_ADDRESS,
//DB_FIELDTYPE_STRING_VALUE,
//DB_FIELDTYPE_TABLELIST

// DialogGetSize "which" argument values
constant	DGS_WIDTH is 0;
constant	DGS_HEIGHT is 1;

constant	DI_HIDDENDIALOGVARIABLEOFFSET is 5000;
constant	DI_POPUPARROWPIXELS is 12;
constant	DI_SCROLLBARWIDTHPIXELS is 17;
constant	DI_EXTRA_DIALOG_ITEM_PIXELS_MAC is 2;

//	Block dialog format constants

constant	BDF_MINIMUM_PIXELS_BETWEEN_PARAMETERS_HORIZONTAL is 4;
constant	BDF_MAXIMUM_PIXELS_BETWEEN_PARAMETERS_HORIZONTAL is 8;
constant	BDF_MINIMUM_PIXELS_BETWEEN_PARAMETERS_VERTICAL is 8;
constant	BDF_MINIMUM_PIXELS_FROM_FRAME_EDGE_VERTICAL is 14;
constant	BDF_MINIMUM_PIXELS_FROM_LABEL is 2;

//	Shift global array column constants
constant	SGA_NAME_COLUMN_INDEX is 0;
constant	SGA_BLOCK_NUMBER_COLUMN_INDEX is 1;

//	Resource Pools global array column constants
constant	RPGA_NAME_COLUMN_INDEX is 0;
constant	RPGA_BLOCK_NUMBER_COLUMN_INDEX is 1;

//	Renegging queues global array column constants
constant	RQGA_BLOCK_NUMBER_COLUMN_INDEX is 0;
constant	RQGA_RESOURCE_TABLE_ELEMENT_COLUMN_INDEX is 1;

//	UserPromptCustomButtons results
constant	UPCB_BUTTON1_CLICKED_RESULT is 1;
constant	UPCB_BUTTON2_CLICKED_RESULT is 2;

//	Renege constants
constant RNG_UPDATE_LOG is 1;
constant RNG_DO_RENEGE is 2;

//	Popup menu options
constant	PMO_NONE is "none";	**	12/23/10
constant	PMO_ALL is "All";	**	12/23/10

//	Fonts

constant	ARIAL_FONT_ID is 2001;		**	3/2/11		
constant	TEXT_TABLE_FONTSIZE is 9;	**	3/8/11		

//	Shifts
constant	OFF_SHIFTSTATUS is 0;		**	3/21/11		
constant	ON_SHIFTSTATUS is 1;		**	3/21/11


