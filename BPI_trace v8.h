******************************************************************
**	Trace v7.h Include											**
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


// this section is for tracing connector values
#ifdef TraceValues

Procedure TCE_TraceConnectors()
{
integer numCons;
integer me;
integer i;
String ConLabel;

	if( sysGlobal2 != 0.0 )														// do this only if tracing is turned on
		{
		me = myBlockNumber();
	
		NumCons = GetNumCons(me);
	
		fileWrite(sysGlobal2,"### calculation at "+BlockName(me)+" number "+me+".  CurrentTime:"+currentTime+".","",True);

		for(i=0;i<NumCons;i++)
			{
			FileWrite(sysGlobal2, "   "+GetConName(me, i)+" = "+GetIndexedConValue(i), FALSE, TRUE);			// write out the table value
			}
		}
	
}

#endif
	
// this section is for tracing dialogs

#ifdef TraceDialogs
	
	
	
	Procedure TCE_OnEndsim()														// called at the end of all simulation runs to dispose of the array storing the trace dialogs
	{
		if(currentSim == numSims - 1)
			DisposeArray(TraceDialogs);
	
	}
	
	
		Procedure TCE_ExtractDIDescription(String31 Dialog, integer me, integer Which)
		{
		integer _prm_pos;
		string31 DialogText;
		
				_prm_pos = StrFind(Dialog, "_prm", FALSE, FALSE);					// get the position of the "_prm" in the dialog name
				if(_prm_pos >= 0)													// if "_prm" is in the dialog name											// if "_prm" is in the dialog name
					{
					Dialog = StrPart(Dialog, 0, _prm_pos);							// get the dialog name withouth "_prm"
					DialogText = GetDialogVariable(me, Dialog+"_lbl", 0, 0);		// Attach "_lbl" to the dialog name	and get the value of that dialog. This is probably the description for the first dialog
					if(DialogText != "")											// if the value of this dialog is not blank, it is the description of the dialog parameter
						{
						TraceDialogs[which][1] = DialogText;						// get the description
						}
					else
						TraceDialogs[which][1] = Dialog;							// description was blank so use the dialog name
					}
				else
					TraceDialogs[which][1] = Dialog;								// no "_prm" use the dialog name
		}
	
	
	
		Procedure TCE_SetTraceDialogs(String TraceThese)
		{
		integer i;
		integer semi_pos;
		String temp;
		string31 Dialog;
		integer me;
		
			if( sysGlobal2 != 0.0 )														// do this only if tracing is turned on
				{
		
				me = MyBlockNumber();													// get the block number
				
				if(TraceThese != "")													// are there any dialog items to trace
					{
					MakeArray(TraceDialogs,100);										// there should not be more than 100 items to trace so initially set the array to a big one
					i = 0;
					temp = TraceThese;
					while(StrLen(temp) > 0 && i < 100)									// loop through all of the dialog items to trace
						{
						semi_pos = StrFind(temp, ";", FALSE, FALSE);					// find the semicolon
						if(semi_pos >= 0)												// a semicolon was found
							{
							Dialog = StrPart(temp, 0, Semi_pos);						// get the dialog variable name
							TraceDialogs[i][0] = Dialog;								// save the dialog variable name for tracing
							if(GetDialogItemInfo(me, Dialog, 4) == DI_PARAMETER)
								{
								TCE_ExtractDIDescription(Dialog,me,i);
								}
							temp = StrPart(temp, Semi_pos + 1, strlen(temp) - semi_pos);// remove this dialog name from the list of dialog names
							}
						else if(strlen(temp) > 0)										// no ; was found, but there is a dialog name, must be the last dialog name
							{
							Dialog = temp;
							TraceDialogs[i][0] = Dialog;								// save the dialog name
							if(GetDialogItemInfo(me, Dialog, 4) == DI_PARAMETER)
								{
								TCE_ExtractDIDescription(Dialog,me,i);
								}
							temp = "";													// clear out the temp string variable, this will end the loop
							}
						i++;
						}
					MakeArray(TraceDialogs,i);
					}
				}
			else
				DisposeArray(TraceDialogs);
			
		}
		
		
		Procedure TCE_TraceDialogs(integer me)											// writes out the dialogs that are traced
		{
		integer numDialogs;
		integer i,row,col;
		integer numrows, numcols;
		integer DI_type;
		String OutputText;
		
			NumDialogs = GetDimension(TraceDialogs);									// get the number of dialogs
			for(i=0;i<NumDialogs;i++)													// write them all out
				{
				DI_type = GetDialogItemInfo(me, TraceDialogs[i][0], 4);					// if this is a numerical parameter
				if(DI_type == DI_PARAMETER)
					{
					fileWrite(sysGlobal2,"     "+TraceDialogs[i][1]+" "+GetDialogVariable(me, TraceDialogs[i][0], 0, 0),"",True);		// write out the parameter and the description
					}
				else if(DI_type == DI_DATA_TABLE || DI_type == DI_TEXT_TABLE)			// if this is a table
					{
					NumRows = GetDialogItemInfo(me, TraceDialogs[i][0], 5)-1;				// get the number of rows in the table
					NumCols = GetDialogItemInfo(me, TraceDialogs[i][0], 6)-1;				// get the number of columns in the table
					for(col = 0; col < NumCols; col++)									// go through all of the columns and write out the table lables
						{
						OutputText = GetDialogItemLabel(me, TraceDialogs[i][0], col);
						FileWrite(sysGlobal2, OutputText, FALSE, FALSE);
						}
					FileWrite(sysGlobal2, "", FALSE, TRUE);								// write the end of line character
					for(row = 0;row < NumRows;row++)									// go through all of the rows
						{
						for(col = 0; col < NumCols; col++)								// go through all of the columns
							{
							OutputText = GetDialogVariable(me, TraceDialogs[i][0], row, col);	// get the value of the table
							FileWrite(sysGlobal2, OutputText, FALSE, FALSE);			// write out the table value
							}
						FileWrite(sysGlobal2, "", FALSE, TRUE);
						}
						
					}
				}
		}
	#endif
	
