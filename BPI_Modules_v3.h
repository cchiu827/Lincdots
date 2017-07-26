******************************************************************************************
*************** Start of Module Function Procedure for each Module ***********************

Procedure Module_DesignHRTLtoW()
{
	Real IP_Flow, IP_HRT, IP_SWD, IP_W, IP_NumOfTrainD, IP_NumOfTrainR, IP_FB;//IP_LtoW, CHE edited
	Real OP_NumOfTrainTtl, OP_DepthTtl, OP_LengthOvl, OP_VolumeTtl, OP_LengthEach;
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Design HRT to Volume")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names

	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	//IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]); CHE, the following moved up 1
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_HRT			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	
	// Module Equation
	OP_NumOfTrainTtl = IP_NumOfTrainD + IP_NumOfTrainR;
	OP_DepthTtl = IP_SWD + IP_FB;
	OP_LengthEach = (IP_HRT*IP_Flow/24/IP_SWD/IP_W/IP_NumOfTrainD*10^6/7.48);//CHE
	OP_LengthOvl = OP_LengthEach * OP_NumofTrainTtl;
	OP_VolumeTtl = IP_SWD*IP_W*OP_LengthEach*7.48/10^6*OP_NumOfTrainTtl;
	
	// Link Module results to output parameters
 	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumOfTrainTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_DepthTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_LengthOvl, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_LengthEach, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_VolumeTtl, 5);
}


Procedure Module_PumpEfficiency_Standard()
{
	Real IP_Flow, IP_TDH, IP_PumpEff, IP_MotorEff, IP_VFD, IP_SG, IP_Num_Pump_D, IP_Num_Pump_S, IP_RunTimeFactor; 	// IP = Input Parameter
	Real OP_Energy, OP_HPEach, OP_NumofPMP; 												// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Pump Efficiency - Standard")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_TDH		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_PumpEff	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7])/100;
	IP_MotorEff	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7])/100;
	IP_VFD		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7])/100;
	IP_SG		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_Num_Pump_D		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_Num_Pump_S		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	IP_RunTimeFactor		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7])/100;
	// Module Equation
	OP_Energy = IP_Flow*IP_TDH/IP_PumpEff/IP_MotorEff/IP_VFD*IP_SG*694/3960*0.7457*52.14*7*24*IP_RunTimeFactor;
	OP_HPEach = IP_Flow*IP_TDH/IP_PumpEff/IP_MotorEff/IP_VFD*IP_SG*694/3960/IP_Num_Pump_D;
	OP_NumofPMP = IP_Num_Pump_D + IP_Num_Pump_S;
	
	// Link Module results to output parameters

	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_Energy, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_HPEach, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_NumofPMP, 5);
}

Procedure Module_RunTime()
{
	Real IP_NumofWk, IP_NumofDay, IP_NumofHour; 	// IP = Input Parameter
	Real OP_RunTimeFactor; 												// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Run Time Factor")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_NumofWk	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumofDay	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumofHour		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	// Module Equation
	OP_RunTimeFactor = IP_NumofWk * IP_NumofDay * IP_NumofHour / 24 / 52.14 / 7 * 100;
	
	// Link Module results to output parameters

	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_RunTimeFactor, 5);
	
}


Procedure Module_RunTimeFull()
{
	Real IP_NumofWk, IP_NumofDay, IP_NumofHour, IP_NumofMinute; 	// IP = Input Parameter
	Real OP_RunTimeFactor; 												// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Run Time Factor")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_NumofWk	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumofDay	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumofHour		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_NumofMinute		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	// Module Equation
	OP_RunTimeFactor = IP_NumofWk * IP_NumofDay * IP_NumofHour * IP_NumofMinute / 24 / 52.14 / 7 / 60 * 100;
	
	// Link Module results to output parameters

	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_RunTimeFactor, 1);
}

Procedure Module_MotorEfficiency()
{
	Real IP_HPEach, IP_MotorEff, IP_RunTimeFactor, IP_Num_Pump_D, IP_Num_Pump_S; 	// IP = Input Parameter
	Real OP_Energy, OP_HPActEach, OP_NumofUnitsTotal; 												// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Motor HP")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_HPEach	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_MotorEff	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7])/100;
	IP_RunTimeFactor		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7])/100;
	IP_Num_Pump_D		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Num_Pump_S		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	// Module Equation
	OP_Energy = IP_HPEach*IP_Num_Pump_D*0.7457*52.14*7*24*IP_RunTimeFactor;
	OP_HPActEach = IP_HPEach/IP_MotorEff;
	OP_NumofUnitsTotal = IP_Num_Pump_D + IP_Num_Pump_S;
	
	// Link Module results to output parameters

	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_Energy, 1);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_HPActEach, 1);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumofUnitsTotal, 1);
}

Procedure Module_DisinfectionCT()
{
	Real IP_ChemDose, IP_ContactTime;
	Real OP_Ct;
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Disinfection - Ct")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_ChemDose		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_ContactTime	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation
	OP_Ct = IP_ChemDose*IP_ContactTime;

	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+2][7] = fixdecimal(OP_Ct, 5);	
}

Procedure Module_DisinfectionRatio()
{
	Real IP_ChemDose, IP_CoCConc;
	Real OP_Ratio;
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Disinfection - Ratio")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_ChemDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_CoCConc	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);

	// Module Equation
	OP_Ratio = IP_ChemDose/IP_CoCConc;
	
	// Link Module results to output parameters

	Module_Input_tbl[ModuleStartRowIndex+2][7] = fixdecimal(OP_Ratio, 5);
}

Procedure Module_DisinfectionDose()
{
	Real IP_ChemDose;
		
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Disinfection - Dose")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_ChemDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	
	// Module Equation
	
	// Link Module results to output parameters
	
		*** for disinfection, a lookup table (C*t vs. RR) is usually used to determine removal rate.
}

