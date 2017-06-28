// Copyright 2017 Stefano Pellegrini

#include "agent.h"

#include "utils.h"

Agent::Agent(const Battery* battery, const int* time) :
  battery_(battery), time_(time), return_to_charging_station_(false) {
  current_direction_ = ChooseRandomDirection();
}

Direction Agent::NextDirection(const Perception& p) {
  // Occasionally change directions without hitting an obstacle in order to
  // avoid just following the walls
  if (Random() < 0.2) {
    return ChooseRandomDirection();
  } else if (!p.HasObstacle(current_direction_)) {
    // If we don't hit an obstacle, keep going in the current direction
    return current_direction_;
  } else {
    // If we do hit an object, change to an orthogonal direction
    return ChangeDirection();
  }
}

Direction Agent::ChooseRandomDirection() {
  const float random = Random();
  // Choose a random initial direction
  if (random < 0.25) {
    current_direction_ = Direction::LEFT;
  } else if (random < 0.5) {
    current_direction_ = Direction::DOWN;
  } else if (random < 0.75) {
    current_direction_ = Direction::UP;
  } else {
    current_direction_ = Direction::RIGHT;
  }
}

Direction Agent::ChangeDirection() {
  const float random = Random();
  if(current_direction_ == Direction::LEFT ||
     current_direction_ == Direction::RIGHT) {
    // If we're moving L to R, turn to U to D
    if (random < 0.5) {
      current_direction_ = Direction::UP;
    } else {
      current_direction_ = Direction::DOWN;
    }
  } else {
    // If we're moving U to D, turn to L to R
    if (random < 0.5) {
      current_direction_ = Direction::LEFT;
    } else {
      current_direction_ = Direction::RIGHT;
    }
  }
  return current_direction_;
}

bool Agent::IsAlive() const {
  return battery_->Level() > 0;
}