#ifdef ITEMTRACE

	Procedure TCE_TraceItemIn(integer ItemIndex, integer WhichInput)				// traces items as they arrive to a block
	{
	integer me;
	
		// sysGlobal2 is the file reference number for the Debug Trace
		if( sysGlobal2 != 0.0 )
			{
			me = MyBlockNumber();
	// template for trace:       |BLOCK NAME *****************|block number |BLOCK NUMBER*******|.| Current Time:|CURRENTTIME  |.|
			fileWrite(sysGlobal2,"--> Item ("+ItemIndex+") arrival to "+BlockName(me)+" number "+me+".  CurrentTime:"+currentTime+".","",True);
			if(getBlockLabel(myBlockNumber()) != "")
				fileWrite(sysGlobal2,"     Block Label: "+getBlockLabel(myBlockNumber()),"",True);
			if(WhichInput >= 0)
				fileWrite(sysGlobal2,"     At input: "+whichInput,"",True);
			#ifdef TraceDialogs
				TCE_TraceDialogs(me);
			#endif
				
			}
	}
	
	
	Procedure TCE_TraceItemOut(integer ItemIndex, integer WhichOutput)				// traces items as they leave the block
	{
	integer me;
	//integer numDialogs;
	//integer i;
	
		// sysGlobal2 is the file reference number for the Debug Trace
		if( sysGlobal2 != 0.0 )
			{
			me = MyBlockNumber();
	// template for trace:       |BLOCK NAME *****************|block number |BLOCK NUMBER*******|.| Current Time:|CURRENTTIME  |.|
			fileWrite(sysGlobal2,"--> Item ("+ItemIndex+") departure from "+BlockName(me)+" number "+me+".  CurrentTime:"+currentTime+".","",True);
			if(getBlockLabel(myBlockNumber()) != "")
				fileWrite(sysGlobal2,"     Block Label: "+getBlockLabel(myBlockNumber()),"",True);
			if(WhichOutput >= 0)
				fileWrite(sysGlobal2,"     At input: "+WhichOutput,"",True);
			
			#ifdef TraceDialogs
				TCE_TraceDialogs(me);
			#endif
				
			}
	}
	
	
	Procedure TCE_TracePassitem(integer ItemIndex, integer WhichOutput)
	{
	integer me;
		// sysGlobal2 is the file reference number for the Debug Trace
		if( sysGlobal2 != 0.0 )
			{
			me = MyBlockNumber();
	// template for trace:       |BLOCK NAME *****************|block number |BLOCK NUMBER*******|.| Current Time:|CURRENTTIME  |.|
			fileWrite(sysGlobal2,">>> Item ("+ItemIndex+") passing through "+BlockName(me)+" number "+me+".  CurrentTime:"+currentTime+".","",True);
			if(getBlockLabel(myBlockNumber()) != "")
				fileWrite(sysGlobal2,"     Block Label: "+getBlockLabel(myBlockNumber()),"",True);
			if(WhichOutput >= 0)
				fileWrite(sysGlobal2,"     At input: "+WhichOutput,"",True);
			
			#ifdef TraceDialogs
				TCE_TraceDialogs(me);
			#endif
			}
	}
#endif