Procedure Module_Summation()
{	
	Real OP_Sum;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Summation")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Sum = 0;
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I") //AND Module_Input_tbl[j][4] == TRUE) //CHE EDITED ON OCT24
		{
		 OP_Sum += StrToReal(Module_Input_tbl[j][7]);
		}
	}
	
	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O") 	Module_Input_tbl[j][7] = fixdecimal(OP_Sum, 5);
	}	
}

Procedure Module_Product()
{	
	Real OP_Product;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Product")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Product = 1;
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I")//AND Module_Input_tbl[j][4] == TRUE) // CHE edited
		{
			OP_Product = OP_Product*StrToReal(Module_Input_tbl[j][7]);
		}
	}

	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O") 	Module_Input_tbl[j][7] = fixdecimal(OP_Product, 5);
	}	
}

Procedure Module_MIN()
{	
	Integer BlankIndex;
	Real OP_Min;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Minimum")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Min = 1000000000000;
	BlankIndex = 0;
	
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I")//AND Module_Input_tbl[j][4] == TRUE) // CHE edited
		{
			if (StrLen(Module_Input_tbl[j][7]) == 0 OR StrLen(OP_Min) == 0) BlankIndex++;
			
			else OP_Min = Min2(OP_Min,StrToReal(Module_Input_tbl[j][7]));
		}
	}

	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O" AND BlankIndex == 0) 	Module_Input_tbl[j][7] = fixdecimal(OP_Min, 5);
		
		else if(Module_Input_tbl[j][2] == "O") Module_Input_tbl[j][7] = "";
	}	
}

Procedure Module_Max()
{	
	Integer BlankIndex;
	Real OP_Max;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Maximum")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	
	// Module Equation
	OP_Max = -1000000000000;
	BlankIndex = 0;
	
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "I")//AND Module_Input_tbl[j][4] == TRUE) // CHE edited
		{
			if (StrLen(Module_Input_tbl[j][7]) == 0 OR StrLen(OP_Max) == 0) BlankIndex++;
			
			else OP_Max = Max2(OP_Max,StrToReal(Module_Input_tbl[j][7]));
		}
	}

	// Link Module results to output parameters
	for (j = ModuleStartRowIndex; j <= ModuleEndRowIndex; j++)
	{
		if (Module_Input_tbl[j][2] == "O" AND BlankIndex == 0) 	Module_Input_tbl[j][7] = fixdecimal(OP_Max, 5);
		else if(Module_Input_tbl[j][2] == "O") Module_Input_tbl[j][7] = "";
	}	
}

Procedure Module_BasinCompartments()
{
	Real IP_NumOfTrainD, IP_NumOfTrainR, IP_W, IP_SWD, IP_FB, IP_AnoxPct, IP_NumOfStage, IP_Lovl; 	// IP = Input Parameter
	Real OP_Lanox, OP_LperStage, OP_VperStage, OP_Vttl; 												// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Basin Compartments")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_AnoxPct		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7])/100;
	IP_NumOfStage	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_Lovl			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	
	// Module Equation
	OP_Lanox = IP_Lovl*IP_AnoxPct;
	OP_LperStage = OP_Lanox/IP_NumOfStage;
	OP_VperStage = IP_W*IP_SWD*OP_LperStage*7.48/10^6;
	OP_Vttl = OP_VperStage*IP_NumOfStage*(IP_NumOfTrainD+IP_NumOfTrainR);
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_Lanox, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_LperStage, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_VperStage, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_Vttl, 5);
}

Procedure Module_ActualHRT_AllinService() //CHE Edited 
{
	Real IP_Flow, IP_Width, IP_SWD, IP_ActLengthEach, IP_NumofTrainsTotal; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlLength; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (All in service)")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Width= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_ActLengthEach= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofTrainsTotal = StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	
	// Module Equation
	OP_ActVol = IP_Width * IP_SWD * IP_ActLengthEach * IP_NumofTrainsTotal *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlLength = IP_ActLengthEach * IP_NumofTrainsTotal;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_OvlLength,5);
}

Procedure Module_ActualHRT_DutyinService() //CHE Added
{
	Real IP_Flow, IP_Width, IP_SWD, IP_ActLengthEach, IP_NumofDutyTrains; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlLengthD; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (Duty in service)")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Width= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_ActLengthEach= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofDutyTrains = StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	
	// Module Equation
	OP_ActVol = IP_Width * IP_SWD * IP_ActLengthEach * IP_NumofDutyTrains *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlLengthD = IP_ActLengthEach * IP_NumofDutyTrains;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_OvlLengthD, 5);
}

Procedure Module_BasinVolume()
{
	Real IP_NumOfTrainD, IP_NumOfTrainR, IP_LperTrain, IP_WperTrain, IP_SWD, IP_FB; 	// IP = Input Parameter
	Real OP_VperTrain, OP_Vttl; 														// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Basin Volume")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_LperTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_WperTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	
	// Module Equation
	OP_VperTrain = IP_LperTrain*IP_WperTrain*IP_SWD*7.48/10^6;
	OP_Vttl = OP_VperTrain*(IP_NumOfTrainD+IP_NumOfTrainR);
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_VperTrain, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_Vttl, 5);
}

Procedure Module_VolumetricLoading() 																**## 1.Change Procedure Name ##**
{
																									**## 2.Change Parameter Name ##**
	Real IP_Flow, IP_CoC, IP_Vttl; 			// IP = Input Parameter
	Real OP_BODLoading, OP_BODLoadingperV; 	// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Volumetric Loading") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Flow	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_CoC	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Vttl	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_BODLoading = IP_Flow*IP_CoC*8.34;
	OP_BODLoadingperV = OP_BODLoading/(IP_Vttl*10^6/7.48/1000);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_BODLoading, 5);
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_BODLoadingperV, 5);
}

Procedure Module_LoadingRemoval()																	
{
																									**## 2.Change Parameter Name ##**
	Real IP_CoC, IP_BODe, IP_Conversion, IP_Flow; 			// IP = Input Parameter
	Real OP_DeltaS; 	// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Loading Removal") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_CoC			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_BODe			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Conversion	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_DeltaS = (IP_CoC-IP_BODe)*IP_Conversion*IP_Flow;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_DeltaS, 5);
}

