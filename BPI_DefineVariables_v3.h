integer myWastewaterTreatedIndex;
integer waterResourcesMgrBlockNumber;
Str255 ls_AnimationName;
integer wastewaterTreatedBlockNumberArray[];
String gs_ModuleAssemblyName;

String gs_ConWaterSrcIn;
String gs_ConFlowOut;
String gs_ConResidualOut;
Integer gi_ResetConnector;
String ExceedGoal;
String gs_DBTableName_IconView;
String gs_IconName;
Str255 SelectIconLabel;
String ActivatedModuleName;
String ActivatedEQAssembly;
Integer DBRecords_EQAssembly;
Integer DBTableIndex_EQAssembly;
String SelectedTable;
String WhichTable;
Integer TableItemDeleteEndRow;
Integer TableItemDeleteStartRow;
Integer ModuleAssemblyInsertIndex;
Integer DBTblIdx_CoCRRAdj;
Integer DBTblIdx_CCUC;
Integer DBTblIdx_OMUC;
Integer ImportTypeIndex;
Integer SelectedCoCRRTblIndex;
Integer SelectedCCUCTblIndex;
Integer SelectedOMUCTblIndex;
Integer InsertCoCRRAdjIndex;
Real FlowFactor;
String OMCostsPopupUCItem_Array[];
String MonitoredVariables_Table_Array[];
String TableName_Array[];
Integer TableType_Array[];
String MonVariables_Array[];
String ChemicalFlowFactor_Array[];

Integer GroupCoCBlockNum;
Integer ActivatepHCalculator;
Integer rParameterMass_pH; 
Real OP_Acidity;
Integer pHCalculatorBlockNumber;
string gsLastEquationSelected;
String MessageEditor_Table_Array[];
String MsgEdtRule_Array[];
Integer pHIndex;
String ModuleInputCC_Array[];
String OMCostsPopupUC_Array[];
Real SubTotalCC;
Real FinalRR;
Str255 gs_PopGadgetLabel;
String LookupTableNames_Array[];
Integer NumOfLookupTables;
Integer NumOfAllGAs;
string LookupTableName;
Integer	LookupTable_NumRows1;
Integer LookupTable_NumCols1;
Integer	LookupTable_NumRows2;
Integer LookupTable_NumCols2;
Integer	LookupTable_NumRows3;
Integer LookupTable_NumCols3;
String TableLabels;
Integer VariableIndex;
String ImportLookupTableName1;
String ImportLookupTableName2;
String ImportLookupTableName3;
Integer DBTableIndex_ConversionF;
Integer	NumberOfConversionF;
String ModuleInputConversionF_Array[];
Integer UserResponse_ModuleInputConversionF;
String ModuleAssembly_Array[];

Integer Assembly_Index;

Integer DBTblIdx_CoCRRAdjustment;
Integer DBTblIdx_Pocketlist;
String Temp_CCTbl_Array[][5];
Integer NumberOfRows_CCTbl;
Integer NumberOfColumns_CCTbl;
Integer NumberOfRetainItem_CC;
Integer NumberOfFinalItems_CC;
Integer NewModuleIdentifier_CC;
Integer NumberOfRepeatedItem_CC;
Integer NumberOfModuleItems_CC;
Integer NewModuleInsertIndex_CC;

String Temp_OMTbl_Array[][8];
Integer NumberOfRows_OMTbl;
Integer NumberOfColumns_OMTbl;
Integer NumberOfRetainItem_OM;
Integer NumberOfFinalItems_OM;
Integer NewModuleIdentifier_OM;
Integer NumberOfRepeatedItem_OM;
Integer NumberOfModuleItems_OM;
Integer NewCostInsertIndex_OM;

Integer BlankValueIndex;
String ProblematicModule;
Integer	RowOfProblematicOutput;
Integer IterationCheck;		

