real RoundDec(String ls_RoundMode, real lr_UglyNum,real lr_NumDecimal);

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
	if (NoValue(OP_HPEach)) OP_HPEach = 0;
	if (OP_HPEach == 0) OP_Energy = 0;
	OP_NumofPMP = IP_Num_Pump_D + IP_Num_Pump_S;
	
	// Link Module results to output parameters

	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_Energy, 5);
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_HPEach, 5);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_NumofPMP, 5);
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

	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_RunTimeFactor, 5);
	
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

	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_RunTimeFactor, 1);
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

	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_Energy, 1);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_HPActEach, 1);
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumofUnitsTotal, 1);
}