Procedure Module_CASAeratedVolume()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Yield, IP_SRT, IP_MLSS, IP_Flow, IP_CoC, IP_BODe; 			// IP = Input Parameter
	Real OP_Vol; 	// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "CAS Aerated Volume") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Yield	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_SRT		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_MLSS		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Flow		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_CoC		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_BODe		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Yield*IP_SRT*IP_Flow*(IP_CoC-IP_BODe)/IP_MLSS;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_TankSizing()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfTrainD, IP_NumOfTrainR, IP_LtoW, IP_SWD, IP_FB, IP_CASVol; // IP = Input Parameter
	Real OP_NumOfTrainttl, OP_Dttl, OP_Lovl, OP_Wovl; 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Tank Sizing") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_CASVol		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfTrainttl = IP_NumOfTrainD+IP_NumOfTrainR;
	OP_Dttl = IP_SWD+IP_FB;
	OP_Wovl = (IP_CASVol/IP_SWD/IP_LtoW/IP_NumOfTrainD/7.48*10^6)^0.5;
	OP_Lovl = OP_Wovl*IP_LtoW;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumOfTrainttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_Dttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_Wovl, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_Lovl, 5);
}

Procedure Module_CASSolidsProduction()
{
																									**## 2.Change Parameter Name ##**
	Real IP_fuv, IP_SRT, IP_Kd, IP_Yield, IP_CoC, IP_BODe, IP_TSS0, IP_Flow; // IP = Input Parameter
	Real OP_SolidProduction; 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "CAS Solids Production") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_fuv		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_SRT		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Kd		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Yield	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_CoC		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_BODe		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_TSS0		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_Flow		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);		

	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SolidProduction = IP_Flow*(IP_CoC-IP_BODe)*8.34*IP_Yield/(1+IP_Kd*IP_SRT)+IP_TSS0*IP_Flow*8.34*IP_fuv;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_SolidProduction, 5);
}

Procedure Module_CASMixer()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfUnitD, IP_NumOfUnitR, IP_UnitPower, IP_Vanox, IP_E, IP_RunHour, IP_RunDay; // IP = Input Parameter
	Real OP_NumOfUnitttl, OP_BHPperUnit, OP_PowerConsumption; 								// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "CAS Mixer") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfUnitD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfUnitR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_UnitPower	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Vanox		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_E			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7])/100;
	IP_RunHour		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_RunDay		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
 	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfUnitttl = IP_NumOfUnitD+IP_NumOfUnitR;
	OP_BHPperUnit = IP_Vanox*10^6/7.48/1000*IP_UnitPower/IP_E/IP_NumOfUnitD;
	OP_PowerConsumption = OP_BHPperUnit*IP_NumOfUnitD*IP_RunHour*IP_RunDay;

	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumOfUnitttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_BHPperUnit, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_PowerConsumption, 5);
}

Procedure Module_MixerGValue()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfUnitD, IP_NumOfUnitR, IP_Vol, IP_E, IP_RunHour, IP_RunDay, IP_G, IP_Visco; // IP = Input Parameter
	Real OP_NumOfUnitttl, OP_BHPperUnit, OP_PowerConsumption; 								// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Mixer G Value") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfUnitD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfUnitR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Vol			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_E			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7])/100;
	IP_RunHour		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_RunDay		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_G			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_Visco		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfUnitttl = IP_NumOfUnitD+IP_NumOfUnitR;
	OP_BHPperUnit = IP_Visco*(IP_Vol*10^6/7.48)*IP_G^2/550/IP_E/IP_NumOfUnitD;
	OP_PowerConsumption = OP_BHPperUnit*IP_NumOfUnitD*IP_RunHour*IP_RunDay*0.7457;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_NumOfUnitttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_BHPperUnit, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_PowerConsumption, 5);
}

Procedure Module_NO3NFormed()
{
																									**## 2.Change Parameter Name ##**
	Real IP_fN, IP_Xw, IP_Factor, IP_NH3Neff, IP_TKNin, IP_Nsoe; 	// IP = Input Parameter
	Real OP_NO3Nformed; 											// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "NO3-N Formed") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_fN		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Xw		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Factor	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_NH3Neff	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_TKNin	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_Nsoe		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NO3Nformed = IP_TKNin-IP_fN*IP_Xw*IP_Factor-IP_Nsoe-IP_NH3Neff;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_NO3Nformed, 5);
}

Procedure Module_ALKforNitrogenRemoval()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NO3N, IP_ALKtoNO3N, IP_ALKrem, IP_ALKin; 	// IP = Input Parameter
	Real OP_ALKreq; 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "ALK Required for Nitrogen Removal") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NO3N			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_ALKtoNO3N	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_ALKrem		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_ALKin		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_ALKreq = IP_ALKtoNO3N*IP_NO3N+IP_ALKrem-IP_ALKin;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_ALKreq, 5);
}

Procedure Module_LowSRTOxygenRequirement()
{
																									**## 2.Change Parameter Name ##**
	Real IP_O2perBOD, IP_CoC, IP_Flow; 	// IP = Input Parameter
	Real OP_O2req; 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Low SRT Oxygen Requirement") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_O2perBOD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_CoC		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Flow		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_O2req = IP_Flow*8.34*IP_CoC*IP_O2perBOD;

	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_O2req, 5);
}

Procedure Module_HighSRTOxygenRequirement()
{
																									**## 2.Change Parameter Name ##**
	Real IP_O2perBOD, IP_O2perNO3N, IP_CoC, IP_Flow, IP_NO3N; 	// IP = Input Parameter
	Real OP_O2req; 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "High SRT Oxygen Requirement") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_O2perBOD		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_O2perNO3N	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_CoC			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);	
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NO3N			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);	
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_O2req = IP_Flow*8.34*IP_CoC*IP_O2perBOD+IP_NO3N*IP_Flow*8.34*IP_O2perNO3N;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_O2req, 5);
}