#IfDef RATETRACE

	*******************************************
	**Called in 
	**An event happen in a rate block which is not only a LP calculation
	Procedure TCE_TraceScheduledEvent(string lsDescription)
	{
		if (sysGlobal2==0.)	// leave the function if tracing is turned off
			return;
		
		fileWrite(sysGlobal2,"*** Scheduled event at "+BlockName(MyNumber)+" number "+MyNumber+".  CurrentTime:"+currentTime+".","",True);
		if (lsDescription!="")
			FileWrite(sysGlobal2, "   "+lsDescription, FALSE, TRUE);
	}//Procedure TCE_TraceScheduledEvent(string lsDescription)

	*******************************************
	**Called in 
	**An event happen in a rate block which generate the calculation of a new LP
	Procedure TCE_TraceStartingLPCalculation(string lsDescription)
	{
		if (sysGlobal2==0.)	// leave the function if tracing is turned off
			return;
		
		fileWrite(sysGlobal2,"*** LP Calculation initiate by "+BlockName(MyNumber)+" number "+MyNumber+".  CurrentTime:"+currentTime+".","",True);
		if (lsDescription!="")
			FileWrite(sysGlobal2, "   "+lsDescription, FALSE, TRUE);
	}//Procedure TCE_TraceStartingLPCalculation(string lsDescription)
	

	*******************************************
	**Called in 
	**An event happen in a rate block which generate the calculation of a new LP
	Procedure TCE_TraceLPConstraint(string lsDescription)
	{
		if (sysGlobal2==0.)	// leave the function if tracing is turned off
			return;
		
		fileWrite(sysGlobal2,"*** Constraint posted for the LP by "+BlockName(MyNumber)+" number "+MyNumber+".  CurrentTime:"+currentTime+".","",True);
		if (lsDescription!="")
			FileWrite(sysGlobal2, "   "+lsDescription, FALSE, TRUE);
	}//END Procedure TCE_TraceLPConstraint(string lsDescription)

	*******************************************
	**Called in 
	**An event happen in a rate block which generate the calculation of a new LP
	Procedure TCE_TraceNewEffectiveRate()
	{
		long liConn;
		string lsInFlowRates, lsOutFlowRates, lsFlowRates;

		if (sysGlobal2==0.)	// leave the function if tracing is turned off
			return;
		
		lsInFlowRates	= "";
		lsOutFlowRates	= "";
		lsFlowRates		= "";
		#IfDef IContinueSection
			if (diFlowIC[0][ccCONNECTED])
				lsFlowRates	= "Effective rate = "+GAGetReal(siInfoR_GA, diFlowIC[0][ccSECTION], ccRATE);
			else if (diFlowOC[0][ccCONNECTED])
				lsFlowRates	= "Effective rate = "+GAGetReal(siInfoR_GA, diFlowOC[0][ccSECTION], ccRATE);
		#Else
			for (liConn=0; liConn<siNumIC; liConn++)
			{
				if (!diFlowIC[liConn][ccCONNECTED])
					continue;
				if (siNumIC_Conn<=1)
					lsInFlowRates	= "Inflow effective rate = "+GAGetReal(siInfoR_GA, diFlowIC[liConn][ccSECTION], ccRATE);
				else if (lsInFlowRates=="")
					lsInFlowRates	= "Inflow effective rates = "+GAGetReal(siInfoR_GA, diFlowIC[liConn][ccSECTION], ccRATE)+" ["+liConn+"]";
				else
					lsInFlowRates	+= "; "+GAGetReal(siInfoR_GA, diFlowIC[liConn][ccSECTION], ccRATE)+" ["+liConn+"]";
			}//END for (liConn=0; liConn<siNumIC; liConn++)

			for (liConn=0; liConn<siNumOC; liConn++)
			{
				if (!diFlowOC[liConn][ccCONNECTED])
					continue;
				if (siNumOC_Conn<=1)
					lsOutFlowRates	= "Outflow effective rate = "+GAGetReal(siInfoR_GA, diFlowOC[liConn][ccSECTION], ccRATE);
				else if (lsOutFlowRates=="")
					lsOutFlowRates	= "Outflow effective rates = "+GAGetReal(siInfoR_GA, diFlowOC[liConn][ccSECTION], ccRATE)+" ["+liConn+"]";
				else
					lsOutFlowRates	+= "; "+GAGetReal(siInfoR_GA, diFlowOC[liConn][ccSECTION], ccRATE)+" ["+liConn+"]";
			}//END for (liConn=0; liConn<siNumOC; liConn++)
		#EndIf	// Not IContinueSection

		if (lsFlowRates!="" || lsInFlowRates!="" || lsOutFlowRates!="")
		{
			fileWrite(sysGlobal2,"*** Reception of new rates "+BlockName(MyNumber)+" number "+MyNumber+".  CurrentTime:"+currentTime+".","",True);
			if (lsFlowRates!="")
				FileWrite(sysGlobal2, "   "+lsFlowRates, FALSE, TRUE);
			if (lsInFlowRates!="")
				FileWrite(sysGlobal2, "   "+lsInFlowRates, FALSE, TRUE);
			if (lsOutFlowRates!="")
				FileWrite(sysGlobal2, "   "+lsOutFlowRates, FALSE, TRUE);
		}//END if (lsFlowRates!="" || lsInFlowRates!="" || lsOutFlowRates!="")
	}//END Procedure TCE_TraceNewEffectiveRate()

#EndIf
