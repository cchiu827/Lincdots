real RoundDec(String ls_RoundMode, real lr_UglyNum,real lr_NumDecimal);

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

	Module_Input_tbl[ModuleStartRowIndex+2][7] = RoundDec(R, OP_Ratio, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_BODLoading, 5);
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_BODLoadingperV, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_Vol, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_SolidProduction, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+7][7] = RoundDec(R, OP_NumOfUnitttl, 5);
	Module_Input_tbl[ModuleStartRowIndex+8][7] = RoundDec(R, OP_BHPperUnit, 5);
	Module_Input_tbl[ModuleStartRowIndex+9][7] = RoundDec(R, OP_PowerConsumption, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_NO3Nformed, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_ALKreq, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_O2req, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_O2req, 5);
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
	Module_Input_tbl[ModuleStartRowIndex+10][7] = RoundDec(R, OP_Vm3, 2);
	Module_Input_tbl[ModuleStartRowIndex+11][7] = RoundDec(R, OP_Vmg, 2);
	Module_Input_tbl[ModuleStartRowIndex+12][7] = RoundDec(R, OP_Vcf, 2);
	Module_Input_tbl[ModuleStartRowIndex+13][7] = RoundDec(R, OP_TotalNumofTrains, 0);
	Module_Input_tbl[ModuleStartRowIndex+14][7] = RoundDec(R, OP_TotalDepth, 0);
	Module_Input_tbl[ModuleStartRowIndex+15][7] = RoundDec(R, OP_CalLengthE, 0);
	Module_Input_tbl[ModuleStartRowIndex+16][7] = RoundDec(R, OP_CalLengthO, 0);
	Module_Input_tbl[ModuleStartRowIndex+17][7] = RoundDec(R, OP_ActVcfO, 2);
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
	Module_Input_tbl[ModuleStartRowIndex+3][7] = RoundDec(R, OP_V0, 1);
	Module_Input_tbl[ModuleStartRowIndex+4][7] = RoundDec(R, OP_Xm, 0);
	Module_Input_tbl[ModuleStartRowIndex+5][7] = RoundDec(R, OP_ISV, 2);
	Module_Input_tbl[ModuleStartRowIndex+6][7] = RoundDec(R, OP_HOR, 0);

}