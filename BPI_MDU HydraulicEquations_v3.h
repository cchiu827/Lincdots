Procedure Module_OpenChannel(String ls_ModuleID);

Procedure Module_HydraulicEq(Integer li_RowIdx)
{
	String ls_ModuleID;
	
	if (Module_tbl[li_RowIdx][2] == "Open Channel Flow")        
	{
		ls_ModuleID = Module_tbl[li_RowIdx][0];	Module_OpenChannel(ls_ModuleID);
	}
}

Procedure Module_OpenChannel(String ls_ModuleID)
{
	*** User input and output parameters
	Real Flow, Channel_Shape, Down_WSE, Invert_EL, Chan_Dim_1, Chan_Dim_2, Chan_Dim_3, Chan_Length, Perc_Slope, Manning_Coef, Downstream_EGL, Downstream_HGL, Tolerance;
	Real Upstream_EGL, Upstream_HGL, Energy_Loss;
	
	*** other intermediate variables
	real flow_cfs;
	real average_depth;
	real average_depth2;
	real delta_depth;
	real delta_vel;
	real hydraulic_rad;
	real area_in_flow;
	real wetted_peri;
	real phi_rad;
	real average_channel_velocity;
	real upstream_channel_velocity;
	real upstream_channel_velocity2;	
	
	******************************************************************************************************************************
	******************* Identify Activated module parameters *********************************************************************
	NumberOfRows_ModuleInputTbl = GetDimension(Module_Input_tbl);
	
	ModuleStartRowIndex = 0;
	while (Module_Input_tbl[ModuleStartRowIndex][0] != ls_ModuleID) ModuleStartRowIndex++; // find activated module start row
	
	ModuleEndRowIndex = 0;
	for (j = 0; j < NumberOfRows_ModuleInputTbl; j++)
	{																								
		if (Module_Input_tbl[j][0] == ls_ModuleID AND Module_Input_tbl[j][1] == "Empirical Relationship - DBP") 	
			ModuleEndRowIndex++;
	}
	ModuleEndRowIndex = ModuleStartRowIndex+ModuleEndRowIndex-1; // find activated module end row
	******************************************************************************************************************************
	
	*** Link values to parameter Names 																
	Flow 			= StrToReal(Module_Input_tbl[ModuleStartRowIndex+0][7]);
	Channel_Shape	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+1][7]);
	Down_WSE		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+2][7]);
	Invert_EL		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+3][7]);
	Chan_Dim_1		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+4][7]);
	Chan_Dim_2		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+5][7]);
	Chan_Dim_3		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+6][7]);
	Chan_Length		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+7][7]);
	Perc_Slope		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+8][7]);
	Manning_Coef	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+9][7]);
	Downstream_EGL	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+10][7]);
	Downstream_HGL	= StrToReal(Module_Input_tbl[ModuleStartRowIndex+11][7]);
	Tolerance		= StrToReal(Module_Input_tbl[ModuleStartRowIndex+12][7]);
	
	*** Module Equation
	flow_cfs = flow*1.547;
	//Set the initial states of required numbers
	delta_depth=0;  //Clear variable to 0
	energy_loss = 0;    //Assumption to get the calcs started
	average_depth = Down_WSE - Invert_EL;    //Assumption to get the calcs started

	do
	{
		Switch (Channel_Shape)
			{
			Case 0: //Trapezoidal
				if (Chan_Dim_3>0)
				{
					phi_rad = 2*pi*((90-Chan_Dim_3)/360);
					Chan_Dim_2 = Chan_Dim_1 + 2 * average_depth * tan(phi_rad);
				}
				area_in_flow = average_depth*(Chan_Dim_2+Chan_Dim_1)/2;
				wetted_peri = 2*Chan_Dim_1*SQRT((average_depth^2)+((Chan_Dim_2-Chan_Dim_1)/2)^2);
				break;
			Case 1:  //Circular
				Chan_Dim_2 = Chan_Dim_1/2;
				phi_rad = 2*acos((Chan_Dim_2-average_depth)/Chan_Dim_2);
				area_in_flow = (Chan_Dim_2^2)*(phi_rad-sin(phi_rad))/2;
				wetted_peri = Chan_Dim_2*phi_rad;
				break;
			Case 2:  //Triangular
				phi_rad = 2*pi*(Chan_Dim_3/2)/360;
				area_in_flow = sqrt(3)/4*(2*average_depth*tan(phi_rad))^2;
				wetted_peri = 2*average_depth/cos(phi_rad);
				break;
			Case 3:  //Rectangular
				area_in_flow = average_depth*Chan_Dim_1;
				wetted_peri = 2*average_depth+Chan_Dim_1;
				break;
			}
		Hydraulic_Rad = area_in_flow/wetted_peri;
		average_channel_velocity = flow_cfs/area_in_flow;
		
		energy_loss = Chan_Length*Manning_Coef^2*average_channel_velocity^2/2.21/(hydraulic_rad^(4/3));
		upstream_EGL = downstream_EGL + energy_loss;
		
		upstream_channel_velocity = average_channel_velocity;  //Assumption to get the calcs started
		do
		{
			upstream_HGL = upstream_EGL - upstream_channel_velocity^2/2/32.2;
			//average_depth = (upstream_HGL-(Invert_EL+Perc_Slope*Chan_Length))
			Switch (Channel_Shape)
				{
				Case 0: //Trapezoidal
					if (Chan_Dim_3>0)
					{
						phi_rad = 2*pi*((90-Chan_Dim_3)/360);
						Chan_Dim_2 = Chan_Dim_1 + 2*(upstream_HGL-(Invert_EL+Perc_Slope*Chan_Length))*tan(phi_rad);
					}
					area_in_flow = (upstream_HGL-(Invert_EL+Perc_Slope*Chan_Length))*(Chan_Dim_2+Chan_Dim_1)/2;
					break;
				Case 1:  //Circular
					Chan_Dim_2 = Chan_Dim_1/2;
					phi_rad = 2*acos((Chan_Dim_2-(upstream_HGL-(Invert_EL+Perc_Slope*Chan_Length)))/Chan_Dim_2);
					area_in_flow = (Chan_Dim_2^2)*(phi_rad-sin(phi_rad))/2;
					break;
				Case 2:  //Triangular
					phi_rad = 2*pi*(Chan_Dim_3/2)/360;
					area_in_flow = sqrt(3)/4*(2*(upstream_HGL-(Invert_EL+Perc_Slope*Chan_Length))*tan(phi_rad))^2;
					break;
				Case 3:  //Rectangular
					area_in_flow = (upstream_HGL-(Invert_EL+Perc_Slope*Chan_Length))*Chan_Dim_1;
					break;
				}
			
			upstream_channel_velocity2 = flow_cfs/area_in_flow;
			delta_vel = upstream_channel_velocity2-upstream_channel_velocity;
			upstream_channel_velocity = upstream_channel_velocity2;
			
		}
		while (delta_vel>Tolerance);
		
		average_depth2=(Down_WSE+upstream_HGL)/2-Invert_EL;
		
		delta_depth = average_depth2 - average_depth;
		average_depth = average_depth2;

	}
	while (delta_depth>Tolerance);

	//Logic Sequence:
	//Step 1: Assume average depth = Down_WSE - Invert_EL.
	//Step 2: Calculate hydraulic radius based on Step 1
	//Step 3: Calculate average channel velocity from flow and area in flow.
	//Step 4: Assume upstream velocity = average channel velocity
	//Step 5: Calculate upstream water depth, associated area in flow
		//and the resulting upstream velocity.
	//Step 6: Assume headloss = 0
	//Step 7: Calculate headloss by channel length * Manning^2 * average
		//channel velocity^2/2.21/(hydraulic radius^4/3)
	//Step 8: Calculate upstream EGL by Downstream EGL+headloss
	//Step 9: Calculate upstream HGL by Upstream EGL - Upstream Channel
		//Velocity^2/2/32.2
	//Step 10: Calculate average depth by (Down_WSE+Upstream HGL)/2-
		//Invert_EL
	//Step 11: If calculated average depth - assumed average depth >
		//tolerance loop until they converge.
	
	*** Link Module results to output parameters 													
	Module_Input_tbl[ModuleStartRowIndex+13][7] = RoundDec(R, Upstream_EGL, 5);
	Module_Input_tbl[ModuleStartRowIndex+14][7] = RoundDec(R, Upstream_HGL, 5);
	Module_Input_tbl[ModuleStartRowIndex+15][7] = RoundDec(R, Energy_Loss, 5);
}