Procedure Module_ImpoundmentStorage()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_StorageHrReq, IP_ImpdSize; 	// IP = Input Parameter
	Real OP_NumOfImpd;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Impoundment Storage") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_StorageHrReq	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_ImpdSize		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);	

	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfImpd = IP_Capacity*IP_StorageHrReq/24/IP_ImpdSize;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_NumOfImpd, 5);
}

Procedure Module_RapidMix()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_DsgnCap, IP_DsgnG, IP_MotorHP, IP_W, IP_L, IP_SWD; 	// IP = Input Parameter
	Real OP_NumOfMixer, OP_DetTime;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Rapid Mix") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_DsgnCap	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_DsgnG	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_MotorHP	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_W		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_SWD		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_NumOfMixer = IP_Capacity/IP_DsgnCap;
	OP_DetTime = IP_W*IP_L*IP_SWD*60*7.48/(IP_DsgnCap*10^6/24/60);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumOfMixer, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_DetTime, 5);
}

Procedure Module_HydraulicFlocculationBasins()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTrain, IP_NumOfStage, IP_WperBasin, IP_L, IP_SWD; 	// IP = Input Parameter
	Real OP_WttlperTrain, OP_SurfaceArea, OP_Volttl, OP_DetTime;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Hydraulic Flocculation Basins") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumOfStage	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_WperBasin	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_L			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_WttlperTrain = IP_NumOfTrain*IP_WperBasin+6;
	OP_SurfaceArea = IP_L*OP_WttlperTrain;
	OP_Volttl = OP_SurfaceArea*IP_SWD*7.48/10^6;
	OP_DetTime = OP_Volttl/IP_Capacity*1440;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_WttlperTrain, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_SurfaceArea, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_Volttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_DetTime, 5);
}

Procedure Module_SedBasinwithHydraulicScraper()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTrain, IP_SfcLR, IP_W, IP_Lbay; 	// IP = Input Parameter
	Real OP_SfcAreaReq, OP_AvailableArea;			 						// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Sed Basin with Hydraulic Scraper") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrain	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SfcLR		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Lbay			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);		

	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SfcAreaReq = IP_Capacity*694/IP_SfcLR;
	OP_AvailableArea = IP_NumOfTrain*IP_W*IP_Lbay;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_SfcAreaReq, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_AvailableArea, 5);
}

Procedure Module_RawWaterPumpStation()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfPump, IP_PumpCap, IP_USHL, IP_DSHL, IP_ImpdOPL, IP_PSGL; 	// IP = Input Parameter
	Real OP_PumpCapttl, OP_TDH;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Raw Water Pump Station") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfPump	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_PumpCap		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_USHL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_DSHL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_ImpdOPL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_PSGL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_PumpCapttl = IP_PumpCap*IP_NumOfPump;
	OP_TDH = IP_PSGL-IP_ImpdOPL+IP_USHL+IP_DSHL;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
		if (Module_Input_tbl[ModuleStartRowIndex+6][3] == "Total Pump Capacity") 	Module_Input_tbl[j][7] = fixdecimal(OP_PumpCapttl, 5);
		if (Module_Input_tbl[ModuleStartRowIndex+7][3] == "Estimated TDH") 			Module_Input_tbl[j][7] = fixdecimal(OP_TDH, 5);
}

Procedure Module_Flocculation()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTrainD, IP_NumOfTrainR, IP_DsgnCap, IP_W, IP_L, IP_SWD; 	// IP = Input Parameter
	Real OP_VolPerTrain, OP_DetTime, OP_DetTimemax;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Flocculation") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_DsgnCap		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_L			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_VolPerTrain = IP_W*IP_L*IP_SWD;
	OP_DetTime = OP_VolPerTrain*7.48/10^6/(IP_DsgnCap/24/60);
	OP_DetTimemax = OP_DetTime/IP_NumOfTrainD*(IP_NumOfTrainD-IP_NumOfTrainR);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_VolPerTrain, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_DetTime, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_DetTimemax, 5);
}

Procedure Module_Sedimentation()
{
																									**## 2.Change Parameter Name ##**
	Real IP_NumOfTrainD, IP_DsgnCap, IP_LtoW, IP_W, IP_SWD, IP_DsgnSfcLR, IP_DsgnWeirLR; 	// IP = Input Parameter
	Real OP_SfcLR, OP_WeirLperBasin;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Sedimentation") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_DsgnCap		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_DsgnSfcLR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_DsgnWeirLR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);		
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SfcLR = IP_DsgnCap*694/(IP_W*IP_W*IP_LtoW);
	OP_WeirLperBasin = IP_DsgnCap*10^6/IP_DsgnWeirLR;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_SfcLR, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_WeirLperBasin, 5);
}

Procedure Module_ChemicalStorageSizing()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_Density, IP_Dose, IP_StorageTime, IP_NumOFTank, IP_DiaOfTank, IP_Strength; 	// IP = Input Parameter
	Real OP_FeedRate, OP_Vol, OP_HOfTank;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Chemical Storage Sizing") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Density		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_Dose			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_StorageTime	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumOFTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_DiaOfTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);		
	IP_Strength	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7])/100;
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_FeedRate = IP_Capacity*IP_Dose/IP_Density/IP_Strength/24*8.34/0.485;
	OP_Vol = Round(OP_FeedRate*24*IP_StorageTime/IP_NumOFTank,1);
	OP_HOfTank = OP_Vol/7.48/(3.14*IP_DiaOfTank^2/4);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_FeedRate, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_Vol, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_HOfTank, 5);
}

Procedure Module_SolidsLoading()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NTU, IP_CoagF, IP_PolyF, IP_SStoNTUR, IP_PACF, IP_CoagDose, IP_PolyDose, IP_PACDose, IP_Recycle; 	// IP = Input Parameter
	Real OP_SolidsLoadingAvg;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Solids Production") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Capacity	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NTU		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_CoagF	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_PolyF	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_SStoNTUR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_PACF		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_CoagDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_PolyDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	IP_PACDose	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	IP_Recycle	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+9][7]);	
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SolidsLoadingAvg = (1+IP_Recycle/100)*IP_Capacity*8.34*(IP_NTU*IP_SStoNTUR+IP_CoagF*IP_CoagDose+IP_PolyF*IP_PolyDose+IP_PACF*IP_PACDose);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_SolidsLoadingAvg, 5);
}