String ModuleCategoryDropDownMenu_Array[];
String ActivatedModule;
Integer NumberOfRows_ModuleTbl;
Integer DBTableIndex_ModuleParameterKnown;
Integer ModuleStartRowIndex, ModuleEndRowIndex;
Integer NumberOfRows_ModuleInputTbl;
String Module_Table_Array[];
Integer DBTableIndex_ModuleParameterName;
Integer DBRecords_ModuleParameterName;
Integer NumberOfModules;
Integer NumOfModuleTableRows;
String ModuleDropDownMenu_Array[];
Integer UserResponse_Module;

Integer x;
Integer NumOfModuleInputTableRows;
String NewModule;
Integer NumOfPara_NewModule;
String ModuleInputTable_Array[];
Integer DBTableIndex_ModuleParameterValue;
Integer DBTableIndex_ModuleParameterUnit;
Integer NewModuleIndex;
Integer NewModuleInsertIndex;
Integer ModuleInputRowIndex;

String ModuleInputCoCDropdown_Array[];
String ModuleInputChemDropdown_Array[];
String ModuleInputFlowDropdown_Array[];
String ModuleInputPocketList_Array[];
Integer UserResponse_ModuleInputCoC;
Integer UserResponse_ModuleInputChem;
Integer UserResponse_ModuleInputFlow;
Integer UserResponse_ModuleInputPocketList;

Integer oldNumOfRows_Lookup1;
Integer oldNumOfRows_Lookup2;
Integer oldNumOfRows_Lookup3;
Integer NumOfRowsToAdd_Lookup1;
Integer NumOfRowsToAdd_Lookup2;
Integer NumOfRowsToAdd_Lookup3;
String Lookup1_Table_Array[];
String Lookup2_Table_Array[];
String Lookup3_Table_Array[];

Integer NumOfOutput_NewModule;
Integer DBTableIndex_ModuleOutputName;
String ModuleOutputTable_Array[];
Integer NumOfModuleOutputTableRows;
Integer NewModuleOutputInsertIndex;
Integer DBTableIndex_ModuleOutputUnit;
Integer DBTableIndex_ModuleOutputCostEst;
Integer ModuleOutputRowIndex;
String ModuleCoCTable_Array[];

Integer RecordRowIndex;
Integer ExistingNumberOfDynamicPara;
String ModuleNumber;
Integer NumberOFField_CoCRRAdjustmentTable;
Integer NumberOfRow_LookupTable;
Integer DBTableIndex_ModulePocketList;
String PocketParaName;
String CC_UnitCost_Table_Array[];
String OM_UnitCost_Table_Array[];
String CC_FixCost_Table_Array[];
String OM_FixCost_Table_Array[];
String CC_Percent_Table_Array[];
String OM_Percent_Table_Array[];
String CostFactorBracket_Table_Array[];

Integer NumOfItems_CC_UnitCost;
Integer NumOfItems_CC_FixCost;
Integer NumOfItems_CC_Percent;
Integer NumOfItems_OM_UnitCost;
Integer NumOfItems_OM_FixCost;
Integer NumOfItems_OM_Percent;

Real Subtotal_CC_UnitCost_NBCF;
Real Subtotal_CC_UnitCost_BCF;
Real Subtotal_CC_UnitCost;
Real Subtotal_CC_FixCost;
Real Subtotal_CC_Percent;
Real Subtotal_OM_UnitCost;
Real Subtotal_OM_UnitCost_NBCF;
Real Subtotal_OM_UnitCost_BCF;
Real Subtotal_OM_FixCost;
Real Subtotal_OM_FixCost_Year;
Real Subtotal_OM_FixCost_Month;
Real Subtotal_OM_FixCost_Week;
Real Subtotal_OM_FixCost_Day;
Real Subtotal_OM_Percent;

Real CCBracketFactor;
Real OMBracketFactor;
Real FlowPercentile;
Integer NumberofBracketTable;
Integer BracketIndex;

Integer MyTimeStep;
String CostsPopup_Array[];
String OMCostsPopup_Array[];
String FixCostsPopup_Array[];
Integer ColClicked;
Integer RowClicked;
Integer UserResponse_Cost;
String TargetTableName;
String TS_WQ_Array[];
String TS_WQp_Array[];
String TS_WQw_Array[];
Integer DBTableIndex_CoCListDynamic;
Integer NumberOfCoCs;
String SimulationMode;

