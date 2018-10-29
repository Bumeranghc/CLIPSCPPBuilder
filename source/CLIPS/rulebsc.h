   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.30  02/04/15            */
   /*                                                     */
   /*         DEFRULE BASIC COMMANDS HEADER FILE          */
   /*******************************************************/

/*************************************************************/
/* Purpose: Implements core commands for the defrule         */
/*   construct such as clear, reset, save, undefrule,        */
/*   ppdefrule, list-defrules, and                           */
/*   get-defrule-list.                                       */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.23: Corrected compilation errors for files         */
/*            generated by constructs-to-c. DR0861           */
/*                                                           */
/*            Changed name of variable log to logName        */
/*            because of Unix compiler warnings of shadowed  */
/*            definitions.                                   */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW,          */
/*            MAC_MCW, and IBM_TBC).                         */
/*                                                           */
/*            Support for join network changes.              */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*            Added code to prevent a clear command from     */
/*            being executed during fact assertions via      */
/*            JoinOperationInProgress mechanism.             */
/*                                                           */
/*************************************************************/

#ifndef _H_rulebsc
#define _H_rulebsc

#ifndef _H_evaluatn
#include "evaluatn.h"
#endif

#ifdef LOCALE
#undef LOCALE
#endif

#ifdef _RULEBSC_SOURCE_
#define LOCALE
#else
#define LOCALE extern
#endif

   LOCALE void                           DefruleBasicCommands(void *);
   LOCALE void                           UndefruleCommand(void *);
   LOCALE intBool                        EnvUndefrule(void *,void *);
   LOCALE void                           GetDefruleListFunction(void *,DATA_OBJECT_PTR);
   LOCALE void                           EnvGetDefruleList(void *,DATA_OBJECT_PTR,void *);
   LOCALE void                          *DefruleModuleFunction(void *);
#if DEBUGGING_FUNCTIONS
   LOCALE void                           PPDefruleCommand(void *);
   LOCALE int                            PPDefrule(void *,const char *,const char *);
   LOCALE void                           ListDefrulesCommand(void *);
   LOCALE void                           EnvListDefrules(void *,const char *,void *);
   LOCALE unsigned                       EnvGetDefruleWatchFirings(void *,void *);
   LOCALE unsigned                       EnvGetDefruleWatchActivations(void *,void *);
   LOCALE void                           EnvSetDefruleWatchFirings(void *,unsigned,void *);
   LOCALE void                           EnvSetDefruleWatchActivations(void *,unsigned,void *);
   LOCALE unsigned                       DefruleWatchAccess(void *,int,unsigned,struct expr *);
   LOCALE unsigned                       DefruleWatchPrint(void *,const char *,int,struct expr *);
#endif

#if ALLOW_ENVIRONMENT_GLOBALS

   LOCALE void                           GetDefruleList(DATA_OBJECT_PTR,void *);
#if DEBUGGING_FUNCTIONS
   LOCALE unsigned                       GetDefruleWatchActivations(void *);
   LOCALE unsigned                       GetDefruleWatchFirings(void *);
   LOCALE void                           ListDefrules(const char *,void *);
   LOCALE void                           SetDefruleWatchActivations(unsigned,void *);
   LOCALE void                           SetDefruleWatchFirings(unsigned,void *);
#endif
   LOCALE intBool                        Undefrule(void *);

#endif /* ALLOW_ENVIRONMENT_GLOBALS */

#endif /* _H_rulebsc */