Procedure Module_Clarifier()
{
																									**## 2.Change Parameter Name ##**
	Real IP_SolidsLAvg, IP_FeedSolidConc, IP_SolidCapture, IP_NumOfClarifier, IP_DiaOfClarifier, IP_SWD, IP_TgtSL, IP_TgtHyL; 	// IP = Input Parameter
	Real OP_SludgeFeed, OP_SolidsLActual, OP_HyLoadingActual;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Clarifier") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_SolidsLAvg		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_FeedSolidConc	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SolidCapture		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_NumOfClarifier	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_DiaOfClarifier	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_SWD				= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_TgtSL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_TgtHyL			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_SludgeFeed = IP_SolidsLAvg*IP_SolidCapture/100/(IP_FeedSolidConc/100)/8.34;
	OP_SolidsLActual = IP_SolidsLAvg/(3.14*IP_DiaOfClarifier^2/4)*IP_NumOfClarifier;
	OP_HyLoadingActual = OP_SludgeFeed/(3.14*IP_DiaOfClarifier^2/4);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_SludgeFeed, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_SolidsLActual, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_HyLoadingActual, 5);
}

Procedure Module_DryingBeds()
{
																									**## 2.Change Parameter Name ##**
	Real IP_SolidsLAvg, IP_NumOfBed, IP_L, IP_W, IP_DsgnSfcLR; 	// IP = Input Parameter
	Real OP_Areattl, OP_SolidsLActual, OP_NumOfBeds;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Drying Beds") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_SolidsLAvg	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfBed		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_L			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_W			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_DsgnSfcLR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Areattl = IP_L*IP_W*0.9683*IP_NumOfBed/43560;
	OP_SolidsLActual = IP_SolidsLAvg/(OP_Areattl*43560)*365;
	OP_NumOfBeds = IP_SolidsLAvg/(IP_DsgnSfcLR/365)/(IP_L*IP_W*0.9683);
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_Areattl, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_SolidsLActual, 5);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumOfBeds, 5);
}

Procedure Module_ExcavationVolume()
{
																									**## 2.Change Parameter Name ##**
	Real IP_L, IP_AL, IP_W, IP_AW, IP_D, IP_AD, IP_F; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Excavation Volume") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_L	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_AL	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_AW	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_D	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_AD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_F	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = (IP_L+IP_AL)*(IP_W+IP_AW)*(IP_D+IP_AD)*IP_F/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_ConcreteVolume_SlabOnGrade()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_W, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Slab on Grade") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_W*IP_T/12)/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_ConcreteVolume_Wall()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_H, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Wall") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_H		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_H*IP_T/12)/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_ConcreteVolume_ElevatedSlab()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_W, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Elevated Slab") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_W		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_W*IP_T/12)/27;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_AreaOfCircle()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Dia; 	// IP = Input Parameter
	Real OP_Area;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Area of Circle") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Dia	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Area = 3.14*IP_Dia^2/4;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+1][7] = fixdecimal(OP_Area, 5);

}

Procedure Module_PerimeterOfCircle()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Dia; 	// IP = Input Parameter
	Real OP_Length;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Perimeter of Circle") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Dia	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Length = 3.14*IP_Dia;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+1][7] = fixdecimal(OP_Length, 5);
}

Procedure Module_ConcreteVolume_CircularSlabOnGrade()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_Area, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Circular Slab on Grade") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Area		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_Area*IP_T/12)/27;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_ConcreteVolume_CircularWall()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_L, IP_H, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Circular Slab on Grade") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_L		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_H		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_L*IP_H*IP_T/12)/27;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_ConcreteVolume_CircularElevatedSlab()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Number, IP_Area, IP_T; 	// IP = Input Parameter
	Real OP_Vol;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Concrete Volume - Circular Elevated Slab") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Number	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Area		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_T		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vol = IP_Number*(IP_Area*IP_T/12)/27;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Vol, 5);
}

Procedure Module_Empirical_Exponential()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Exponential") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*Exp(IP_X*IP_b);
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Y, 5);
}

Procedure Module_Empirical_Linear()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Linear") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*IP_X+IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Y, 5);
}

Procedure Module_Empirical_Logrithmatic_e()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Logrithmatic (e)") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*LOG(IP_X)+IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Y, 5);
}

Procedure Module_Empirical_Logrithmatic_10()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Logrithmatic (10)") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*LOG10(IP_X)+IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Y, 5);
}

Procedure Module_Empirical_Polymonial()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b, IP_c, IP_d, IP_e, IP_f; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Polymonial") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_c	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_d	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_e	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_f	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*IP_X^5+IP_b*IP_X^4+IP_c*IP_X^3+IP_d*IP_X^2+IP_e*IP_X^1+IP_f;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_Y, 5);
}

Procedure Module_Empirical_Power()
{
																									**## 2.Change Parameter Name ##**
	Real IP_X, IP_a, IP_b; 	// IP = Input Parameter
	Real OP_Y;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Power") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_X	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Y = IP_a*IP_X^IP_b;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_Y, 5);
}

Procedure Module_Empirical_DBP()
{
																									**## 2.Change Parameter Name ##**
	Real IP_pH, IP_TOC, IP_SUVA, IP_Cl2, IP_Time, IP_Temp, IP_a, IP_b, IP_c, IP_d, IP_e, IP_f, IP_g; 	// IP = Input Parameter
	Real OP_THM;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Empirical Relationship - Power") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_pH	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_TOC	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SUVA	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Cl2	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Time	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_Temp	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_a	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	IP_b	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	IP_c	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	IP_d	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+9][7]);
	IP_e	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+10][7]);
	IP_f	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+11][7]);
	IP_g	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+12][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_THM = IP_a*IP_pH^IP_b*IP_TOC^IP_c*IP_SUVA^IP_d*IP_Cl2^IP_e*IP_Time^IP_f*IP_Temp^IP_g;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+13][7] = fixdecimal(OP_THM, 5);
}

