/*
 * State.h
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */

#ifndef STATE_H_
#define STATE_H_

template<class T, class E>
class State
{
public:
  virtual ~State()
  {
  }

  /// Called by the state machine when entity is entering this state.
  virtual void OnEnter(T* entity)
  {
  }

  ///Called by the state machine when entity is leaving this state.
  virtual void OnLeave(T* entity)
  {
  }

  ///Called by the state machine when the entity is being updated
  virtual void OnUpdate(T* entity)
  {
  }

  ///Called by the state machine when the entity is being reloaded
  virtual void OnReload(T* entity)
  {

  }

  /// Called by the state machine when a message is to be processed for
  /// an entity.
  virtual bool OnEvent(T* entity, E event)
  {
    return false;
  }
};
#endif /* STATE_H_ */