Integer DBTableIndex_CoCProcessRR;
Integer NumberOfProcessBlocks;
Integer DBTableIndex_CoCList;

String Scenario_Site;
String Scenario_Phase;

Integer DBTableIndex_ProcessScenarios;
Integer NumberOfScenarios;
Integer ProcessTableNumber;
Integer DBTableIndex_WQSource;
Real subtot_om_cost; 
Real Subtotal_OM_UnitCost_NBCF_D;
Real Subtotal_OM_UnitCost_NBCF_W;
Real Subtotal_OM_UnitCost_NBCF_M;
Real Subtotal_OM_UnitCost_NBCF_Y;
Real Subtotal_OM_UnitCost_BCF_D;
Real Subtotal_OM_UnitCost_BCF_W;
Real Subtotal_OM_UnitCost_BCF_M;
Real Subtotal_OM_UnitCost_BCF_Y;
String OMCostsPopup_Array_2[];
String gs_TimeStepUnit;
integer myCIPIndex;
integer CIPManagerBlockNumber;
integer CIPBlockNumberArray[];

integer DBIndexLookup;
integer DBTableIndexProjections;
integer DBRecNumProjections;

real lrCurrentTimeFlow;
real lrPrevTimeFlow;
real lrInitialYear;

integer iArrayIncr,iConnIncr;   
real rCostCapital;
real rParameterMass_TS;
real rParameterMass_SS;
real rParameterMass_iPFD;
constant NA_SAR is 23;
constant CA_SAR is 40;
constant MG_SAR is 24;
constant ARRAYSIZE is 50;
Constant Array_Flow is 0;		*** Chiu 02/21/2014 ***
Constant Array_WQ_TS is 1;		*** Chiu 02/21/2014 ***
Constant Array_WQ_SS is 2;		*** Chiu 02/21/2014 ***
Constant Array_WQ_iPFD is 3;	*** Chiu 05/10/2014 ***
Constant Array_WQ_pH is 4;    *** Chiu 11/21/2014 ***
//Constant Array_WQr_TS is 3;		*** Chiu 02/21/2014 *** Deactivated 05/02/2014
//Constant Array_WQr_SS is 4;		*** Chiu 02/21/2014 *** Deactivated 05/02/2014

integer DBIndex;				//Model database pointer - DB var to copy
integer DBTableIndex_1;			//Database table 1 (Output) pointer - DB var to copy
integer DBTableIndex_2;			//Database table 2 (Input) pointer - DB var to copy
integer DBTableIndex_3;			//Database table 3 (Input WQ) pointer - DB var to copy

integer DBRecNum_Output;		//DB var to copy
integer DBRecNum_Input;			//DB var to copy
integer DBRecNum_Input_2;		//DB var to copy	
integer DBRecNum_Input_WQ;		//DB var to copy
integer i;						//DB var to copy
integer j;						//DB var to copy
integer k;						//DB var to copy
integer check;					//DB var to copy
integer c_cost_method;			//DB var to copy
integer om_cost_method;			//DB var to copy

integer NumValuesInCon;
						
real test_val;					//holder variable for water quality parameters
string CoCName;				//holder variable for water quality parameter labels
string CoCUnit;	

real cost_val;					//holder variable for cost parameters
real cost_val_2;				//holder variable for cost parameters
string cost_label_1;			//holder variable for cost labels
string cost_label_2;			//holder variable for cost labels
string cost_label_3;			//holder variable for cost labels
string cost_label_4;			//holder variable for cost labels


real tot_c_cost;
real tot_om_cost;

string blocknumber;				
string blockID;					//Block ID or name given to the block in Excel

string temp_dyn_array_1[];   		//dynamic array to hold values for the text table to allow variable rows dependent on Excel dashboard inputs
string temp_dyn_array_2[];		//dynamic array to hold the capital cost value text table values to allow variable rows
string temp_dyn_array_3[];		//dynamic array to hold the capital cost value text table values to allow variable rows
string temp_dyn_array_4[];
string temp_dyn_array_5[];

