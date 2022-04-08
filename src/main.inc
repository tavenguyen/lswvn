//       		  			
//    |			  ____		 _.                 _.
//    |			 (		 	 |.				   .|
//	  |		      `---.	  	  `|.            .'|   
//    |               |			 '_.  /\   ._'
//    |_____	  ___.'			   '_'  '_'
//
//	----- Copyright (C) 2022 Los Santos World Remake v2.0 - tavenguyxn (Github: tavenguyen)
//		
//		
//			Insprition:
//				- lswrp (Arashi)
//				- suckless-rp (Duy Dang)
//				- ScavengeSurvive (Southclaws)
//	
//			Founder:		
//				- Bambo
//				- BmTan
// 				- Arashi (Old) 
//
//
//			Scripter:
//				- tavenguyxn (Vietnam, Can Tho City)
//				- Arashi (Vietnam, Ho Chi Minh City)
//				- Huynh (Vietnam, Ho Chi Minh City)
//
//			Supporter:
//				- Duy Dang
//			
//			Mapping:
//				- Toan Dank (Vietnam)
//
//
// ------- This project was remaked by tavenguyen on 08/04/2022 | 5:00 PM

#include <a_samp>

/*==============================================================================
	Library Predefinitions
==============================================================================*/

#define PP_SYNTAX_AWAIT
#define PP_SYNTAX_GENERIC
#define YSI_NO_KEYWORD_List
#define YSI_YES_HEAP_MALLOC
#define YSI_NO_MODE_CACHE
#define CGEN_MEMORY 30000

#define task_unblock(%0) \
	task_detach(); \
	task_yield(%0)

main() {} 