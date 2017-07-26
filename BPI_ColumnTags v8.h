******************************************************************
**	ColumnTags v7.h Include										**
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

constant TAG_NOTHING  is 0;

//string lookup tags
constant TAG_SL is 10;
constant TAG_SL_POP  is 11;
constant TAG_SL_PREPEND is 16;
constant TAG_SL_APPEND is 17;

//dialog item tags
constant TAG_CHECKBOX is 20;
constant TAG_BUTTON is 21;	
constant TAG_RADIO is 22;
constant TAG_INFINITY is 26;

//database tags
constant TAG_DB_FIELD is 30;
constant TAG_DB_ADDRESS_POP is 31;
constant TAG_DB_ADDRESS is 32;

//popup tags
constant TAG_POPUP  is 40; 								
constant TAG_CONDITIONAL_POPUP is 42;
constant TAG_CONDITIONAL_POPUP_ARRAY is 43;

//calendar date format tags
constant TAG_DATE is 50;
constant TAG_DATE_CONVERT is 51;

//block tags
constant TAG_BLOCK_LABEL is 60;
constant TAG_BLOCK_NAME is 61;
constant TAG_BLOCK_LABEL_NAME is 62;

constant TAG_PERCENT is 70;
constant TAG_NUMBER is 71;				//used when have a text table object and a column that holds numberic data-  maintains proper numeric formating

//flag tags
constant TAG_STR_FLAG is 80;
constant TAG_STR_FLAG_NOED is 81;

constant TAG_HIDE is 98;
constant TAG_DISABLE is 99;

//head tags
constant TAG_HEAD_TAG_POPUP  is 100; 	
constant TAG_NO_HEAD_TAG  is 101;


