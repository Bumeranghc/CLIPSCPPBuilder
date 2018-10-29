   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.30  08/22/14            */
   /*                                                     */
   /*                 AGENDA HEADER FILE                  */
   /*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*   Provides functionality for examining, manipulating,     */
/*   adding, and removing activations from the agenda.       */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*      6.23: Corrected compilation errors for files         */
/*            generated by constructs-to-c. DR0861           */
/*                                                           */
/*      6.24: Removed CONFLICT_RESOLUTION_STRATEGIES and     */
/*            DYNAMIC_SALIENCE compilation flags.            */
/*                                                           */
/*            Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*            Added EnvGetActivationBasisPPForm function.    */
/*                                                           */
/*      6.30: Added salience groups to improve performance   */
/*            with large numbers of activations of different */
/*            saliences.                                     */
/*                                                           */
/*            Borland C (IBM_TBC) and Metrowerks CodeWarrior */
/*            (MAC_MCW, IBM_MCW) are no longer supported.    */
/*                                                           */
/*            Support for long long integers.                */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*************************************************************/

#ifndef _H_agenda

#define _H_agenda

#ifndef _H_ruledef
#include "ruledef.h"
#endif
#ifndef _H_symbol
#include "symbol.h"
#endif
#ifndef _H_match
#include "match.h"
#endif

#define WHEN_DEFINED 0
#define WHEN_ACTIVATED 1
#define EVERY_CYCLE 2

#define MAX_DEFRULE_SALIENCE  10000
#define MIN_DEFRULE_SALIENCE -10000
  
/*******************/
/* DATA STRUCTURES */
/*******************/

struct activation
  {
   struct defrule *theRule;
   struct partialMatch *basis;
   int salience;
   unsigned long long timetag;
   int randomID;
#if CERTAINTY_FACTORS  
   double CF;
   double StdConcludingCF;
#if FUZZY_DEFTEMPLATES  
   double FuzzyCrispConcludingCF;
#endif
#endif
   struct activation *prev;
   struct activation *next;
  };

struct salienceGroup
  {
   int salience;
   struct activation *first;
   struct activation *last;
   struct salienceGroup *next;
   struct salienceGroup *prev;
  };

typedef struct activation ACTIVATION;

#define AGENDA_DATA 17

struct agendaData
  { 
#if DEBUGGING_FUNCTIONS
   unsigned WatchActivations;
#endif
   unsigned long NumberOfActivations;
   unsigned long long CurrentTimetag;
   int AgendaChanged;
   intBool SalienceEvaluation;
   int Strategy;
#if CERTAINTY_FACTORS 
   intBool CFEvaluation;
#endif
  };

#define AgendaData(theEnv) ((struct agendaData *) GetEnvironmentData(theEnv,AGENDA_DATA))

#ifdef LOCALE
#undef LOCALE
#endif

#ifdef _AGENDA_SOURCE_
#define LOCALE
#else
#define LOCALE extern
#endif

/****************************************/
/* GLOBAL EXTERNAL FUNCTION DEFINITIONS */
/****************************************/

   LOCALE void                    AddActivation(void *,void *,void *);
   LOCALE void                    ClearRuleFromAgenda(void *,void *);
   LOCALE void                   *EnvGetNextActivation(void *,void *);
   LOCALE struct partialMatch    *EnvGetActivationBasis(void *,void *);
   LOCALE const char             *EnvGetActivationName(void *,void *);
   LOCALE struct defrule         *EnvGetActivationRule(void *,void *);
   LOCALE int                     EnvGetActivationSalience(void *,void *);
   LOCALE int                     EnvSetActivationSalience(void *,void *,int);
   LOCALE void                    EnvGetActivationPPForm(void *,char *,size_t,void *);
   LOCALE void                    EnvGetActivationBasisPPForm(void *,char *,size_t,void *);
   LOCALE intBool                 MoveActivationToTop(void *,void *);
   LOCALE intBool                 EnvDeleteActivation(void *,void *);
   LOCALE intBool                 DetachActivation(void *,void *);
   LOCALE void                    EnvAgenda(void *,const char *,void *);
   LOCALE void                    RemoveActivation(void *,void *,int,int);
   LOCALE void                    RemoveAllActivations(void *);
   LOCALE int                     EnvGetAgendaChanged(void *);
   LOCALE void                    EnvSetAgendaChanged(void *,int);
   LOCALE unsigned long           GetNumberOfActivations(void *);
   LOCALE intBool                 EnvGetSalienceEvaluation(void *);
   LOCALE intBool                 EnvSetSalienceEvaluation(void *,intBool);
   LOCALE void                    EnvRefreshAgenda(void *,void *);
   LOCALE void                    EnvReorderAgenda(void *,void *);
   LOCALE void                    InitializeAgenda(void *);
   LOCALE void                   *SetSalienceEvaluationCommand(void *);
   LOCALE void                   *GetSalienceEvaluationCommand(void *);
   LOCALE void                    RefreshAgendaCommand(void *);
   LOCALE void                    RefreshCommand(void *);
   LOCALE intBool                 EnvRefresh(void *,void *);
#if DEBUGGING_FUNCTIONS
   LOCALE void                    AgendaCommand(void *);
#endif
#if CERTAINTY_FACTORS   
   LOCALE intBool                 GetCFEvaluation(void *);
   LOCALE intBool                 SetCFEvaluation(void *,intBool);
   LOCALE void                   *SetCFEvaluationCommand(void *);
   LOCALE void                   *GetCFEvaluationCommand(void *);
#endif

#if ALLOW_ENVIRONMENT_GLOBALS

   LOCALE void                    Agenda(const char *,void *);
   LOCALE intBool                 DeleteActivation(void *);
   LOCALE struct partialMatch    *GetActivationBasis(void *);
   LOCALE const char             *GetActivationName(void *);
   LOCALE void                    GetActivationPPForm(char *,unsigned,void *);
   LOCALE struct defrule         *GetActivationRule(void *);
   LOCALE int                     GetActivationSalience(void *);
   LOCALE int                     GetAgendaChanged(void);
   LOCALE void                   *GetNextActivation(void *);
   LOCALE intBool                 GetSalienceEvaluation(void);
   LOCALE intBool                 Refresh(void *);
   LOCALE void                    RefreshAgenda(void *);
   LOCALE void                    ReorderAgenda(void *);
   LOCALE int                     SetActivationSalience(void *,int);
   LOCALE void                    SetAgendaChanged(int);
   LOCALE intBool                 SetSalienceEvaluation(int);

#endif

#endif