Procedure Module_Ratio() // Use Naming Convention: Module_CC000XXXXXX... CC = Category Abbreviation, 000 = Numeric ID, XXXX... are descriptive name of the moduel.
{
																									**## 2.Change Parameter Name ##**
	Real IP_Numerator, IP_Denominator; 	// IP = Input Parameter
	Real OP_Ratio;			 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Ratio") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Numerator	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Denominator	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Ratio = IP_Numerator/IP_Denominator;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+2][7] = fixdecimal(OP_Ratio, 5);
}

Procedure Module_RemovalEff() // Use Naming Convention: Module_CC000XXXXXX... CC = Category Abbreviation, 000 = Numeric ID, XXXX... are descriptive name of the moduel.
{
																									**## 2.Change Parameter Name ##**
	Real IP_InfCon, IP_EffCon; 	// IP = Input Parameter
	Real OP_RemovalEff;			 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Removal Efficiency") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_InfCon	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_EffCon	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_RemovalEff = (IP_InfCon-IP_EffCon)/IP_InfCon * 100;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+2][7] = fixdecimal(OP_RemovalEff, 2);
}

Procedure Module_HLR()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTank, IP_NumofStandby, IP_Width, IP_SWD, IP_TgtHyL, IP_LengthActual, IP_FB; 	// IP = Input Parameter
	Real OP_LengthEach, OP_LengthOvl, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains, OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "HLR") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_Width		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtHyL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_LengthActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_FB =StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);

	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_LengthEach = IP_Capacity * 1000000 / IP_TgtHyL / IP_Width / IP_NumOfTank;
	OP_TotalNumofTrains = IP_NumofTank + IP_NumofStandby;
	OP_LengthOvl = OP_LengthEach * OP_TotalNumofTrains;
	OP_HyLoadingActualAll = IP_Capacity * 1000000 / IP_Width / IP_LengthActual ;
	OP_HyLoadingActualDuty = IP_Capacity * 1000000 / IP_Width / IP_LengthActual/(IP_NumOfTank/OP_TotalNumofTrains);
	OP_TotalDepth = IP_SWD + IP_FB;
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_LengthEach, 2);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_LengthOvl, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = fixdecimal(OP_TotalNumofTrains, 2);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = fixdecimal(OP_TotalDepth, 2);
}

Procedure Module_SLR()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTank, IP_NumofStandby, IP_Width, IP_SWD, IP_TgtSldL, IP_LengthActual, IP_TSSCon, IP_FB; 	// IP = Input Parameter
	Real OP_TSSLoad, OP_LengthEach, OP_LengthOvl, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains,OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "SLR") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTank	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_Width		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtSldL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_LengthActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_TSSCon	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
		IP_FB	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_TSSLoad = IP_TSSCon * IP_Capacity * 8.34;
	OP_LengthEach = OP_TSSLoad / IP_TgtSldL / IP_Width / IP_NumOfTank;
	OP_TotalNumofTrains = IP_NumofTank + IP_NumofStandby;
	OP_LengthOvl = OP_LengthEach * OP_TotalNumofTrains;
	OP_HyLoadingActualAll = OP_TSSLoad / IP_Width / IP_LengthActual ;
	OP_HyLoadingActualDuty = OP_TSSLoad / IP_Width / IP_LengthActual/(IP_NumOfTank/OP_TotalNumofTrains);
	OP_TotalDepth = IP_FB + IP_SWD;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_TSSLoad, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_LengthEach, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_LengthOvl, 2);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = fixdecimal(OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = fixdecimal(OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+14][7] = fixdecimal(OP_TotalNumofTrains, 2);
	Module_Input_tbl[ModuleStartRowIndex+15][7] = fixdecimal(OP_TotalDepth, 2);
}

Procedure Module_DesignHRTLtoWCircular() // New Module by Chiu
{
	Real IP_Flow, IP_HRT, IP_SWD, IP_Dia, IP_NumOfTrainD, IP_NumOfTrainR, IP_FB;//IP_LtoW, CHE edited
	Real OP_NumOfTrainTtl, OP_DepthTtl, OP_VolumeTtl, OP_PerimeterEach, OP_PerimeterOvl; // Chiu Edited
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Design HRT to Volume - Circular")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names

	IP_NumOfTrainD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_NumOfTrainR	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	//IP_LtoW			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]); CHE, the following moved up 1
	IP_Dia			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_HRT			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_Flow			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	
	// Module Equation
	OP_NumOfTrainTtl = IP_NumOfTrainD + IP_NumOfTrainR;
	OP_DepthTtl = IP_SWD + IP_FB;
	OP_PerimeterEach = sqrt((IP_HRT*IP_Flow/24/IP_SWD/(3.14/4)/IP_NumOfTrainD*10^6/7.48));//CHE
	OP_PerimeterOvl = OP_PerimeterEach * OP_NumofTrainTtl;
	OP_VolumeTtl = IP_SWD*(3.14*IP_Dia^2/4)*7.48/10^6*OP_NumOfTrainTtl; // Chiu
	
	// Link Module results to output parameters
 	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_NumOfTrainTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_DepthTtl, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_PerimeterOvl, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_PerimeterEach, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_VolumeTtl, 5);
}

Procedure Module_ActualHRT_AllinServiceCircular() //Chiu Edited 
{
	Real IP_Flow, IP_Dia, IP_SWD, IP_NumofTrainsTotal; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlPerimeter; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (All in service) - Circular")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Dia= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
//	IP_ActLengthEach= 		StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofTrainsTotal = 	StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation
	OP_ActVol = IP_SWD * (3.14*IP_Dia^2/4) * IP_NumofTrainsTotal *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlPerimeter = (3.14*IP_Dia) * IP_NumofTrainsTotal;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_OvlPerimeter, 5);
}