integer maxWQparam;				//maximum number of water quality parameters entered in excel dashboard
integer maxCCparam;				//maximum number of capital cost parameters entered in excel dashboard
integer maxOMparam;				//maximum number of O&M cost parameters entered in excel dashboard
integer maxLCparam;				//maximum number of Life Cycle cost parameters entered in Excel dashboard


real WaterSourceIn[][6];			//OLD VARIABLE - NOT REFERENCED IN CODE
real Product[][6];					//The "Product" of the mass/flow of the incoming, variable connectors
real FlowOut_P[][6];					//Passes Product water flow and water quality parameters out of the block
real FlowOut_P_1[][6];
real FlowOut_P_2[][6];
real FlowOut_P_3[][6];
real FlowOut_P_4[][6];
real FlowOut_P_5[][6];
real FlowOut_P_6[][6];
real FlowOut_P_7[][6];
real FlowOut_P_8[][6];
real FlowOut_P_9[][6];
real FlowOut_P_10[][6];

real FlowOut_r[][6];                    //Passes Waste flow and water quality parameters out of the block
real Concentrate[][6];
real rInflowIncr[][6];

integer curTimeStep;

real capacityCompare;
Integer CapacityDeficitCount;
Integer DBTableIndex_TS_Label;
Integer DBRecNum_TS_Label;
Integer DBFieldIndex_TS_Label_Time;
Integer DBFieldIndex_TS_Label_DB_StartYear;
Integer DBInput_StartYear;
Integer DBTableIndex_ChemicalUsage;
Integer DBFieldIndex_ChemicalName;
Integer NumberofChemicals;
Integer LocationIndex;
Integer DBTableIndex_Chemical_Inventory;
Integer DBFieldIndex_ChemInv_UnitPrice;
Integer DBTableIndex_TimeframeDisplay;

Integer DBFieldIndex_PlanningTimeframe;
Integer DBFieldIndex_TimeStepUnit;

String Timestep_Array[];
String Costs_TextTable_Array[];
String Residual_WQ_Array[];
String ProcessPara_Array[];
String TS_Table_Label;
String Chemical_Cost_Array[];
String ChemicalName;
String UnitCost;

Integer CurrentYear;
Integer Phase1Year;
Integer Phase2Year;
Integer Phase3Year;
Integer Phase4Year;
Integer Phase5Year;
Integer Phase1_TimetoImprove;
Integer Phase2_TimetoImprove;
Integer Phase3_TimetoImprove;
Integer Phase4_TimetoImprove;
Integer Phase5_TimetoImprove;

Real Input_Array[][6];
Real Output_Array[][6];
Integer Output_Array_Size;

Real Total_Chemical_UnitCost;

Integer DBTableIndex_ScenarioManager;
Real WARNING_FvC;
Real STOP_FvC;

Integer StartMonth;
Integer DBFieldIndex_StartMonth;

Integer BODTKNCompare;

Real Chemical_Cost;
Real Monthly_OM_Cost;
integer MethanolCheck;
Integer MethanolLocIdx;
Integer NutrientLocIdx;
Integer BODLocIdx;
Integer TKNLocIdx;
Real BODTKNRatio;

Integer CatalaseCheck;
Integer CatalaseLocIdx;
Integer H2O2LocIdx;
Real CatH2O2Ratio;
Real H2O2RemPct;

Integer PACCheck;
Integer PACLocIdx;
Integer O3Check;
Integer O3LocIdx;
Integer TriazolesLocIdx;
Real PACDose;
Real TriazolesRemPct;
Real O3Dose;

Integer TNLocIdx;
Integer CODLocIdx;
Integer NH4LocIdx;
Integer TOCLocIdx;
Real SRTRatio;

