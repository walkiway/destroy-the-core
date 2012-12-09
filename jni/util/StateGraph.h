  /*
 * StateGraph.h
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */

#ifndef STATEGRAPH_H_
#define STATEGRAPH_H_

#include "State.h"

template<class T, class E>
class StateGraph
{

public:

  StateGraph(T* owner) :
    Owner(owner), Current(0), Previous(0)
  {
  }

  virtual ~StateGraph()
  {
  }

  void SetCurrentState(State<T, E>* state)
  {
    Current = state;
  }

  State<T, E>* GetCurrentState()
  {
    return Current;
  }

  void SetWorldState(State<T, E>* state)
  {
    World = state;
  }

  State<T, E>* GetWorldState()
  {
    return World;
  }

  void SetPreviousState(State<T, E>* state)
  {
    Previous = state;
  }

  State<T, E>* SetPreviousState()
  {
    return Previous;
  }

  void OnUpdate()
  {
    if (NULL != Current)
    {
      Current->OnUpdate(Owner);
    }

    if (NULL != World)
    {
      World->OnUpdate(Owner);
    }
  }

  bool HandleEvent(E event)
  {
    //Do not send events to the world state, the current state will handle the events
    //and modify the world accordingly (which in some cases is not at all).
    if (NULL != Current)
    {
      return Current->OnEvent(Owner, event);
    }

    return false;
  }

protected:
  void OnReload()
  {
    if (NULL != Current)
    {
      Current->OnReload(Owner);
    }

    if (NULL != World)
    {
      World->OnReload(Owner);
    }
  }

private:
  T* Owner; //Owner of this state machine instance
  State<T, E>* Current; // Current state of the state machine
  State<T, E>* Previous; // Previous state of the state machine
  State<T, E>* World; //The state of the existing world.
};
#endif /* STATEGRAPH_H_ */