Procedure Module_ActualHRT_DutyinServiceCircular() //Chiu Added
{
	Real IP_Flow, IP_Dia, IP_SWD, IP_NumofDutyTrains; 	// IP = Input Parameter
	Real OP_ActVol, OP_HRT, OP_OvlPerimeterD; 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Actual HRT (Duty in service) - Circular")
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names
	IP_Flow	= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Dia= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_SWD= 				StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
//	IP_ActLengthEach= 		StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_NumofDutyTrains = 	StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	
	// Module Equation
	OP_ActVol = IP_SWD * (3.14*IP_Dia^2/4) * IP_NumofDutyTrains *7.48 / 1000000;
	OP_HRT = OP_ActVol / IP_Flow *24;
	OP_OvlPerimeterD = (3.14*IP_Dia) * IP_NumofDutyTrains;
	
	// Link Module results to output parameters
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_ActVol, 5);
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_HRT, 5);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_OvlPerimeterD, 5);
}


Procedure Module_HLRCircular()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTankD, IP_NumofStandby, IP_DiaActual, IP_SWD, IP_TgtHyL, IP_FB; 	// IP = Input Parameter
	Real OP_Diameter, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains, OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "HLR - Circular") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTankD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_DiaActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtHyL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_FB 			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Diameter = sqrt(IP_Capacity * 1000000 / IP_TgtHyL / (3.14/4) / IP_NumOfTankD);
	OP_TotalNumofTrains = IP_NumofTankD + IP_NumofStandby;
	OP_HyLoadingActualAll = IP_Capacity * 1000000 / (3.14*IP_DiaActual^2/4) / OP_TotalNumofTrains;
	OP_HyLoadingActualDuty = IP_Capacity * 1000000 / (3.14*IP_DiaActual^2/4)/(IP_NumOfTankD);
	OP_TotalDepth = IP_SWD + IP_FB;
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_Diameter, 0);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_TotalNumofTrains, 0);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_TotalDepth, 0);
}

Procedure Module_SLRCircular()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Capacity, IP_NumOfTankD, IP_NumofStandby, IP_DiaActual, IP_SWD, IP_TgtSldL, IP_TSSCon, IP_FB; 	// IP = Input Parameter
	Real OP_Diameter, OP_TSSLoad, OP_HyLoadingActualAll,OP_HyLoadingActualDuty,OP_TotalNumofTrains,OP_TotalDepth;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "SLR - Circular") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Capacity		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_NumOfTankD	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_NumOfStandby	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_DiaActual	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_SWD			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_TgtSldL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_TSSCon		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_FB			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_TSSLoad = IP_TSSCon * IP_Capacity * 8.34;
	OP_Diameter = sqrt(OP_TSSLoad / IP_TgtSldL / (3.14/4) / IP_NumOfTankD);
	OP_TotalNumofTrains = IP_NumofTankD + IP_NumofStandby;
	OP_HyLoadingActualAll = OP_TSSLoad / (3.14*IP_DiaActual^2/4)/OP_TotalNumofTrains;
	OP_HyLoadingActualDuty = OP_TSSLoad / (3.14*IP_DiaActual^2/4) / (IP_NumOfTankD);
	OP_TotalDepth = IP_FB + IP_SWD;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
//	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_TSSLoad, 2);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_Diameter, 0);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_HyLoadingActualAll, 2);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_HyLoadingActualDuty, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_TotalNumofTrains, 0);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = fixdecimal(OP_TotalDepth, 0);
}


Procedure Module_ABasinV()//CHE Added)
{
																									**## 2.Change Parameter Name ##**
	Real IP_Loading, IP_Ynet, IP_SRT, IP_MLSS, IP_NumOfTankD, IP_NumStandby, IP_Width, IP_SWD, IP_FB, IP_ActLengthO; 	// IP = Input Parameter
	Real OP_Vm3, OP_Vmg,OP_Vcf,OP_TotalNumofTrains, OP_TotalDepth, OP_CalLengthE,OP_CalLengthO, OP_ActVcfO;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Aeration Basin Volume") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_Loading		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_Ynet	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
		IP_SRT	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
		IP_MLSS	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
		IP_NumOfTankD		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
		IP_NumStandby		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
		IP_Width 			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
		IP_SWD 			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);	
		IP_FB 			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
		IP_ActLengthO	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+9][7]);
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Vm3 = IP_Loading * 0.453515 * IP_SRT * IP_Ynet / IP_MLSS * 1000;
	OP_Vmg = OP_Vm3 * 264.1721 / 1000000;
	OP_Vcf = OP_Vm3 * 35.31467;
	OP_TotalNumofTrains = IP_NumofTankD + IP_NumStandby;
	OP_TotalDepth = IP_SWD + IP_FB;
	OP_CalLengthE = OP_Vcf / IP_Width / IP_SWD / IP_NumofTankD;
	OP_CalLengthO = OP_CalLengthE * OP_TotalNumofTrains;
	OP_ActVcfO = IP_ActLengthO * IP_Width * IP_SWD;
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_Vm3, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_Vmg, 2);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = fixdecimal(OP_Vcf, 2);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = fixdecimal(OP_TotalNumofTrains, 0);
	Module_Input_tbl[ModuleStartRowIndex+14][7] = fixdecimal(OP_TotalDepth, 0);
	Module_Input_tbl[ModuleStartRowIndex+15][7] = fixdecimal(OP_CalLengthE, 0);
	Module_Input_tbl[ModuleStartRowIndex+16][7] = fixdecimal(OP_CalLengthO, 0);
	Module_Input_tbl[ModuleStartRowIndex+17][7] = fixdecimal(OP_ActVcfO, 2);
}

