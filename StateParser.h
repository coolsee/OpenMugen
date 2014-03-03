#ifndef ___STATEPARSER__H
#define ___STATEPARSER__H

class CStateParser
{
      CAllocater         *m_pAlloc;
      
      
      void ParseStateDef(CTokenizer &tok,CStateManager &StateManager);
      void PareseState(CTokenizer &tok,CStateManager &StateManager);
      void ParseTrigger(CTokenizer &tok,CStateManager &StateManager);
//Expression parser
      void EvaluateExpression(CTokenizer &tok,CStateManager &StateManager);
      void Term(CTokenizer &tok,CStateManager &StateManager);
      void Primary(CTokenizer &tok,CStateManager &StateManager);
//helper functions      
      int  GetControllerType(const char * strType,CTokenizer &tok);
      int  GetTriggerType(const char * strTrigger,CTokenizer &tok);
      void Error(const char * strErrorMsg,CTokenizer &tok);
      int nController;
//controller parser
      void ParserController(CTokenizer &tok,CStateManager &StateManager,u16 nControllerType);
      void ParseChangeState(CTokenizer &tok,CStateManager &StateManager);
public:
       CStateParser();
       ~CStateParser();
       
       void ParseStateFile(const char * strFileName,CStateManager &StateManager,CAllocater *a);
      
};


#endif