Real CostAdjFac;
Integer DBTableIndex_CoCList_Dynamic;
Integer NumOfCoC_iPFD;
Integer iPFDTable_NumOfFields;
String iPFD_WQ_Array[];
String iPFD_WQp_Array[];
String iPFD_WQw_Array[];
Real iPFD_WQ_val;

Integer DBTableIndex_ProcessBlockNumber;
String MyBlockLabel;
Integer NumofProcessBlock;
Integer DBTableIndex_MyTreatedWQDB;

Integer StartRowSave;
String EQModule_Table_Array[];
String EQModuleInputTable_Array[];
String IntegratedEQInput_Array[];

Integer PreviousNumOfTbls_A;

String EQ_ModuleTable_Array[];
String EQ_ModuleInputTable_Array[];

Integer HSV_red[];
Integer HSV_green[];
Integer HSV_blue[];
Integer HSV_gray[];
Integer HSV_black[];

Integer DBTableIndex_IconView;
Integer gi_NumOfConOut;
String gs_FlowOutArrayName[][6];

String array_FlowSplit[];
Integer DBTableIndex_SourceScenarios;
Integer SourceTableNumber;
Integer NumberOfSourceBlocks;
real CoCConc;
String MonitoredCoCArray[];
Integer PositionIndex;

Integer ExceedCount;

Integer array_ConFlowIn[][2];
Integer	DBTblIdx_InflowWQs;


String array_ConnectorType[];
Integer gi_ConFNumber;
Integer gi_ConPNumber;
Integer gi_ConWNumber;

// New variables for Module Assembly and Equation Assembly Databases
Integer DBIdx_MDU;
Integer DBIdx_EQ;
Integer DBIdx_TS;


String ModuleInputGlobalCVBlock_Array[];
String ModuleInputGlobalCV_Array[];

Integer gi_AnimationColor;
Integer gi_UseAnimation;

Constant RU is "RU";
Constant RD is "RD";
Constant R is "R";
Real gr_ThisYearCapacity;
Integer gi_NumOfTimeSteps;
Integer gi_TimeStepIndex;

Real gr_LastYearCapacity;

Integer DemandDeficitCount;

Integer AnimationLeft;
Integer AnimationTop;


Integer gi_SimStartRow;
Integer gi_SimEndRow;
Integer FlowDecimal;

integer CompiledEquation_da[];

real iV[];
real oV[];

Real NewInitialLevel; //Ryan Hejka 7/24/15
Integer array_ConFlowOut2[][2];
String array_DropdownMenu[];

String array_GadgetPopLabel[];

************************************
// Equation Module Variables
************************************
integer giDBIdx;

integer giDBEquationInputOutputsTIdx;
integer giEquationNameEqIOFIdx;
integer giInputOutputEqIOFIdx;
integer giVariableTypeEqIOFIdx;
integer giVariableNameEqIOFIdx;
integer giValueEqIOFIdx;
integer giUnitEqIOFIdx;

integer giDBEquationsTIdx;
integer giEquationNameEqFIdx;
integer giEquationRIdxEqFIdx;
integer giEquationEqFIdx;
integer giEquationEqV2FIdx;
integer giEquationPointerEqFIdx;

integer giDBEquationDescriptionsTIdx;
integer giEquationNameEqDFIdx;
integer giEquationPointerEqDFIdx;
integer giEquationDescriptionEqDFIdx;


//string gsDialogTable[][5];
//string gsDBEquationList[];
//integer CompiledEquation_da[];

//real iV[];
//real oV[];

Constant csInputName is "Input";
Constant csOutputName is "Output";

Constant csIntegerName is "Integer";
Constant csRealName is "Real";

// DB Equation Inventory Field Constants
Constant cDBEquationNameF is 0;
Constant cNumOfInputsF is 1;
Constant cNumOfOutputsF is 2;
Constant cRenameF is 3;
Constant cDeleteF is 4;

String array_DIProperty[][15]; //DI Name;Top;Left;Bottom;Right;Color;LinkDI;LinkRow;LinkColumn;
Constant li_NumOfDashboardLabels is 20;

String array_SelectIcon[];