Procedure Module_ISV()//CHE Added)
{
	String 	IP_EqtTyp;																						**## 2.Change Parameter Name ##**
	Real IP_SVI,  IP_MLSS; 	// IP = Input Parameter
	Real OP_V0, OP_Xm,OP_ISV,OP_HOR, OP_V0Xm;			 									// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Secondary Clarifier ISV") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
		IP_SVI		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
		IP_EqtTyp	= Module_Input_tbl[ModuleStartRowIndex+1][7];
		IP_MLSS	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
				
	// Module Equation 	                                                                          **## 5.Change Module Equation ##**     
	
	if(IP_EqtTyp == "Pitman" OR IP_EqtTyp == "P")                                          
	{ 
	OP_V0Xm = 0.2228*1000000*EXP(-0.0107*IP_SVI);
	OP_Xm = 1000000/((-393*(LOG10(OP_V0Xm)-6)-96));    // BioTran Row 3726
	OP_V0 = OP_V0Xm / OP_Xm;
	}
	
	if(IP_EqtTyp == "Daigger" OR IP_EqtTyp == "D")                                          
	{ 
	OP_Xm = 2;//1000/(0.165+0.001586*IP_SVI);
	OP_V0 = 21.3;
	}
	
	OP_ISV = OP_V0 * EXP(-IP_MLSS/OP_Xm);
	OP_HOR = OP_ISV * 7.48 * 24;
	
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+3][7] = fixdecimal(OP_V0, 1);
	Module_Input_tbl[ModuleStartRowIndex+4][7] = fixdecimal(OP_Xm, 0);
	Module_Input_tbl[ModuleStartRowIndex+5][7] = fixdecimal(OP_ISV, 2);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = fixdecimal(OP_HOR, 0);

}


// Add Module Step 2: Copy the last procedure above to before this line. 

Procedure Module_pH()//Chiu Added 11/19/2014
{
																									**## 2.Change Parameter Name ##**
	Real IP_TDS, IP_Temp, IP_pH, IP_Alk, IP_Ca, IP_Cl, IP_SO4; 	// IP = Input Parameter
	Real OP_pH, OP_CCPP, OP_LSI, OP_Ca, OP_Alk, OP_Cl, OP_SO4;			 									// OP = Output Parameter
	Integer pHCalculatorBlockNumber;
	Integer DBTableIndex_ChemicalDB;
	Integer ChemicalIndex;
	Integer NumOfBlocks;

	
	DBTableIndex_ChemicalDB = DBTableGetIndex(DBIndex, "Chemicals_DB");
	pHIndex ++;
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "pH Calculator") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_TDS	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Temp	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	IP_pH	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	IP_Alk	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	IP_Ca	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	IP_Cl	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	IP_SO4	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);

	// Module Equation 																				**## 5.Change Module Equation ##**
	NumOfBlocks = NumBlocks();
	
	for (k = 0; k < NumOfBlocks; k++)
	{
		if (BlockName(k) == "pH Calculator") pHCalculatorBlockNumber = k;
	}
	
	*** Chemical Input ***
	for (k = 0 ; k < GetDialogItemInfo(pHCalculatorBlockNumber, "ChemicalAddition_tbl", 5); k++)
	{
		for (j = 0 ; j < GetDialogItemInfo(pHCalculatorBlockNumber, "ChemicalAddition_tbl", 6); j++)
		{
			SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_tbl", BLANK, k, j);
		}
	}
	
	ChemicalIndex = 0;
	for (k = 0; k < GetDimension(ChemicalCost_tbl); k++)
	{
		for (j = 1; j < DBRecordsGetNum(DBIndex, DBTableIndex_ChemicalDB); j++)
		{
			if (ChemicalCost_tbl[k][0] == DBDataGetAsString(DBIndex, DBTableIndex_ChemicalDB, 1, j))
			{
				SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_tbl", ChemicalCost_tbl[k][0], ChemicalIndex, 0);
				SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_tbl", ChemicalCost_tbl[k][1], ChemicalIndex, 1);
				ChemicalIndex++;
			}
		}
	}
	
	*** WQ input ***
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "ChemicalAddition_rbtn",	TRUE, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_TDS",	IP_TDS, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_T",	IP_Temp, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_pH",	IP_pH, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_ALK",	IP_Alk, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_Ca",	IP_Ca, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_Cl",	IP_Cl, 0, 0);
	SetDialogVariableNoMsg(pHCalculatorBlockNumber, "measured_SO4",	IP_SO4, 0, 0);
	
	*** Retrive result back ***
	OP_pH 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "pH_Final_diag", 0, 0));
	OP_CCPP 	= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "CCPP_diag", 0, 0));
	OP_LSI 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "LSI_diag", 0, 0));
	OP_Ca 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Ca_Final_diag", 0, 0));
	OP_Alk 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Alk_Final_diag", 0, 0));
	OP_Cl 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Cl_Final_diag", 0, 0));
	OP_SO4 		= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "SO4_Final_diag", 0, 0));
	OP_Acidity	= StrToReal(GetDialogVariable(pHCalculatorBlockNumber, "Acidity_Final_diag", 0, 0));
	
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+7][7] = fixdecimal(OP_pH, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = fixdecimal(OP_CCPP, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = fixdecimal(OP_LSI, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = fixdecimal(OP_Ca, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = fixdecimal(OP_Alk, 5);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = fixdecimal(OP_Cl, 5);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = fixdecimal(OP_SO4, 5);
}

Procedure Module_Subtraction()
{
																									**## 2.Change Parameter Name ##**
	Real IP_Minuend, IP_Subtrahend; 		// IP = Input Parameter
	Real OP_Difference;			 			// OP = Output Parameter

	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ActivatedModule) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								**## 3.Change Module Name ##**
		if (Module_Input_tbl[j][0] == ActivatedModule AND Module_Input_tbl[j][1] == "Subtraction") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	// Link values to parameter Names 																**## 4.Link Parameter Value to Given Name ##**
	IP_Minuend	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	IP_Subtrahend	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	
	// Module Equation 																				**## 5.Change Module Equation ##**
	OP_Difference = IP_Minuend-IP_Subtrahend;
		
	// Link Module results to output parameters 													**## 6.Link Result to Output Parameters ##**
	Module_Input_tbl[ModuleStartRowIndex+2][7] = fixdecimal(OP_Difference, 5);	
}